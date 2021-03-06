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

#include <stdarg.h>
#include <stdio.h>

#include <arch/southern-islands/asm/asm.h>
#include <lib/mhandle/mhandle.h>
#include <lib/util/debug.h>

#include "dis-inst.h"
#include "dis-inst-info.h"
#include "main.h"
#include "parser.h"
#include "stream.h"
#include "symbol.h"
#include "task.h"


/* File name with assembly code */
char *input_file_name;


void yyerror(const char *s)
{
	fprintf(stderr, "%s:%d: error: %s\n",
			input_file_name, yylineno, s);
	exit(1);
}


void yyerror_fmt(char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	fprintf(stderr, "%s:%d: error: ", input_file_name, yylineno);
	vfprintf(stderr, fmt, va);
	fprintf(stderr, "\n");
	fflush(NULL);
	exit(1);
}


int main(int argc, char **argv) 
{
	/* Check syntax */
	if (argc != 2)
		fatal("syntax: %s <file>", *argv);

	/* Open input file */
	input_file_name = argv[1];
	yyin = fopen(input_file_name, "r");
	if (!yyin)
		fatal("%s: cannot open input file", input_file_name);
	
	/* Initialize */
	si_disasm_init();
	si_dis_inst_info_init();
	si_task_list_init();
	si_symbol_table_init();
	si_stream_init();

	/* Parse input */
	yyparse();

	/* Process tasks */
	si_task_list_process();

	/* Finalize */
	si_task_list_done();
	si_symbol_table_done();
	si_stream_done();
	si_dis_inst_info_done();
	si_disasm_done();

	mhandle_done();
	
	return 0;
}

