module idemp_wait
  (/*AUTOARG*/
   // Outputs
   fetchwavedecode_recover_en, fetchwavedecode_recover_wfid,
   fetch_recover_pc, idemp_wait_arry,
   // Inputs
   clk, rst, f_decode_valid, f_decode_idemp_barrier,
   f_mem2cu_page_fault_en, f_mem2cu_page_fault_tag, mem_wait_arry,
   no_instr_inflight_array, f_decode_wfid, f_decode_instr_pc
   );

   input clk, rst;

   input f_decode_valid, f_decode_idemp_barrier, f_mem2cu_page_fault_en;

   input [6:0] f_mem2cu_page_fault_tag;
   input [`WF_PER_CU-1:0] mem_wait_arry, no_instr_inflight_array;
   input [`WF_ID_LENGTH-1:0] f_decode_wfid;
   input [31:0] 	    f_decode_instr_pc;
   
   output 		 fetchwavedecode_recover_en;
   
   output [`WF_ID_LENGTH-1:0] fetchwavedecode_recover_wfid;
   output [31:0] 	     fetch_recover_pc;
   output [`WF_PER_CU-1:0]    idemp_wait_arry;

   wire [`WF_PER_CU-1:0]      idemp_valid_decoded, idemp_waiting, next_idemp_waiting;

  decoder_6b_40b_en barrier_valid_decoder
     (
      .addr_in(f_decode_wfid),
      .en(f_decode_valid & f_decode_idemp_barrier),
      .out(idemp_valid_decoded)
      );
   

   dff  waiting_wf_reg[`WF_PER_CU-1:0]
     (
      .q(idemp_waiting),
      .d(next_idemp_waiting),
      .clk(clk),
      .rst(rst)
      );

   assign next_idemp_waiting 
     = ( idemp_waiting | idemp_valid_decoded ) &
       ~( idemp_waiting & ~mem_wait_arry & no_instr_inflight_array);
   			      
   reg_40xX_1r_1w #(32) wg_info_reg
     ( 
       .rd_addr(f_mem2cu_page_fault_tag[5:0]),
       .rd_data(fetch_recover_pc),
       .wr_en(f_decode_valid & f_decode_idemp_barrier),
       .wr_addr(f_decode_wfid),
       .wr_data(f_decode_instr_pc),
       .clk(clk),
       .rst(rst)
       );

   
   assign fetchwavedecode_recover_wfid = f_mem2cu_page_fault_tag[5:0];
   assign fetchwavedecode_recover_en = f_mem2cu_page_fault_en;

   assign idemp_wait_arry = idemp_waiting;
   


endmodule   
