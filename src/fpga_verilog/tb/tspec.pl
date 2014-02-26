#!/usr/bin/perl -w

use warnings "all";
use strict;
use Getopt::Long;

my $opt_result;
my $log = "";
my $nominal = 0;
my $threshold = 0;
my $help = 0;
my $outfile;

my $line;
my @line_parts;
my $hier;
my $type;
my $time;
my $module_hash_ref = {};
my $arrival;

my $last_clock_edge;
my $cycle_hash_ref = {};
my $mycycle;
my $cycle_count;
my $cycle_violation_count;
my $cycle_violation_percentage = 0;

my $script_name = $0;
my $pwd;
my $hostname;

$pwd = `pwd`;
chomp($pwd);
$hostname = `hostname`;
chomp($hostname);

#Parse arguments
$opt_result = GetOptions (
  "log=s"        => \$log,
  "nominal=s"    => \$nominal,
  "threshold=s"  => \$threshold,
  "help"         => \$help
);

#Sanity check of arguments
if(!$opt_result)
{
  print STDERR "$script_name: Invalid command line options!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if($help)
{
  print_help();
  exit 0;
}
if($log eq "")
{
  print STDERR "$script_name: Compulsory option -log is missing!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if(!(-e $log))
{
  print STDERR "$script_name: Log file $log cannot be found\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if($nominal == 0)
{
  print STDERR "$script_name: Compulsory option -nominal is missing!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if($nominal !~ m/^\d+$/)
{
  print STDERR "$script_name: $nominal is not a valid nominal period!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if($threshold == 0)
{
  print STDERR "$script_name: Compulsory option -threshold is missing!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if($threshold !~ m/^\d+$/)
{
  print STDERR "$script_name: $threshold is not a valid speculation threshold!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if($threshold >= $nominal)
{
  print STDERR "$script_name: Threshold $threshold should be less than Nominal period $nominal!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}

$outfile = $log;
$outfile =~ s/run\.log$/tspec_report_${threshold}ps_${nominal}ps.log/g;

$module_hash_ref = {};
#Read in run.log and process
open(RUNLOG,"$log");
$last_clock_edge = 0;
while($line = <RUNLOG>)
{
  if($line !~ m/^GATES MONITOR/)
  {
    next;
  }
  @line_parts = split(" ", $line);
  $hier = $line_parts[2];
  $type = $line_parts[6];
  $time = $line_parts[9];
 
  if($type eq "CLK")
  {
    $last_clock_edge = $time;
    $cycle_hash_ref->{$last_clock_edge} = 0;
    #print "$hier $type $time\n";
    next;
  }
  else
  {
    if(($last_clock_edge == 0) || ($cycle_hash_ref->{$last_clock_edge} == 1))
    {
    #print "$last_clock_edge \n";
      next;
    }
    else
    {
      $arrival = $time -  $last_clock_edge;
      if(($arrival >= $threshold) && ($arrival < $nominal))
      {
        $cycle_hash_ref->{$last_clock_edge} = 1;
        next;
      }
    }
  }
}
close(RUNLOG);

#Parsing internal hash for creating summary
$cycle_count = 0;
$cycle_violation_count = 0;
foreach $mycycle (keys %$cycle_hash_ref)
{
  $cycle_count = $cycle_count + 1;
  if($cycle_hash_ref->{$mycycle} == 1)
  {
    $cycle_violation_count = $cycle_violation_count + 1;
  }
}
$cycle_violation_percentage = 100 * ($cycle_violation_count / $cycle_count);

open(OUTFILE,">$outfile");
print OUTFILE "Nominal period            : $nominal ps\n";
print OUTFILE "Speculation threshold     : $threshold ps\n";
print OUTFILE "Total cycle count         : $cycle_count\n";
print OUTFILE "Violated cycle count      : $cycle_violation_count\n";
print OUTFILE "Percentage violation      : $cycle_violation_percentage \%\n";
close(OUTFILE);

#Subroutine for help message
sub print_help
{
print STDOUT qq{$script_name:

TODO

};
}
