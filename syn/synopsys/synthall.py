import sys
import subprocess

modules = "rfa salu wavepool exec fetch decode issue simd simf lsu sgpr vgpr compute_unit"
# modules = "compute_unit"
#modules = "fpu_post_norm_div"
#modules = "fpu_post_norm_addsub"
#modules = "dff"
#modules = "vgpr"

if __name__ == '__main__':

    for module in modules.split(" ") :
        print "--- Starting out on " + module + " --- "

        # collect rtl_files for synthesis
#        subprocess.call('rm -f rtl_files.txt', shell=True)
#        subprocess.call('ls -1 ../../src/verilog/rtl/common/build/*.v > rtl_files.txt', shell=True)
#        subprocess.call('ls -1 ../../src/verilog/rtl/'+ module +  '/build/*.v >> rtl_files.txt', shell=True)
        
        # Remove old scripts
        subprocess.call('rm -f synth.scr', shell=True)

        # Create new synth script
        filTemplate = open('synthscr.tcl', 'r')
        synthTemplate = filTemplate.read()
        filTemplate.close()
        
        synthScrText = ''
        for line in synthTemplate.split('\n') : 
#            if line.find("#CUESYNTHSCR_RTLFILES") > -1 : 
#                filRTLfiles = open('rtl_files.txt', 'r')
#                txtRTLfiles= filRTLfiles.read()
#                filRTLfiles.close()
#                synthScrText = synthScrText + line[:line.find('#CUES')]
#                for rtlfile in txtRTLfiles.split('\n') : 
#                    if (rtlfile) : 
#                        synthScrText = synthScrText + rtlfile + ' '
#                synthScrText = synthScrText + ' ] \n'
            if line.find("#CUESYNTHSCR_TOPLEVEL") > -1 : 
                synthScrText = synthScrText + line.replace("#CUESYNTHSCR_TOPLEVEL", module) +'\n'
            else : 
                synthScrText = synthScrText + line + '\n'

        filSynthScr = open('synth.scr', 'w')
        filSynthScr.write(synthScrText)
        filSynthScr.close()

        # Run dc_shell
        #subprocess.call('dc_shell-t -f synth.scr > module', shell=True)
        subprocess.call("dc_shell-t -f synth.scr |& tee '%s'.synth.log" % module, shell=True)
