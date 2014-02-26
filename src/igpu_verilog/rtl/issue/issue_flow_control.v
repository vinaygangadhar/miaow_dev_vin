module issue_flow_control
  (/*AUTOARG*/
   // Outputs
   wave_valid_entries,
   // Inputs
   clk, rst, tracemon_barrier_retire_en, f_mem2cu_page_fault_en,
   valid_entry_out, idemp_wait_arry,
   tracemon_barrier_retire_wf_bitmap, f_decode_wfid,
   f_salu_branch_wfid, alu_wfid, f_decode_valid, f_decode_waitcnt,
   f_salu_branch_en, alu_valid, alu_branch, f_mem2cu_page_fault_tag
   );

   input clk,rst;
   input tracemon_barrier_retire_en, f_mem2cu_page_fault_en;
   input [`WF_PER_CU-1:0] valid_entry_out, idemp_wait_arry;
   input [`WF_PER_CU-1:0] tracemon_barrier_retire_wf_bitmap;
   input [`WF_ID_LENGTH-1:0] f_decode_wfid, f_salu_branch_wfid,
			     alu_wfid;
   input 		     f_decode_valid, f_decode_waitcnt,
			     f_salu_branch_en,
			     alu_valid, alu_branch;

   input [6:0] 		     f_mem2cu_page_fault_tag;

   wire [`WF_PER_CU-1:0]     flopped_valid_entry_out;
   wire [`WF_PER_CU-1:0]     valid_barrier_retire_wf_bitmap;
   wire [`WF_PER_CU-1:0]     decoded_decode_waitcnt, decoded_branch_retired;
   wire [`WF_PER_CU-1:0]     flopped_idemp_wait_arry;
   
   wire [`WF_PER_CU-1:0]     decoded_exception, 
			     decoded_branch_issued, flopped_decoded_branch_issued;
   
			
   output [`WF_PER_CU-1:0]   wave_valid_entries;

   wire 		     f2_mem2cu_page_fault_en;
		     
   wire [6:0] 		     f2_mem2cu_page_fault_tag;
   

   decoder_6b_40b_en branch_issue
     (
      .addr_in(alu_wfid),
      .out(decoded_branch_issued),
      .en(alu_valid & alu_branch)
      );
   
   decoder_6b_40b_en branch_retire
     (
      .addr_in(f_salu_branch_wfid),
      .out(decoded_branch_retired),
      .en(f_salu_branch_en)
      );

   decoder_6b_40b_en exception_decoder
     (
      .addr_in(f2_mem2cu_page_fault_tag[5:0]),
      .out(decoded_exception),
      .en(f2_mem2cu_page_fault_en)
      );

 
   decoder_6b_40b_en wait_cnt_decoder
     (
      .addr_in(f_decode_wfid),
      .out(decoded_decode_waitcnt),
      .en(f_decode_valid & f_decode_waitcnt)
      );


   dff exception_flop[(7+1)-1:0]
     (
      .q({f2_mem2cu_page_fault_en, f2_mem2cu_page_fault_tag}),
      .d({f_mem2cu_page_fault_en, f_mem2cu_page_fault_tag}),
      .clk(clk),
      .rst(rst)
      );
   
   dff valid_entry_out_flop[`WF_PER_CU-1:0]
     (
      .q(flopped_valid_entry_out),
      .d(valid_entry_out),
      .clk(clk),
      .rst(rst)
      );


   dff branch_issued_flop[`WF_PER_CU-1:0]
     (
      .q(flopped_decoded_branch_issued),
      .d(decoded_branch_issued),
      .clk(clk),
      .rst(rst)
      );

   dff idemp_wait_flop[`WF_PER_CU-1:0]
     (
      .q(flopped_idemp_wait_arry),
      .d(idemp_wait_arry),
      .clk(clk),
      .rst(rst)
      );

   assign valid_barrier_retire_wf_bitmap 
     = ( tracemon_barrier_retire_en )? tracemon_barrier_retire_wf_bitmap : 
       {`WF_PER_CU{1'b0}};

   // Ask for new instructions when valid goes down (instruction is issued) or when
   // a barrier or a branch of a waitcnt retire.
   // Do not ask for new instructions when a branch was issued last cycle
   assign wave_valid_entries 
     = (  ( (valid_entry_out ^ flopped_valid_entry_out) & flopped_valid_entry_out ) | 
	  ( (idemp_wait_arry ^ flopped_idemp_wait_arry) & flopped_idemp_wait_arry ) |
	  valid_barrier_retire_wf_bitmap | decoded_decode_waitcnt | decoded_branch_retired/* | decoded_exception */ ) &
       ~flopped_decoded_branch_issued;   
endmodule
