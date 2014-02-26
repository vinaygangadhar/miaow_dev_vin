module sgpr( 
      lsu_source1_addr,
      lsu_source2_addr,
      lsu_dest_addr,
      lsu_dest_data,
      lsu_dest_wr_en,
      lsu_instr_done_wfid,
      lsu_instr_done,
      lsu_source1_rd_en,
      lsu_source2_rd_en,
      simd0_rd_addr,
      simd0_rd_en,
      simd1_rd_addr,
      simd1_rd_en,
      simd2_rd_addr,
      simd2_rd_en,
      simd3_rd_addr,
      simd3_rd_en,
      simd0_wr_addr,
      simd0_wr_en,
      simd0_wr_data,
      simd1_wr_addr,
      simd1_wr_en,
      simd1_wr_data,
      simd2_wr_addr,
      simd2_wr_en,
      simd2_wr_data,
      simd3_wr_addr,
      simd3_wr_en,
      simd3_wr_data,
      simd0_wr_mask,
      simd1_wr_mask,
      simd2_wr_mask,
      simd3_wr_mask,
      simf0_rd_addr,
      simf0_rd_en,
      simf1_rd_addr,
      simf1_rd_en,
      simf2_rd_addr,
      simf2_rd_en,
      simf3_rd_addr,
      simf3_rd_en,
      simf0_wr_addr,
      simf0_wr_en,
      simf0_wr_data,
      simf1_wr_addr,
      simf1_wr_en,
      simf1_wr_data,
      simf2_wr_addr,
      simf2_wr_en,
      simf2_wr_data,
      simf3_wr_addr,
      simf3_wr_en,
      simf3_wr_data,
      simf0_wr_mask,
      simf1_wr_mask,
      simf2_wr_mask,
      simf3_wr_mask,
      salu_dest_data,
      salu_dest_addr,
      salu_dest_wr_en,
      salu_source2_addr,
      salu_source1_addr,
      salu_instr_done_wfid,
      salu_instr_done,
      salu_source1_rd_en,
      salu_source2_rd_en,
      rfa_select_fu,
      lsu_source1_data,
      lsu_source2_data,
      simd_rd_data,
      simf_rd_data,
      salu_source2_data,
      salu_source1_data,
      issue_alu_wr_done_wfid,
      issue_alu_wr_done,
      issue_alu_dest_reg_addr,
      issue_alu_dest_reg_valid,
      issue_lsu_instr_done_wfid,
      issue_lsu_instr_done,
      issue_lsu_dest_reg_addr,
      issue_lsu_dest_reg_valid,
      issue_valu_dest_reg_valid,
      issue_valu_dest_addr,
      clk,
      rst
 );

input clk;

input rst;
input salu_source1_rd_en,
      salu_source2_rd_en,
      lsu_source1_rd_en,
      lsu_source2_rd_en;

input lsu_instr_done, simd0_rd_en, simd1_rd_en, simd2_rd_en,
         simd3_rd_en, simd0_wr_en, simd1_wr_en, simd2_wr_en, simd3_wr_en, simf0_rd_en,
         simf1_rd_en, simf2_rd_en, simf3_rd_en, simf0_wr_en, simf1_wr_en, simf2_wr_en,
         simf3_wr_en, salu_instr_done;
input[1:0] salu_dest_wr_en;
input[3:0] lsu_dest_wr_en;
input[5:0] lsu_instr_done_wfid, salu_instr_done_wfid;
input[8:0] lsu_source1_addr, lsu_source2_addr, lsu_dest_addr, simd0_rd_addr,
         simd1_rd_addr, simd2_rd_addr, simd3_rd_addr, simd0_wr_addr, simd1_wr_addr,
         simd2_wr_addr, simd3_wr_addr, simf0_rd_addr, simf1_rd_addr, simf2_rd_addr,
         simf3_rd_addr, simf0_wr_addr, simf1_wr_addr, simf2_wr_addr, simf3_wr_addr,
         salu_dest_addr, salu_source2_addr, salu_source1_addr;
input[15:0] rfa_select_fu;
input[127:0] lsu_dest_data;
input[63:0] simd0_wr_data, simd1_wr_data, simd2_wr_data, simd3_wr_data,
         simf0_wr_data, simf1_wr_data, simf2_wr_data, simf3_wr_data, salu_dest_data,
         simd0_wr_mask, simd1_wr_mask, simd2_wr_mask, simd3_wr_mask,
         simf0_wr_mask, simf1_wr_mask, simf2_wr_mask, simf3_wr_mask;

output issue_alu_wr_done, issue_lsu_instr_done, issue_valu_dest_reg_valid;
output[3:0] issue_lsu_dest_reg_valid;
output [1:0] issue_alu_dest_reg_valid;
output[5:0] issue_alu_wr_done_wfid, issue_lsu_instr_done_wfid;
output[8:0] issue_alu_dest_reg_addr, issue_lsu_dest_reg_addr, issue_valu_dest_addr;
output[31:0] lsu_source2_data, simd_rd_data, simf_rd_data;
output[63:0] salu_source2_data, salu_source1_data;
output[127:0] lsu_source1_data;

///////////////////////////////
//Your code goes here - beware: script does not recognize changes
// into files. It ovewrites everithing without mercy. Save your work before running the script
///////////////////////////////
wire dummy;
assign dummy = rst;

wire [31:0] simx_rd_data;

wire [8:0] simx_muxed_rd_addr;
wire [31:0] simx_muxed_rd_data;
wire simx_muxed_rd_en;

wire simx_muxed_wr_en;
wire [8:0] simx_muxed_wr_addr;
wire [63:0] simx_muxed_wr_data;
wire [63:0] simx_rd_old_data;
wire [63:0] simx_wr_merged_data;
wire [63:0] simx_muxed_wr_mask;

wire [8:0] final_port0_addr;
wire [8:0] final_port1_addr;

wire [127:0] final_port0_data;
wire [63:0] final_port1_data;
wire [127:0] port0_distribute_data;
wire [127:0] port1_distribute_data;

assign issue_alu_wr_done_wfid = salu_instr_done_wfid;
assign issue_alu_wr_done = salu_instr_done;
assign issue_alu_dest_reg_addr = salu_dest_addr;
assign issue_alu_dest_reg_valid = salu_dest_wr_en;

assign issue_lsu_instr_done_wfid = lsu_instr_done_wfid;
assign issue_lsu_instr_done = lsu_instr_done;
assign issue_lsu_dest_reg_addr = lsu_dest_addr;
assign issue_lsu_dest_reg_valid = lsu_dest_wr_en;

//For writes from simx, read the old value using a ead port and modify only
//the bits specified by the wr mask
assign simx_wr_merged_data = (simx_muxed_wr_data & simx_muxed_wr_mask) | (simx_rd_old_data & (~simx_muxed_wr_mask));

reg_512x32b_3r_3w sgpr_reg_file(
.rd0_addr(final_port0_addr),
.rd0_data(final_port0_data),
.rd1_addr(final_port1_addr),
.rd1_data(final_port1_data),
.rd2_addr(simx_muxed_wr_addr),
.rd2_data(simx_rd_old_data),
.wr0_en(lsu_dest_wr_en),
.wr0_addr(lsu_dest_addr),
.wr0_data(lsu_dest_data),
.wr1_en(salu_dest_wr_en),
.wr1_addr(salu_dest_addr),
.wr1_data(salu_dest_data),
.wr2_en(simx_muxed_wr_en),
.wr2_addr(simx_muxed_wr_addr),
.wr2_data(simx_wr_merged_data),
.clk(clk)
);

sgpr_simx_rd_port_mux simx_rd_port_mux(
.port0_rd_en(simd0_rd_en),
.port0_rd_addr(simd0_rd_addr),
.port1_rd_en(simd1_rd_en),
.port1_rd_addr(simd1_rd_addr),
.port2_rd_en(simd2_rd_en),
.port2_rd_addr(simd2_rd_addr),
.port3_rd_en(simd3_rd_en),
.port3_rd_addr(simd3_rd_addr),
.port4_rd_en(simf0_rd_en),
.port4_rd_addr(simf0_rd_addr),
.port5_rd_en(simf1_rd_en),
.port5_rd_addr(simf1_rd_addr),
.port6_rd_en(simf2_rd_en),
.port6_rd_addr(simf2_rd_addr),
.port7_rd_en(simf3_rd_en),
.port7_rd_addr(simf3_rd_addr),
.port_rd_data(simx_rd_data),
.rd_addr(simx_muxed_rd_addr),
.rd_data(simx_muxed_rd_data),
.rd_en(simx_muxed_rd_en)
);
assign simd_rd_data = simx_rd_data;
assign simf_rd_data = simx_rd_data;

sgpr_3to1_rd_port_mux rd_port0_mux(
.port0_rd_en(lsu_source1_rd_en),
.port0_rd_addr(lsu_source1_addr),
.port1_rd_en(1'b0),
.port1_rd_addr(9'b0),
.port2_rd_en(salu_source1_rd_en),
.port2_rd_addr(salu_source1_addr),
.port_rd_data(port0_distribute_data),
.rd_addr(final_port0_addr),
.rd_data(final_port0_data)
);
assign lsu_source1_data = port0_distribute_data;
assign salu_source1_data = port0_distribute_data[63:0];

sgpr_3to1_rd_port_mux rd_port1_mux(
.port0_rd_en(lsu_source2_rd_en),
.port0_rd_addr(lsu_source2_addr),
.port1_rd_en(simx_muxed_rd_en),
.port1_rd_addr(simx_muxed_rd_addr),
.port2_rd_en(salu_source2_rd_en),
.port2_rd_addr(salu_source2_addr),
.port_rd_data(port1_distribute_data),
.rd_addr(final_port1_addr),
.rd_data({64'b0,final_port1_data})
);
assign lsu_source2_data = port1_distribute_data[31:0];
assign simx_muxed_rd_data = port1_distribute_data[31:0];
assign salu_source2_data = port1_distribute_data[63:0];

///////////////////////////////////////////
sgpr_simx_wr_port_mux simx_wr_port_mux(
.wr_port_select(rfa_select_fu),
.port0_wr_en(simd0_wr_en),
.port0_wr_addr(simd0_wr_addr),
.port0_wr_data(simd0_wr_data),
.port0_wr_mask(simd0_wr_mask),
.port1_wr_en(simd1_wr_en),
.port1_wr_addr(simd1_wr_addr),
.port1_wr_data(simd1_wr_data),
.port1_wr_mask(simd1_wr_mask),
.port2_wr_en(simd2_wr_en),
.port2_wr_addr(simd2_wr_addr),
.port2_wr_data(simd2_wr_data),
.port2_wr_mask(simd2_wr_mask),
.port3_wr_en(simd3_wr_en),
.port3_wr_addr(simd3_wr_addr),
.port3_wr_data(simd3_wr_data),
.port3_wr_mask(simd3_wr_mask),
.port4_wr_en(simf0_wr_en),
.port4_wr_addr(simf0_wr_addr),
.port4_wr_data(simf0_wr_data),
.port4_wr_mask(simf0_wr_mask),
.port5_wr_en(simf1_wr_en),
.port5_wr_addr(simf1_wr_addr),
.port5_wr_data(simf1_wr_data),
.port5_wr_mask(simf1_wr_mask),
.port6_wr_en(simf2_wr_en),
.port6_wr_addr(simf2_wr_addr),
.port6_wr_data(simf2_wr_data),
.port6_wr_mask(simf2_wr_mask),
.port7_wr_en(simf3_wr_en),
.port7_wr_addr(simf3_wr_addr),
.port7_wr_data(simf3_wr_data),
.port7_wr_mask(simf3_wr_mask),
.muxed_port_wr_en(simx_muxed_wr_en),
.muxed_port_wr_addr(simx_muxed_wr_addr),
.muxed_port_wr_data(simx_muxed_wr_data),
.muxed_port_wr_mask(simx_muxed_wr_mask)
);

assign issue_valu_dest_reg_valid = simx_muxed_wr_en;
assign issue_valu_dest_addr = simx_muxed_wr_addr;

endmodule
