// D-flipflop
// Copied from http://pages.cs.wisc.edu/~karu/courses/cs552/spring2009/handouts/verilog_code/dff.v
module dff (q, d, clk, rst);

    output         q;
    input          d;
    input          clk;
    input          rst;

    reg            state;

    assign #(1) q = state;

    always @(posedge clk) begin
      state = rst? 0 : d;
    end

endmodule
