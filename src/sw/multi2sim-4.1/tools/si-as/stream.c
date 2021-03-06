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

#include <lib/mhandle/mhandle.h>
#include <lib/util/debug.h>
#include <lib/util/elf-format.h>

#include "dis-inst.h"
#include "main.h"
#include "task.h"
#include "stream.h"


/*
 * Stream Object
 */

struct si_stream_t *si_stream_create(int size)
{
	struct si_stream_t *stream;
	
	stream = xcalloc(1, sizeof(struct si_stream_t));
	stream->buf = xcalloc(1, size);
	stream->size = size;
	
	return stream;
}


void si_stream_free(struct si_stream_t *stream)
{
	free(stream->buf);
	free(stream);
}


void si_stream_add_inst(struct si_stream_t *stream,
		struct si_dis_inst_t *inst)
{
	/* Generate code for instruction */
	si_dis_inst_gen(inst);

	/* Size of stream exceeded */
	if (stream->offset + inst->size > stream->size)
		yyerror("output stream size exceeded");

	/* Add instruction */
	memcpy(stream->buf + stream->offset, inst->inst_bytes.bytes, inst->size);
	stream->offset += inst->size;
}


void si_stream_dump(struct si_stream_t *stream, FILE *f)
{
	struct elf_buffer_t buffer;

	buffer.ptr = stream->buf;
	buffer.size = stream->offset;
	si_disasm_buffer(&buffer, f);
}



/*
 * Global
 */

struct si_stream_t *si_out_stream;

void si_stream_init(void)
{
	si_out_stream = si_stream_create(1 << 20);  /* 2KB */
}


void si_stream_done(void)
{
	si_stream_dump(si_out_stream, stdout);
	si_stream_free(si_out_stream);
}

