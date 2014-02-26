module instruction_arbiter
  (/*AUTOARG*/
   // Outputs
   simd0_alu_select, simd1_alu_select, simd2_alu_select,
   simd3_alu_select, simf0_alu_select, simf1_alu_select,
   simf2_alu_select, simf3_alu_select, lsu_lsu_select,
   salu_alu_select, lsu_wfid, alu_wfid, alu_valid, lsu_valid,
   // Inputs
   clk, rst, salu_ready_to_issue, simd_ready_to_issue,
   simf_ready_to_issue, lsu_ready_to_issue, simd0_alu_ready,
   simd1_alu_ready, simd2_alu_ready, simd3_alu_ready, simf0_alu_ready,
   simf1_alu_ready, simf2_alu_ready, simf3_alu_ready, salu_alu_ready,
   lsu_ready
   );
   input clk, rst;
   
   input [`WF_PER_CU-1:0] salu_ready_to_issue, simd_ready_to_issue,
			  simf_ready_to_issue, lsu_ready_to_issue;
   input 		  simd0_alu_ready, simd1_alu_ready, 
			  simd2_alu_ready, simd3_alu_ready, 
			  simf0_alu_ready, simf1_alu_ready, 
			  simf2_alu_ready, simf3_alu_ready, 
			  salu_alu_ready, lsu_ready;
   
   output 		  simd0_alu_select, simd1_alu_select, 
			  simd2_alu_select, simd3_alu_select, 
			  simf0_alu_select, simf1_alu_select, 
			  simf2_alu_select, simf3_alu_select, 
			  lsu_lsu_select, salu_alu_select;
   output [`WF_ID_LENGTH-1:0] lsu_wfid, alu_wfid;
   output 		      alu_valid, lsu_valid;
   
   wire 		      lsu_wf_valid, salu_wf_valid, simd_wf_valid, simf_wf_valid;
   wire [`WF_ID_LENGTH-1:0]   lsu_wf_chosen, salu_wf_choosen, simd_wf_choosen, simf_wf_choosen,
			      issued_wfid;
   

   wire 		      issued_fu_valid;
   
   arbiter lsu_arbiter
     (
      .clk(clk),
      .rst(rst),
      
      .input_arry(lsu_ready_to_issue),
      
      .issued_en(issued_fu_valid),
      .issued_wf_id(lsu_wfid),
      
      .choosen_valid(lsu_wf_valid),
      .choosen_wf_id(lsu_wf_chosen)
      );

   arbiter salu_arbiter
     (
      .clk(clk),
      .rst(rst),
      .input_arry(salu_ready_to_issue),
      .issued_en(issued_fu_valid),
      .issued_wf_id(alu_wfid),
      
      .choosen_valid(salu_wf_valid),
      .choosen_wf_id(salu_wf_choosen)
      );
   
   arbiter simd_arbiter
     (
      .clk(clk),
      .rst(rst),
      
      .input_arry(simd_ready_to_issue),
      
      .issued_en(issued_fu_valid),
      .issued_wf_id(alu_wfid),
      
      .choosen_valid(simd_wf_valid),
      .choosen_wf_id(simd_wf_choosen)
      );

   arbiter simf_arbiter
     (
      .clk(clk),
      .rst(rst),
      
      .input_arry(simf_ready_to_issue),
      
      .issued_en(issued_fu_valid),
      .issued_wf_id(alu_wfid),
      
      .choosen_valid(simf_wf_valid),
      .choosen_wf_id(simf_wf_choosen)
      );
   
   alu_issue_logic alu_issue_logic
     (/*AUTOINST*/
      // Outputs
      .issued_fu_valid			(issued_fu_valid),
      .simd0_alu_select			(simd0_alu_select),
      .simd1_alu_select			(simd1_alu_select),
      .simd2_alu_select			(simd2_alu_select),
      .simd3_alu_select			(simd3_alu_select),
      .simf0_alu_select			(simf0_alu_select),
      .simf1_alu_select			(simf1_alu_select),
      .simf2_alu_select			(simf2_alu_select),
      .simf3_alu_select			(simf3_alu_select),
      .lsu_lsu_select			(lsu_lsu_select),
      .salu_alu_select			(salu_alu_select),
      .issued_wfid			(issued_wfid[`WF_ID_LENGTH-1:0]),
      // Inputs
      .clk				(clk),
      .rst				(rst),
      .lsu_ready			(lsu_ready),
      .salu_alu_ready			(salu_alu_ready),
      .simf3_alu_ready			(simf3_alu_ready),
      .simf2_alu_ready			(simf2_alu_ready),
      .simf1_alu_ready			(simf1_alu_ready),
      .simf0_alu_ready			(simf0_alu_ready),
      .simd3_alu_ready			(simd3_alu_ready),
      .simd2_alu_ready			(simd2_alu_ready),
      .simd1_alu_ready			(simd1_alu_ready),
      .simd0_alu_ready			(simd0_alu_ready),
      .lsu_wf_valid			(lsu_wf_valid),
      .simd_wf_valid			(simd_wf_valid),
      .simf_wf_valid			(simf_wf_valid),
      .salu_wf_valid			(salu_wf_valid),
      .lsu_wf_chosen			(lsu_wf_chosen[`WF_ID_LENGTH-1:0]),
      .simd_wf_choosen			(simd_wf_choosen[`WF_ID_LENGTH-1:0]),
      .simf_wf_choosen			(simf_wf_choosen[`WF_ID_LENGTH-1:0]),
      .salu_wf_choosen			(salu_wf_choosen[`WF_ID_LENGTH-1:0]));

   assign alu_wfid = issued_wfid;
   assign lsu_wfid = issued_wfid;
   assign alu_valid = simd0_alu_select | simd1_alu_select | simd2_alu_select | 
		      simd3_alu_select | simf0_alu_select | simf1_alu_select | 
		      simf2_alu_select | simf3_alu_select | salu_alu_select;
   
   assign lsu_valid = lsu_lsu_select;
   
endmodule

