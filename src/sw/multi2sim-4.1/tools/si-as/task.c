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
#include <string.h>

#include <arch/southern-islands/asm/asm.h>
#include <lib/mhandle/mhandle.h>
#include <lib/util/debug.h>
#include <lib/util/list.h>
#include <lib/util/misc.h>

#include "main.h"
#include "stream.h"
#include "symbol.h"
#include "task.h"


/*
 * Task Object
 */

struct si_task_t *si_task_create(int offset, struct si_symbol_t *symbol)
{
	struct si_task_t *task;
	
	/* Allocate */
	task = xcalloc(1, sizeof(struct si_task_t));
	
	/* Initialize the task's offset and ID */
	task->offset = offset;
	task->symbol = symbol;
	
	/* Return */
	return task;

}

void si_task_free(struct si_task_t *task)
{
	free(task);
}


void si_task_dump(struct si_task_t *task, FILE *f)
{
	fprintf(f, "offset=%d, symbol={", task->offset);
	si_symbol_dump(task->symbol, f);
	fprintf(f, "}");
}


void si_task_process(struct si_task_t *task)
{
	struct si_symbol_t *label;
	union si_inst_microcode_t *inst;

	/* Check whether symbol is resolved */
	label = task->symbol;
	if (!label->defined)
		yyerror_fmt("undefined label: %s", label->name);

	/* Resolve label */
	assert(IN_RANGE(task->offset, 0, si_out_stream->offset - 4));
	inst = si_out_stream->buf + task->offset;
	inst->sopp.simm16 = (label->value - task->offset) / 4 - 1;
}




/*
 * Global Functions
 */

struct list_t *si_task_list;

		
void si_task_list_init(void)
{							  
	si_task_list = list_create();
}


void si_task_list_done(void)
{
	int index;
	
	LIST_FOR_EACH(si_task_list, index)
		si_task_free(list_get(si_task_list, index));
	list_free(si_task_list);
}


void si_task_list_dump(FILE *f)
{
	int index;
	
	fprintf(f, "Task list:\n");
	LIST_FOR_EACH(si_task_list, index)
	{
		fprintf(f, "\ttask %d: ", index);
		si_task_dump(list_get(si_task_list, index), f);
		fprintf(f, "\n");
	}
}


void si_task_list_process(void)
{
	int index;

	LIST_FOR_EACH(si_task_list, index)
		si_task_process(list_get(si_task_list, index));
}
