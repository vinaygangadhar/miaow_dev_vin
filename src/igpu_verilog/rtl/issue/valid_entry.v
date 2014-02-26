module valid_entry
  (/*AUTOARG*/
   // Outputs
   valid_entry_out,
   // Inputs
   clk, rst, f_decode_valid, f_decode_wf_halt, f_decode_barrier,
   f_salu_branch_en, f_salu_branch_taken, lsu_valid, alu_valid,
   f_decode_waitcnt, f_decode_idemp_barrier, f_mem2cu_page_fault_en,
   f_decode_wfid, lsu_wfid, alu_wfid, f_salu_branch_wfid,
   f_mem2cu_page_fault_tag
   );

   // Valid entry is set at decode and cleared at issue

   input clk,rst;
   input f_decode_valid, f_decode_wf_halt, f_decode_barrier, 
	 f_salu_branch_en, f_salu_branch_taken, lsu_valid, alu_valid,
	 f_decode_waitcnt, f_decode_idemp_barrier, f_mem2cu_page_fault_en;
   input [`WF_ID_LENGTH-1:0] f_decode_wfid, lsu_wfid, alu_wfid, 
			     f_salu_branch_wfid;
   input [6:0] 		     f_mem2cu_page_fault_tag;
   
   
   wire 		     decode_init_en;
   wire [`WF_PER_CU-1:0]     decoded_init_instr, decoded_lsu_issue, 
			     decoded_alu_issue, decoded_branch_taken,
			     decoded_exception, next_valid_entry;

   output [`WF_PER_CU-1:0]   valid_entry_out;

   assign decode_init_en = f_decode_valid & ~f_decode_wf_halt & ~f_decode_barrier & ~f_decode_waitcnt & ~f_decode_idemp_barrier;

   decoder_6b_40b_en init_instr_decoder(
					.addr_in(f_decode_wfid),
					.out(decoded_init_instr),
					.en(decode_init_en)
					);

   decoder_6b_40b_en lsu_issue_decoder(
				       .addr_in(lsu_wfid),
				       .out(decoded_lsu_issue),
				       .en(lsu_valid)
				       );

   decoder_6b_40b_en alu_issue_decoder(
				       .addr_in(alu_wfid),
				       .out(decoded_alu_issue),
				       .en(alu_valid)
				       );

   decoder_6b_40b_en exception_decoder(
				       .addr_in(f_mem2cu_page_fault_tag[5:0]),
				       .out(decoded_exception),
				       .en(f_mem2cu_page_fault_en)
				       );

   decoder_6b_40b_en branch_taken_decoder(
				       .addr_in(f_salu_branch_wfid),
				       .out(decoded_branch_taken),
				       .en((f_salu_branch_en & f_salu_branch_taken))
				       );

   dff valid_reg[`WF_PER_CU-1:0] 
     (
      .q(valid_entry_out),
      .d(next_valid_entry),
      .clk(clk),
      .rst(rst)
      );

   
   assign next_valid_entry = (valid_entry_out | (decoded_init_instr)) & 
			     ~(decoded_alu_issue | decoded_lsu_issue | decoded_branch_taken | decoded_exception);
   
   
endmodule
