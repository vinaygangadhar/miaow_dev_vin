// synopsys translate_off
`include "timescale.v"
// synopsys translate_on
`include "or1200_defines.v"
`include "compiledefs.v"

extern "C" void initializeMemorySubSystem();
extern "C" int getMemoryData(int address); // 32bit
extern "C" void setMemoryData(int address, int data, int byteenable); // 32bit
extern "C" void stepCycle(); // 32bit
extern "C" void displayInst(int pc, int inst, int flag); // 32bit


module testbench;

   reg cpuclk;
   reg reset;
 
   reg [63:0] clkcycle;
   reg [63:0] icount;
   reg [63:0] lsu_busy;
   reg [63:0] lsu_occupied;
   
   parameter idw = `OR1200_OPERAND_WIDTH;
   
   reg 	      r_IAck;
   reg [idw-1:0] r_IData;
   reg 		 r_DAck;
   reg [31:0] 	 r_DData;

   reg [63:0] 	 maxtimeout;
   reg 		 calltimeout_pctrack;
   
   reg 		 usercode;
   reg 		 printstats;
   reg 		 exitdone;
   
//   assign printstats = (clkcycle == maxtimeout);

   or1800_stats
     or1800_stats
       (
	.clk(cpuclk),
	.rst(reset),
	.usercode(usercode),
	.printstats(printstats)
	);
   
   
   initial begin
      cpuclk = 0;
      maxtimeout = 64'h0000_0000_0FFF_FFFF;
      
      while (1) begin
         #40;
         cpuclk = ~cpuclk;
      end
   end
   

   
   always @(posedge cpuclk)
     if (reset)
       begin
	  usercode <= 1'b0;
	  printstats <= 1'b0;
	  exitdone <= 1'b0;
       end
     else
       begin
	  begin   
	     //insert here
	     
	   
	     
	     //to here
	     if (clkcycle == maxtimeout) begin
		$display("Time out called %d\n", clkcycle);
		$finish;
	     end
	  end
       end // always @ (posedge cpuclk)
`define PCTRACK
`ifdef PCTRACK
   integer pctrackfile;
   reg [31:0] actualpc;
   integer    commitTimeOut;
   
   initial begin
      pctrackfile = $fopen("origpctrace.txt", "r");
   end

   always @(posedge cpuclk)
     if (reset)
       begin
	  commitTimeOut <= 'd0;
       end
     else
       begin
	  commitTimeOut <= commitTimeOut + 'd1;
	  if ($feof(pctrackfile)) begin
	     calltimeout_pctrack <= 1'b1;
	     $display("PC TRACK FILE EXHAUSTED");
	  end
	  calltimeout_pctrack <= 1'b0;
	  if (clkcycle == maxtimeout) begin
	     $fclose(pctrackfile);
	  end

	  if (testbench.or1200_top.or1200_cpu.commit_valid0_s)
	    begin
	       commitTimeOut <= 'd0;
	       $fscanf(pctrackfile, "PC = %h\n", actualpc);
	       if (actualpc != {testbench.or1200_top.or1200_cpu.commit_pc0_s[31:0]})
		 begin
		    calltimeout_pctrack <= 1'b1;
		    $display(" ====== PC TRACE DOES NOT MATCH WITH SINGLE ISSUE, Expected PC = %h, OOO PC = %h ======= ", actualpc, {testbench.or1200_top.or1200_cpu.commit_pc0_s[31:0]});
		 end
	    end
	  if (testbench.or1200_top.or1200_cpu.commit_valid1_s)
	    begin
	       commitTimeOut <= 'd0;
	       $fscanf(pctrackfile, "PC = %h\n", actualpc);
	       if (actualpc != {testbench.or1200_top.or1200_cpu.commit_pc1_s[31:0]})
		 begin
		    calltimeout_pctrack <= 1'b1;
                    $display(" ====== PC TRACE DOES NOT MATCH WITH SINGLE ISSUE, Expected PC = %h, OOO PC = %h ======= ", actualpc, {testbench.or1200_top.or1200_cpu.commit_pc1_s[31:0]});
		 end
	    end
	  if (commitTimeOut > 'd1000)
	    begin
	       $display(" ====== COMMIT TIME OUT CALLED  ======= ");
	       calltimeout_pctrack <= 1'b1;
	       
	    end
       end
`endif
   
`define DUMPPC 1
`ifdef DUMPPC
   integer fname0;

   
   initial begin
      fname0 = $fopen("./logs/pctrace.txt", "w");
   end
   
   always @(posedge cpuclk)
     begin
	if (clkcycle == maxtimeout) begin
	   $fclose(fname0);
	end
	if (testbench.or1200_top.or1200_cpu.commit_valid0_s)
	  $fwrite(fname0, "PC = %h \n", {testbench.or1200_top.or1200_cpu.commit_pc0_s[31:0]});
	if (testbench.or1200_top.or1200_cpu.commit_valid1_s)
	  $fwrite(fname0, "PC = %h \n", {testbench.or1200_top.or1200_cpu.commit_pc1_s[31:0]});
     end
    

`endif //  `ifdef DUMPPC

   always @(posedge cpuclk) begin
      if (!reset) 
	begin
	 if (usercode & testbench.or1200_top.or1200_cpu.valid_instr_lsu_iq_ex_s)
	   lsu_busy <= lsu_busy + 'd1;
 `ifdef PERFLSU
	   if (usercode & |testbench.or1200_top.or1200_cpu.or1800_iqperf_lsu.valids)
             lsu_occupied <= lsu_occupied + 'd1;
 `else
	   if (usercode & |testbench.or1200_top.or1200_cpu.or1800_iq_lsu.valids)
	     lsu_occupied <= lsu_occupied + 'd1;
 `endif
	end
      else
	begin
	   lsu_busy <= 'd0;
	   lsu_occupied <= 'd0;
	end
   end

 `define DUMPTLBUPDATES
 `ifdef DUMPTLBUPDATES
   integer tlbupdatefile;

   initial begin
      tlbupdatefile = $fopen("./logs/tlbupdates.txt", "w");
   end

   always @(posedge cpuclk) begin
      if (!reset)
	if (clkcycle == maxtimeout) begin
	   $fclose(tlbupdatefile);
	end
      if (testbench.or1200_top.or1200_immu_top.or1200_immu_tlb.tlb_mr_en & testbench.or1200_top.or1200_immu_top.or1200_immu_tlb.tlb_mr_we)
	$fwrite(tlbupdatefile, "IMMU : Addr : %h : Value : %h \n", testbench.or1200_top.or1200_immu_top.or1200_immu_tlb.tlb_index, testbench.or1200_top.or1200_immu_top.or1200_immu_tlb.tlb_mr_ram_in);
      if (testbench.or1200_top.or1200_dmmu_top.or1200_dmmu_tlb.tlb_mr_en & testbench.or1200_top.or1200_dmmu_top.or1200_dmmu_tlb.tlb_mr_we)
	$fwrite(tlbupdatefile, "DMMU : Addr : %h : Value : %h \n", testbench.or1200_top.or1200_dmmu_top.or1200_dmmu_tlb.tlb_index, testbench.or1200_top.or1200_dmmu_top.or1200_dmmu_tlb.tlb_mr_ram_in);
   end
 `endif
   
   
// `define MEMDUMP 1
 `ifdef MEMDUMP
   integer memdump;
   integer memnumber;
   
   initial begin
      memdump = $fopen("./logs/memdump_ooo.txt", "w");
      memnumber <= 'd0;
      
   end

   always @(posedge cpuclk) begin
      if (!reset) begin	
	 if (clkcycle == maxtimeout) begin
	    $fclose(memdump);
	 end
 if (testbench.or1200_top.or1200_cpu.execdone_lsu_s)
   begin
      `ifndef PERFLSU
	      $fwrite(memdump, "NO : %h : OP : %h : AD : %h : OF : %h", memnumber, {testbench.or1200_top.or1200_cpu.or1200_lsu.id_lsu_op[3:0]}, {testbench.or1200_top.or1200_cpu.or1200_lsu.id_addrbase[31:0]}, {testbench.or1200_top.or1200_cpu.or1200_lsu.id_addrofs[31:0]});
      `else
	      $fwrite(memdump, "NO : %h : OP : %h : AD : %h : OF : %h",{testbench.or1200_top.or1200_cpu.or1800_iqperf_lsu.insnnumstations[{testbench.or1200_top.or1200_cpu.or1800_iqperf_lsu.read_address[2:0]}][31:0]}, {testbench.or1200_top.or1200_cpu.or1200_lsu.id_lsu_op[3:0]}, {testbench.or1200_top.or1200_cpu.or1200_lsu.id_addrbase[31:0]}, {testbench.or1200_top.or1200_cpu.or1200_lsu.id_addrofs[31:0]});
      `endif
	      if ({testbench.or1200_top.or1200_cpu.or1200_lsu.id_lsu_op[3]})
		// Store
		$fwrite(memdump, " VL : %h \n",{testbench.or1200_top.or1200_cpu.or1200_lsu.lsu_datain[31:0]});
	      else
		$fwrite(memdump, " VL : %h \n",{testbench.or1200_top.or1200_cpu.or1200_lsu.lsu_dataout[31:0]} );
	      
	      memnumber <= memnumber + 'd1;
	   end
      end
   end
	
 `endif
   

   
`define REGDUMP 1
`ifdef REGDUMP
   integer regdump;
   integer regdump_time;
   integer regwritecount;
   

   initial begin
      regdump = $fopen("./logs/regdump_ooo.txt", "w");
      regdump_time = $fopen("./logs/regdump_ooo_time.txt","w");
      regwritecount <= 'd0;
   end
   
   always @(posedge cpuclk) begin
      if (!reset) begin
	 if (testbench.or1200_top.or1200_cpu.or1200_rfram_6port.we_w0 == 1'b1)
	   begin
	      $fwrite(regdump, "RegWrite %h <= %h, Instr Tag = %h  Actual Log Reg = %h \n", {testbench.or1200_top.or1200_cpu.or1200_rfram_6port.addr_w0[5:0]}, {testbench.or1200_top.or1200_cpu.or1200_rfram_6port.di_w0[31:0]}, {testbench.or1200_top.or1200_cpu.insttag_0_s}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[testbench.or1200_top.or1200_cpu.insttag_0_s][10:6]}); 
	      $fwrite(regdump_time, "RegWrite %h <= %h, Instr Tag = %h  Actual Log Reg = %h ALU0 : %d\n", {testbench.or1200_top.or1200_cpu.or1200_rfram_6port.addr_w0[5:0]}, {testbench.or1200_top.or1200_cpu.or1200_rfram_6port.di_w0[31:0]}, {testbench.or1200_top.or1200_cpu.insttag_0_s}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[testbench.or1200_top.or1200_cpu.insttag_0_s][10:6]}, regwritecount);
	   end
	 
	 if (testbench.or1200_top.or1200_cpu.or1200_rfram_6port.we_w1 == 1'b1)
	   begin
	      $fwrite(regdump, "RegWrite %h <= %h; Instr Tag = %h  Actual Log Reg = %h \n", {testbench.or1200_top.or1200_cpu.or1200_rfram_6port.addr_w1[5:0]}, {testbench.or1200_top.or1200_cpu.or1200_rfram_6port.di_w1[31:0]}, {testbench.or1200_top.or1200_cpu.insttag_1_s}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.insttag_1_s}][10:6]});
	      $fwrite(regdump_time, "RegWrite %h <= %h; Instr Tag = %h  Actual Log Reg = %h ALU1 : %d\n", {testbench.or1200_top.or1200_cpu.or1200_rfram_6port.addr_w1[5:0]}, {testbench.or1200_top.or1200_cpu.or1200_rfram_6port.di_w1[31:0]}, {testbench.or1200_top.or1200_cpu.insttag_1_s}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.insttag_1_s}][10:6]}, regwritecount);

	   end
	 
	 if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.re_0_s)
	   begin
	      if ({testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.abort_commit0_s})
		$fwrite(regdump, "Aborting Instr Tag %h : Log Reg %h \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][10:6]});
	      else
		$fwrite(regdump, "Commiting Instr Tag %h : Log Reg %h : rb : %h \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][10:6]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.rfwb_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}]});
	      
	      if ({testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.abort_commit0_s})
		begin
		   $fwrite(regdump_time, "Aborting Instr Tag %h : Log Reg %h : Insn %h : PC %h ", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][10:6]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.insn_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][31:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.instpc_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][31:0]});
		   if ( {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.rfwb_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}]})
		     $fwrite(regdump_time, " Old Reg : %h \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][5:0]});
		   else
		     $fwrite(regdump_time, "\n");
		end
	      else
		begin
		   $fwrite(regdump_time, "Commiting Instr Tag %h : Log Reg %h : Insn %h : PC %h ", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][10:6]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.insn_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][31:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.instpc_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][31:0]});
		   if ( {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.rfwb_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}]})
		     $fwrite(regdump_time, " Old Reg : %h \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}][5:0]});
		   else
		     $fwrite(regdump_time, "\n"); 
		end // else: !if({testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.abort_commit0_s})
	   end
	 
	 if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.re_1_s)
	   begin  
	      if ({testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.abort_commit1_s})
		$fwrite(regdump, "Aborting Instr Tag %h : Log Reg %h \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][10:6]});
	      else
		$fwrite(regdump, "Commiting Instr Tag %h : Log Reg %h : rb : %h  \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][10:6]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.rfwb_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}]});
	      
	      if ({testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.abort_commit1_s})
		begin
		   $fwrite(regdump_time, "Aborting Instr Tag %h : Log Reg %h : Insn %h : PC %h ", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][10:6]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.insn_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][31:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.instpc_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][31:0]});
		   if ( {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.rfwb_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}]})
		     $fwrite(regdump_time, " Old Reg : %h \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][5:0]});
		   else
		     $fwrite(regdump_time, "\n"); 
		end
	      else
		begin
		   $fwrite(regdump_time, "Commiting Instr Tag %h : Log Reg %h : Insn %h : PC %h ", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][10:6]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.insn_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][31:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.instpc_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][31:0]});
		   if ( {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.rfwb_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}]})
		     $fwrite(regdump_time, " Old Reg : %h \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfifo.mem[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}][5:0]});
		   else
		     $fwrite(regdump_time, "\n");
		end // else: !if({testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.abort_commit1_s})
	   end

	 if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.using_free_reg0_i)
	   begin
	      $fwrite(regdump_time, "FL : using %h, read ptr %h AL : wptr : %h time : %d \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.free_reg0_o[5:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.freelistfifo.read_pointer0_o[6:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.write_pointer0_s[5:0]}, $time);
	   end
	 if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.using_free_reg1_i)
	   begin
	      $fwrite(regdump_time, "FL : using %h, read ptr %h AL : wptr : %h time : %d \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.free_reg1_o[5:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.freelistfifo.read_pointer1_o[6:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.write_pointer1_s[5:0]}, $time);
	   end
	 if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.reg_freed0_valid_i)
	   begin
	      $fwrite(regdump_time, "FL : freey %h, writ ptr %h AL : rptr : %h time : %d \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.reg_freed0_i[5:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.freelistfifo.write_pointer0_o[6:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer0_s[5:0]}, $time);
	   end
	 if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.reg_freed1_valid_i)
	   begin
	      $fwrite(regdump_time, "FL : freey %h, writ ptr %h AL : rptr : %h time : %d \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.reg_freed1_i[5:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_freelist.freelistfifo.write_pointer1_o[6:0]},{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.read_pointer1_s[5:0]}, $time);
	   end
	 if (|testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.state & testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.reg_freed0_valid_o)
	   begin
	      $fwrite(regdump_time, "FL : Exception, fptr : %h time : %d \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.flush_pointer_s[5:0]}, $time);
 	   end
	 if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_regrename.exception_raddr_update_i)
	   begin
	      $fwrite(regdump_time, "REN : Exception : Writing Log Reg : %h on Phy Reg %h time : %d \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_regrename.exception_raddr_log_i}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_regrename.exception_raddr_log_i}, $time);
	   end
	 if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.state == 2'd1)
	   begin 
	      $fwrite(regdump_time, " EXCEPTION TRIGGERED : PC = %h, Tag = %h \n", {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.instpc_s[{testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.flush_pointer_s[5:0]}][31:0]}, {testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.flush_pointer_s[5:0]});
	   end
	 
      end // if (!reset)
   end // always @ (posedge cpuclk)
   

`endif


//`define BPRED 1
`ifdef BPRED
   integer bpredfile;

   initial
     begin
	bpredfile = $fopen("./logs/bpred.txt", "w");
     end

   always @(posedge cpuclk)
     begin
	if (clkcycle == maxtimeout) begin
	   $fclose(bpredfile);
	end

	if (testbench.or1200_top.or1200_cpu.branch_commit_s)
	  if (|testbench.or1200_top.or1200_cpu.branch_abort_s)
	    $fwrite(bpredfile, "ABORT : PC : %h : DIR : %d\n", testbench.or1200_top.or1200_cpu.commit_pc0_s, testbench.or1200_top.or1200_cpu.or1800_branch.actual_branch_taken_s );
	  else
	    $fwrite(bpredfile, "COMMIT : PC : %h : DIR : %d\n", testbench.or1200_top.or1200_cpu.commit_pc0_s, testbench.or1200_top.or1200_cpu.or1800_branch.actual_branch_taken_s );
	
     end
   
`endif
   
   
   initial begin
      initializeMemorySubSystem();
    
      reset = 1;
      #1010;
      reset = 0;
   end
   
   always @(posedge cpuclk) begin
      if (reset)
	clkcycle <= 'd0;
      // TODO-ISSUE-raghu-20120803 : ifdef this
      else if (calltimeout_pctrack | exitdone)
	clkcycle <= maxtimeout;
      else if (testbench.or1200_top.or1200_cpu.or1800_regwrap.or1800_activelist.activelistfull_o)
	begin
//	   $display("Active List full \n, %x", clkcycle);
	   if (usercode)
	     clkcycle <= clkcycle + 'd1;
	end
      else if (usercode)
	clkcycle <= clkcycle + 'd1;
      
   end
   
   always @(posedge cpuclk) begin
      if (reset)
	icount <= 'd0;
      else
	if ((testbench.or1200_top.or1200_cpu.commit_valid0_s == 1'b1) && (testbench.or1200_top.or1200_cpu.commit_valid1_s == 1'b1))
	  icount <= icount + 'd2;
	else if ((testbench.or1200_top.or1200_cpu.commit_valid0_s == 1'b1) || (testbench.or1200_top.or1200_cpu.commit_valid1_s == 1'b1))
	  icount <= icount + 'd1;
   end

//   always @(posedge cpuclk) begin
//      if (icount[8:0] == 'd0 && icount != 'd0)
//	$display("Progress : icount = %h", icount);
//   end
   
   always @(posedge cpuclk) begin
      stepCycle();
   end

   parameter dw = `OR1200_OPERAND_WIDTH;
   parameter aw = `OR1200_OPERAND_WIDTH;
   parameter ppic_ints = `OR1200_PIC_INTS;
 
//   parameter idw = `OR1200_OPERAND_WIDTH;
   


   //
   // System
   //
   wire        clk_i = cpuclk;
   wire        rst_i = reset;
   wire [1:0] clmode_i = 0;
   wire [ppic_ints-1:0] pic_ints_i = 0;

   //
   // Instruction WISHBONE interface
   //
   wire           iwb_ack_i = r_IAck;
   wire           iwb_err_i = 0;
   wire           iwb_rty_i = 0;
   wire [idw-1:0]  iwb_dat_i = r_IData;
   wire           iwb_cyc_o;
   wire [aw-1:0]  iwb_adr_o;
   wire           iwb_stb_o;
   wire           iwb_we_o; 
   wire [3:0]     iwb_sel_o;
   wire [dw-1:0]  iwb_dat_o;
   wire           iwb_cab_o;

   //
   // Data WISHBONE interface
   //
   wire           dwb_ack_i = r_DAck;
   wire           dwb_err_i = 0;
   wire           dwb_rty_i = 0;
   wire [dw-1:0]  dwb_dat_i = r_DData;
   wire          dwb_cyc_o;
   wire [aw-1:0] dwb_adr_o;
   wire          dwb_stb_o;
   wire          dwb_we_o;
   wire [3:0]    dwb_sel_o;
   wire [dw-1:0] dwb_dat_o;
   wire          dwb_cab_o;
   
   //
   // External Debug Interface
   //
   wire           dbg_stall_i = 0;
   wire           dbg_ewt_i = 0;
   wire [3:0]    dbg_lss_o;
   wire [1:0]    dbg_is_o;
   wire [10:0]   dbg_wp_o;
   wire          dbg_bp_o;
   wire           dbg_stb_i = 0;
   wire           dbg_we_i = 0;
   wire [aw-1:0]  dbg_adr_i = 0;
   wire [dw-1:0]  dbg_dat_i = 0;
   wire [dw-1:0] dbg_dat_o;
   wire          dbg_ack_o;
   
   wire        pm_cpustall_i = 0;


   wire [3:0] pm_clksd_o;
   wire       pm_dc_gate_o;
   wire       pm_ic_gate_o;
   wire       pm_dmmu_gate_o;
   wire       pm_immu_gate_o;
   wire       pm_tt_gate_o;
   wire       pm_cpu_gate_o;
   wire       pm_wakeup_o;
   wire       pm_lvolt_o;
   
   // Additional input/output
   // 
   wire [10:0] icd_addr;
   wire        icd_en;
   wire [3:0]  icd_we;
   wire [idw-1:0] icd_datain;
   wire [idw-1:0] icd_dataout;

   wire [8:0]  ict_addr;
   wire        ict_en;
   wire        ict_we;
   wire [19:0] ict_datain;
   wire        ict_tag_v;
   wire [18:0] ict_tag;

   wire [10:0] dcd_addr;
   wire        dcd_en;
   wire [3:0]  dcd_we;
   wire [31:0] dcd_datain;
   wire [31:0] dcd_dataout;

   wire [8:0]  dct_addr;
   wire        dct_en;
   wire        dct_we;
   wire [19:0] dct_datain;
   wire        dct_tag_v;
   wire [18:0] dct_tag;

   
   or1200_top
     or1200_top(
                // Outputs
                .iwb_cyc_o              (iwb_cyc_o),
                .iwb_adr_o              (iwb_adr_o[aw-1:0]),
                .iwb_stb_o              (iwb_stb_o),
                .iwb_we_o               (iwb_we_o),
                .iwb_sel_o              (iwb_sel_o[3:0]),
                .iwb_dat_o              (iwb_dat_o[dw-1:0]),
`ifdef OR1200_WB_CAB
                .iwb_cab_o              (iwb_cab_o),
`endif
                .dwb_cyc_o              (dwb_cyc_o),
                .dwb_adr_o              (dwb_adr_o[aw-1:0]),
                .dwb_stb_o              (dwb_stb_o),
                .dwb_we_o               (dwb_we_o),
                .dwb_sel_o              (dwb_sel_o[3:0]),
                .dwb_dat_o              (dwb_dat_o[dw-1:0]),
`ifdef OR1200_WB_CAB		
                .dwb_cab_o              (dwb_cab_o),
`endif		
                .dbg_lss_o              (dbg_lss_o[3:0]),
                .dbg_is_o               (dbg_is_o[1:0]),
                .dbg_wp_o               (dbg_wp_o[10:0]),
                .dbg_bp_o               (dbg_bp_o),
                .dbg_dat_o              (dbg_dat_o[dw-1:0]),
                .dbg_ack_o              (dbg_ack_o),
                .pm_clksd_o             (pm_clksd_o[3:0]),
                .pm_dc_gate_o           (pm_dc_gate_o),
                .pm_ic_gate_o           (pm_ic_gate_o),
                .pm_dmmu_gate_o         (pm_dmmu_gate_o),
                .pm_immu_gate_o         (pm_immu_gate_o),
                .pm_tt_gate_o           (pm_tt_gate_o),
                .pm_cpu_gate_o          (pm_cpu_gate_o),
                .pm_wakeup_o            (pm_wakeup_o),
                .pm_lvolt_o             (pm_lvolt_o),
                // Inputs
                .clk_i                  (clk_i),
                .rst_i                  (rst_i),
                .clmode_i               (clmode_i[1:0]),
                .pic_ints_i             (pic_ints_i[ppic_ints-1:0]),
		.iwb_clk_i (clk_i),
		.iwb_rst_i (rst_i),
                .iwb_ack_i              (iwb_ack_i),
                .iwb_err_i              (iwb_err_i),
                .iwb_rty_i              (iwb_rty_i),
                .iwb_dat_i              (iwb_dat_i[idw-1:0]),
                .dwb_ack_i              (dwb_ack_i),
                .dwb_err_i              (dwb_err_i),
                .dwb_rty_i              (dwb_rty_i),
                .dwb_dat_i              (dwb_dat_i[dw-1:0]),
  		.dwb_clk_i (clk_i),
		.dwb_rst_i (rst_i),
		.dbg_stall_i            (dbg_stall_i),
                .dbg_ewt_i              (dbg_ewt_i),
                .dbg_stb_i              (dbg_stb_i),
                .dbg_we_i               (dbg_we_i),
                .dbg_adr_i              (dbg_adr_i[aw-1:0]),
                .dbg_dat_i              (dbg_dat_i[dw-1:0]),
                .pm_cpustall_i          (pm_cpustall_i)
                
                );

   wire        clk = cpuclk;
   wire        rst = reset;
   
   // Memory Sub System
   // parameter D1 = 2;
   

      parameter D1 = 2;
   always @(posedge cpuclk) begin
      if (reset) begin
         r_IAck <= #D1 1'b0;
         r_IData <= #D1 32'd0;
      end else begin
         if (r_IAck == 1'b0) begin
            if (iwb_stb_o == 1'b1) begin
               r_IAck <= #D1 1'b1;
               r_IData <= #D1 getMemoryData(iwb_adr_o);
            end  
         end else begin
            r_IAck <= #D1 1'b0;
            r_IData <= #D1 32'd0;
         end
      end
   end // always @ (posedge cpuclk)
   
   always @(posedge cpuclk) begin
      if (reset) begin
         r_DAck <= #D1 1'b0;
         r_DData <= #D1 32'd0;
      end else begin
         if (r_DAck == 1'b0) begin
            if (dwb_stb_o == 1'b1) begin
               r_DAck <= #D1 1'b1;
               if (dwb_we_o == 1'b1) begin
                  if (dwb_adr_o == 32'hffff0004) begin
//                     writeData();
                  end
                  setMemoryData(dwb_adr_o, dwb_dat_o, {28'd0, dwb_sel_o});
               end else begin
                  r_DData <= #D1 getMemoryData(dwb_adr_o);
               end
            end
         end else begin
            r_DAck <= #D1 1'b0;
            r_DData <= #D1 32'd0;
         end
      end
   end // always @ (posedge cpuclk)

endmodule // testbench

