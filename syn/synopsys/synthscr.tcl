get_license DesignWare

set gate_lib_file saed32rvt_tt1p05v25c.db
set sram_lib_file saed32sramlp_tt0p85v25ci0p85v.db

set link_library $gate_lib_file

# set wire_library_file   {saed32rvt_tt1p05v25c.db}
# set wire_library   None
# set wire_model_name      05x05
# set wireload_mode      top

set search_path [concat $search_path /p/vertical/afs-huge0/synopsys/32nmlib/SAED32_EDK/lib/stdcell_rvt/db_nldm/]
set link_library [concat * $link_library ]
set symbol_library {}

set search_path [concat $search_path script/]

set search_path [concat $syn_home \
		     $search_path ]

set my_toplevel #CUESYNTHSCR_TOPLEVEL

#CUESYNTHSCR_SAIFMAPSTART
#CUESYNTHSCR_SAIFORNOT

if { $saif_analysis == no } {
source #CUESYNTHSCR_FILELIST
} else {
#CUESYNTHSCR_SAIFREADDDC
#CUESYNTHSCR_READSAIF
set filename [format "%s%s"  $my_toplevel ".saif.rpt"]
#CUESYNTHSCR_REPORTSAIF
}

#set my_verilog_files [ list #CUESYNTHSCR_RTLFILES ]


set link_library [concat $link_library \
                         $mem_libs \
		      $black_box_designs \
		     $sram_lib_file]

# set target_library $syn_home/lsi_10k.db
set target_library saed32rvt_tt1p05v25c.db

set target_library [concat $target_library \
			$mem_libs]


#/* The name of the clock pin. If no clock-pin     */
#/* exists, pick anything                          */
set my_clock_pin clk

#/* Target frequency in MHz for optimization       */
#set my_clk_freq_MHz 100
# See clock period which is set later

#/* Delay of input signals (Clock-to-Q, Package etc.)  */
set my_input_delay_ns 0.0

#/* Reserved time for output signals (Holdtime etc.)   */
set my_output_delay_ns 0.0


set bus_naming_style {%s[%d]}

#/**************************************************/
#/* No modifications needed below                  */
#/**************************************************/
define_design_lib WORK -path ./WORK

if { $saif_analysis == no } {
echo "------------ Step 1/4 ----------------------"
echo "------------ Starting Analyze --------------"
set filename [format "%s%s"  $my_toplevel ".analyze.log"]
analyze -f verilog $my_verilog_files > $filename
#analyze -f verilog -autoread -top $my_toplevel $my_verilog_files
# > analyze.log
echo "------------ Analyze Done ------------------"

echo "------------ Step 2/4 ----------------------"
echo "------------ Starting Elaborate ------------"
set filename [format "%s%s"  $my_toplevel ".elaborate.log"]
elaborate $my_toplevel -architecture verilog > $filename
#> elab.log 
echo "------------ Elaborate Done ----------------"

current_design $my_toplevel

link 
set power_preserve_rtl_hier_names TRUE

set_dont_touch [get_cells -hier *ram*] true
#CUESYNTHSCR_STUBDONTTOUCH
set my_period 8.00

set find_clock [ find port [list $my_clock_pin] ]
if {  $find_clock != [list] } {
   set clk_name $my_clock_pin
   create_clock -period $my_period $clk_name
} else {
   set clk_name clk
   create_clock -period $my_period -name $clk_name
} 

set_input_delay $my_input_delay_ns -clock $clk_name [remove_from_collection [all_inputs] $my_clock_pin]
set_output_delay $my_output_delay_ns -clock $clk_name [all_outputs]


set_dont_touch_network { clk }

ungroup -all -flatten
set_fix_hold clk


echo "------------ Step 3/4 ----------------------"
echo "------------ Starting Compile --------------"
set filename [format "%s%s"  $my_toplevel ".compile.log"]
compile -map_effort high -area_effort high -power_effort high > $filename
# > compile.log
#compile_ultra > compile.log
}

echo "------------ Compile done ------------------"

echo "------------ Step 4/4 ----------------------"
echo "------------ Generating reports ------------"

set filename [format "%s%s"  $my_toplevel ".vlog"]
write -format ddc -output $filename -hier

set filename [format "%s%s"  $my_toplevel ".syn.v"]
write -f verilog -hier -output $filename

set filename [format "%s%s"  $my_toplevel ".syn.sdf"]
write_sdf -significant_digit 6 $filename

set filename [format "%s%s"  $my_toplevel ".syn.ddc"]
write -format ddc -output $filename

set filename [format "%s%s"  $my_toplevel ".area.rpt"]
report_area -hier > $filename

set filename [format "%s%s"  $my_toplevel ".power.rpt"]
report_power -hierarchy > $filename

set filename [format "%s%s"  $my_toplevel ".timing.rpt"]
report_timing -delay max -max_paths 5 -significant_digit 6 > $filename

set filename [format "%s%s"  $my_toplevel ".warnings.rpt"]
check_design > $filename


echo "--------- Done generating reports ----------"

quit
