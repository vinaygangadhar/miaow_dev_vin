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


#include <arch/x86/emu/context.h>
#include <arch/x86/emu/regs.h>
#include <arch/southern-islands/asm/input.h>
#include <arch/southern-islands/emu/ndrange.h>
#include <arch/southern-islands/emu/opengl-bin-file.h>
#include <arch/southern-islands/timing/gpu.h>
#include <lib/mhandle/mhandle.h>
#include <lib/util/debug.h>
#include <lib/util/list.h>
#include <lib/util/misc.h>
#include <mem-system/memory.h>

#include "opengl.h"
#include "si-program.h"
#include "si-shader.h"

/* Debug */
int opengl_debug_category;

#define SI_DRIVER_MAX_WORK_GROUP_BUFFER_SIZE 16

/* Error messages */
static char *opengl_err_not_impl =
	"\tThe OpenGL interface is implemented in library 'm2s-opengl.so' as a set of\n"
	"\tsystem calls, intercepted by Multi2Sim and emulated in 'opengl.c'.\n"
	"\tHowever, only a subset of this interface is currently implemented in the simulator.\n"
	"\tTo request the implementation of a specific OpenGL call, please email\n"
	"\t'development@multi2sim.org'.\n";

static char *opengl_version_code =
	"\tAn invalid function code was generated by your application in a OpenGL system\n"
	"\tcall. Probably, this means that your application is using an incompatible\n"
	"\tversion of the Multi2Sim OpenGL runtime library ('libm2s-opengl'). Please\n"
	"\trecompile your application and try again.\n";

struct opengl_abi_si_driver_state_t
{
	struct opengl_si_shader_t *shader;
	struct si_ndrange_t *ndrange;
	int ready_for_work;
	int wait_for_ndrange_completion;
	int ndrange_complete;
};

struct opengl_abi_si_driver_state_t driver_state;


/* List of OpenGL Runtime calls */
enum opengl_abi_call_t
{
	opengl_abi_call_invalid = 0,
#define OPENGL_ABI_CALL(name, code) opengl_abi_##name = code,
#include "opengl.dat"
#undef OPENGL_ABI_CALL
	opengl_abi_call_count
};


/* List of OpenGL ABI call names */
char *opengl_abi_call_name[opengl_abi_call_count + 1] =
{
	NULL,
#define OPENGL_ABI_CALL(name, code) #name,
#include "opengl.dat"
#undef OPENGL_ABI_CALL
	NULL
};

/* Forward declarations of OpenGL Runtime functions */
#define OPENGL_ABI_CALL(name, code) \
	static int opengl_abi_##name##_impl(X86Context *ctx);
#include "opengl.dat"
#undef OPENGL_ABI_CALL


/* List of OpenGL Runtime functions */
typedef int (*opengl_abi_call_t)(X86Context *ctx);
static opengl_abi_call_t opengl_abi_call_table[opengl_abi_call_count + 1] =
{
	NULL,
#define OPENGL_ABI_CALL(name, code) opengl_abi_##name##_impl,
#include "opengl.dat"
#undef OPENGL_ABI_CALL
	NULL
};


#define __NOT_IMPL__  fatal("%s: not implemented.\n%s", \
	__FUNCTION__, opengl_err_not_impl);

/*
 * OpenGL global variables
 */

void opengl_init(void)
{
}


void opengl_done(void)
{
}


int opengl_abi_call(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	/* Variables */
	int code;
	int ret;

	/* Function code */
	code = regs->ebx;
	if (code <= opengl_abi_call_invalid || code >= opengl_abi_call_count)
		fatal("%s: invalid OpenGL function (code %d).\n%s",
			__FUNCTION__, code, opengl_version_code);

	/* Debug */
	opengl_debug("OpenGL runtime call '%s' (code %d)\n",
		opengl_abi_call_name[code], code);

	/* Call OPENGL function */
	assert(opengl_abi_call_table[code]);
	ret = opengl_abi_call_table[code](ctx);

	/* Return value */
	return ret;
}


/*
 * OpenGL ABI call #1 - init
 *
 * Returns the version of the OpenGL driver.
 *
 * @param struct opengl_version_t *version
 *
 * 	The driver returns its version information in this argument, with a
 * 	data structure formed of two integer fields:
 *
 * 	struct opengl_version_t
 * 	{
 * 		int major;
 * 		int minor;
 * 	};
 *
 * @return
 *	The function always returns 0.
 */

/* NOTE: when modifying the values of these two macros, the same values should
 * be reflected in 'runtime/opengl/context.c'. */
#define OPENGL_VERSION_MAJOR  1
#define OPENGL_VERSION_MINOR  1000

struct opengl_version_t
{
	int major;
	int minor;
};

static int opengl_abi_init_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	unsigned int version_ptr;
	struct opengl_version_t version;

	/* Arguments */
	version_ptr = regs->ecx;
	opengl_debug("\tversion_ptr=0x%x\n", version_ptr);

	/* Return version */
	assert(sizeof(struct opengl_version_t) == 8);
	version.major = OPENGL_VERSION_MAJOR;
	version.minor = OPENGL_VERSION_MINOR;
	mem_write(mem, version_ptr, sizeof version, &version);
	opengl_debug("\tMulti2Sim OpenGL implementation in host: v. %d.%d.\n",
		OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR);
	opengl_debug("\tMulti2Sim OpenGL Runtime in guest: v. %d.%d.\n",
		version.major, version.minor);

	/* Return success */
	return 0;
}

/*
 * OpenGL ABI call #2 - done
 *
 * Finialize, free all created objects 
 *
 * @return
 *	The function always returns 0.
 */

static int opengl_abi_done_impl(X86Context *ctx)
{
	/* Free */
	opengl_si_program_list_done();
	opengl_si_shader_list_done();

	/* Return success */
	return 0;
}

/*
 * OpenGL ABI call #3 - si_mem_alloc
 *
 * Allocates memory in the Southern Islands device.
 *
 * @param unsigned int size
 *
 * 	Number of bytes to allocate.
 *
 * @return void *
 *
 *	The function returns a pointer in the device memory space. This pointer
 *	should not be dereferenced in the runtime, but instead passed to other
 *	ABI calls taking device pointers as input arguments.
 */

static int opengl_abi_si_mem_alloc_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	unsigned int size;
	unsigned int device_ptr;

	/* Arguments */
	size = regs->ecx;
	opengl_debug("\tsize = %u\n", size);

	/* For now, memory allocation in device memory is done by just 
	 * incrementing a pointer to the top of the global memory space. 
	 * Since memory deallocation is not implemented, "holes" in the 
	 * memory space are not considered. */
	device_ptr = si_emu->video_mem_top;
	si_emu->video_mem_top += size;
	opengl_debug("\t%d bytes of device memory allocated at 0x%x\n",
			size, device_ptr);

	/* Return device pointer */
	return device_ptr;
}




/*
 * OpenGL ABI call #4 - si_mem_read
 *
 * Read memory from Southern Islands device into host memory space.
 *
 * @param void *host_ptr
 *
 * 	Destination pointer in host memory space.
 *
 * @param void *device_ptr
 *
 * 	Source pointer in device memory space.
 *
 * @param unsigned int size
 *
 * 	Number of bytes to read.
 *
 * @return void
 *
 *	The function does not have any return value.
 */

static int opengl_abi_si_mem_read_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	unsigned int host_ptr;
	unsigned int device_ptr;
	unsigned int size;

	void *buf;

	/* Arguments */
	host_ptr = regs->ecx;
	device_ptr = regs->edx;
	size = regs->esi;
	opengl_debug("\thost_ptr = 0x%x, device_ptr = 0x%x, size = %d bytes\n",
			host_ptr, device_ptr, size);

	/* Check memory range */
	if (device_ptr + size > si_emu->video_mem_top)
		fatal("%s: accessing device memory not allocated",
				__FUNCTION__);

	/* Read memory from device to host */
	buf = xmalloc(size);
	mem_read(si_emu->video_mem, device_ptr, size, buf);
	mem_write(mem, host_ptr, size, buf);
	free(buf);

	/* Return */
	return 0;
}




/*
 * OpenGL ABI call #5 - si_mem_write
 *
 * Write memory from host into Southern Islands device.
 *
 * @param void *device_ptr
 *
 * 	Destination pointer in device memory.
 *
 * @param void *host_ptr
 *
 * 	Source pointer in host memory.
 *
 * @param unsigned int size
 *
 * 	Number of bytes to read.
 *
 * @return void
 *
 *	The function does not have any return value.
 */

static int opengl_abi_si_mem_write_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	unsigned int device_ptr;
	unsigned int host_ptr;
	unsigned int size;

	void *buf;

	/* Arguments */
	device_ptr = regs->ecx;
	host_ptr = regs->edx;
	size = regs->esi;
	opengl_debug("\tdevice_ptr = 0x%x, host_ptr = 0x%x, size = %d bytes\n",
			device_ptr, host_ptr, size);

	/* Check memory range */
	if (device_ptr + size > si_emu->video_mem_top)
		fatal("%s: accessing device memory not allocated",
				__FUNCTION__);

	/* Write memory from host to device */
	buf = xmalloc(size);
	mem_read(mem, host_ptr, size, buf);
	mem_write(si_emu->video_mem, device_ptr, size, buf);
	free(buf);

	/* Return */
	return 0;
}




/*
 * OpenGL ABI call #6 - si_mem_copy
 *
 * Copy memory across two different regions of the Southern Islands device
 * memory space.
 *
 * @param void *dest_ptr
 *
 * 	Destination pointer in device memory.
 *
 * @param void *src_ptr
 *
 * 	Source pointer in device memory.
 *
 * @param unsigned int size
 *
 * 	Number of bytes to read.
 *
 * @return void
 *
 *	The function does not have any return value.
 */

static int opengl_abi_si_mem_copy_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	unsigned int dest_ptr;
	unsigned int src_ptr;
	unsigned int size;

	void *buf;

	/* Arguments */
	dest_ptr = regs->ecx;
	src_ptr = regs->edx;
	size = regs->esi;
	opengl_debug("\tdest_ptr = 0x%x, src_ptr = 0x%x, size = %d bytes\n",
			dest_ptr, src_ptr, size);

	/* Check memory range */
	if (src_ptr + size > si_emu->video_mem_top ||
			dest_ptr + size > si_emu->video_mem_top)
		fatal("%s: accessing device memory not allocated",
				__FUNCTION__);

	/* Write memory from host to device */
	buf = xmalloc(size);
	mem_read(si_emu->video_mem, src_ptr, size, buf);
	mem_write(si_emu->video_mem, dest_ptr, size, buf);
	free(buf);

	/* Return */
	return 0;
}


/*
 * OpenGL ABI call #7 - si_mem_free
 *
 * Deallocated memory in Southern Islands global memory scope.
 *
 * @param unsigned int device_ptr
 *
 * 	Memory address in device global memory returned previously by a call to
 *	'si_mem_alloc'.
 *
 * @return void
 *
 *	No value is returned.
 */

static int opengl_abi_si_mem_free_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	unsigned int device_ptr;

	/* Arguments */
	device_ptr = regs->ecx;
	opengl_debug("\tdevice_ptr = %u\n", device_ptr);

	/* For now, this call is ignored. No deallocation of global memory can
	 * happen. */

	/* Return device pointer */
	return device_ptr;
}



/*
 * OpenGL ABI call #8 - si_program_create
 *
 * Create a Southern Islands program object 
 *
 * @return int
 *
 *	Program ID.
 */

static int opengl_abi_si_program_create_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct opengl_si_program_t *program;
	unsigned int program_id;

	/* Arguments */
	program_id = regs->ecx;

	/* Create program */
	program = opengl_si_program_create(program_id);
	opengl_debug("\tnew program_id = %d\n", program->id);

	/* Return program ID */
	return program->id;
}



/*
 * OpenGL ABI call #9 - si_program_free
 *
 * Free a Southern Islands program object 
 *
 * @return int
 *
 *	No value is returned.
 */

static int opengl_abi_si_program_free_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct opengl_si_program_t *program;
	unsigned int program_id;

	/* Arguments */
	program_id = regs->ecx;

	/* Create program */
	program = list_get(opengl_si_program_list ,program_id);
	opengl_debug("\tfree program ID = %d\n", program->id);

	/* Free program object */
	opengl_si_program_free(program);

	/* Return */
	return 0;
}



/*
 * OpenGL ABI call #10 - si_program_set_binary
 *
 * Associate a binary to a Southern Islands program. Also setup associated shaders. 
 *
 * @param int program_id
 *
 * 	Program ID, as returned by a previous ABI call to 'si_program_create'.
 *
 * @param void *buf
 *
 * 	Pointer to the memory space where the program binary can be found.
 *
 * @param unsigned int size
 *
 * 	Size of the program binary
 *
 * @return void
 *
 *	No return value.
 */

static int opengl_abi_si_program_set_binary_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct opengl_si_program_t *program;
	int program_id;

	unsigned int bin_ptr;
	unsigned int bin_size;
	void *buf;


	/* Arguments */
	program_id = regs->ecx;
	bin_ptr = regs->edx;
	bin_size = regs->esi;
	opengl_debug("\tprogram_id = %d, bin_ptr = 0x%x, size = %u\n",
			program_id, bin_ptr, bin_size);

	/* Get program */
	program = list_get(opengl_si_program_list, program_id);
	if (!program)
		fatal("%s: invalid program ID (%d)",
				__FUNCTION__, program_id);

	/* Set the binary */
	buf = xmalloc(bin_size);
	mem_read(ctx->mem, bin_ptr, bin_size, buf);
	opengl_si_program_set_binary(program, buf, bin_size);
	free(buf);
	
	/* No return value */
	return 0;
}



/*
 * OpenGL ABI call #11 - si_shader_create
 *
 * Create a Southern Islands shader object and return a unique identifier
 * for it.
 *
 * @return void
 *
 *	No return value.
 */

static int opengl_abi_si_shader_create_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct opengl_si_program_t *program;

	unsigned int program_id;
	unsigned int shader_id;
	unsigned int shader_type;

	/* Arguments */
	program_id = regs->ecx;
	shader_id = regs->edx;
	shader_type = regs->esi;
	opengl_debug("\tprogram_id=%d, shader_id=%d, type=%x\n", program_id, shader_id, shader_type);

	/* Create a shader object, will be initialized with shaders in program object */
	program = list_get(opengl_si_program_list, program_id);
	if (program)
	{
		opengl_si_shader_create(shader_id, shader_type);	
		opengl_si_shader_init(program, shader_id);
	}

	/* Return */	
	return 0;
}



/*
 * OpenGL ABI call #12 - si_shader_free
 *
 * Free a Southern Islands shader object 
 *
 */

static int opengl_abi_si_shader_free_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct opengl_si_shader_t *shdr;

	unsigned int shader_id;

	/* Arguments */
	shader_id = regs->ecx;
	opengl_debug("\tshader_id=%d\n", shader_id);

	/* Get and free */
	shdr = list_get(opengl_si_shader_list, shader_id);
	if (shdr)
		opengl_si_shader_free(shdr);

	return 0;
}

/*
 * OpenGL ABI call #13 - si_shader_set_input
 *
 * Set up the expected input in a shader 
 *
 */

static int opengl_abi_si_shader_set_input_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	struct opengl_si_shader_t *shdr;
	struct list_t *input_list;
	struct si_input_t *input;

	unsigned int args[6];
	unsigned int shader_id;
	unsigned int device_ptr;
	unsigned int num_elems;
	unsigned int data_type;
	unsigned int size;
	unsigned int index;

	/* Arguments */
	mem_read(mem, regs->ecx, 6 * sizeof(unsigned int), args);
	shader_id = args[0];
	device_ptr = args[1];
	num_elems = args[2];
	data_type = args[3];
	size = args[4];
	index = args[5];
	opengl_debug("\tshader_id = %d, device_ptr = 0x%d, num_elems = %d, type = %d, size = %d, index = %d\n",
		shader_id, device_ptr, num_elems, data_type, size, index);

	/* Shader has the indices of vertex attribute array in its encoding dictionary */
	shdr = list_get(opengl_si_shader_list, shader_id);
	input_list = shdr->shader_bin->shader_enc_dict->input_list;
	input = list_get(input_list, index);
	if (!input || input->usage_index != index)
		fatal("Vertex attribute array at index %d is not needed by the vertex shader\n", index);
	else
	{
		input->set = 1;
		input->num_elems = num_elems;
		input->type = si_input_get_type(data_type);
		input->device_ptr = device_ptr;
		input->size = size;
	}

	return 0;
}

/*
 * OpenGL ABI call #14- si_ndrange_initialize
 *
 * Create and initialize an ND-Range for the supplied shader.
 *
 * @param int shader_id
 *
 * 	Shader ID, assigned in OpenGL runtime and bound to certain OpenGL program
 *
 * @param int work_dim
 *
 * 	Number of work dimensions. This is an integer number between 1 and 3,
 * 	which determines the number of elements of the following arrays.
 *
 * @param unsigned int *global_offset
 *
 *	Array of 'work_dim' integers containing global offsets.
 *
 * @param unsigned int *global_size
 *
 *	Array of 'work_dim' integers containing the ND-Range global size in each
 *	dimension.
 *
 * @param unsigned int *local_size
 *
 *	Array of 'work_dim' integers containing the local size in each
 *	dimension.
 *
 * @return int
 *
 *	Unique shader ID.
 */

static int opengl_abi_si_ndrange_initialize_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	struct elf_buffer_t *elf_buffer;
	struct opengl_si_shader_t *shader;
	struct si_bin_enc_user_element_t *user_elements;
	struct si_ndrange_t *ndrange;

	int i;
	int shader_id;
	int user_element_count;
	int work_dim;

	unsigned int global_offset_ptr;
	unsigned int global_size_ptr;
	unsigned int local_size_ptr;

	unsigned int global_offset[3];
	unsigned int global_size[3];
	unsigned int local_size[3];


	/* Arguments */
	shader_id = regs->ecx;
	work_dim = regs->edx;
	global_offset_ptr = regs->esi;
	global_size_ptr = regs->edi;
	local_size_ptr = regs->ebp;
	opengl_debug("\tshader_id = %d, work_dim = %d\n", shader_id, work_dim);
	opengl_debug("\tglobal_offset_ptr = 0x%x, global_size_ptr = 0x%x, "
		"local_size_ptr=0x%x\n", global_offset_ptr, global_size_ptr, 
		local_size_ptr);
	
	/* Debug */
	assert(IN_RANGE(work_dim, 1, 3));
	mem_read(mem, global_offset_ptr, work_dim * 4, global_offset);
	mem_read(mem, global_size_ptr, work_dim * 4, global_size);
	mem_read(mem, local_size_ptr, work_dim * 4, local_size);
	for (i = 0; i < work_dim; i++)
		opengl_debug("\tglobal_offset[%d] = %u\n", i, global_offset[i]);
	for (i = 0; i < work_dim; i++)
		opengl_debug("\tglobal_size[%d] = %u\n", i, global_size[i]);
	for (i = 0; i < work_dim; i++)
		opengl_debug("\tlocal_size[%d] = %u\n", i, local_size[i]);

	/* Get shader */
	shader = list_get(opengl_si_shader_list, shader_id);
	if (!shader)
		fatal("%s: invalid shader ID (%d)", __FUNCTION__, shader_id);

	/* Create ND-Range */
	ndrange = si_ndrange_create();
	ndrange->local_mem_top = shader->mem_size_local;
	ndrange->num_sgpr_used = shader->shader_bin->
		shader_enc_dict->num_sgpr_used;
	ndrange->num_vgpr_used = shader->shader_bin->
		shader_enc_dict->num_vgpr_used;
	ndrange->wg_id_sgpr = shader->shader_bin->
		shader_enc_dict->shader_pgm_rsrc2_vs->user_sgpr;
	

	si_ndrange_setup_size(ndrange, global_size, local_size, work_dim);

	/* Copy user elements from shader to ND-Range */
	user_element_count = shader->shader_bin->
		shader_enc_dict->userElementCount;
	user_elements = shader->shader_bin->shader_enc_dict->
		userElements;
	ndrange->userElementCount = user_element_count;
	for (i = 0; i < user_element_count; i++)
	{
		ndrange->userElements[i] = user_elements[i];
	}

	/* Set up instruction memory */
	/* Initialize wavefront instruction buffer and PC */
	elf_buffer = shader->shader_bin->shader_isa;
	if (!elf_buffer->size)
		fatal("%s: cannot load shader code", __FUNCTION__);

	si_ndrange_setup_inst_mem(ndrange, elf_buffer->ptr, 
		elf_buffer->size, 0);

	assert(!driver_state.shader);
	driver_state.shader = shader;

	assert(!driver_state.ndrange);
	driver_state.ndrange = ndrange;

	assert(!si_emu->ndrange);
	si_emu->ndrange = ndrange;

	if (si_gpu)
		si_gpu_map_ndrange(ndrange);

	/* No return value */
	return 0;
}




/*
 * OpenGL ABI call #15 - si_ndrange_get_num_buffer_entries
 *
 * Returns the number of available buffer entries in the waiting 
 * work-group queue.
 *
 * @param unsigned int *host_ptr
 *
 *	Location to be populated with the number of available 
 *	buffer entry slots.
 *
 * @return int
 *
 *	The function always returns 0.
 */


static int opengl_abi_si_ndrange_get_num_buffer_entries_impl(
	X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	unsigned int host_ptr;

	int available_buffer_entries;

	/* Arguments */
	host_ptr = regs->ecx;

	available_buffer_entries = SI_DRIVER_MAX_WORK_GROUP_BUFFER_SIZE -
		list_count(si_emu->waiting_work_groups);

	opengl_debug("\tavailable buffer entries = %d\n", 
		available_buffer_entries);

	mem_write(mem, host_ptr, sizeof available_buffer_entries,
		&available_buffer_entries);

	return 0;
}

/*
 * OpenGL ABI call #16 - si_ndrange_send_work_groups
 *
 * Receives a range of work-group IDs to add to the waiting 
 * work-group queue. The x86 context performing this call
 * suspends until the emulator needs more work.
 *
 * @param int work_group_start_id 
 *
 *	The first work-group ID to add to the waiting queue.
 *
 * @param int work_group_count
 *
 *	The number of work groups to add to the waiting queue.
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opengl_abi_si_ndrange_send_work_groups_can_wakeup(
	X86Context *ctx, void *user_data)
{
	assert(!user_data);

	return driver_state.ready_for_work;
}

static void opengl_abi_si_ndrange_send_work_groups_wakeup(
	X86Context *ctx, void *user_data)
{
	assert(!user_data);
}

static int opengl_abi_si_ndrange_send_work_groups_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	int i, j, k;

	unsigned int work_group_start_ptr;
	unsigned int work_group_count_ptr;
	unsigned int work_group_sizes_ptr;
	unsigned int work_group_start[3];
	unsigned int work_group_count[3];
	unsigned int work_group_sizes[3];
	unsigned int total_num_groups;

	long work_group_id;

	assert(driver_state.ndrange);
	assert(driver_state.ndrange->const_buf_table);
	assert(driver_state.ndrange->uav_table);
	assert(driver_state.ndrange->resource_table);

	/* Arguments */
	work_group_start_ptr = regs->ecx;
	work_group_count_ptr = regs->edx;
	work_group_sizes_ptr = regs->esi;

	mem_read(mem, work_group_start_ptr, 3 * 4, work_group_start);
	mem_read(mem, work_group_count_ptr, 3 * 4, work_group_count);
	mem_read(mem, work_group_sizes_ptr, 3 * 4, work_group_sizes);

	total_num_groups = work_group_count[2] * work_group_count[1] * 
		work_group_count[0];
	assert(total_num_groups <= SI_DRIVER_MAX_WORK_GROUP_BUFFER_SIZE -
		list_count(si_emu->waiting_work_groups));

	opengl_debug("\treceiving work groups (%d,%d,%d) through (%d,%d,%d)\n",
		work_group_start[0], work_group_start[1], work_group_start[2],
		work_group_start[0] + work_group_count[0] - 1, 
		work_group_start[1] + work_group_count[1] - 1, 
		work_group_start[2] + work_group_count[2] - 1);

	/* Receive work groups (add them to the waiting queue) */
	for (i = work_group_start[2]; i < work_group_start[2] + work_group_count[2]; i++)
	{
		for (j = work_group_start[1]; j < work_group_start[1] + work_group_count[1]; j++)
		{
			for (k = work_group_start[0]; k < work_group_start[0] + work_group_count[0]; k++)
			{
				work_group_id = (i * work_group_sizes[1] * 
					work_group_sizes[0]) + (j * 
					work_group_sizes[0]) + k;

				list_enqueue(si_emu->waiting_work_groups, 
					(void*)work_group_id);
				opengl_debug("\tadding wg %ld\n", 
					work_group_id);
			}
		}
	}

	/* XXX Later, check if waiting queue is still under a threshold.  
	 * If it is, set as ready for work */
	driver_state.ready_for_work = 0;

	/* Suspend x86 context until driver needs more work */
	X86ContextSuspend(ctx, 
		opengl_abi_si_ndrange_send_work_groups_can_wakeup, NULL,
		opengl_abi_si_ndrange_send_work_groups_wakeup, NULL);

	return 0;
}

/*
 * OpenGL ABI call #17 - si_ndrange_finish
 *
 * Tells the driver that there are no more work groups to execute
 * from the ND-Range.
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opengl_abi_si_ndrange_finish_can_wakeup(X86Context *ctx, 
	void *user_data)
{
	assert(!user_data);

	return driver_state.ndrange_complete;
}

static void opengl_abi_si_ndrange_finish_wakeup(X86Context *ctx, 
	void *user_data)
{
	assert(!user_data);

	/* Reset driver state */
	si_ndrange_free(driver_state.ndrange);
	driver_state.ndrange = NULL;
	driver_state.shader = NULL;
	driver_state.wait_for_ndrange_completion = 0;
	driver_state.ndrange_complete = 0;
	driver_state.ready_for_work = 0;

	si_emu->ndrange = NULL;
}

static int opengl_abi_si_ndrange_finish_impl(X86Context *ctx)
{
	driver_state.wait_for_ndrange_completion = 1;

	if (!list_count(si_emu->running_work_groups) && 
		!list_count(si_emu->waiting_work_groups))
	{
		/* Reset driver state */
		si_ndrange_free(driver_state.ndrange);
		driver_state.ndrange = NULL;
		driver_state.shader = NULL;
		driver_state.wait_for_ndrange_completion = 0;
		driver_state.ndrange_complete = 0;
		driver_state.ready_for_work = 0;

		si_emu->ndrange = NULL;
	}
	else 
	{
		/* Suspend x86 context until simulation completes */
		X86ContextSuspend(ctx, opengl_abi_si_ndrange_finish_can_wakeup, 
			NULL, opengl_abi_si_ndrange_finish_wakeup, NULL);
	}

	return 0;
}


/*
 * OpenGL ABI call #18 - si_ndrange_pass_mem_objs
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opengl_abi_si_ndrange_pass_mem_objs_impl(X86Context *ctx)
{
	struct opengl_si_shader_t *shader;
	struct si_ndrange_t *ndrange;

	shader = driver_state.shader;
	ndrange = driver_state.ndrange;

	opengl_si_shader_create_ndrange_tables(ndrange); 
	opengl_si_shader_create_ndrange_constant_buffers(ndrange); 
	opengl_si_shader_setup_ndrange_constant_buffers(ndrange);
	opengl_si_shader_setup_ndrange_inputs(shader, ndrange);
	opengl_si_shader_debug_ndrange_state(shader, ndrange);

	return 0;
	__NOT_IMPL__;
}

