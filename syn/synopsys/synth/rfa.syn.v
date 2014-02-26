
module rfa ( simd0_queue_entry_valid, simd1_queue_entry_valid, 
        simd2_queue_entry_valid, simd3_queue_entry_valid, 
        simf0_queue_entry_valid, simf1_queue_entry_valid, 
        simf2_queue_entry_valid, simf3_queue_entry_valid, 
        simd0_queue_entry_serviced, simd1_queue_entry_serviced, 
        simd2_queue_entry_serviced, simd3_queue_entry_serviced, 
        simf0_queue_entry_serviced, simf1_queue_entry_serviced, 
        simf2_queue_entry_serviced, simf3_queue_entry_serviced, 
        execvgprsgpr_select_fu, clk, rst );
  output [15:0] execvgprsgpr_select_fu;
  input simd0_queue_entry_valid, simd1_queue_entry_valid,
         simd2_queue_entry_valid, simd3_queue_entry_valid,
         simf0_queue_entry_valid, simf1_queue_entry_valid,
         simf2_queue_entry_valid, simf3_queue_entry_valid, clk, rst;
  output simd0_queue_entry_serviced, simd1_queue_entry_serviced,
         simd2_queue_entry_serviced, simd3_queue_entry_serviced,
         simf0_queue_entry_serviced, simf1_queue_entry_serviced,
         simf2_queue_entry_serviced, simf3_queue_entry_serviced;
  wire   \high_pr_flop[0]/d_int , \high_pr_flop[1]/d_int ,
         \high_pr_flop[2]/d_int , \high_pr_flop[3]/d_int , n50, n51, n52, n53,
         n54, n55, n56, n57, n58, n59, n60, n61, n62, n63, n64, n67, n68, n69,
         n70, n71, n72, n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83,
         n84, n85, n86, n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97,
         n98, n99, n100, n101, n102, n103, n104, n105, n106, n107, n108, n109,
         n110, n111, n112, n113, n114, n115, n116, n117, n118, n119, n120,
         n121, n122, n123, n124, n125, n126, n127, \add_73/carry[3] ,
         \add_73/carry[2] , \add_72/carry[3] , \add_72/carry[2] ,
         \add_72/carry[1] , n128, n129, n138, n139, n140, n141, n142, n143,
         n144, n145, n146, n147, n148, n149, n150, n151, n152, n153;
  wire   [3:0] highest_priority;
  wire   [3:0] cur_priority;
  wire   [4:0] dummy_entry_serviced;
  wire   [3:0] dummy_next_highest_priority;

  DFFARX1_RVT \high_pr_flop[3]/dff_0/state_reg  ( .D(\high_pr_flop[3]/d_int ), 
        .CLK(clk), .RSTB(n153), .Q(highest_priority[3]), .QN(n53) );
  DFFARX1_RVT \high_pr_flop[0]/dff_0/state_reg  ( .D(\high_pr_flop[0]/d_int ), 
        .CLK(clk), .RSTB(n153), .Q(highest_priority[0]), .QN(n50) );
  DFFARX1_RVT \high_pr_flop[1]/dff_0/state_reg  ( .D(\high_pr_flop[1]/d_int ), 
        .CLK(clk), .RSTB(n153), .Q(highest_priority[1]), .QN(n51) );
  DFFARX1_RVT \high_pr_flop[2]/dff_0/state_reg  ( .D(\high_pr_flop[2]/d_int ), 
        .CLK(clk), .RSTB(n153), .Q(highest_priority[2]), .QN(n52) );
  AO22X1_RVT U22 ( .A1(dummy_next_highest_priority[3]), .A2(n54), .A3(n141), 
        .A4(highest_priority[3]), .Y(\high_pr_flop[3]/d_int ) );
  AO22X1_RVT U23 ( .A1(dummy_next_highest_priority[2]), .A2(n54), .A3(
        highest_priority[2]), .A4(n141), .Y(\high_pr_flop[2]/d_int ) );
  AO22X1_RVT U24 ( .A1(dummy_next_highest_priority[1]), .A2(n54), .A3(
        highest_priority[1]), .A4(n141), .Y(\high_pr_flop[1]/d_int ) );
  AO22X1_RVT U25 ( .A1(n140), .A2(n54), .A3(highest_priority[0]), .A4(n141), 
        .Y(\high_pr_flop[0]/d_int ) );
  AND2X1_RVT U26 ( .A1(n55), .A2(n56), .Y(execvgprsgpr_select_fu[9]) );
  AND2X1_RVT U27 ( .A1(n57), .A2(n55), .Y(execvgprsgpr_select_fu[8]) );
  AND2X1_RVT U28 ( .A1(n58), .A2(n59), .Y(simf3_queue_entry_serviced) );
  AND2X1_RVT U29 ( .A1(n60), .A2(n58), .Y(simf2_queue_entry_serviced) );
  AND2X1_RVT U30 ( .A1(n61), .A2(n59), .Y(simf1_queue_entry_serviced) );
  AND2X1_RVT U31 ( .A1(n61), .A2(n60), .Y(simf0_queue_entry_serviced) );
  AND2X1_RVT U32 ( .A1(n62), .A2(n59), .Y(simd3_queue_entry_serviced) );
  AND2X1_RVT U33 ( .A1(n62), .A2(n60), .Y(simd2_queue_entry_serviced) );
  AND2X1_RVT U34 ( .A1(n59), .A2(n55), .Y(simd1_queue_entry_serviced) );
  AND2X1_RVT U35 ( .A1(n63), .A2(dummy_entry_serviced[0]), .Y(n59) );
  AND2X1_RVT U36 ( .A1(n58), .A2(n56), .Y(execvgprsgpr_select_fu[15]) );
  AND2X1_RVT U37 ( .A1(n58), .A2(n57), .Y(execvgprsgpr_select_fu[14]) );
  AND2X1_RVT U38 ( .A1(dummy_entry_serviced[2]), .A2(dummy_entry_serviced[1]), 
        .Y(n58) );
  AND2X1_RVT U39 ( .A1(n61), .A2(n56), .Y(execvgprsgpr_select_fu[13]) );
  AND2X1_RVT U40 ( .A1(n61), .A2(n57), .Y(execvgprsgpr_select_fu[12]) );
  AND2X1_RVT U41 ( .A1(dummy_entry_serviced[2]), .A2(n139), .Y(n61) );
  AND2X1_RVT U42 ( .A1(n62), .A2(n56), .Y(execvgprsgpr_select_fu[11]) );
  AND2X1_RVT U43 ( .A1(dummy_entry_serviced[0]), .A2(n64), .Y(n56) );
  AND2X1_RVT U44 ( .A1(n62), .A2(n57), .Y(execvgprsgpr_select_fu[10]) );
  AND2X1_RVT U45 ( .A1(n64), .A2(n140), .Y(n57) );
  AND2X1_RVT U46 ( .A1(dummy_entry_serviced[3]), .A2(n54), .Y(n64) );
  AND2X1_RVT U47 ( .A1(dummy_entry_serviced[1]), .A2(n138), .Y(n62) );
  AND2X1_RVT U48 ( .A1(n60), .A2(n55), .Y(simd0_queue_entry_serviced) );
  AND2X1_RVT U49 ( .A1(n139), .A2(n138), .Y(n55) );
  AND2X1_RVT U50 ( .A1(n63), .A2(n140), .Y(n60) );
  NOR2X0_RVT U51 ( .A1(n141), .A2(dummy_entry_serviced[3]), .Y(n63) );
  AND4X1_RVT U53 ( .A1(n67), .A2(n68), .A3(n144), .A4(n69), .Y(cur_priority[3]) );
  AND3X1_RVT U54 ( .A1(n149), .A2(n70), .A3(n71), .Y(n69) );
  NAND4X0_RVT U55 ( .A1(n150), .A2(n72), .A3(n145), .A4(n142), .Y(n68) );
  OA21X1_RVT U56 ( .A1(n74), .A2(n75), .A3(n71), .Y(cur_priority[2]) );
  AND4X1_RVT U57 ( .A1(n151), .A2(n76), .A3(n146), .A4(n77), .Y(n71) );
  NAND2X0_RVT U58 ( .A1(n149), .A2(n70), .Y(n75) );
  NAND3X0_RVT U59 ( .A1(n67), .A2(n78), .A3(n144), .Y(n74) );
  NAND4X0_RVT U60 ( .A1(n73), .A2(n152), .A3(n145), .A4(n79), .Y(n78) );
  AND2X1_RVT U61 ( .A1(n150), .A2(n72), .Y(n79) );
  NAND3X0_RVT U62 ( .A1(n80), .A2(n147), .A3(n143), .Y(n73) );
  AND3X1_RVT U63 ( .A1(n82), .A2(n77), .A3(n146), .Y(cur_priority[1]) );
  NAND3X0_RVT U64 ( .A1(n76), .A2(n84), .A3(n151), .Y(n82) );
  NAND3X0_RVT U65 ( .A1(n67), .A2(n86), .A3(n144), .Y(n84) );
  NAND3X0_RVT U66 ( .A1(n70), .A2(n88), .A3(n149), .Y(n86) );
  NAND3X0_RVT U67 ( .A1(n90), .A2(n152), .A3(n145), .Y(n88) );
  NAND3X0_RVT U68 ( .A1(n72), .A2(n92), .A3(n150), .Y(n90) );
  NAND3X0_RVT U69 ( .A1(n80), .A2(n81), .A3(n143), .Y(n92) );
  NAND2X0_RVT U70 ( .A1(n148), .A2(n95), .Y(n81) );
  OA21X1_RVT U71 ( .A1(n97), .A2(n83), .A3(n77), .Y(cur_priority[0]) );
  NAND2X0_RVT U72 ( .A1(n98), .A2(n53), .Y(n77) );
  AO22X1_RVT U73 ( .A1(n99), .A2(n53), .A3(n100), .A4(n101), .Y(n83) );
  OA21X1_RVT U74 ( .A1(n102), .A2(n85), .A3(n76), .Y(n97) );
  AOI22X1_RVT U75 ( .A1(n103), .A2(n53), .A3(n104), .A4(n101), .Y(n76) );
  AO22X1_RVT U76 ( .A1(n105), .A2(n53), .A3(n101), .A4(n106), .Y(n85) );
  OA21X1_RVT U77 ( .A1(n107), .A2(n87), .A3(n67), .Y(n102) );
  AOI22X1_RVT U78 ( .A1(n101), .A2(n108), .A3(n109), .A4(n53), .Y(n67) );
  AND2X1_RVT U79 ( .A1(highest_priority[2]), .A2(highest_priority[3]), .Y(n101) );
  AO22X1_RVT U80 ( .A1(n110), .A2(highest_priority[3]), .A3(n111), .A4(n53), 
        .Y(n87) );
  OA21X1_RVT U81 ( .A1(n112), .A2(n89), .A3(n70), .Y(n107) );
  AOI22X1_RVT U82 ( .A1(n113), .A2(highest_priority[3]), .A3(n114), .A4(n53), 
        .Y(n70) );
  AO22X1_RVT U83 ( .A1(n115), .A2(highest_priority[3]), .A3(
        simf3_queue_entry_valid), .A4(n53), .Y(n89) );
  OA21X1_RVT U84 ( .A1(n116), .A2(n91), .A3(n152), .Y(n112) );
  AO22X1_RVT U85 ( .A1(highest_priority[2]), .A2(n109), .A3(n108), .A4(n52), 
        .Y(n98) );
  AO21X1_RVT U86 ( .A1(n100), .A2(highest_priority[2]), .A3(n99), .Y(n91) );
  AO22X1_RVT U87 ( .A1(highest_priority[2]), .A2(n111), .A3(n117), .A4(n52), 
        .Y(n99) );
  OA21X1_RVT U88 ( .A1(n118), .A2(n93), .A3(n72), .Y(n116) );
  AOI21X1_RVT U89 ( .A1(n104), .A2(highest_priority[2]), .A3(n103), .Y(n72) );
  AO22X1_RVT U90 ( .A1(highest_priority[2]), .A2(n114), .A3(n119), .A4(n52), 
        .Y(n103) );
  AO21X1_RVT U91 ( .A1(highest_priority[2]), .A2(n106), .A3(n105), .Y(n93) );
  AO22X1_RVT U92 ( .A1(n120), .A2(n52), .A3(simf3_queue_entry_valid), .A4(
        highest_priority[2]), .Y(n105) );
  OA21X1_RVT U93 ( .A1(n121), .A2(n94), .A3(n80), .Y(n118) );
  NOR2X0_RVT U94 ( .A1(n109), .A2(n108), .Y(n80) );
  AO22X1_RVT U95 ( .A1(n122), .A2(n51), .A3(highest_priority[1]), .A4(n123), 
        .Y(n108) );
  AO22X1_RVT U96 ( .A1(highest_priority[1]), .A2(n114), .A3(n124), .A4(n51), 
        .Y(n109) );
  OR2X1_RVT U97 ( .A1(n110), .A2(n111), .Y(n94) );
  AO22X1_RVT U98 ( .A1(n125), .A2(n51), .A3(simf3_queue_entry_valid), .A4(
        highest_priority[1]), .Y(n111) );
  AO21X1_RVT U99 ( .A1(highest_priority[2]), .A2(n117), .A3(n100), .Y(n110) );
  AND3X1_RVT U100 ( .A1(highest_priority[0]), .A2(highest_priority[1]), .A3(
        simd0_queue_entry_valid), .Y(n100) );
  AO22X1_RVT U101 ( .A1(n126), .A2(n51), .A3(highest_priority[1]), .A4(n127), 
        .Y(n117) );
  AND2X1_RVT U102 ( .A1(n95), .A2(n96), .Y(n121) );
  OR2X1_RVT U103 ( .A1(n115), .A2(simf3_queue_entry_valid), .Y(n96) );
  AO21X1_RVT U104 ( .A1(highest_priority[2]), .A2(n120), .A3(n106), .Y(n115)
         );
  AO22X1_RVT U105 ( .A1(highest_priority[1]), .A2(n126), .A3(
        simd0_queue_entry_valid), .A4(highest_priority[0]), .Y(n106) );
  AO21X1_RVT U106 ( .A1(simd2_queue_entry_valid), .A2(highest_priority[0]), 
        .A3(simd1_queue_entry_valid), .Y(n126) );
  AO21X1_RVT U107 ( .A1(highest_priority[1]), .A2(n125), .A3(n127), .Y(n120)
         );
  AO21X1_RVT U108 ( .A1(simf0_queue_entry_valid), .A2(highest_priority[0]), 
        .A3(simd3_queue_entry_valid), .Y(n127) );
  AO21X1_RVT U109 ( .A1(simf2_queue_entry_valid), .A2(highest_priority[0]), 
        .A3(simf1_queue_entry_valid), .Y(n125) );
  NOR2X0_RVT U110 ( .A1(n113), .A2(n114), .Y(n95) );
  AO22X1_RVT U111 ( .A1(simf3_queue_entry_valid), .A2(highest_priority[0]), 
        .A3(simf2_queue_entry_valid), .A4(n50), .Y(n114) );
  AO21X1_RVT U112 ( .A1(highest_priority[2]), .A2(n119), .A3(n104), .Y(n113)
         );
  AND2X1_RVT U113 ( .A1(highest_priority[1]), .A2(n122), .Y(n104) );
  AO22X1_RVT U114 ( .A1(simd1_queue_entry_valid), .A2(highest_priority[0]), 
        .A3(simd0_queue_entry_valid), .A4(n50), .Y(n122) );
  AO21X1_RVT U115 ( .A1(highest_priority[1]), .A2(n124), .A3(n123), .Y(n119)
         );
  AO22X1_RVT U116 ( .A1(simd3_queue_entry_valid), .A2(highest_priority[0]), 
        .A3(simd2_queue_entry_valid), .A4(n50), .Y(n123) );
  AO22X1_RVT U117 ( .A1(simf1_queue_entry_valid), .A2(highest_priority[0]), 
        .A3(simf0_queue_entry_valid), .A4(n50), .Y(n124) );
  HADDX1_RVT \add_73/U1_1_1  ( .A0(dummy_entry_serviced[1]), .B0(
        dummy_entry_serviced[0]), .C1(\add_73/carry[2] ), .SO(
        dummy_next_highest_priority[1]) );
  HADDX1_RVT \add_73/U1_1_2  ( .A0(dummy_entry_serviced[2]), .B0(
        \add_73/carry[2] ), .C1(\add_73/carry[3] ), .SO(
        dummy_next_highest_priority[2]) );
  HADDX1_RVT \add_73/U1_1_3  ( .A0(dummy_entry_serviced[3]), .B0(
        \add_73/carry[3] ), .SO(dummy_next_highest_priority[3]) );
  FADDX1_RVT \add_72/U1_0  ( .A(cur_priority[0]), .B(highest_priority[0]), 
        .CI(1'b0), .CO(\add_72/carry[1] ), .S(dummy_entry_serviced[0]) );
  FADDX1_RVT \add_72/U1_1  ( .A(cur_priority[1]), .B(highest_priority[1]), 
        .CI(\add_72/carry[1] ), .CO(\add_72/carry[2] ), .S(
        dummy_entry_serviced[1]) );
  FADDX1_RVT \add_72/U1_2  ( .A(cur_priority[2]), .B(highest_priority[2]), 
        .CI(\add_72/carry[2] ), .CO(\add_72/carry[3] ), .S(
        dummy_entry_serviced[2]) );
  FADDX1_RVT \add_72/U1_3  ( .A(cur_priority[3]), .B(highest_priority[3]), 
        .CI(\add_72/carry[3] ), .S(dummy_entry_serviced[3]) );
  NAND2X0_RVT U118 ( .A1(n128), .A2(n129), .Y(n54) );
  NOR4X1_RVT U119 ( .A1(simf0_queue_entry_valid), .A2(simf1_queue_entry_valid), 
        .A3(simf2_queue_entry_valid), .A4(simf3_queue_entry_valid), .Y(n128)
         );
  NOR4X1_RVT U120 ( .A1(simd0_queue_entry_valid), .A2(simd1_queue_entry_valid), 
        .A3(simd2_queue_entry_valid), .A4(simd3_queue_entry_valid), .Y(n129)
         );
  NBUFFX2_RVT U121 ( .A(simf3_queue_entry_serviced), .Y(
        execvgprsgpr_select_fu[7]) );
  NBUFFX2_RVT U122 ( .A(simf2_queue_entry_serviced), .Y(
        execvgprsgpr_select_fu[6]) );
  NBUFFX2_RVT U123 ( .A(simf1_queue_entry_serviced), .Y(
        execvgprsgpr_select_fu[5]) );
  NBUFFX2_RVT U124 ( .A(simf0_queue_entry_serviced), .Y(
        execvgprsgpr_select_fu[4]) );
  NBUFFX2_RVT U125 ( .A(simd3_queue_entry_serviced), .Y(
        execvgprsgpr_select_fu[3]) );
  NBUFFX2_RVT U126 ( .A(simd2_queue_entry_serviced), .Y(
        execvgprsgpr_select_fu[2]) );
  NBUFFX2_RVT U127 ( .A(simd1_queue_entry_serviced), .Y(
        execvgprsgpr_select_fu[1]) );
  NBUFFX2_RVT U128 ( .A(simd0_queue_entry_serviced), .Y(
        execvgprsgpr_select_fu[0]) );
  INVX1_RVT U130 ( .A(dummy_entry_serviced[2]), .Y(n138) );
  INVX1_RVT U131 ( .A(dummy_entry_serviced[1]), .Y(n139) );
  INVX1_RVT U132 ( .A(dummy_entry_serviced[0]), .Y(n140) );
  INVX1_RVT U133 ( .A(n54), .Y(n141) );
  INVX1_RVT U134 ( .A(n73), .Y(n142) );
  INVX1_RVT U135 ( .A(n94), .Y(n143) );
  INVX1_RVT U136 ( .A(n87), .Y(n144) );
  INVX1_RVT U137 ( .A(n91), .Y(n145) );
  INVX1_RVT U138 ( .A(n83), .Y(n146) );
  INVX1_RVT U139 ( .A(n81), .Y(n147) );
  INVX1_RVT U140 ( .A(n96), .Y(n148) );
  INVX1_RVT U141 ( .A(n89), .Y(n149) );
  INVX1_RVT U142 ( .A(n93), .Y(n150) );
  INVX1_RVT U143 ( .A(n85), .Y(n151) );
  INVX1_RVT U144 ( .A(n98), .Y(n152) );
  INVX1_RVT U145 ( .A(rst), .Y(n153) );
endmodule

