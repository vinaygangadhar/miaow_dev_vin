/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <assert.h>

#include <lib/esim/esim.h>
#include <lib/esim/trace.h>
#include <lib/util/list.h>
#include <arch/fermi/emu/warp.h>

#include "sm.h"
#include "gpu.h"
#include "simd-unit.h"
#include "uop.h"


void frm_simd_complete(struct frm_simd_t *simd)
{
	struct frm_uop_t *uop;
	int list_entries;
	int list_index = 0;
	int i;

	list_entries = list_count(simd->exec_buffer);

	assert(list_entries <= frm_gpu_simd_exec_buffer_size);

	for (i = 0; i < list_entries; i++)
	{
		uop = list_get(simd->exec_buffer, list_index);
		assert(uop);

		if (frm_gpu->cycle < uop->execute_ready)
		{
			list_index++;
			continue;
		}

		/* Access complete, remove the uop from the queue */
		list_remove(simd->exec_buffer, uop);

		frm_trace("si.end_inst id=%lld cu=%d\n", uop->id_in_sm,
			uop->sm->id);

		/* Free uop */
		frm_uop_free(uop);

		/* Statistics */
		simd->inst_count++;
		frm_gpu->last_complete_cycle = esim_cycle;
	}
}

void frm_simd_execute(struct frm_simd_t *simd)
{
	struct frm_uop_t *uop;
	int list_entries;
	int list_index = 0;
	int instructions_processed = 0;
	int i;

	list_entries = list_count(simd->decode_buffer);

	/* Sanity check the decode buffer */
	assert(list_entries <= frm_gpu_simd_decode_buffer_size);

	for (i = 0; i < list_entries; i++)
	{
		uop = list_get(simd->decode_buffer, list_index);
		assert(uop);

		instructions_processed++;

		/* Uop is not ready yet */
		if (frm_gpu->cycle < uop->decode_ready)
		{
			list_index++;
			continue;
		}

		/* Stall if the width has been reached */
		if (instructions_processed > frm_gpu_simd_width)
		{
			frm_trace("si.inst id=%lld cu=%d wf=%d uop_id=%lld "
				"stg=\"s\"\n", uop->id_in_sm, 
				simd->sm->id, uop->warp->id, 
				uop->id_in_warp);
			list_index++;
			continue;
		}

		/* Sanity check exec buffer */
		assert(list_count(simd->exec_buffer) <= 
			frm_gpu_simd_exec_buffer_size);

		/* Stall if SIMD unit is full */
		if (list_count(simd->exec_buffer) == 
			frm_gpu_simd_exec_buffer_size)
		{
			frm_trace("si.inst id=%lld cu=%d wf=%d uop_id=%lld "
				"stg=\"s\"\n", uop->id_in_sm, 
				simd->sm->id, uop->warp->id, 
				uop->id_in_warp);
			list_index++;
			continue;
		}

		/* Includes time for pipelined read-exec-write of 
		 * all subwarps */
		uop->execute_ready = frm_gpu->cycle + frm_gpu_simd_exec_latency;

		/* Transfer the uop to the outstanding execution buffer */
		list_remove(simd->decode_buffer, uop);
		list_enqueue(simd->exec_buffer, uop);

		frm_trace("si.inst id=%lld cu=%d wf=%d uop_id=%lld "
			"stg=\"simd-e\"\n", uop->id_in_sm, 
			simd->sm->id, uop->warp->id, 
			uop->id_in_warp);
	}
}

void frm_simd_decode(struct frm_simd_t *simd)
{
	struct frm_uop_t *uop;
	int instructions_processed = 0;
	int list_entries;
	int list_index = 0;
	int i;

	list_entries = list_count(simd->issue_buffer);

	/* Sanity check the issue buffer */
	assert(list_entries <= frm_gpu_simd_issue_buffer_size);

	for (i = 0; i < list_entries; i++)
	{
		uop = list_get(simd->issue_buffer, list_index);
		assert(uop);

		instructions_processed++;

		/* Uop not ready yet */
		if (frm_gpu->cycle < uop->issue_ready)
		{
			list_index++;
			continue;
		}

		/* Stall if the issue width has been reached. */
		if (instructions_processed > frm_gpu_simd_width)
		{
			frm_trace("si.inst id=%lld cu=%d wf=%d uop_id=%lld "
				"stg=\"s\"\n", uop->id_in_sm, 
				simd->sm->id, uop->warp->id, 
				uop->id_in_warp);
			list_index++;
			continue;
		}

		/* Sanity check the decode buffer */
		assert(list_count(simd->decode_buffer) <= 
				frm_gpu_simd_decode_buffer_size);

		/* Stall if the decode buffer is full. */
		if (list_count(simd->decode_buffer) == 
			frm_gpu_simd_decode_buffer_size)
		{
			frm_trace("si.inst id=%lld cu=%d wf=%d uop_id=%lld "
				"stg=\"s\"\n", uop->id_in_sm, 
				simd->sm->id, uop->warp->id, 
				uop->id_in_warp);
			list_index++;
			continue;
		}

		uop->decode_ready = frm_gpu->cycle + frm_gpu_simd_decode_latency;
		list_remove(simd->issue_buffer, uop);
		list_enqueue(simd->decode_buffer, uop);

		frm_trace("si.inst id=%lld cu=%d wf=%d uop_id=%lld "
			"stg=\"simd-d\"\n", uop->id_in_sm, 
			simd->sm->id, uop->warp->id, 
			uop->id_in_warp);
	}
}

void frm_simd_run(struct frm_simd_t *simd)
{
	/* SIMD stages */
	frm_simd_complete(simd);
	frm_simd_execute(simd);
	frm_simd_decode(simd);
}
