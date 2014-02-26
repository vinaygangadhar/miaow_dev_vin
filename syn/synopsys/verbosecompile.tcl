get_license DesignWare

set libDir /p/vertical/plug/tools/arm_55nm/standard_cells/aci/sc-ad10/synopsys
set symbolDir /p/vertical/plug/tools/arm_55nm/standard_cells/aci/sc-ad10/symbols/synopsys
set dwDir /s/synopsys-2008_08_20/i386_cent40/A-2007.12-SP5/libraries/syn

source rtl_files.tcl

set my_toplevel compute_unit

#/* The name of the clock pin. If no clock-pin     */
#/* exists, pick anything                          */
set my_clock_pin clk

#/* Target frequency in MHz for optimization       */
set my_clk_freq_MHz 266

#/* Delay of input signals (Clock-to-Q, Package etc.)  */
set my_input_delay_ns 0.1

#/* Reserved time for output signals (Holdtime etc.)   */
set my_output_delay_ns 0


set bus_naming_style {%s[%d]}

#/**************************************************/
#/* No modifications needed below                  */
#/**************************************************/
define_design_lib WORK -path ./WORK

analyze -f verilog $my_verilog_files > analyze.log
echo "Analyze complete"

elaborate $my_toplevel -architecture verilog 
# > elab.log
echo "Elab complete"

current_design $my_toplevel

link 
set power_preserve_rtl_hier_names TRUE

set_dont_touch [get_cells -hier *ram*] true
set_dont_touch [get_cells -hier *mult_mac*] true

set my_period 3.85

set find_clock [ find port [list $my_clock_pin] ]
if {  $find_clock != [list] } {
   set clk_name $my_clock_pin
   create_clock -period $my_period $clk_name
} else {
   set clk_name vclk
   create_clock -period $my_period -name $clk_name
} 

set_input_delay $my_input_delay_ns -clock $clk_name [remove_from_collection [all_inputs] $my_clock_pin]
set_output_delay $my_output_delay_ns -clock $clk_name [all_outputs]


set_dont_touch_network { clk }

set_wire_load_model -name 140000


compile > compile.log
#compile_ultra > compile.log

write -format ddc -output compute_unit.vlog -hier

ungroup -all -flatten
set filename [format "%s%s"  $my_toplevel ".syn.v"]
write -f verilog -hier -output $filename
#set filename [format "%s%s"  $my_toplevel ".syn.sdf"]
#write_sdf -significant_digit 6 $filename

set filename [format "%s%s"  $my_toplevel ".syn.ddc"]
write -format ddc -output $filename

report_area -hier > area.rpt
report_timing -delay max -significant_digit 6 > timing.rpt
#report_timing -delay min -significant_digit 6 >> orig_timing.rpt

quit
