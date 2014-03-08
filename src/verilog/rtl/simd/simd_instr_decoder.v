module simd_instr_decoder (
 in_source1_addr,
 in_source2_addr,
 in_source3_addr,
 in_sgpr_dest_addr,
 in_opcode,
 out_vcc_wr_en,
 out_vgpr_wr_en,
 out_sgpr_wr_en,
 out_source1_mux_select,
 out_source2_mux_select,
 out_source3_mux_select,
 out_vgpr_source1_rd_en,
 out_vgpr_source2_rd_en,
 out_vgpr_source3_rd_en,
 out_sgpr_rd_en,
 out_exec_rd_en
);

input [11:0] in_source1_addr;
input [11:0] in_source2_addr;
input [11:0] in_source3_addr;
input [31:0] in_opcode;
input [11:0] in_sgpr_dest_addr;

output out_vcc_wr_en;
output out_vgpr_wr_en;
output out_sgpr_wr_en;
output [3:0] out_source1_mux_select;
output [3:0] out_source2_mux_select;
output [3:0] out_source3_mux_select;
output out_vgpr_source1_rd_en;
output out_vgpr_source2_rd_en;
output out_vgpr_source3_rd_en;
output out_sgpr_rd_en;
output out_exec_rd_en;

reg out_vcc_wr_en;
reg out_vgpr_wr_en;
reg out_sgpr_wr_en;
reg [3:0] out_source1_mux_select;
reg [3:0] out_source2_mux_select;
reg [3:0] out_source3_mux_select;
reg out_vgpr_source1_rd_en;
reg out_vgpr_source2_rd_en;
reg out_vgpr_source3_rd_en;

reg temp_vcc_wr_en;
reg temp_sgpr_wr_en;


assign out_exec_rd_en = 1'b1;
assign out_sgpr_rd_en = 1'b1;

always @* begin
   casex({in_opcode[31:24], in_sgpr_dest_addr})
      {`ALU_VOP3A_FORMAT, 12'b1_1_1_0_0000_0001}:
         begin
            out_vcc_wr_en <= 1'b1;
            out_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP3A_FORMAT, 12'b1_1_0_?????????}:
         begin
            out_vcc_wr_en <= 1'b0;
            out_sgpr_wr_en <= 1'b1;
         end
      default:
         begin
            out_vcc_wr_en <= temp_vcc_wr_en;
            out_sgpr_wr_en <= temp_sgpr_wr_en;
         end
      endcase
end

always @ (in_opcode) begin
	casex(in_opcode)
		{`ALU_VOP1_FORMAT, 12'h???, 12'h001} : //V_MOV_B32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h025} : //V_ADD_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h026} : //V_SUB_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h01B} : //V_AND_B32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h11B} : //V_AND_B32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h01C} : //V_OR_B32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h01A} : //V_LSHLREV_B32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h014} : //V_MAX_U32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h114} : //V_MAX_U32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h012} : //V_MAX_I32  - VIN
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h013} : //V_MIN_U32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h113} : //V_MIN_U32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h016} : //V_LSHRREV_B32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h018} : //V_ASHRREV_I32 - VIN
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP2_FORMAT, 12'h???, 12'h000} : //V_CNDMASK_B32
			begin
				temp_vcc_wr_en <= 1'b0;
				out_vgpr_wr_en <= 1'b1;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h080} : //V_CMP_F_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h081} : //V_CMP_LT_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h082} : //V_CMP_EQ_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h083} : //V_CMP_LE_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h084} : //V_CMP_GT_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h085} : //V_CMP_LG_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h086} : //V_CMP_GE_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h087} : //V_CMP_TRU_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h0C0} : //V_CMP_F_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h0C1} : //V_CMP_LT_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h0C2} : //V_CMP_EQ_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h0C3} : //V_CMP_LE_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h0C4} : //V_CMP_GT_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h0C5} : //V_CMP_LG_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h0C6} : //V_CMP_GE_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOPC_FORMAT, 12'h???, 12'h0C7} : //V_CMP_TRU_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b0;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h080} : //V_CMP_F_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h081} : //V_CMP_LT_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h082} : //V_CMP_EQ_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h083} : //V_CMP_LE_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h084} : //V_CMP_GT_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h085} : //V_CMP_LG_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h086} : //V_CMP_GE_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h087} : //V_CMP_TRU_I32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h0C0} : //V_CMP_F_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h0C1} : //V_CMP_LT_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h0C2} : //V_CMP_EQ_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h0C3} : //V_CMP_LE_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h0C4} : //V_CMP_GT_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h0C5} : //V_CMP_LG_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h0C6} : //V_CMP_GE_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
		{`ALU_VOP3A_FORMAT, 12'h???, 12'h0C7} : //V_CMP_TRU_U32
			begin
				temp_vcc_wr_en <= 1'b1;
				out_vgpr_wr_en <= 1'b0;
				temp_sgpr_wr_en <= 1'b1;
			end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h16A} : // V_MUL_HI_U32 => /* D.u = (S0.u * S1.u)>>32 */ VCC not used
         begin
         	temp_vcc_wr_en <= 1'b0;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h009} : // V_MUL_I32_I24 => /* D.i = S0.i[23:0] * S1.i[23:0]. */ VCC not used
         begin
         	temp_vcc_wr_en <= 1'b0;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h109} : // V_MUL_I32_I24 => /* D.i = S0.i[23:0] * S1.i[23:0]. */ VCC not used
         begin
         	temp_vcc_wr_en <= 1'b0;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h16B} : // V_MUL_LO_I32 => /* D.i = S0.i * S1.i. */ VCC not used
         begin
         	temp_vcc_wr_en <= 1'b0;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
       end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h169} : // V_MUL_LO_U32 => /* D.u = S0.u * S1.u. */ VCC not used
         begin
         	temp_vcc_wr_en <= 1'b0;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h148} : // V_BFE_U32
         begin
         	temp_vcc_wr_en <= 1'b0;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h149} : // V_BFE_I32 = VIN
         begin
         	temp_vcc_wr_en <= 1'b0;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h14A} : // V_BFI_B32
         begin
         	temp_vcc_wr_en <= 1'b0;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h028} : // V_ADDC_U32 - VIN
         begin
         	temp_vcc_wr_en <= 1'b1;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
				 end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h027} : // V_SUBREV_I32 - VIN
         begin
         	temp_vcc_wr_en <= 1'b1;
         	out_vgpr_wr_en <= 1'b1;
         	temp_sgpr_wr_en <= 1'b0;
				 end
		default:
			begin
				temp_vcc_wr_en <= 1'bx;
				out_vgpr_wr_en <= 1'bx;
				temp_sgpr_wr_en <= 1'b0;
			end
	endcase
end

always @ (in_source1_addr) begin
	casex(in_source1_addr)
		12'b0_11111111111 : //literal constant
			begin
				out_source1_mux_select <= 4'b0000;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b0_0_?????????? : //constant value
			begin
				out_source1_mux_select <= 4'b0001;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_0_?????????? : //read VGPR
			begin
				out_source1_mux_select <= 4'b0010;
				out_vgpr_source1_rd_en <= 1'b1;
			end
		12'b1_1_0_????????? : //read value from SGPR
			begin
				out_source1_mux_select <= 4'b0011;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0001 : //read VCC_LO
			begin
				out_source1_mux_select <= 4'b0100;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0010 : //read VCC_HI
			begin
				out_source1_mux_select <= 4'b0101;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0100 : //read M0
			begin
				out_source1_mux_select <= 4'b0110;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_1000 : //read EXEC_LO
			begin
				out_source1_mux_select <= 4'b0111;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0001_0000 : //read EXEC_HI
			begin
				out_source1_mux_select <= 4'b1000;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0010_0000 : //read VCCZ
			begin
				out_source1_mux_select <= 4'b1001;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0100_0000 : //read EXECZ
			begin
				out_source1_mux_select <= 4'b1010;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		12'b1_1_1_0_1000_0000 : //read SCC
			begin
				out_source1_mux_select <= 4'b1011;
				out_vgpr_source1_rd_en <= 1'b0;
			end
		default:
			begin
				out_source1_mux_select <= 4'bx;
				out_vgpr_source1_rd_en <= 1'bx;
			end
	endcase
end

always @ (in_source2_addr) begin
	casex(in_source2_addr)
		12'b0_11111111111 : //literal constant
			begin
				out_source2_mux_select <= 4'b0000;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b0_0_?????????? : //constant value
			begin
				out_source2_mux_select <= 4'b0001;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_0_?????????? : //read VGPR
			begin
				out_source2_mux_select <= 4'b0010;
				out_vgpr_source2_rd_en <= 1'b1;
			end
		12'b1_1_0_????????? : //read value from SGPR
			begin
				out_source2_mux_select <= 4'b0011;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0001 : //read VCC_LO
			begin
				out_source2_mux_select <= 4'b0100;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0010 : //read VCC_HI
			begin
				out_source2_mux_select <= 4'b0101;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0100 : //read M0
			begin
				out_source2_mux_select <= 4'b0110;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_1000 : //read EXEC_LO
			begin
				out_source2_mux_select <= 4'b0111;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0001_0000 : //read EXEC_HI
			begin
				out_source2_mux_select <= 4'b1000;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0010_0000 : //read VCCZ
			begin
				out_source2_mux_select <= 4'b1001;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0100_0000 : //read EXECZ
			begin
				out_source2_mux_select <= 4'b1010;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		12'b1_1_1_0_1000_0000 : //read SCC
			begin
				out_source2_mux_select <= 4'b1011;
				out_vgpr_source2_rd_en <= 1'b0;
			end
		default:
			begin
				out_source2_mux_select <= 4'bx;
				out_vgpr_source2_rd_en <= 1'bx;
			end
	endcase
end

always @ (in_source3_addr) begin
	casex(in_source3_addr)
		12'b0_11111111111 : //literal constant
			begin
				out_source3_mux_select <= 4'b0000;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b0_0_?????????? : //constant value
			begin
				out_source3_mux_select <= 4'b0001;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_0_?????????? : //read VGPR
			begin
				out_source3_mux_select <= 4'b0010;
				out_vgpr_source3_rd_en <= 1'b1;
			end
		12'b1_1_0_????????? : //read value from SGPR
			begin
				out_source3_mux_select <= 4'b0011;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0001 : //read VCC_LO
			begin
				out_source3_mux_select <= 4'b0100;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0010 : //read VCC_HI
			begin
				out_source3_mux_select <= 4'b0101;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_0100 : //read M0
			begin
				out_source3_mux_select <= 4'b0110;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0000_1000 : //read EXEC_LO
			begin
				out_source3_mux_select <= 4'b0111;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0001_0000 : //read EXEC_HI
			begin
				out_source3_mux_select <= 4'b1000;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0010_0000 : //read VCCZ
			begin
				out_source3_mux_select <= 4'b1001;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_1_1_0_0100_0000 : //read EXECZ
			begin
				out_source3_mux_select <= 4'b1010;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		12'b1_1_1_0_1000_0000 : //read SCC
			begin
				out_source3_mux_select <= 4'b1011;
				out_vgpr_source3_rd_en <= 1'b0;
			end
		default:
			begin
				out_source3_mux_select <= 4'bx;
				out_vgpr_source3_rd_en <= 1'bx;
			end
	endcase
end
endmodule
