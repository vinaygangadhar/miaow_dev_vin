#!/usr/bin/perl -w

use warnings "all";
use Getopt::Long;
use File::Compare;

my $opt_result;
my $test = "";
my $rdir = "";
my $outdir = "";
my $waves = 0;
my $force = 0;
my $list = 0;
my $ifault_count = 0;
my $cycle = 0;
my $help = 0;
my $script_name = $0;

my @run_result;
my @summary = ();
my $gray_area_count;
my $uarch_match_count;
my $sdc_runs;
my $terminated_runs;
my $total_runs;
my $starttime = 0;
my $endtime = 0;
my $elapsedtime = 0;
my $pwd;
my $hostname;

my $file_size = 0;
my $num_cycles = 100;
my $finish_cycles = 100;

$pwd = `pwd`;
chomp($pwd);
$hostname = `hostname`;
chomp($hostname);

#Parse arguments
$opt_result = GetOptions (
  "test=s"     => \$test,
  "rdir=s"     => \$rdir,
  "outdir=s"   => \$outdir,
  "waves"      => \$waves,
  "force"      => \$force,
  "list"       => \$list,
  "ifault_count=s" => \$ifault_count,
  "cycle=s" => \$cycle,
  "num_cycles=s" => \$num_cycles,
  "help"       => \$help
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
if($test eq "")
{
  print STDERR "$script_name: Compulsory option -test is missing!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if($rdir eq "")
{
  print STDERR "$script_name: Compulsory option -rdir is missing!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if(($outdir eq "") && (0 == $list))
{
  print STDERR "$script_name: Compulsory option -outdir is missing!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if(($ifault_count eq 0) && (0 == $list))
{
  print STDERR "$script_name: Compulsory option -ifault_count is missing or invalid!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
if(($cycle < 10) && (0 == $list))
{
  print STDERR "$script_name: Compulsory option -icycle is missing or invalid!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}
$batchdir = "results/$outdir";
if((-d $batchdir) && (0 == $force) && (0 == $list))
{
  print STDERR "$script_name: Result directory $outdir already exists! Use -f to overwrite or try another name.\n";
  die;
}

if(1 == $list)
{
  system "run.pl -r $rdir -t $test -l";
  exit 0;
}

if(0 == open(INFILE, "fault_sites"))
{
  print STDERR "$script_name: Cannot open the file fault_sites for reading!\n";
  die;
}
@input_file = <INFILE>;
close(INFILE);

#Create the batch directory
`rm -rf $batchdir && mkdir -p $batchdir`;

$uarch_dump_path = "$batchdir/uarch_dump";
#Create directory for dumping uarch
`mkdir -p $uarch_dump_path`;

#GOLDEN RUN
{
  print "run: GOLDEN RUN\n";

  #Open the current_fault file and print fault cycle and fault site
  if (0 == open(OUTFILE, ">./$batchdir/current_fault"))
  {
    print STDERR "$script_name: Cannot open file $batchdir/current_fault for writing!\n";
    die;
  }
  $finish_cycle = $cycle + $num_cycles;

  print OUTFILE "$pwd/floplist\n";
  print OUTFILE "$pwd/$uarch_dump_path/uarch_dump_golden\n";
  print OUTFILE "$cycle\n";
  print OUTFILE "$finish_cycle\n";
  close(OUTFILE);
  $current_outdir = "${outdir}/run_golden";

  if(1 == $waves)
  {
    system "run.pl -r $rdir -t $test -o $current_outdir -f -a +dump_uarch=1 -w -k 100000";
  }
  else
  {
    system "run.pl -r $rdir -t $test -o $current_outdir -f -a +dump_uarch=1 -k 100000";
  }
  
  `cd $batchdir/run_golden && ls */kernel_*/*trace* | grep -v ".verilog" | xargs rm -f`;
  
  @golden_trace_files = `cd $batchdir/run_golden && ls */kernel_*/*`;
  chomp(@golden_trace_files);

  foreach $trace_file (@golden_trace_files)
  {
    if ($trace_file =~ m/(.*).verilog$/)
    {
      system "cd $batchdir/run_golden && mv $1.verilog $1"
    }
  }
}

$gray_area_count = 0;
$sdc_runs = 0;
$terminated_runs = 0;
$total_runs = 0;
$uarch_match_count = 0;

#Open summary file
open(SUMMARY, ">$batchdir/summary.txt");
print SUMMARY "***************************************************\n";
print SUMMARY "Summary:\n";

$starttime = time;
$file_size = scalar(@input_file);

for ($fault_count = 1; (($fault_count <= $ifault_count) || ($fault_count >= $file_size)); $fault_count++)
{
   print "run: $fault_count\n";

   $line = $input_file[$fault_count - 1];

  #Open the current_fault file and print fault cycle and fault site
  if (0 == open(OUTFILE, ">./$batchdir/current_fault"))
  {
    print STDERR "$script_name: Cannot open file $batchdir/current_fault for writing!\n";
    die;
  }
  $finish_cycle = $cycle + $num_cycles;

  print OUTFILE "$pwd/floplist\n";
  print OUTFILE "$pwd/$uarch_dump_path/uarch_dump_${fault_count}\n";
  print OUTFILE "$cycle\n";
  print OUTFILE "$finish_cycle\n";
  print OUTFILE $line;
  close(OUTFILE);

  $current_outdir = "${outdir}/run_${fault_count}";

  if(1 == $waves)
  {
    system "run.pl -r \"${batchdir}/run_golden\" -t $test -o $current_outdir -f -a \"+inject_fault=1 +dump_uarch=1\" -w -k 100000";
  }
  else
  {
    system "run.pl -r \"${batchdir}/run_golden\" -t $test -o $current_outdir -f -a \"+inject_fault=1 +dump_uarch=1\" -k 100000";
  }

  @run_result = `grep -c "FAIL" $batchdir/run_${fault_count}/summary.txt`;
  chomp(@run_result);
  $total_runs++;
  if($run_result[0] eq "0")
  {
    if (compare("$pwd/$uarch_dump_path/uarch_dump_golden","$pwd/$uarch_dump_path/uarch_dump_${fault_count}") == 0)
    {
      $uarch_match_count++;
      print SUMMARY "run_${fault_count}\tuARCH MATCH\n";
      push(@summary, "run_${fault_count}\tuARCH MATCH\n");
      system "rm -f $uarch_dump_path/uarch_dump_${fault_count}";
    }
    else
    {
      $gray_area_count++;
      print SUMMARY "run_${fault_count}\tGRAY AREA\n";
      push(@summary, "run_${fault_count}\tGRAY AREA\n");
    }
    system "rm -rf $batchdir/run_${fault_count}";
  }
  else
  {
    system "rm -f $uarch_dump_path/uarch_dump_${fault_count}";

    @run_result = `grep -c "(Hang)" $batchdir/run_${fault_count}/summary.txt`;
    chomp(@run_result);
    if($run_result[0] eq "0")
    {
      $sdc_runs++;
      print SUMMARY "run_${fault_count}\tFAIL: SDC\n";
      push(@summary, "run_${fault_count}\tFAIL: SDC\n");
    }
    else
    {
      $terminated_runs++;
      print SUMMARY "run_${fault_count}\tFAIL: TERMINATED\n";
      push(@summary, "run_${fault_count}\tFAIL: TERMINATED\n");
    }
  }
  push(@summary, "Cycle $cycle : $line\n");
}

$endtime = time;
$elapsedtime = $endtime - $starttime;
system("echo \"Total wall time taken in $hostname: $elapsedtime seconds\"");

#Write to sumamry file
print SUMMARY "***************************************************\n";
print SUMMARY "Total test count: $total_runs\n";
print SUMMARY "Total uArch match count: $uarch_match_count\n";
print SUMMARY "Total Gray area count: $gray_area_count\n";
print SUMMARY "Total SDC count: $sdc_runs\n";
print SUMMARY "Total terminated count: $terminated_runs\n";
print SUMMARY "Total wall time taken in $hostname: $elapsedtime seconds\n";
print SUMMARY "***************************************************\n";
print SUMMARY @summary;
print SUMMARY "***************************************************\n";
close(SUMMARY);

#Subroutine for help message
sub print_help
{
print STDOUT qq{$script_name:

DESCRIPTION:
  This script is for injecting faults while running unit tests/benchmarks. The summary of fault injection can be found in summary.txt present in /miaow/src/verilog/tb/results/<outputdir>
  The fault sites at which the faults are to be injected should be provided in the file "fault_sites".
  This script calls run.pl internally for running the tests. See run.pl help for more details about output of individual tests.

USAGE:
  $script_name -r <0 for benchmarks, 1/2/3/4/5 for random test folder> -t <testname/regex> -o <outputdir> -i <number of fault injection runs> [-w] [-f] [-l] [-h]

ARGUMENTS:

-r
-folder from which tests will be picked. Provide 0 for benchmarks and 1/2/3/4/5 for random tests.

-t
-test <testname/regex>  This is a compulsory argument; used to specify the name of the unit test/benchmark to be run. When this is a regular expression, it can select multiple tests

-o
-outdir <outputdir> This is a compulsory argument; used to specify the name of the batch directory where tests are run

-w
-waves      This option enables waveform dumps. Makes simulations run slower, output directories to occupy more disc space

-f
-force      This option forces overwrite of output directories if already existing

-l
-list     With this option, no tests are launched. Instead the script will just list out the tests which would be selected.

-h
-help     Well, you know what this option is for! You couldn't be reading this otherwise.

EXAMPLE USAGE:
  $script_name -r 1 -t test_000_branch -o trial1 -i 100
  This will pick the test test_000_branch from rand_unit_tests_1 folder, and run 100 fault injection runs
  For above run, results can be found at /miaow/src/verilog/tb/results/trial1

  $script_name -r 0 -t BinarySearch -o trial1 -i 100
  This will pick the test BinarySearch from benchmarks folder, and run 100 fault injection runs
  For above run, results can be found at /miaow/src/verilog/tb/results/trial1

  $script_name -r 1 -t "_0|_1" -o trial1 -l
  This will just list the tests which will be selected

  $script_name -r 1 -t "_0|_1" -o trial1 -i 100
  This will run tests without waveform dumps

  $script_name -r 1 -t "_0|_1" -o trial1 -i 100 -w
  This will run tests with waveform dumps
};
}
