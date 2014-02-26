module reg_512x32b_3r_3w (
  rd0_data, rd1_data, rd2_data,
  clk,
  rd0_addr, rd1_addr, rd2_addr,
  wr0_addr, wr1_addr, wr2_addr,
  wr0_en, wr1_en, wr2_en, wr0_data, wr1_data, wr2_data
);
input clk;
output [127:0] rd0_data;
output [63:0] rd1_data;
output [63:0] rd2_data;
input [8:0] rd0_addr;
input [8:0] rd1_addr;
input [8:0] rd2_addr;
input [8:0] wr0_addr;
input [8:0] wr1_addr;
input [8:0] wr2_addr;
input [3:0] wr0_en;
input [1:0] wr1_en;
input wr2_en;
input [127:0] wr0_data;
input [63:0] wr1_data;
input [63:0] wr2_data;
endmodule
