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

#include <arch/southern-islands/asm/bin-file.h>
#include <arch/southern-islands/emu/isa.h>
#include <arch/southern-islands/emu/ndrange.h>
#include <arch/southern-islands/emu/wavefront.h>
#include <arch/southern-islands/emu/work-group.h>
#include <arch/southern-islands/emu/work-item.h>
#include <lib/mhandle/mhandle.h>
#include <lib/util/debug.h>
#include <lib/util/list.h>
#include <lib/util/string.h>
#include <mem-system/memory.h>

#include "opencl.h"
#include "si-kernel.h"
#include "si-program.h"

/*MIAOW start */
#define MIAOW_DEBUG
#include <math.h>
/*MIAOW stop */

static char *opencl_err_si_kernel_symbol =
	"\tThe ELF file analyzer is trying to find a name in the ELF symbol table.\n"
	"\tIf it is not found, it probably means that your application is requesting\n"
	"\texecution of a kernel function that is not present in the encoded binary.\n"
	"\tPlease, check the parameters passed to the 'clCreateKernel' function in\n"
	"\tyour application.\n"
	"\tThis could be also a symptom of compiling an OpenCL kernel source on a\n"
	"\tmachine with an installation of the AMD SDK (using 'm2s-clcc') but\n"
	"\twith an incorrect or missing installation of the GPU driver. In this case,\n"
	"\tthe tool will still compile the kernel into LLVM, but the ISA section will\n"
	"\tbe missing in the kernel binary.\n";

static char *opencl_err_si_kernel_metadata =
	"\tThe kernel binary loaded by your application is a valid ELF file. In this\n"
	"\tfile, a '.rodata' section contains specific information about the OpenCL\n"
	"\tkernel. However, this information is only partially supported by Multi2Sim.\n"
	"\tTo request support for this error, please email 'development@multi2sim.org'.\n";

static void opencl_si_create_buffer_desc(unsigned int base_addr,
	unsigned int size, int num_elems, 
	enum opencl_si_arg_data_type_t data_type,
	struct si_buffer_desc_t *buffer_desc);


/*
 * Kernel List
 */


struct list_t *opencl_si_kernel_list;

void opencl_si_kernel_list_init(void)
{
	/* Already initialized */
	if (opencl_si_kernel_list)
		return;

	/* Initialize and add one empty element */
	opencl_si_kernel_list = list_create();
	list_add(opencl_si_kernel_list, NULL);
}


void opencl_si_kernel_list_done(void)
{
	struct opencl_si_kernel_t *kernel;
	int index;

	/* Not initialized */
	if (!opencl_si_kernel_list)
		return;

	/* Free list of Southern Islands kernels */
	LIST_FOR_EACH(opencl_si_kernel_list, index)
	{
		kernel = list_get(opencl_si_kernel_list, index);
		if (kernel)
			opencl_si_kernel_free(kernel);
	}
	list_free(opencl_si_kernel_list);
}




/*
 * Argument
 */

struct opencl_si_arg_t *opencl_si_arg_create(enum opencl_si_arg_type_t type,
		char *name)
{
	struct opencl_si_arg_t *arg;

	/* Initialize */
	arg = xcalloc(1, sizeof(struct opencl_si_arg_t));
	arg->type = type;
	arg->name = xstrdup(name);

	/* Return */
	return arg;
}


void opencl_si_arg_free(struct opencl_si_arg_t *arg)
{
	/* Specific fields per type */
	switch (arg->type)
	{
	case opencl_si_arg_value:

		if (arg->value.value_ptr)
			free(arg->value.value_ptr);
		break;

	default:
		break;
	}

	/* Rest */
	free(arg->name);
	free(arg);
}


/* Infer argument size from its data type */
int opencl_si_arg_get_data_size(enum opencl_si_arg_data_type_t data_type)
{
	switch (data_type)
	{

	case opencl_si_arg_i8:
	case opencl_si_arg_u8:
	case opencl_si_arg_struct:
	case opencl_si_arg_union:
	case opencl_si_arg_event:
	case opencl_si_arg_opaque:

		return 1;

	case opencl_si_arg_i16:
	case opencl_si_arg_u16:

		return 2;

	case opencl_si_arg_i32:
	case opencl_si_arg_u32:
	case opencl_si_arg_float:

		return 4;

	case opencl_si_arg_i64:
	case opencl_si_arg_u64:
	case opencl_si_arg_double:

		return 8;

	default:

		panic("%s: invalid data type (%d)",
				__FUNCTION__, data_type);
		return 0;
	}
}




/*
 * Kernel
 */

static void opencl_si_kernel_expect(struct opencl_si_kernel_t *kernel,
		struct list_t *token_list, char *head_token)
{
	char *token;

	token = str_token_list_first(token_list);
	if (strcmp(token, head_token))
		fatal("%s: token '%s' expected, '%s' found.\n%s",
				__FUNCTION__, head_token, token,
				opencl_err_si_kernel_metadata);
}


static void opencl_si_kernel_expect_int(struct opencl_si_kernel_t *kernel,
		struct list_t *token_list)
{
	char *token;
	int err;

	token = str_token_list_first(token_list);
	str_to_int(token, &err);
	if (err)
		fatal("%s: integer number expected, '%s' found.\n%s",
				__FUNCTION__, token,
				opencl_err_si_kernel_metadata);
}


static void opencl_si_kernel_expect_count(struct opencl_si_kernel_t *kernel,
		struct list_t *token_list, int count)
{
	char *head_token;

	head_token = str_token_list_first(token_list);
	if (token_list->count != count)
		fatal("%s: %d tokens expected for '%s', %d found.\n%s",
				__FUNCTION__, count, head_token, token_list->count,
				opencl_err_si_kernel_metadata);
}


static struct str_map_t opencl_si_arg_dimension_map =
{
	2,
	{
		{ "2D", 2 },
		{ "3D", 3 }
	}
};


static struct str_map_t opencl_si_arg_access_type_map =
{
	3,
	{
		{ "RO", opencl_si_arg_read_only },
		{ "WO", opencl_si_arg_write_only },
		{ "RW", opencl_si_arg_read_write }
	}
};


static struct str_map_t opencl_si_arg_data_type_map =
{
	16,
	{
		{ "i1", opencl_si_arg_i1 },
		{ "i8", opencl_si_arg_i8 },
		{ "i16", opencl_si_arg_i16 },
		{ "i32", opencl_si_arg_i32 },
		{ "i64", opencl_si_arg_i64 },
		{ "u1", opencl_si_arg_u1 },
		{ "u8", opencl_si_arg_u8 },
		{ "u16", opencl_si_arg_u16 },
		{ "u32", opencl_si_arg_u32 },
		{ "u64", opencl_si_arg_u64 },
		{ "float", opencl_si_arg_float },
		{ "double", opencl_si_arg_double },
		{ "struct", opencl_si_arg_struct },
		{ "union", opencl_si_arg_union },
		{ "event", opencl_si_arg_event },
		{ "opaque", opencl_si_arg_opaque }
	}
};


static struct str_map_t opencl_si_arg_scope_map =
{
	10,
	{
		{ "g", opencl_si_arg_global },
		{ "p", opencl_si_arg_emu_private },
		{ "l", opencl_si_arg_emu_local },
		{ "uav", opencl_si_arg_uav },
		{ "c", opencl_si_arg_emu_constant },
		{ "r", opencl_si_arg_emu_gds },
		{ "hl", opencl_si_arg_hw_local },
		{ "hp", opencl_si_arg_hw_private },
		{ "hc", opencl_si_arg_hw_constant },
		{ "hr", opencl_si_arg_hw_gds }
	}
};


static void opencl_si_kernel_load_metadata_v3(struct opencl_si_kernel_t *kernel)
{
	struct elf_buffer_t *buffer = &kernel->metadata_buffer;
	struct opencl_si_arg_t *arg;
	struct list_t *token_list;

	char line[MAX_STRING_SIZE];
	char *token;
	int err;

	for (;;)
	{
		/* Read the next line */
		elf_buffer_read_line(buffer, line, sizeof line);
		opencl_debug("\t%s\n", line);
		token_list = str_token_list_create(line, ":;");

		/* Stop when ARGEND is found or line is empty */
		token = str_token_list_first(token_list);
		if (!token_list->count || !strcmp(token, "ARGEND"))
		{
			str_token_list_free(token_list);
			break;
		}


		/*
		 * Kernel argument metadata
		 */

		/* Value */
		if (!strcmp(token, "value"))
		{
			/* 6 tokens expected */
			opencl_si_kernel_expect_count(kernel, token_list, 6);

			/* Token 1 - Name */
			token = str_token_list_shift(token_list);
			arg = opencl_si_arg_create(opencl_si_arg_value, token);

			/* Token 2 - Data type */
			token = str_token_list_shift(token_list);
			arg->value.data_type = str_map_string_err(&opencl_si_arg_data_type_map,
					token, &err);
			if (err)
				fatal("%s: invalid data type '%s'.\n%s",
					__FUNCTION__, token, 
					opencl_err_si_kernel_metadata);

			/* Token 3 - Number of elements */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->value.num_elems = atoi(token);
			assert(arg->value.num_elems > 0);

			/* Token 4 - Constant buffer */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			opencl_si_kernel_expect(kernel, token_list, "1");
			arg->value.constant_buffer_num = atoi(token);

			/* Token 5 - Conastant offset */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->value.constant_offset = atoi(token);

			/* Infer argument size from its type */
			arg->size = arg->value.num_elems *
				opencl_si_arg_get_data_size(
					arg->value.data_type);

			/* Debug */
			opencl_debug("\targument '%s' - value stored in "
				"constant buffer %d at offset %d\n",
				arg->name, arg->value.constant_buffer_num,
				arg->value.constant_offset);

			/* Add argument */
			list_add(kernel->arg_list, arg);
			str_token_list_free(token_list);
			continue;
		}

		/* Pointer */
		if (!strcmp(token, "pointer"))
		{
			/* APP SDK 2.5 supplies 9 tokens, 2.6 supplies
			 * 10 tokens. Metadata version 3:1:104 (as specified
			 * in entry 'version') uses 12 items. */
			opencl_si_kernel_expect_count(kernel, token_list, 12);

			/* Token 1 - Name */
			token = str_token_list_shift(token_list);
			arg = opencl_si_arg_create(opencl_si_arg_pointer, 
				token);

			/* Token 2 - Data type */
			token = str_token_list_shift(token_list);
			arg->pointer.data_type = str_map_string_err(
				&opencl_si_arg_data_type_map, token, &err);
			if (err)
				fatal("%s: invalid data type '%s'.\n%s",
					__FUNCTION__, token, 
					opencl_err_si_kernel_metadata);

			/* Token 3 - Number of elements
			 * Arrays of pointers not supported, 
			 * only "1" allowed. */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			opencl_si_kernel_expect(kernel, token_list, "1");
			arg->pointer.num_elems = atoi(token);

			/* Token 4 - Constant buffer */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->pointer.constant_buffer_num = atoi(token);

			/* Token 5 - Constant offset */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->pointer.constant_offset = atoi(token);

			/* Token 6 - Memory scope */
			token = str_token_list_shift(token_list);
			arg->pointer.scope = str_map_string_err(
				&opencl_si_arg_scope_map, token, &err);
			if (err)
				fatal("%s: invalid scope '%s'.\n%s",
					__FUNCTION__, token, 
					opencl_err_si_kernel_metadata);

			/* Token 7 - Buffer number */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->pointer.buffer_num = atoi(token);

			/* Token 8 - Alignment */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->pointer.alignment = atoi(token);

			/* Token 9 - Access type */
			token = str_token_list_shift(token_list);
			arg->pointer.access_type = str_map_string_err(
				&opencl_si_arg_access_type_map, token, &err);
			if (err)
				fatal("%s: invalid access type '%s'.\n%s",
					__FUNCTION__, token, 
					opencl_err_si_kernel_metadata);

			/* Token 10 - ??? */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect(kernel, token_list, "0");

			/* Token 11 - ??? */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect(kernel, token_list, "0");

			/* Data size inferred here is always 4, the size 
			 * of a pointer. */
			arg->size = 4;

			/* Debug */
			opencl_debug("\targument '%s' - Pointer stored in "
				"constant buffer %d at offset %d\n",
				arg->name, arg->pointer.constant_buffer_num,
				arg->pointer.constant_offset);

			/* Add argument */
			list_add(kernel->arg_list, arg);
			str_token_list_free(token_list);
			continue;
		}

		/* Image */
		if (!strcmp(token, "image"))
		{
			/* 7 tokens expected */
			opencl_si_kernel_expect_count(kernel, token_list, 7);

			/* Token 1 - Name */
			token = str_token_list_shift(token_list);
			arg = opencl_si_arg_create(opencl_si_arg_image, token);

			/* Token 2 - Dimension */
			token = str_token_list_shift(token_list);
			arg->image.dimension = str_map_string_err(&opencl_si_arg_dimension_map,
					token, &err);
			if (err)
				fatal("%s: invalid image dimensions '%s'.\n%s",
					__FUNCTION__, token, opencl_err_si_kernel_metadata);

			/* Token 3 - Access type */
			token = str_token_list_shift(token_list);
			arg->image.access_type = str_map_string_err(&opencl_si_arg_access_type_map,
					token, &err);
			if (err)
				fatal("%s: invalid access type '%s'.\n%s",
					__FUNCTION__, token, opencl_err_si_kernel_metadata);

			/* Token 4 - UAV */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->image.uav = atoi(token);

			/* Token 5 - Constant buffer */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->image.constant_buffer_num = atoi(token);

			/* Token 6 - Constant offset */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->image.constant_offset = atoi(token);

			/* Add argument */
			list_add(kernel->arg_list, arg);
			str_token_list_free(token_list);
			continue;
		}

		/* Entry 'sampler'. */
		if (!strcmp(token, "sampler"))
		{
			/* 5 tokens expected */
			opencl_si_kernel_expect_count(kernel, token_list, 5);

			/* Token 1 - Name */
			token = str_token_list_shift(token_list);
			arg = opencl_si_arg_create(opencl_si_arg_sampler, token);

			/* Token 2 - ID */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->sampler.id = atoi(token);

			/* Token 3 - Location */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->sampler.location = atoi(token);

			/* Token 4 - Value */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			arg->sampler.value = atoi(token);

			/* Add argument */
			list_add(kernel->arg_list, arg);
			str_token_list_free(token_list);
			continue;
		}

		/*
		 * Non-kernel argument metadata
		 */

		/* Memory
		 * Used to let the GPU know how much local and private memory
		 * is required for a kernel, where it should be allocated,
		 * as well as other information. */
		if (!strcmp(token, "memory"))
		{
			/* Token 1 - Memory scope */
			token = str_token_list_shift(token_list);
			if (!strcmp(token, "hwprivate"))
			{
				/* FIXME Add support for private memory by
				 * adding space in global memory */

				/* Token 2 - ??? */
				token = str_token_list_shift(token_list);
				opencl_si_kernel_expect(kernel, token_list, "0");
			}
			else if (!strcmp(token, "hwregion"))
			{
				/* 2 more tokens expected */
				opencl_si_kernel_expect_count(kernel, token_list, 2);

				/* Token 2 - ??? */
				token = str_token_list_shift(token_list);
				opencl_si_kernel_expect(kernel, token_list, "0");
			}
			else if (!strcmp(token, "hwlocal"))
			{
				/* 2 more tokens expected */
				opencl_si_kernel_expect_count(kernel, token_list, 2);

				/* Token 2 - Size of local memory */
				token = str_token_list_shift(token_list);
				opencl_si_kernel_expect_int(kernel, token_list);
				kernel->mem_size_local = atoi(token);
			}
			else if (!strcmp(token, "datareqd"))
			{
				/* 1 more token expected */
				opencl_si_kernel_expect_count(kernel, token_list, 1);
			}
			else if (!strcmp(token, "uavprivate"))
			{
				/* 2 more tokens expected */
				opencl_si_kernel_expect_count(kernel, token_list, 2);
			}
			else
			{
				fatal("%s: not supported metadata '%s'.\n%s",
						__FUNCTION__, token, opencl_err_si_kernel_metadata);
			}

			/* Next */
			str_token_list_free(token_list);
			continue;
		}

		/* Function
		 * Used for multi-kernel compilation units. */
		if (!strcmp(token, "function"))
		{
			/* Expect 3 token */
			opencl_si_kernel_expect_count(kernel, token_list, 3);

			/* Token 1 - ??? */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect(kernel, token_list, "1");

			/* Token 2 - Function ID */
			token = str_token_list_shift(token_list);
			opencl_si_kernel_expect_int(kernel, token_list);
			kernel->func_uniqueid = atoi(token);

			/* Next */
			str_token_list_free(token_list);
			continue;
		}

		/* Reflection
		 * Format: reflection:<arg_id>:<type>
		 * Observed first in version 3:1:104 of metadata.
		 * This entry specifies the type of the argument, as
		 * specified in the OpenCL kernel function header. It is
		 * currently ignored, since this information is extracted from
		 * the argument descriptions in 'value' and 'pointer' entries.
		 */
		if (!strcmp(token, "reflection"))
		{
			/* Expect 3 tokens */
			opencl_si_kernel_expect_count(kernel, token_list, 3);

			/* Next */
			str_token_list_free(token_list);
			continue;
		}

		/* Privateid
		 * Format: privateid:<id>
		 * Observed first in version 3:1:104 of metadata.
		 * Not sure what this entry is for.
		 */
		if (!strcmp(token, "privateid"))
		{
			/* Expect 2 tokens */
			opencl_si_kernel_expect_count(kernel, token_list, 2);

			/* Next */
			str_token_list_free(token_list);
			continue;
		}

		/* Constarg
		 * Format: constarg:<arg_id>:<arg_name>
		 * Observed first in version 3:1:104 of metadata.
		 * It shows up when an argument is declared as
		 * '__global const'. Entry ignored here. */
		if (!strcmp(token, "constarg"))
		{
			/* Expect 3 tokens */
			opencl_si_kernel_expect_count(kernel, token_list, 3);

			/* Next */
			str_token_list_free(token_list);
			continue;
		}

		/* Device
		 * Device that the kernel was compiled for. */
		if (!strcmp(token, "device"))
		{
			/* Expect 2 tokens */
			opencl_si_kernel_expect_count(kernel, token_list, 2);

			/* Next */
			str_token_list_free(token_list);
			continue;
		}

		/* Uniqueid
		 * A mapping between a kernel and its unique ID */
		if (!strcmp(token, "uniqueid"))
		{
			/* Expect 2 tokens */
			opencl_si_kernel_expect_count(kernel, token_list, 2);

			/* Next */
			str_token_list_free(token_list);
			continue;
		}

		/* Uavid 
		 * ID of a raw UAV */
		if (!strcmp(token, "uavid"))
		{
			/* Expect 2 tokens */
			opencl_si_kernel_expect_count(kernel, token_list, 2);

			/* Next */
			str_token_list_free(token_list);
			continue;
		}

		/* Crash when uninterpreted entries appear */
		fatal("kernel '%s': unknown metadata entry '%s'",
			kernel->name, token);
	}
}


static void opencl_si_kernel_load_metadata(struct opencl_si_kernel_t *kernel)
{
	struct elf_buffer_t *elf_buffer = &kernel->metadata_buffer;
	struct list_t *token_list;

	char line[MAX_STRING_SIZE];
	int version;

	/* First line example:
	 * ;ARGSTART:__OpenCL_opencl_mmul_kernel */
	elf_buffer_read_line(elf_buffer, line, sizeof line);
	token_list = str_token_list_create(line, ";:");
	opencl_si_kernel_expect(kernel, token_list, "ARGSTART");
	opencl_si_kernel_expect_count(kernel, token_list, 2);
	str_token_list_free(token_list);

	/* Second line contains version info. Example:
	 * ;version:3:1:104 */
	elf_buffer_read_line(elf_buffer, line, sizeof line);
	token_list = str_token_list_create(line, ";:");
	opencl_si_kernel_expect(kernel, token_list, "version");
	opencl_si_kernel_expect_count(kernel, token_list, 4);
	str_token_list_shift(token_list);
	version = atoi(str_token_list_first(token_list));
	str_token_list_free(token_list);

	/* Parse rest of the metadata based on version number */
	switch (version)
	{
	case 3:

		opencl_si_kernel_load_metadata_v3(kernel);
		break;

	default:

		fatal("%s: metadata version %d not supported.\n%s",
				__FUNCTION__, version, opencl_err_si_kernel_metadata);
	}
}


struct opencl_si_kernel_t *opencl_si_kernel_create(struct opencl_si_program_t *program,
		char *name)
{
	struct opencl_si_kernel_t *kernel;
	struct elf_file_t *elf_file;
	char symbol_name[MAX_STRING_SIZE];

	struct elf_symbol_t *metadata_symbol;
	struct elf_symbol_t *header_symbol;
	struct elf_symbol_t *kernel_symbol;

	/* Initialize */
	kernel = xcalloc(1, sizeof(struct opencl_si_kernel_t));
	kernel->name = xstrdup(name);
	kernel->program = program;
	kernel->arg_list = list_create();

	/* Insert in kernel list */
	opencl_si_kernel_list_init();
	list_add(opencl_si_kernel_list, kernel);
	kernel->id = list_count(opencl_si_kernel_list) - 1;

	/* Check that program has been built */
	elf_file = program->elf_file;
	if (!elf_file)
		fatal("%s: program not built", __FUNCTION__);

	/* Get symbols from program binary */
	snprintf(symbol_name, sizeof symbol_name, "__OpenCL_%s_metadata", name);
	metadata_symbol = elf_symbol_get_by_name(elf_file, symbol_name);
	snprintf(symbol_name, sizeof symbol_name, "__OpenCL_%s_header", name);
	header_symbol = elf_symbol_get_by_name(elf_file, symbol_name);
	snprintf(symbol_name, sizeof symbol_name, "__OpenCL_%s_kernel", name);
	kernel_symbol = elf_symbol_get_by_name(elf_file, symbol_name);
	if (!metadata_symbol || !header_symbol || !kernel_symbol)
		fatal("%s: invalid kernel function (ELF symbol '__OpenCL_%s_xxx missing')\n%s",
				__FUNCTION__, name, opencl_err_si_kernel_symbol);

	/* Read contents pointed to by symbols */
	elf_symbol_read_content(elf_file, metadata_symbol, &kernel->metadata_buffer);
	elf_symbol_read_content(elf_file, header_symbol, &kernel->header_buffer);
	elf_symbol_read_content(elf_file, kernel_symbol, &kernel->kernel_buffer);
	opencl_debug("\tmetadata symbol: offset=0x%x, size=%u\n",
			metadata_symbol->value, kernel->metadata_buffer.size);
	opencl_debug("\theader symbol: offset=0x%x, size=%u\n",
			header_symbol->value, kernel->header_buffer.size);
	opencl_debug("\tkernel symbol: offset=0x%x, size=%u\n",
			kernel_symbol->value, kernel->kernel_buffer.size);

	/* Create and parse kernel binary (internal ELF).
	 * The internal ELF is contained in the buffer pointer to by
	 * the 'kernel' symbol. */
	snprintf(symbol_name, sizeof symbol_name, "kernel<%s>.InternalELF", name);
	kernel->bin_file = si_bin_file_create(kernel->kernel_buffer.ptr,
		kernel->kernel_buffer.size, symbol_name);

	/* Load metadata */
	opencl_si_kernel_load_metadata(kernel);

	/* Return */
	return kernel;
}


void opencl_si_kernel_free(struct opencl_si_kernel_t *kernel)
{
	int index;

	/* Free argument list */
	LIST_FOR_EACH(kernel->arg_list, index)
		opencl_si_arg_free(list_get(kernel->arg_list, index));
	list_free(kernel->arg_list);

	/* Rest */
	si_bin_file_free(kernel->bin_file);
	free(kernel->name);
	free(kernel);
}

void opencl_si_kernel_setup_ndrange_state(struct opencl_si_kernel_t *kernel,
		struct si_ndrange_t *ndrange)
{
	struct si_wavefront_t *wavefront;
	struct si_work_item_t *work_item;
	struct si_bin_enc_user_element_t *user_elements;

	int work_item_id;
	int wavefront_id;
	int i;

	unsigned int user_sgpr;
	unsigned int user_element_count;
	unsigned int zero = 0;

	float f;

	/*MIAOW start */
	FILE* unit_test_config = NULL;
	FILE* config = NULL;
	char unit_test_input_buf[1500];

	unit_test_config = fopen("unit_test_config.txt", "r");
	if (unit_test_config != 0)
	{
		//Discard first line
		fgets(unit_test_input_buf, 1500, unit_test_config);
	}

	config = fopen("config.txt", "w");
	fprintf(config,"%d;%d;\n", ndrange->group_count, ndrange->global_size);

#ifdef MIAOW_DEBUG
	fflush(config);
#endif
	/*MIAOW stop*/

	/* Save local IDs in registers */
	SI_FOREACH_WORK_ITEM_IN_NDRANGE(ndrange, work_item_id)
	{
		work_item = ndrange->work_items[work_item_id];

		//Initializing all vreg values to zero, so that config.txt doesnt change with each run
		/*MIAOW start*/
		for (int vreg_init_index = 0; vreg_init_index < 256; vreg_init_index++)
		{
			work_item->vreg[vreg_init_index].as_int = 0;
		}
		/*MIAOW stop*/

		work_item->vreg[0].as_int = 
			work_item->id_in_work_group_3d[0];  /* V0 */
		work_item->vreg[1].as_int = 
			work_item->id_in_work_group_3d[1];  /* V1 */
		work_item->vreg[2].as_int = 
			work_item->id_in_work_group_3d[2];  /* V2 */
	}

#ifdef MIAOW_DEBUG
		fprintf(config,"Processing Wavefronts\n");
		fflush(config);
#endif

	/* Initialize the wavefronts */
	SI_FOREACH_WAVEFRONT_IN_NDRANGE(ndrange, wavefront_id)
	{
		/* Get wavefront */
		wavefront = ndrange->wavefronts[wavefront_id];
		/* Save work-group IDs in registers */
		user_sgpr = kernel->bin_file->
			enc_dict_entry_southern_islands->
			compute_pgm_rsrc2->user_sgpr;
		wavefront->sreg[user_sgpr].as_int =
			wavefront->work_group->id_3d[0];
		wavefront->sreg[user_sgpr + 1].as_int =
			wavefront->work_group->id_3d[1];
		wavefront->sreg[user_sgpr + 2].as_int =
			wavefront->work_group->id_3d[2];

		/* Initialize sreg pointers to internal data structures */
		user_element_count = kernel->bin_file->
			enc_dict_entry_southern_islands->userElementCount;
		user_elements = kernel->bin_file->
			enc_dict_entry_southern_islands->userElements;
		for (i = 0; i < user_element_count; i++)
		{
			if (user_elements[i].dataClass == IMM_CONST_BUFFER)
			{
				/* Store CB pointer in sregs */
				si_wavefront_init_sreg_with_cb(wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount,
					user_elements[i].apiSlot);
			}
			else if (user_elements[i].dataClass == IMM_UAV)
			{
				/* Store UAV pointer in sregs */
				si_wavefront_init_sreg_with_uav(wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount,
					user_elements[i].apiSlot);
			}
			else if (user_elements[i].dataClass ==
				PTR_CONST_BUFFER_TABLE)
			{
				/* Store CB table in sregs */
				si_wavefront_init_sreg_with_cb_table(wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount);
			}
			else if (user_elements[i].dataClass == PTR_UAV_TABLE)
			{
				/* Store UAV table in sregs */
				si_wavefront_init_sreg_with_uav_table(
					wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount);
			}
			else if (user_elements[i].dataClass == IMM_SAMPLER)
			{
				/* Store sampler in sregs */
				assert(0);
			}
			else if (user_elements[i].dataClass ==
				PTR_RESOURCE_TABLE)
			{
				/* Store resource table in sregs */
				assert(0);
			}
			else if (user_elements[i].dataClass ==
				PTR_INTERNAL_GLOBAL_TABLE)
			{
				fatal("%s: PTR_INTERNAL_GLOBAL_TABLE not "
					"supported", __FUNCTION__);
			}
			else
			{
				fatal("%s: Unimplemented User Element: "
					"dataClass:%d", __FUNCTION__,
					user_elements[i].dataClass);
			}
		}

		/* Initialize the execution mask */
		wavefront->sreg[SI_EXEC].as_int = 0xffffffff;
		wavefront->sreg[SI_EXEC + 1].as_int = 0xffffffff;
		wavefront->sreg[SI_EXECZ].as_int = 0;

		/*MIAOW start*/
		if(unit_test_config != NULL)
		{
			char *tok = NULL;
			char vreg_str[64][500];
			char sreg_str[500];

			if(NULL != fgets(unit_test_input_buf, 1500, unit_test_config))
			{
				int num_of_threads = 0;
				int thread_init_count = 0;

				tok = strtok(unit_test_input_buf, ";"); //WGID
				tok = strtok(NULL, ";"); //WFID
				tok = strtok(NULL, ";"); //WF count
				tok = strtok(NULL, ";"); //thread count

				num_of_threads = atoi(tok);
#ifdef MIAOW_DEBUG
				if (num_of_threads != wavefront->work_item_count)
				{
					fprintf(config, "num_thread MISMATCH %d!=%d\n", num_of_threads, wavefront->work_item_count);
				}
				else
				{
					fprintf(config, "num_thread match %d=%d\n", num_of_threads, wavefront->work_item_count);
				}
				fflush(config);
#endif

				tok = strtok(NULL, ";"); //VREG size
				kernel->bin_file->enc_dict_entry_southern_islands->num_vgpr_used = atoi(tok);
				ndrange->num_vgpr_used = atoi(tok);

				tok = strtok(NULL, ";"); //SREG size
				kernel->bin_file->enc_dict_entry_southern_islands->num_sgpr_used = atoi(tok);
				ndrange->num_sgpr_used = atoi(tok);

				tok = strtok(NULL, ";"); //LDS size
				kernel->bin_file->enc_dict_entry_southern_islands->lds_size_used = atoi(tok);

				for(thread_init_count = 0; thread_init_count < num_of_threads; thread_init_count++)
				{
					tok = strtok(NULL, ";");
					strcpy((char*)vreg_str[thread_init_count], tok);
					assert(vreg_str[thread_init_count][0] == 'V');
				}

				tok = strtok(NULL, ";");
				strcpy((char*)sreg_str, tok);
				assert(sreg_str[0] == 'S');

				tok = strtok(NULL, ";"); //PC
			}

#ifdef MIAOW_DEBUG
			fprintf(config, "Initializing VREG \n");
			fflush(config);
#endif
			//VREG value init
			int wi_init_count = 0;
			for (wi_init_count = 0; wi_init_count < wavefront->work_item_count; wi_init_count++)
			{
				if (wavefront->work_items != NULL)
				{
					int vreg_init_count = 0;
					char *reg_tok;
					struct si_work_item_t* wi = wavefront->work_items[wi_init_count];

					reg_tok = strtok(vreg_str[wi_init_count], ":");
					reg_tok = strtok(NULL, "=");

					for(vreg_init_count = 0; reg_tok != NULL; vreg_init_count++)
					{
						int vreg_index = atoi(reg_tok);
						reg_tok = strtok(NULL, ",");
						assert(reg_tok != NULL);
						wi->vreg[vreg_index].as_int = atoi(reg_tok);
						reg_tok = strtok(NULL, "=");
					}

					// make sure that all reg values were read
					assert(reg_tok == NULL);
				}
			}

#ifdef MIAOW_DEBUG
			fprintf(config, "Initializing SREG \n");
			fflush(config);
#endif

			//EXEC Mask init
			long long mask = pow(2, wavefront->work_item_count) - 1;

			wavefront->sreg[SI_EXEC].as_int = mask;
			wavefront->sreg[SI_EXEC + 1].as_int = mask>>32;
			wavefront->sreg[SI_EXECZ].as_int = 0;

#ifdef MIAOW_DEBUG
			fprintf(config, "MASK HI: %d \n", wavefront->sreg[SI_EXEC + 1].as_int);
			fprintf(config, "MASK LO: %d \n", wavefront->sreg[SI_EXEC].as_int);
			fflush(config);
#endif
			//SREG value init
			int sreg_init_count = 0;
			char *sreg_tok;
			sreg_tok = strtok(sreg_str, ":");
			sreg_tok = strtok(NULL, "=");
			for(sreg_init_count=0; sreg_tok != NULL; sreg_init_count++)
			{
				int sreg_index = atoi(sreg_tok);
				sreg_tok = strtok(NULL, ",");
				assert(sreg_tok != NULL);
				wavefront->sreg[sreg_index].as_int = atoi(sreg_tok);
				sreg_tok = strtok(NULL, "=");
			}
			// make sure that all reg values were read
			assert(sreg_tok == NULL);
		}

		//WorkGroup ID
		fprintf(config,"%d;",wavefront->work_group->id);

		//Wavefront ID
		fprintf(config,"%d;",wavefront->id_in_work_group);

		//Wavefront Count
		fprintf(config,"%d;",wavefront->work_group->wavefront_count);

		//Thread count
		fprintf(config,"%d;",wavefront->work_item_count);

		//VGPR size, SGPR size, LDS size
		fprintf(config,"%d;",kernel->bin_file->enc_dict_entry_southern_islands->num_vgpr_used);
		fprintf(config,"%d;",kernel->bin_file->enc_dict_entry_southern_islands->num_sgpr_used);
		fprintf(config,"%d;",kernel->bin_file->enc_dict_entry_southern_islands->lds_size_used);

#ifdef MIAOW_DEBUG
		fflush(config);
#endif
		int wi_count = 0;
		for (wi_count = 0; wi_count < wavefront->work_item_count; wi_count++)
		{
			//VGPR initial values
			if (wavefront->work_items != NULL)
			{
				struct si_work_item_t* wi = wavefront->work_items[wi_count];

				fprintf(config,"V:");
				int vgpr_count = 0;
				for (vgpr_count = 0; vgpr_count < (kernel->bin_file->enc_dict_entry_southern_islands->num_vgpr_used - 1); vgpr_count++)
				{
					//All VGPR values except the last
					fprintf(config,"%d=%d,", vgpr_count, wi->vreg[vgpr_count]);
				}
				//Last SGPR value
				fprintf(config,"%d=%d;", vgpr_count, wi->vreg[vgpr_count]);
			}
		}

		//SGPR initial values
		fprintf(config,"S:");
		int sgpr_count = 0;
		for (sgpr_count = 0; sgpr_count < (kernel->bin_file->enc_dict_entry_southern_islands->num_sgpr_used - 1); sgpr_count++)
		{
			//All SGPR values except the last
			fprintf(config,"%d=%d,", sgpr_count, wavefront->sreg[sgpr_count]);
		}
		//Last SGPR value
		fprintf(config,"%d=%d;", sgpr_count, wavefront->sreg[sgpr_count]);

		//PC start
		//fprintf(config,"%d",wavefront->wavefront_pool_start);
		fprintf(config, "0");
		fprintf(config,"\n");
		/*MIAOW stop */
	}

	/*MIAOW start */
	fclose(config);
	if(unit_test_config != NULL)
	{
		fclose(unit_test_config);
	}
	/*MIAOW stop */

	/* CB0 bytes 0:15 */

	/* Global work size for the {x,y,z} dimensions */
	si_ndrange_const_buf_write(ndrange, 0, 0, 
		&ndrange->global_size3[0], 4);
	si_ndrange_const_buf_write(ndrange, 0, 4, 
		&ndrange->global_size3[1], 4);
	si_ndrange_const_buf_write(ndrange, 0, 8, 
		&ndrange->global_size3[2], 4);

	/* Number of work dimensions */
	si_ndrange_const_buf_write(ndrange, 0, 12, &ndrange->work_dim, 4);

	/* CB0 bytes 16:31 */

	/* Local work size for the {x,y,z} dimensions */
	si_ndrange_const_buf_write(ndrange, 0, 16, 
		&ndrange->local_size3[0], 4);
	si_ndrange_const_buf_write(ndrange, 0, 20, 
		&ndrange->local_size3[1], 4);
	si_ndrange_const_buf_write(ndrange, 0, 24, 
		&ndrange->local_size3[2], 4);

	/* 0  */
	si_ndrange_const_buf_write(ndrange, 0, 28, &zero, 4);

	/* CB0 bytes 32:47 */

	/* Global work size {x,y,z} / local work size {x,y,z} */
	si_ndrange_const_buf_write(ndrange, 0, 32, 
		&ndrange->group_count3[0], 4);
	si_ndrange_const_buf_write(ndrange, 0, 36, 
		&ndrange->group_count3[1], 4);
	si_ndrange_const_buf_write(ndrange, 0, 40, 
		&ndrange->group_count3[2], 4);

	/* 0  */
	si_ndrange_const_buf_write(ndrange, 0, 44, &zero, 4);

	/* CB0 bytes 48:63 */

	/* FIXME Offset to private memory ring (0 if private memory is
	 * not emulated) */

	/* FIXME Private memory allocated per work_item */

	/* 0  */
	si_ndrange_const_buf_write(ndrange, 0, 56, &zero, 4);

	/* 0  */
	si_ndrange_const_buf_write(ndrange, 0, 60, &zero, 4);

	/* CB0 bytes 64:79 */

	/* FIXME Offset to local memory ring (0 if local memory is
	 * not emulated) */

	/* FIXME Local memory allocated per group */

	/* 0 */
	si_ndrange_const_buf_write(ndrange, 0, 72, &zero, 4);

	/* FIXME Pointer to location in global buffer where math library
	 * tables start. */

	/* CB0 bytes 80:95 */

	/* 0.0 as IEEE-32bit float - required for math library. */
	f = 0.0f;
	si_ndrange_const_buf_write(ndrange, 0, 80, &f, 4);

	/* 0.5 as IEEE-32bit float - required for math library. */
	f = 0.5f;
	si_ndrange_const_buf_write(ndrange, 0, 84, &f, 4);

	/* 1.0 as IEEE-32bit float - required for math library. */
	f = 1.0f;
	si_ndrange_const_buf_write(ndrange, 0, 88, &f, 4);

	/* 2.0 as IEEE-32bit float - required for math library. */
	f = 2.0f;
	si_ndrange_const_buf_write(ndrange, 0, 92, &f, 4);

	/* CB0 bytes 96:111 */

	/* Global offset for the {x,y,z} dimension of the work_item spawn */
	si_ndrange_const_buf_write(ndrange, 0, 96, &zero, 4);
	si_ndrange_const_buf_write(ndrange, 0, 100, &zero, 4);
	si_ndrange_const_buf_write(ndrange, 0, 104, &zero, 4);

	/* Global single dimension flat offset: x * y * z */
	si_ndrange_const_buf_write(ndrange, 0, 108, &zero, 4);

	/* CB0 bytes 112:127 */

	/* Group offset for the {x,y,z} dimensions of the work_item spawn */
	si_ndrange_const_buf_write(ndrange, 0, 112, &zero, 4);
	si_ndrange_const_buf_write(ndrange, 0, 116, &zero, 4);
	si_ndrange_const_buf_write(ndrange, 0, 120, &zero, 4);

	/* Group single dimension flat offset, x * y * z */
	si_ndrange_const_buf_write(ndrange, 0, 124, &zero, 4);

	/* CB0 bytes 128:143 */

	/* FIXME Offset in the global buffer where data segment exists */
	/* FIXME Offset in buffer for printf support */
	/* FIXME Size of the printf buffer */
}

void opencl_si_kernel_setup_ndrange_tables(struct si_ndrange_t *ndrange)
{
	unsigned int base_addr;

	struct si_buffer_desc_t buffer_desc;

	/* Setup internal tables */
	ndrange->const_buf_table = si_emu->global_mem_top;
	si_emu->global_mem_top += SI_EMU_CONST_BUF_TABLE_SIZE;
	ndrange->resource_table = si_emu->global_mem_top;
	si_emu->global_mem_top += SI_EMU_RESOURCE_TABLE_SIZE;
	ndrange->uav_table = si_emu->global_mem_top;
	si_emu->global_mem_top += SI_EMU_UAV_TABLE_SIZE;

	/* Initialize constant buffer 0 */
	base_addr = si_emu->global_mem_top;
	si_emu->global_mem_top += SI_EMU_CONST_BUF_0_SIZE;

	opencl_si_create_buffer_desc(base_addr, SI_EMU_CONST_BUF_0_SIZE, 1, 
		opencl_si_arg_i32, &buffer_desc);

	si_ndrange_insert_buffer_into_const_buf_table(ndrange, &buffer_desc, 0);

	/* Initialize constant buffer 1 */
	base_addr = si_emu->global_mem_top;
	si_emu->global_mem_top += SI_EMU_CONST_BUF_1_SIZE;

	opencl_si_create_buffer_desc(base_addr, SI_EMU_CONST_BUF_1_SIZE, 1,
		opencl_si_arg_i32, &buffer_desc);

	si_ndrange_insert_buffer_into_const_buf_table(ndrange, &buffer_desc, 1);

	return;
}


void opencl_si_kernel_setup_ndrange_args(struct opencl_si_kernel_t *kernel,
		struct si_ndrange_t *ndrange)
{
	struct opencl_si_arg_t *arg;
	struct opencl_si_constant_buffer_t *constant_buffer;
	struct si_buffer_desc_t buffer_desc;

	int index;
	int zero = 0;

	/* Initial top of local memory is determined by the static local memory
	 * specified in the kernel binary. Number of vector and scalar 
	 * registers used by the kernel recorded as well. */
	ndrange->local_mem_top = kernel->mem_size_local;
	ndrange->num_sgpr_used = kernel->bin_file->
			enc_dict_entry_southern_islands->num_sgpr_used;
	ndrange->num_vgpr_used = kernel->bin_file->
			enc_dict_entry_southern_islands->num_vgpr_used;

	/* Kernel arguments */
	LIST_FOR_EACH(kernel->arg_list, index)
	{
		arg = list_get(kernel->arg_list, index);
		assert(arg);

		/* Check that argument was set */
		if (!arg->set)
			fatal("%s: kernel '%s': argument '%s' not set",
				__FUNCTION__, kernel->name, arg->name);

		/* Process argument depending on its type */
		switch (arg->type)
		{

		case opencl_si_arg_value:

			/* Value copied directly into device constant
			 * memory */
			assert(arg->size);
			si_ndrange_const_buf_write(ndrange,
				arg->value.constant_buffer_num,
				arg->value.constant_offset,
				arg->value.value_ptr, arg->size);
			break;

		case opencl_si_arg_pointer:

			switch (arg->pointer.scope)
			{

			/* Hardware local memory */
			case opencl_si_arg_hw_local:

				/* Pointer in __local scope.
				 * Argument value is always NULL, just assign
				 * space for it. */
				si_ndrange_const_buf_write(ndrange, 
					arg->pointer.constant_buffer_num,
					arg->pointer.constant_offset,
					&ndrange->local_mem_top, 4);

				opencl_debug("\targument %d: %u bytes reserved"
					" in local memory at 0x%x\n", index,
					arg->size, ndrange->local_mem_top);

				ndrange->local_mem_top += arg->size;

				break;

			/* UAV */
			case opencl_si_arg_uav:
			{
				/* Create descriptor for argument */
				opencl_si_create_buffer_desc(
					arg->pointer.device_ptr,
					arg->size,
					arg->pointer.num_elems,
					arg->pointer.data_type, &buffer_desc);

				/* Add to UAV table */
				si_ndrange_insert_buffer_into_uav_table(
					ndrange, &buffer_desc,
					arg->pointer.buffer_num);

				/* Write 0 to CB1 */
				si_ndrange_const_buf_write(ndrange, 
					arg->pointer.constant_buffer_num,
					arg->pointer.constant_offset,
					&zero, 4);

				break;
			}

			/* Hardware constant memory */
			case opencl_si_arg_hw_constant:
			{
				opencl_si_create_buffer_desc(
					arg->pointer.device_ptr,
					arg->size,
					arg->pointer.num_elems,
					arg->pointer.data_type, &buffer_desc);

				/* Data stored in hw constant memory 
				 * uses a 4-byte stride */
				buffer_desc.stride = 4;

				/* Add to Constant Buffer table */
				si_ndrange_insert_buffer_into_const_buf_table(
					ndrange, &buffer_desc,
					arg->pointer.buffer_num);

				/* Write 0 to CB1 */
				si_ndrange_const_buf_write(ndrange, 
					arg->pointer.constant_buffer_num,
					arg->pointer.constant_offset,
					&zero, 4);

				break;
			}

			default:

				fatal("%s: not implemented memory scope",
						__FUNCTION__);
			}

			break;

		case opencl_si_arg_image:

			fatal("%s: type 'image' not implemented", __FUNCTION__);
			break;

		case opencl_si_arg_sampler:

			fatal("%s: type 'sampler' not implemented", 
				__FUNCTION__);
			break;

		default:

			fatal("%s: argument type not recognized (%d)",
				__FUNCTION__, arg->type);

		}
	}

	/* Add program-wide constant buffers to the ND-range. 
	 * Program-wide constant buffers start at number 2. */
	for (index = 2; index < 25; index++) 
	{
		constant_buffer = list_get(
			kernel->program->constant_buffer_list, index);

		if (!constant_buffer)
			break;

		opencl_si_create_buffer_desc(
			constant_buffer->device_ptr,
			constant_buffer->size,
			4,
			opencl_si_arg_float,
			&buffer_desc);

		/* Data stored in hw constant memory 
		 * uses a 16-byte stride */
		buffer_desc.stride = 16; // XXX Use or don't use?

		/* Add to Constant Buffer table */
		si_ndrange_insert_buffer_into_const_buf_table(ndrange, 
			&buffer_desc, index);
	}
}

static void opencl_si_create_buffer_desc(unsigned int base_addr,
	unsigned int size, int num_elems, 
	enum opencl_si_arg_data_type_t data_type,
	struct si_buffer_desc_t *buffer_desc)
{
	int num_format;
	int data_format;
	int elem_size;

	/* Zero-out the buffer resource descriptor */
	assert(sizeof(struct si_buffer_desc_t) == 16);
	memset(buffer_desc, 0, sizeof(struct si_buffer_desc_t));

	num_format = SI_BUF_DESC_NUM_FMT_INVALID;
	data_format = SI_BUF_DESC_DATA_FMT_INVALID;

	switch (data_type)
	{

	case opencl_si_arg_i8:
	case opencl_si_arg_u8:

		num_format = SI_BUF_DESC_NUM_FMT_SINT;
		switch (num_elems)
		{
		case 1:
			data_format = SI_BUF_DESC_DATA_FMT_8;
			break;

		case 2:
			data_format = SI_BUF_DESC_DATA_FMT_8_8;
			break;

		case 4:
			data_format = SI_BUF_DESC_DATA_FMT_8_8_8_8;
			break;

		default:
			fatal("%s: invalid number of i8/u8 elements (%d)",
					__FUNCTION__, num_elems);
		}
		elem_size = 1 * num_elems;
		break;

	case opencl_si_arg_i16:
	case opencl_si_arg_u16:

		num_format = SI_BUF_DESC_NUM_FMT_SINT;
		switch (num_elems)
		{

		case 1:
			data_format = SI_BUF_DESC_DATA_FMT_16;
			break;

		case 2:
			data_format = SI_BUF_DESC_DATA_FMT_16_16;
			break;

		case 4:
			data_format = SI_BUF_DESC_DATA_FMT_16_16_16_16;
			break;

		default:
			fatal("%s: invalid number of i16/u16 elements (%d)",
					__FUNCTION__, num_elems);
		}
		elem_size = 2 * num_elems;
		break;

	case opencl_si_arg_i32:
	case opencl_si_arg_u32:

		num_format = SI_BUF_DESC_NUM_FMT_SINT;
		switch (num_elems)
		{

		case 1:
			data_format = SI_BUF_DESC_DATA_FMT_32;
			break;

		case 2:
			data_format = SI_BUF_DESC_DATA_FMT_32_32;
			break;

		case 3:
			data_format = SI_BUF_DESC_DATA_FMT_32_32_32;
			break;

		case 4:
			data_format = SI_BUF_DESC_DATA_FMT_32_32_32_32;
			break;

		default:
			fatal("%s: invalid number of i32/u32 elements (%d)",
					__FUNCTION__, num_elems);
		}
		elem_size = 4 * num_elems;
		break;

	case opencl_si_arg_float:

		num_format = SI_BUF_DESC_NUM_FMT_FLOAT;
		switch (num_elems)
		{
		case 1:
			data_format = SI_BUF_DESC_DATA_FMT_32;
			break;

		case 2:
			data_format = SI_BUF_DESC_DATA_FMT_32_32;
			break;

		case 3:
			data_format = SI_BUF_DESC_DATA_FMT_32_32_32;
			break;

		case 4:
			data_format = SI_BUF_DESC_DATA_FMT_32_32_32_32;
			break;

		default:
			fatal("%s: invalid number of float elements (%d)",
					__FUNCTION__, num_elems);
		}
		elem_size = 4 * num_elems;
		break;

	case opencl_si_arg_struct:

		num_format = SI_BUF_DESC_NUM_FMT_UINT;
		data_format = SI_BUF_DESC_DATA_FMT_8;
		elem_size = 1;
		break;

	default:
		fatal("%s: invalid data type for SI buffer (%d)",
			__FUNCTION__, data_type);
	}
	assert(num_format != SI_BUF_DESC_NUM_FMT_INVALID);
	assert(data_format != SI_BUF_DESC_DATA_FMT_INVALID);

	buffer_desc->base_addr = base_addr;
	buffer_desc->num_format = num_format;
	buffer_desc->data_format = data_format;
	buffer_desc->elem_size = elem_size;
	buffer_desc->num_records = size;

	return;
}

void opencl_si_kernel_debug_ndrange_state(struct opencl_si_kernel_t *kernel, 
	struct si_ndrange_t *ndrange) 
{
        int i;

	struct si_buffer_desc_t buffer_desc;

        si_isa_debug("\n");
        si_isa_debug("================ Initialization Summary ================"
                "\n");
        si_isa_debug("\n");

        /* Table locations */
        si_isa_debug("NDRange table locations:\n");
        si_isa_debug("\t------------------------------------------------\n");
        si_isa_debug("\t|    Name            |    Address Range        |\n");
        si_isa_debug("\t------------------------------------------------\n");
        si_isa_debug("\t| Const Buffer table | [%10u:%10u] |\n",
                ndrange->const_buf_table,
                ndrange->const_buf_table +
                SI_EMU_CONST_BUF_TABLE_SIZE-1);
        si_isa_debug("\t| Resource table     | [%10u:%10u] |\n",
                ndrange->resource_table,
                ndrange->resource_table +
                SI_EMU_RESOURCE_TABLE_SIZE-1);
        si_isa_debug("\t| UAV table          | [%10u:%10u] |\n",
                ndrange->uav_table,
                ndrange->uav_table + SI_EMU_UAV_TABLE_SIZE - 1);
        si_isa_debug("\t------------------------------------------------\n");
        si_isa_debug("\n");

        /* SREG initialization */
        unsigned int userElementCount =
                kernel->bin_file->enc_dict_entry_southern_islands->
                userElementCount;
        struct si_bin_enc_user_element_t* userElements =
                kernel->bin_file->enc_dict_entry_southern_islands->
                userElements;
        si_isa_debug("Scalar register initialization prior to execution:\n");
        si_isa_debug("\t-------------------------------------------\n");
        si_isa_debug("\t|  Registers  |   Initialization Value    |\n");
        si_isa_debug("\t-------------------------------------------\n");
        for (int i = 0; i < userElementCount; i++)
        {
                if (userElements[i].dataClass == IMM_CONST_BUFFER)
                {
                        /* Constant buffer descriptor */
                        if (userElements[i].userRegCount > 1)
                        {
                                si_isa_debug("\t| SREG[%2d:%2d] |  CB%1d "
                                        "Descriptor           |\n",
                                        userElements[i].startUserReg,
                                        userElements[i].startUserReg +
                                        userElements[i].userRegCount - 1,
                                        userElements[i].apiSlot);
                        }
                        else
                        {
                                si_isa_debug("\t| SREG[%2d]    |  CB%1d "
                                        "Descriptor         |\n",
                                        userElements[i].startUserReg,
                                        userElements[i].apiSlot);
                        }
                }

                else if (userElements[i].dataClass == IMM_UAV)
                {
                        /* UAV buffer descriptor */
                        si_isa_debug("\t| SREG[%2d:%2d] |  UAV%-2d "
                                "Descriptor         |\n",
                                userElements[i].startUserReg,
                                userElements[i].startUserReg +
                                userElements[i].userRegCount - 1,
                                userElements[i].apiSlot);
                }
                else if (userElements[i].dataClass ==
                        PTR_CONST_BUFFER_TABLE)
                {
                        si_isa_debug("\t| SREG[%2d:%2d] |  Constant Buffer "
                                "Table    |\n",
                                userElements[i].startUserReg,
                                userElements[i].startUserReg +
                                userElements[i].userRegCount - 1);
                }
                else if (userElements[i].dataClass == PTR_UAV_TABLE)
                {
                        si_isa_debug("\t| SREG[%2d:%2d] |  UAV "
                                "Table                |\n",
                                userElements[i].startUserReg,
                                userElements[i].startUserReg +
                                userElements[i].userRegCount - 1);
                }
                else
                {
                        assert(0);
                }
        }
        si_isa_debug("\t-------------------------------------------\n");
        si_isa_debug("\n");

#if 0
        /* Dump constant buffer 1 (argument mapping) */
        si_isa_debug("Constant buffer 1 initialization (kernel arguments):\n");
        si_isa_debug("\t-------------------------------------------\n");
        si_isa_debug("\t| CB1 Idx | Arg # |   Size   |    Name    |\n");
        si_isa_debug("\t-------------------------------------------\n");
        for (i = 0; i < list_count(kernel->arg_list); i++)
        {
                arg = list_get(kernel->arg_list, i);
                assert(arg);

                /* Check that argument was set */
                if (!arg->set)
                {
                        fatal("kernel '%s': argument '%s' has not been "
                                "assigned with 'clKernelSetArg'.",
                                kernel->name, arg->name);
                }

                /* Process argument depending on its type */
                switch (arg->kind)
                {

                case SI_OPENCL_KERNEL_ARG_KIND_VALUE:
                {
                        /* Value copied directly into device constant 
                         * memory */
                        assert(arg->size);
                        si_isa_debug("\t| CB1[%2d] | %5d | %8d | %-10s |\n",
                                arg->pointer.constant_offset/4, i, arg->size,
                                arg->name);

                        break;
                }

                case SI_OPENCL_KERNEL_ARG_KIND_POINTER:
                {
                        if (arg->pointer.mem_type !=
                                SI_OPENCL_KERNEL_ARG_MEM_TYPE_HW_LOCAL)
                        {
                                si_isa_debug("\t| CB1[%2d] | %5d | %8d | %-10s"
                                        " |\n", arg->pointer.constant_offset/4,
                                        i, arg->size,
                                        arg->name);
                        }
                        else
                        {
                                assert(0);
                        }
                        break;
                }

                case SI_OPENCL_KERNEL_ARG_KIND_IMAGE:
                {
                        assert(0);
                        break;
                }

                case SI_OPENCL_KERNEL_ARG_KIND_SAMPLER:
                {
                        assert(0);
                        break;
                }

                default:
                {
                        fatal("%s: argument type not reconized",
                                __FUNCTION__);
                }

                }
        }
        si_isa_debug("\t-------------------------------------------\n");
        si_isa_debug("\n");
#endif
        /* Initialized constant buffers */
	si_isa_debug("Initialized constant buffers:\n");
	si_isa_debug("\t-----------------------------------\n");
	si_isa_debug("\t|  CB   |      Address Range      |\n");
	si_isa_debug("\t-----------------------------------\n");
        for (i = 0; i < SI_EMU_MAX_NUM_CONST_BUFS; i++)
	{
		if (!ndrange->const_buf_table_entries[i].valid)
		{
                	continue;
		}

        	mem_read(si_emu->global_mem, 
			ndrange->const_buf_table + 
			i*SI_EMU_CONST_BUF_TABLE_ENTRY_SIZE, 
			sizeof(buffer_desc), &buffer_desc);

        	si_isa_debug("\t| CB%-2d  | [%10u:%10u] |\n",
			i, (unsigned int)buffer_desc.base_addr,
			(unsigned int)buffer_desc.base_addr + 
			(unsigned int)buffer_desc.num_records - 1);
	}
	si_isa_debug("\t-----------------------------------\n");
        si_isa_debug("\n");

        /* Initialized UAVs */
	si_isa_debug("Initialized UAVs:\n");
	si_isa_debug("\t-----------------------------------\n");
	si_isa_debug("\t|  UAV  |      Address Range      |\n");
	si_isa_debug("\t-----------------------------------\n");
        for (i = 0; i < SI_EMU_MAX_NUM_UAVS; i++)
	{
		if (!ndrange->uav_table_entries[i].valid)
		{
                	continue;
		}

        	mem_read(si_emu->global_mem, 
			ndrange->uav_table + i*SI_EMU_UAV_TABLE_ENTRY_SIZE, 
			sizeof(buffer_desc), &buffer_desc);

        	si_isa_debug("\t| UAV%-2d | [%10u:%10u] |\n",
			i, (unsigned int)buffer_desc.base_addr,
			(unsigned int)buffer_desc.base_addr + 
			(unsigned int)buffer_desc.num_records - 1);
	}
	si_isa_debug("\t-----------------------------------\n");
        si_isa_debug("\n");
        si_isa_debug("========================================================"
                "\n");
}

