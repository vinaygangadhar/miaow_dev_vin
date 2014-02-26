compile: testbench.v counter.v dff.v
	vcs -full64 testbench.v counter.v  dff.v -timescale=1ns/1ns -l compile.log -debug_all

run: simv
	simv +print_outputs=1 -l run.log

waves: simv
	simv +print_outputs=1 +dump_waveforms=1 -l run.log

browse:
	dve -full64 -vpd vcdplus.vpd	

interact: simv
	simv +print_outputs=1 +dump_waveforms=1 -l run.log -gui

clean:
	rm -rf csrc simv simv.daidir ucli.key compile.log run.log DVEfiles vcdplus.vpd inter.vpd
