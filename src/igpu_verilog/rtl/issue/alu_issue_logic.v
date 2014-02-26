module alu_issue_logic
  (/*AUTOARG*/
   // Outputs
   issued_fu_valid, simd0_alu_select, simd1_alu_select,
   simd2_alu_select, simd3_alu_select, simf0_alu_select,
   simf1_alu_select, simf2_alu_select, simf3_alu_select,
   lsu_lsu_select, salu_alu_select, issued_wfid,
   // Inputs
   clk, rst, lsu_ready, salu_alu_ready, simf3_alu_ready,
   simf2_alu_ready, simf1_alu_ready, simf0_alu_ready, simd3_alu_ready,
   simd2_alu_ready, simd1_alu_ready, simd0_alu_ready, lsu_wf_valid,
   simd_wf_valid, simf_wf_valid, salu_wf_valid, lsu_wf_chosen,
   simd_wf_choosen, simf_wf_choosen, salu_wf_choosen
   );
   
   input clk,rst;

   input 		  lsu_ready, salu_alu_ready,
			  simf3_alu_ready,simf2_alu_ready,
			  simf1_alu_ready,simf0_alu_ready,
			  simd3_alu_ready,simd2_alu_ready,
			  simd1_alu_ready,simd0_alu_ready;
   

   input 		  lsu_wf_valid, simd_wf_valid, simf_wf_valid ,salu_wf_valid;
   input [`WF_ID_LENGTH-1:0] lsu_wf_chosen, simd_wf_choosen, simf_wf_choosen, salu_wf_choosen;

   output 		     issued_fu_valid;
   output 		     simd0_alu_select, simd1_alu_select, 
			     simd2_alu_select, simd3_alu_select, 
			     simf0_alu_select, simf1_alu_select, 
			     simf2_alu_select, simf3_alu_select, 
			     lsu_lsu_select, salu_alu_select;
   
   output [`WF_ID_LENGTH-1:0] issued_wfid;

   reg [`WF_ID_LENGTH-1:0] issued_wfid;
   
   
   wire [1:0] 		     last_fu_selected;
   
   reg [1:0] 		     curr_fu_selected;
   
   reg_param #(2) last_fu(.out(last_fu_selected), .in(curr_fu_selected), 
			  .wr_en(issued_fu_valid), .clk(clk), .rst(rst));

   
   reg 			     issued_fu_valid;
   reg 			     simd0_alu_select, simd1_alu_select, 
			     simd2_alu_select, simd3_alu_select, 
			     simf0_alu_select, simf1_alu_select, 
			     simf2_alu_select, simf3_alu_select, 
			     lsu_lsu_select, salu_alu_select;
 			     
   reg [3:0] 		     fu_ready_shifted, fu_selected_shifted;
   reg [3:0] 		     fu_ready_arry, fu_selected_arry;
			 
   always @(last_fu_selected or lsu_ready
	    or lsu_wf_chosen or lsu_wf_valid or salu_alu_ready
	    or salu_wf_choosen or salu_wf_valid or simd0_alu_ready
	    or simd1_alu_ready or simd2_alu_ready or simd3_alu_ready
	    or simd_wf_choosen or simd_wf_valid or simf0_alu_ready
	    or simf1_alu_ready or simf2_alu_ready or simf3_alu_ready
	    or simf_wf_choosen or simf_wf_valid
	    or fu_ready_arry or fu_ready_shifted or fu_selected_shifted
	    or fu_selected_arry) begin
      

      fu_ready_arry <= { (simd0_alu_ready | simd1_alu_ready | simd2_alu_ready | 
			 simd3_alu_ready) & simd_wf_valid,
			(simf0_alu_ready | simf1_alu_ready | simf2_alu_ready | 
			 simf3_alu_ready) & simf_wf_valid,
			lsu_ready & lsu_wf_valid,
			salu_alu_ready & salu_wf_valid };

      // Select one fu based on round robin between fu classes
      case( last_fu_selected )
	2'b00 : fu_ready_shifted <= fu_ready_arry;
	2'b01 : fu_ready_shifted <= {fu_ready_arry[0], fu_ready_arry[3:1]};
	2'b10 : fu_ready_shifted <= {fu_ready_arry[1:0], fu_ready_arry[3:2]};
	2'b11 : fu_ready_shifted <= {fu_ready_arry[2:0], fu_ready_arry[3]};
      endcase

      casex( fu_ready_shifted )

	4'b1??? : begin
	   fu_selected_shifted <= fu_ready_shifted & 4'b1000;
	   curr_fu_selected <= 2'h3;
	end

	4'b01?? : begin
	   fu_selected_shifted <= fu_ready_shifted & 4'b0100;
	   curr_fu_selected <= 2'h2;
	end

	4'b001? : begin 
	   fu_selected_shifted <= fu_ready_shifted & 4'b0010;
	   curr_fu_selected <= 2'h1;
	end
			      
	4'b0001 : begin
	   fu_selected_shifted <= fu_ready_shifted & 4'b0001;
	   curr_fu_selected <= 2'h0;
	end
	   
	default : begin
	   fu_selected_shifted <= 4'b0000;
	   curr_fu_selected <= last_fu_selected;
	end
	
      endcase // casex ( fu_ready_shifted )

      case( last_fu_selected )
	2'b00 : fu_selected_arry <= fu_selected_shifted;
	2'b01 : fu_selected_arry <= {fu_selected_shifted[2:0], fu_selected_shifted[3]};
	2'b10 : fu_selected_arry <= {fu_selected_shifted[1:0], fu_selected_shifted[3:2]};
	2'b11 : fu_selected_arry <= {fu_selected_shifted[0], fu_selected_shifted[3:1]};
      endcase // case ( last_fu_selected )

      // With the class selected, we select the correct alu
      casex( { simd0_alu_ready,simd1_alu_ready,simd2_alu_ready,simd3_alu_ready} )
	4'b1??? : begin
	   simd0_alu_select <= fu_selected_arry[3];
	   simd1_alu_select <= 1'b0;
	   simd2_alu_select <= 1'b0;
	   simd3_alu_select <= 1'b0;
	end
	
	4'b01?? : begin
	   simd0_alu_select <= 1'b0;
	   simd1_alu_select <= fu_selected_arry[3];
	   simd2_alu_select <= 1'b0;
	   simd3_alu_select <= 1'b0;
	end
	
	4'b001? : begin
	   simd0_alu_select <= 1'b0;
	   simd1_alu_select <= 1'b0;
	   simd2_alu_select <= fu_selected_arry[3];
	   simd3_alu_select <= 1'b0;
	end
	
	4'b0001 : begin
	   simd0_alu_select <= 1'b0;
	   simd1_alu_select <= 1'b0;
	   simd2_alu_select <= 1'b0;
	   simd3_alu_select <= fu_selected_arry[3];
	end
	
	default : begin
	   simd0_alu_select <= 1'b0;
	   simd1_alu_select <= 1'b0;
	   simd2_alu_select <= 1'b0;
	   simd3_alu_select <= 1'b0;
	end
      endcase
	
      casex( { simf0_alu_ready,simf1_alu_ready,simf2_alu_ready,simf3_alu_ready} )
	4'b1??? : begin
	   simf0_alu_select <= fu_selected_arry[2];
	   simf1_alu_select <= 1'b0;
	   simf2_alu_select <= 1'b0;
	   simf3_alu_select <= 1'b0;
	end
	
	4'b01?? : begin
	   simf0_alu_select <= 1'b0;
	   simf1_alu_select <= fu_selected_arry[2];
	   simf2_alu_select <= 1'b0;
	   simf3_alu_select <= 1'b0;
	end
	
	4'b001? : begin
	   simf0_alu_select <= 1'b0;
	   simf1_alu_select <= 1'b0;
	   simf2_alu_select <= fu_selected_arry[2];
	   simf3_alu_select <= 1'b0;
	end
	
	4'b0001 : begin
	   simf0_alu_select <= 1'b0;
	   simf1_alu_select <= 1'b0;
	   simf2_alu_select <= 1'b0;
	   simf3_alu_select <= fu_selected_arry[2];
	end
	
	default : begin
	   simf0_alu_select <= 1'b0;
	   simf1_alu_select <= 1'b0;
	   simf2_alu_select <= 1'b0;
	   simf3_alu_select <= 1'b0;
	end
	
      endcase
      lsu_lsu_select <= fu_selected_arry[1];
      salu_alu_select <= fu_selected_arry[0];
      
      // Select the correct wfid
      case( fu_selected_arry )
	4'b1000 : issued_wfid <= simd_wf_choosen;
	4'b0100 : issued_wfid <= simf_wf_choosen;
	4'b0010 : issued_wfid <= lsu_wf_chosen;
	4'b0001 : issued_wfid <= salu_wf_choosen;
      endcase // case ( fu_selected_arry )

      issued_fu_valid <= |fu_selected_arry;
            
   end
   
      
   
endmodule
