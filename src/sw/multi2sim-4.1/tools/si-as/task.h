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

#ifndef TOOLS_SI_AS_TASK_H
#define TOOLS_SI_AS_TASK_H

#include <stdio.h>


/*
 * Task Object
 */

/* Forward declaration */
struct si_symbol_t;

struct si_task_t
{
	int offset;
	struct si_symbol_t *symbol;
};

struct si_task_t *si_task_create(int offset, struct si_symbol_t *symbol);
void si_task_free(struct si_task_t *task);

void si_task_dump(struct si_task_t *task, FILE *f);
void si_task_process(struct si_task_t *task);



/*
 * Global
 */

extern struct list_t *si_task_list;

void si_task_list_init(void);
void si_task_list_done(void);

void si_task_list_process(void);

#endif
