For running a simulation and generating traces from multi2sim, the following steps are to be followed:

1) Compile multi2sim code to generate the m2s executable:
  	cd /src/sw/multi2sim-4.0
        libtoolize
        aclocal
        autoconf
        automake --add-missing
        ./configure
        make

2) Running Sample OpenCL tests:
   Some sample OpenCl tests are present in the /src/sw/tests folder.
   For running the test:
   	cd /src/sw/tests/
   	run -i <test_name>

   For a test folder named foobar, the input needed by multi2sim are:
   foobar                	-> executable that runs on the CPU
   foorbar_Kernels.bin   	-> the OpenCL kernel binary

   Output produced by the 'run' command:
   foobar_trace        		-> the trace generated by multi2sim
   config.txt        		-> the initial settings to be set before running the 
   				   kernel on the GPU. These values will be parsed by 
				   the testbench PLI and used accordingly.
   data.mem          		-> The initial GPU device memory data before the kernel 
   				   begins to run.
   instr.mem         		-> The instruction buffer.

3) Running Unit tests:
   Unit test for each instruction supported are present in the folder
   For running the test:
   	cd /src/sw/unit_tests/
   	run -i <test_name>

   For a unit test folder named foobar, the inputs needed are:
   unit_test_config.txt   	-> The initial SGPR abd VGPR values to be set in
   				   multi2sim before running the test.
   unit_test_data.mem     	-> The contents of the data memory needed for
   				   running the unit test. This data will be 
				   copied to multi2sim simulator's GPU device memory 
				   before running the test
   unit_test_instr.mem		-> Machine code of the instructions to be
   				   tested.

   Outputs produced are:
   <test_name>_trace  		-> the trace generated by multi2sim
   config.txt        		-> the initial settings to be set before running the 
   				   kernel on the GPU. These values will be parsed by 
				   the testbench PLI and used accordingly.
   data.mem          		-> The initial GPU device memory data before the kernel 
   				   begins to run.
   instr.mem         		-> The instruction buffer.

