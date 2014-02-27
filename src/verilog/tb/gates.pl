#!/usr/bin/perl -w
use warnings "all";
use strict;

my @test_list = ("BinarySearch", "MatrixTranspose", "PrefixSum", "ScanLargeArrays", "Reduction");
#my @test_list = ("MatrixTranspose");
my $test;
my $nominal = "11000";
my @thresholds = ("10999", "10500", "10000", "9500", "9000", "8500", "8000", "7500", "7000", "6500", "6000", "5500", "5000", "4500", "4000", "3500", "3000", "2500", "2000", "1500", "1000", "500", "250", "100", "50", "20", "10", "5", "1");
my $runcount = scalar(@thresholds);
my $threshold_ns;
my $my_viol_percent;
my $i;
my $logline;
my @logarray;

`make clean && make compile GATES=1`;
#`run.pl -r 1 -t 001_mov -o r1_mov -f -a "+CLOCKPERIOD=8000" -k 2000000`;
`run.pl -r 0 -t "BinarySearch|MatrixTranspose|PrefixSum|ScanLargeArrays|Reduction" -o r0_all_GATES -f -a "+CLOCKPERIOD=22000" -k 500000000000`;

$logline = "Threshold";
foreach $test (@test_list)
{
  $logline = "$logline,$test";
}
$logline = "$logline\n";
push(@logarray,$logline);

for($i=0;$i<$runcount;$i=$i+1)
{
  $threshold_ns = $thresholds[$i]/1000;
  $logline = "$threshold_ns";
  foreach $test (@test_list)
  {
    print "$thresholds[$i] $test\n";
    `./tspec.pl -l results/r0_all_GATES/$test/run.log -n $nominal -t $thresholds[$i]`;
    $my_viol_percent = 0;
    $my_viol_percent = `grep Percentage results/r0_all_GATES/$test/tspec_report_${thresholds[$i]}ps_${nominal}ps.log | cut -f 2 -d ':' | cut -f 2 -d ' '`;
    chomp($my_viol_percent);
    $logline = "$logline,$my_viol_percent";
  }
  $logline = "$logline\n";
  push(@logarray,$logline);
}
open(TSPECSUMMARY,">results/r0_all_GATES/tspec.summary");
print TSPECSUMMARY @logarray;
close(TSPECSUMMARY);
