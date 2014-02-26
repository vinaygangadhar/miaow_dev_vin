#!/usr/bin/perl -w
use warnings "all";
use strict;
my @tests = ("BinarySearch", "MatrixTranspose", "PrefixSum", "ScanLargeArrays", "Reduction");
my $test;

`make clean && make compile SAIF=1`;

foreach $test (@tests)
{
  `
    ./run.pl -r 0 -t $test -o r0_${test}_saif &&
    cd ../../../syn/synopsys &&
    ./synth.pl -s -o ${test}_saif -b "../../src/verilog/tb/results/r0_${test}_saif/$test/backward.saif synth" &&
    cd ../../src/verilog/tb/results/r0_${test}_saif/$test &&
    rm -rf backward.saif
  `;
}
