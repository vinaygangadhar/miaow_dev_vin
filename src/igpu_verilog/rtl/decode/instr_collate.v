module instr_collate 
  (/*AUTOARG*/
   // Outputs
   out_instr, out_valid, out_pc, out_long,
   // Inputs
   in_wfid, in_instr, in_valid, in_pc, flush_valid, flush_wfid,
   in_long, clk, rst
   );

   input [5:0] in_wfid;
   input [31:0] in_instr;
   input 	in_valid;
   input [31:0] in_pc;

   input 	flush_valid;
   input[5:0] 	flush_wfid;
	
   
   output [63:0] out_instr;
   output 	 out_valid;
   output [31:0] out_pc;

   input 	 in_long;
   output 	 out_long;

   input 	 clk;
   input 	 rst;

   wire [`WF_PER_CU-1:0] valid_reg_in, valid_reg_out;
   
   wire [`WF_PER_CU-1:0] decoded_in_wfid, decoded_in_long, decoded_flush_valid;
   
   wire [31:0] 	 stored_instr;
   wire [31:0] 	 stored_pc;
   
   reg_40xX_1r_1w #(64) reg_instr_pc (
				      .rd_addr(in_wfid),
				      .rd_data({stored_instr,stored_pc}),
				      .wr_en(in_long&in_valid),
				      .wr_addr(in_wfid),
				      .wr_data({in_instr,in_pc}),
				      .clk(clk),
				      .rst(rst)
				      );

   // Valid state reg
   decoder_6b_40b_en in_wfid_decoder(
    .addr_in(in_wfid),
    .en(1'b1),
    .out(decoded_in_wfid));

   decoder_6b_40b_en in_long_decoder(
    .addr_in(in_wfid),
    .en(in_long),
    .out(decoded_in_long));

   decoder_6b_40b_en flush_valid_decoder(
    .addr_in(flush_wfid),
    .en(flush_valid),
    .out(decoded_flush_valid));

   assign valid_reg_in = ( (valid_reg_out & ~decoded_in_wfid) | decoded_in_long ) &  
		  ~decoded_flush_valid;
   
   dff reg_valid[`WF_PER_CU-1:0]
     (.q(valid_reg_out),
      .d(valid_reg_in),
      .clk(clk),
      .rst(rst)
      );

   mux_40xX_to_1xX valid_read_mux 
     (.out(out_long), 
      .in(valid_reg_out), 
      .select(in_wfid));
   
   assign out_instr = out_long ? {in_instr,stored_instr} : {32'b0,in_instr};
   assign out_pc = out_long ? stored_pc : in_pc;
   assign out_valid = in_valid & (~in_long);

endmodule
