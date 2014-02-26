module rfa(
      simd0_queue_entry_valid,
      simd1_queue_entry_valid,
      simd2_queue_entry_valid,
      simd3_queue_entry_valid,
      simf0_queue_entry_valid,
      simf1_queue_entry_valid,
      simf2_queue_entry_valid,
      simf3_queue_entry_valid,
      simd0_queue_entry_serviced,
      simd1_queue_entry_serviced,
      simd2_queue_entry_serviced,
      simd3_queue_entry_serviced,
      simf0_queue_entry_serviced,
      simf1_queue_entry_serviced,
      simf2_queue_entry_serviced,
      simf3_queue_entry_serviced,
      execvgprsgpr_select_fu,
      clk,
      rst
 );

input clk;

input rst;

input simd0_queue_entry_valid, simd1_queue_entry_valid, simd2_queue_entry_valid,
         simd3_queue_entry_valid, simf0_queue_entry_valid, simf1_queue_entry_valid,
         simf2_queue_entry_valid, simf3_queue_entry_valid;

output simd0_queue_entry_serviced, simd1_queue_entry_serviced, simd2_queue_entry_serviced,
         simd3_queue_entry_serviced, simf0_queue_entry_serviced, simf1_queue_entry_serviced,
         simf2_queue_entry_serviced, simf3_queue_entry_serviced;
output[15:0] execvgprsgpr_select_fu;


wire [15:0] entry_valid;
wire [15:0] entry_serviced;

wire [15:0] shifted_valid;
wire [3:0] highest_priority, next_highest_priority;
wire [3:0] cur_priority;
wire [31:0] dummy_entry_serviced;
wire [31:0] dummy_next_highest_priority;

assign entry_valid = {8'b0, simf3_queue_entry_valid, simf2_queue_entry_valid,
                        simf1_queue_entry_valid, simf0_queue_entry_valid,
                        simd3_queue_entry_valid, simd2_queue_entry_valid,
                        simd1_queue_entry_valid, simd0_queue_entry_valid};

assign {simf3_queue_entry_serviced, simf2_queue_entry_serviced,
         simf1_queue_entry_serviced, simf0_queue_entry_serviced,
         simd3_queue_entry_serviced, simd2_queue_entry_serviced,
         simd1_queue_entry_serviced, simd0_queue_entry_serviced} = entry_serviced[7:0];

assign execvgprsgpr_select_fu = entry_serviced;

dff_en high_pr_flop[3:0] (highest_priority, next_highest_priority, |entry_valid, clk, rst);

circular_shift circ_shift (
                           .out(shifted_valid),
                           .in(entry_valid),
                           .shift_amount(highest_priority)
                           );

priority_encoder_16_to_4 priority_encoder (
                                 .out(cur_priority),
                                 .in(shifted_valid),
                                 .enable(1'b1)
                                 );

assign dummy_entry_serviced = cur_priority + highest_priority;
assign dummy_next_highest_priority = dummy_entry_serviced + 1;
assign next_highest_priority = dummy_next_highest_priority[3:0];

decoder_param_en #(.BITS(4), .SIZE(16)) entry_serviced_decoder (.out(entry_serviced), .in(dummy_entry_serviced[3:0]), .en(|entry_valid));

endmodule
