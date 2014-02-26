module issue
  (/*AUTOARG*/
   // Outputs
   salu_alu_select, simd0_alu_select, simd1_alu_select,
   simd2_alu_select, simd3_alu_select, simf0_alu_select,
   simf1_alu_select, simf2_alu_select, simf3_alu_select,
   lsu_lsu_select, fetchwave_wf_done_en, tracemon_barrier_retire_en,
   tracemon_waitcnt_retire_en, lsu_wfid, alu_wfid,
   fetchwave_wf_done_wf_id, fetch_wg_wfid,
   tracemon_waitcnt_retire_wfid, lsu_source_reg1, lsu_source_reg2,
   lsu_source_reg3, lsu_dest_reg, lsu_mem_sgpr, alu_source_reg1,
   alu_source_reg2, alu_source_reg3, alu_dest_reg1, alu_dest_reg2,
   lsu_imm_value0, alu_imm_value0, lsu_lds_base, lsu_imm_value1,
   lsu_opcode, alu_imm_value1, alu_opcode, alu_instr_pc, lsu_instr_pc,
   tracemon_waitcnt_retire_pc, tracemon_barrier_retire_pc,
   wave_valid_entries, tracemon_barrier_retire_wf_bitmap,
   // Inputs
   clk, rst, decode_branch, decode_barrier, decode_vcc_wr,
   decode_vcc_rd, decode_scc_wr, decode_scc_rd, decode_exec_rd,
   decode_exec_wr, decode_m0_rd, decode_m0_wr, decode_wf_halt,
   decode_valid, decode_waitcnt, vgpr_alu_wr_done,
   vgpr_alu_dest_reg_valid, vgpr_lsu_wr_done, sgpr_alu_wr_done,
   sgpr_lsu_instr_done, sgpr_valu_dest_reg_valid, simd0_alu_ready,
   simd1_alu_ready, simd2_alu_ready, simd3_alu_ready, simf0_alu_ready,
   simf1_alu_ready, simf2_alu_ready, simf3_alu_ready, salu_alu_ready,
   lsu_ready, exec_salu_wr_vcc_en, exec_salu_wr_exec_en,
   exec_salu_wr_scc_en, exec_salu_wr_m0_en, exec_valu_wr_vcc_en,
   salu_branch_en, salu_branch_taken, decode_fu,
   sgpr_alu_dest_reg_valid, vgpr_lsu_dest_reg_valid,
   sgpr_lsu_dest_reg_valid, fetch_wg_wf_count, decode_wfid,
   vgpr_alu_wr_done_wfid, vgpr_lsu_wr_done_wfid,
   sgpr_alu_wr_done_wfid, sgpr_lsu_instr_done_wfid, exec_salu_wr_wfid,
   exec_valu_wr_vcc_wfid, fetch_wg_wgid, salu_branch_wfid,
   sgpr_alu_dest_reg_addr, sgpr_lsu_dest_reg_addr,
   sgpr_valu_dest_addr, vgpr_alu_dest_reg_addr,
   vgpr_lsu_dest_reg_addr, decode_source_reg2, decode_source_reg3,
   decode_dest_reg2, decode_source_reg1, decode_source_reg4,
   decode_dest_reg1, decode_imm_value0, decode_lds_base,
   decode_instr_pc, decode_opcode, decode_imm_value1
   );
   input clk;
   input rst;
   input decode_branch, decode_barrier, decode_vcc_wr, decode_vcc_rd, decode_scc_wr,
         decode_scc_rd, decode_exec_rd, decode_exec_wr, decode_m0_rd, decode_m0_wr,
         decode_wf_halt, decode_valid, decode_waitcnt, 
	 vgpr_alu_wr_done, vgpr_alu_dest_reg_valid,
         vgpr_lsu_wr_done, sgpr_alu_wr_done, sgpr_lsu_instr_done, sgpr_valu_dest_reg_valid,
	 simd0_alu_ready, simd1_alu_ready, simd2_alu_ready, simd3_alu_ready, 
	 simf0_alu_ready, simf1_alu_ready, simf2_alu_ready, simf3_alu_ready, 
	 salu_alu_ready, lsu_ready,
	 exec_salu_wr_vcc_en, exec_salu_wr_exec_en, exec_salu_wr_scc_en, exec_salu_wr_m0_en,
         exec_valu_wr_vcc_en, salu_branch_en, salu_branch_taken;
   input [1:0] decode_fu, sgpr_alu_dest_reg_valid;
   input [3:0] vgpr_lsu_dest_reg_valid, sgpr_lsu_dest_reg_valid, fetch_wg_wf_count;
   input [5:0] decode_wfid, vgpr_alu_wr_done_wfid, vgpr_lsu_wr_done_wfid,
               sgpr_alu_wr_done_wfid, sgpr_lsu_instr_done_wfid, exec_salu_wr_wfid,
               exec_valu_wr_vcc_wfid, fetch_wg_wgid, salu_branch_wfid;
   input [8:0] sgpr_alu_dest_reg_addr, sgpr_lsu_dest_reg_addr, sgpr_valu_dest_addr;
   input [9:0] vgpr_alu_dest_reg_addr, vgpr_lsu_dest_reg_addr;
   input [12:0] decode_source_reg2, decode_source_reg3, decode_dest_reg2;
   input [13:0] decode_source_reg1, decode_source_reg4, decode_dest_reg1;
   input [15:0] decode_imm_value0, decode_lds_base;
   input [31:0] decode_instr_pc, decode_opcode, decode_imm_value1;
   output 	salu_alu_select, simd0_alu_select, simd1_alu_select, simd2_alu_select,
		simd3_alu_select, simf0_alu_select, simf1_alu_select, simf2_alu_select,
		simf3_alu_select, lsu_lsu_select, fetchwave_wf_done_en, tracemon_barrier_retire_en,
		tracemon_waitcnt_retire_en;
   output [5:0] lsu_wfid, alu_wfid, fetchwave_wf_done_wf_id, fetch_wg_wfid,
		tracemon_waitcnt_retire_wfid;
   output [11:0] lsu_source_reg1, lsu_source_reg2, lsu_source_reg3, lsu_dest_reg,
		 lsu_mem_sgpr, alu_source_reg1, alu_source_reg2, alu_source_reg3, alu_dest_reg1,
		 alu_dest_reg2;
   output [15:0] lsu_imm_value0, alu_imm_value0, lsu_lds_base;
   output [31:0] lsu_imm_value1, lsu_opcode, alu_imm_value1, alu_opcode,
		 alu_instr_pc, lsu_instr_pc, tracemon_waitcnt_retire_pc, tracemon_barrier_retire_pc;
   output [39:0] wave_valid_entries;
   output [39:0] tracemon_barrier_retire_wf_bitmap;
endmodule
