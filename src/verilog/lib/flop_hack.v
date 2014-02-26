`ifdef GATES
  //always @(posedge CLK)
  //begin
  //  $display("FLOP MONITOR %m: Posedge of CLK at time %t", $time);
  //end
  always @(D)
  begin
    $display("GATES MONITOR %m: Transition of D at time %t", $time);
  end
`endif
