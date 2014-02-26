module counter (count, clk, rst);
  output [2:0] count;
  input clk;
  input rst;

  dff f1(count[0],~count[2],clk,rst);
  dff f2(count[1],count[0],clk,rst);
  dff f3(count[2],count[1],clk,rst);
endmodule
/*
module dff(C,R_,D,Q);
  input C;
  input R_;
  input D;
  output Q;
  reg Q;
  always @(posedge C or negedge R_) begin
    if (~R_) begin
      Q <= 1'b0;
    end
    else begin
      Q <= D;
    end
  end
endmodule
*/
