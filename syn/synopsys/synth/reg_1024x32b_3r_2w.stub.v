module reg_1024x32b_3r_2w (
  rd0_addr,
  rd0_data,

  rd1_addr,
  rd1_data,

  rd2_addr,
  rd2_data,

  wr0_en,
  wr0_addr,
  wr0_data,

  wr1_en,
  wr1_addr,
  wr1_data,

  clk
);
output [127:0] rd0_data;
output [31:0] rd1_data;
output [31:0] rd2_data;
input [9:0] rd0_addr;
input [9:0] rd1_addr;
input [9:0] rd2_addr;
input [9:0] wr0_addr;
input [9:0] wr1_addr;
input wr0_en;
input [3:0] wr1_en;
input [31:0] wr0_data;
input [127:0] wr1_data;
input clk;
endmodule
