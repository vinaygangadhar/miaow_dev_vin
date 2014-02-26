extern "C" int initialize_fault_injection();
extern "C" int get_finish_cycle();
extern "C" void inject_fault(int tick);
extern "C" void dump_uarch(int tick);

module fault_injection(clk);

   input clk;
   integer fault_cycle;
   integer finish_cycle;
   integer clock_cycle;

   initial begin
      clock_cycle = 0;
      fault_cycle = 0;
      finish_cycle = 0;
      if ($test$plusargs("inject_fault") || $test$plusargs("dump_uarch"))
      begin
         fault_cycle = initialize_fault_injection();
         finish_cycle = get_finish_cycle();
      end
   end

   always @(posedge clk)
   begin
      if (clock_cycle++ == fault_cycle)
      begin
         if ($test$plusargs("inject_fault"))
         begin
            #1
            inject_fault($time);
         end
      end

      if (clock_cycle == finish_cycle)
      begin
         if ($test$plusargs("dump_uarch"))
         begin
            #1
            dump_uarch($time);
            $finish;
         end
      end
   end
endmodule