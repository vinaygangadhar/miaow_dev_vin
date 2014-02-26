module reg_256x32b_3r_2w
(
  rd0_data, rd1_data, rd2_data,
  clk,
  rd0_addr, rd1_addr, rd2_addr,
  wr0_addr, wr1_addr,
  wr0_en, wr1_en, wr0_data, wr1_data
);
input clk;
output [31:0] rd0_data;
output [31:0] rd1_data;
output [31:0] rd2_data;
input [7:0] 	  rd0_addr;
input [7:0] 	  rd1_addr;
input [7:0] 	  rd2_addr;
input [7:0] 	  wr0_addr;
input [7:0] 	  wr1_addr;
input 	  wr0_en;
input 	  wr1_en;
input [31:0]   wr0_data;
input [31:0]   wr1_data;
endmodule
