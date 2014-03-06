module simf_instr_decoder (
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
      {`ALU_VOP2_FORMAT, 12'h???, 12'h003} : //V_ADD_F32
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h004} : //V_SUB_F32
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
        end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h005} : //V_SUBREV_F32
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
        end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h008} : //V_MUL_F32
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
        end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h000} : //V_CMP_F_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h001} : //V_CMP_LT_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h002} : //V_CMP_EQ_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h003} : //V_CMP_LE_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h004} : //V_CMP_GT_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h005} : //V_CMP_LG_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h006} : //V_CMP_GE_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h009} : //V_CMP_NGE_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h00A} : //V_CMP_NLG_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h00B} : //V_CMP_NGT_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h00C} : //V_CMP_NLE_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h00D} : //V_CMP_NEQ_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h00E} : //V_CMP_NLT_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOPC_FORMAT, 12'h???, 12'h00F} : //V_CMP_TRU_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b0;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h000} : //V_CMP_F_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h001} : //V_CMP_LT_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h002} : //V_CMP_EQ_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h003} : //V_CMP_LE_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h004} : //V_CMP_GT_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h005} : //V_CMP_LG_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h006} : //V_CMP_GE_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h009} : //V_CMP_NGE_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h00A} : //V_CMP_NLG_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h00B} : //V_CMP_NGT_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h00C} : //V_CMP_NLE_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h00D} : //V_CMP_NEQ_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h00E} : //V_CMP_NLT_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h00F} : //V_CMP_TRU_F32
         begin
            temp_vcc_wr_en <= 1'b1;
            out_vgpr_wr_en <= 1'b0;
            temp_sgpr_wr_en <= 1'b1;
         end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h103} : //V_ADD_F32
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
        end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h104} : //V_SUB_F32
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
        end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h105} : //V_SUBREV_F32
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
        end
      {`ALU_VOP3A_FORMAT, 12'h???, 12'h108} : //V_MUL_F32
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
        end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h01F} : //V_MAC_F32  - VIN
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
        end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h020} : //V_MADMK_F32  - VIN
         begin
      		temp_vcc_wr_en <= 1'b0;
      		out_vgpr_wr_en <= 1'b1;
            temp_sgpr_wr_en <= 1'b0;
				 end
      {`ALU_VOP2_FORMAT, 12'h???, 12'h010} : //V_MAX_F32  - VIN
         begin
      		temp_vcc_wr_en <= 1'b0;
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
