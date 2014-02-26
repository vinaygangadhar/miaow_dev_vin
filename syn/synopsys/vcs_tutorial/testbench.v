module testbench;
  
  //wires
  wire [2:0] out;
  reg reset;
  reg clock;

  //instantiation of dut
  counter c1(out,clock,reset);
  
  //stimulii
  initial begin
    forever #5 clock = ~clock;
  end
  initial begin
    #3 clock = 1'b0;
    #16 reset = 1'b1;
    #10 reset = 1'b0;
    #100;
    $finish;
  end

  //monitors
  initial begin
    if ($test$plusargs("print_outputs")) begin
      $monitor("counter output = %b", out);
    end
  end

  //waveforms
  initial begin
    if ($test$plusargs("dump_waveforms")) begin
      $vcdpluson(0,testbench);
      //$vcdpluson(<level>,scope,<signal>);
      //Lots of options for dumping waves
      //(both system calls and run time arguments)
      // http://read.pudn.com/downloads97/sourcecode/others/399556/vcs_0123.pdf
    end
  end

endmodule
