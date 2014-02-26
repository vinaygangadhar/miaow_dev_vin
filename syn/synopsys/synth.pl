#!/usr/bin/perl -w

use warnings "all";
use strict;
use Getopt::Long;

########################################################
#Variable declarations
our $module_hash_ref;
my $child;
my $opt_result;
our $outdir = "synth";
my $force = 0;
my $missing = 0;
my $pick = "";
my $dontpick = "";
my $backsaif = "";
my $list = 0;
my $allbutsynth = 0;
my $skiprtlbuild = 0;
my $help = 0;
my @saifparts;
my $saiffile;
my $ddcfolder;

my $key;

my $starttime = 0;
my $endtime = 0;
my $elapsedtime = 0;
my $hostname;
my $script_name;
my $pwd;
my $module;
my @listed_modules;
my @common_file_list = ();
my @part_of_list;
my @custom_file_list;
my $list_size;
my $i;
my @synth_script;
my $script_size;
our @area_summary;
our @power_summary;
########################################################

########################################################
#Get script name, current working directory and hostname
$script_name = $0;
$pwd = `pwd`;
chomp($pwd);
if($pwd !~ m/syn\/synopsys$/)
{
  print STDERR "$script_name: $script_name should be invoked from /miaow/syn/synopsys\n";
  die;
}
$hostname = `hostname`;
chomp($hostname);
########################################################

########################################################
#Defining the module hash reference
#FINDME_MODULE_HIERARCHY
$module_hash_ref =
{
  "compute_unit" =>
  {
    "children" =>
    {
      "rfa" => 1,
      "salu" => 1,
      "wavepool" => 1,
      "exec" => 1,
      "fetch" => 1,
      "decode" => 1,
      "issue" => 1,
      "simd" => 4,
      "simf" => 4,
      "lsu" => 1,
      "sgpr" => 1,
      "vgpr" => 1
    },
    "hierarchy" => "gpu_tb/DUT[0]"
  },
  "rfa" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/rfa0"
  },
  "salu" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/salu0"
  },
  "wavepool" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/wavepool0"
  },
  "exec" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/exec0"
  },
  "fetch" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/fetch0"
  },
  "decode" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/decode0"
  },
  "issue" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/issue0"
  },
  "simd" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/simd0"
  },
  "simf" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/simf0"
  },
  "lsu" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/lsu0"
  },
  "sgpr" => 
  {
    "hierarchy" => "gpu_tb/DUT[0]/sgpr0"
  },
  "vgpr" =>
  {
    "hierarchy" => "gpu_tb/DUT[0]/vgpr0"
  }
};
########################################################

########################################################
#Check for module tree completeness
foreach $module (keys %$module_hash_ref)
{
  if(exists $module_hash_ref->{$module}->{"children"})
  {
    foreach $child (keys %{$module_hash_ref->{$module}->{"children"}})
    {
      #print "$module\t$child\t$module_hash_ref->{$module}->{\"children\"}->{$child}\n";
      if(! exists $module_hash_ref->{$child})
      {
        print STDERR "$script_name: You have made a mistake while editing the module hash reference.\n";
        print STDERR "$script_name: Module $module has a child $child which is not defined as a module in the hash.\n";
        die;
      }
    }
  }
}
#TODO: cyclic parent-child relationships should be caught here
#TODO: Such a relationship will currently lead to a hang when calculating overall area
########################################################

########################################################
#Parse command line arguments and check for sanity
$opt_result = GetOptions(
  "outdir=s"       => \$outdir,
  "force"          => \$force,
  "missing"        => \$missing,
  "pick=s"         => \$pick,
  "dontpick=s"     => \$dontpick,
  "backwardsaif=s" => \$backsaif,
  "list"           => \$list,
  "allbutsynth"    => \$allbutsynth,
  "skiprtlbuild"   => \$skiprtlbuild,
  "help"           => \$help
);

# Error if there are unrecognized arguments
if(!$opt_result)
{
  print STDERR "$script_name: Invalid command line options!\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}

# Print help message and exit for -h
if($help)
{
  print_help();
  exit 0;
}

# With no module selection arguments and no -f, error out if directory exists
if((-d $outdir) && (0 == $force) && (0 == $missing) && ("" eq $pick) && ("" eq $dontpick) && (0 == $list))
{
  print STDERR "$script_name: Synthesis directory $outdir already exists! Use -f to overwrite or one of -m,-p or -d for partial synthesis or try another name.\n";
  die;
}

# -m is used; pick missing modules for synthesis
if((1 == $missing) && ("" eq $pick) && ("" eq $dontpick))
{
  `mkdir -p $outdir`;
  #Find standalone area of each module from pre-existing area reports
  find_myareaPower();
  foreach $module (keys %$module_hash_ref)
  {
    if((-e "$outdir/$module.syn.v") && ($module_hash_ref->{$module}->{"myarea"} != 0))
    {
      $module_hash_ref->{$module}->{"synthesize"} = "no";
    }
    else
    {
      $module_hash_ref->{$module}->{"synthesize"} = "yes";
    }
  }
}
# -p is used; pick specified modules for synthesis
elsif((0 == $missing) && ("" ne $pick) && ("" eq $dontpick))
{
  `mkdir -p $outdir`;
  foreach $module (keys %$module_hash_ref)
  {
    $module_hash_ref->{$module}->{"synthesize"} = "no";
  }
  $pick =~ s/\s+/ /g;
  @listed_modules = split(" ",$pick);
  foreach $module (@listed_modules)
  {
    if(exists $module_hash_ref->{$module})
    {
      if((0 == $force) && (-e "$outdir/$module.syn.v"))
      {
        print STDERR "$script_name: Synthesized file $outdir/$module.syn.v exists for module $module specified with -p. Use -f to overwrite this and other synthesized files if any\n";
        die;
      }
      else
      {
        $module_hash_ref->{$module}->{"synthesize"} = "yes";
      }
    }
    else
    {
      print STDERR "$script_name: Module $module specified with -p is invalid.\n";
      print STDERR "$script_name: Use -help if you need it :)\n";
      die;
    }
  }
}
# -d is used; exclude specified modules for synthesis
elsif((0 == $missing) && ("" eq $pick) && ("" ne $dontpick))
{
  `mkdir -p $outdir`;
  foreach $module (keys %$module_hash_ref)
  {
    $module_hash_ref->{$module}->{"synthesize"} = "yes";
  }
  $dontpick =~ s/\s+/ /g;
  @listed_modules = split(" ",$dontpick);
  foreach $module (@listed_modules)
  {
    if(exists $module_hash_ref->{$module})
    {
      $module_hash_ref->{$module}->{"synthesize"} = "no";
    }
    else
    {
      print STDERR "$script_name: Module $module specified with -d is invalid.\n";
      print STDERR "$script_name: Use -help if you need it :)\n";
      die;
    }
  }
  foreach $module (keys %$module_hash_ref)
  {
    if(($module_hash_ref->{$module}->{"synthesize"} eq "yes") && (0 == $force) && (-e "$outdir/$module.syn.v"))
    {
      print STDERR "$script_name: Synthesized file $outdir/$module.syn.v exists for module $module specified with -d. Use -f to overwrite this and other synthesized files if any\n";
      die;
    }
  }
}
#Neither of -m. -p and -d are used; select all modules for synthesis
elsif((0 == $missing) && ("" eq $pick) && ("" eq $dontpick))
{
  `rm -rf $outdir`;
  `mkdir -p $outdir`;
  foreach $module (keys %$module_hash_ref)
  {
    $module_hash_ref->{$module}->{"synthesize"} = "yes";
  }
}
# more than one of -m , -p and -d are used; error condition
else
{
  print STDERR "$script_name: Only one of -m,-p or -d are allowed.\n";
  print STDERR "$script_name: Use -help if you need it :)\n";
  die;
}

# If list is specified, print the selected modules and exit
if(1 == $list)
{
  print "If launched without -l, $script_name would have synthesized following modules:\n";
  foreach $module (keys %$module_hash_ref)
  {
    if($module_hash_ref->{$module}->{"synthesize"} eq "yes")
    {
      print "$module\n";
    }
  }
  exit 0;
}

if($backsaif ne "")
{
  @saifparts=split(" ", $backsaif);
  if(scalar(@saifparts) != 2)
  {
    print STDERR "$script_name: -b option should have two arguments separated by space and enclosed in a single pair of quotations.\n";
    print STDERR "$script_name: Use -help if you need it :)\n";
    die;
  }
  $saiffile = $saifparts[0];
  $ddcfolder = $saifparts[1];
  if(! -e $saiffile)
  {
    print STDERR "$script_name: Saif file $saiffile does not exist.\n";
    print STDERR "$script_name: Use -help if you need it :)\n";
    die;
  }
  else
  {
    #If relative path, add ..
    if($saiffile !~ m/^\//)
    {
      $saiffile = "../$saiffile";
    }
  }
  if(! -e $ddcfolder)
  {
    print STDERR "$script_name: ddc folder $ddcfolder does not exist.\n";
    print STDERR "$script_name: Use -help if you need it :)\n";
    die;
  }
  else
  {
    #If relative path, add ..
    if($ddcfolder !~ m/^\//)
    {
      $ddcfolder = "../$ddcfolder";
    }
  }
}
########################################################

########################################################
#Clean and build rtl
if(0 == $skiprtlbuild)
{
  `cd ../../src/verilog/tb && make clean && make build`;
}
########################################################

########################################################
#Generate verilog file list

#first push the header line
push(@common_file_list, "set my_verilog_files [ list \\\n");

#Now push the definition files
@part_of_list = `cd $outdir && ls ../../../src/verilog/rtl/*/build/*.v | grep -v "/rtl/tracemon/build/" | grep -v "/rtl/memory/build/" | grep -v "/rtl/instr_buffer/build/" | grep "_definitions.v" | sed -e 's/\\\(.*\\\)/& \\\\/g'`;
#chomp(@part_of_list);
@common_file_list = (@common_file_list, @part_of_list);

#Now push all verilog files other than definitions
@part_of_list = `cd $outdir && ls ../../../src/verilog/rtl/*/build/*.v | grep -v "/rtl/tracemon/build/" | grep -v "/rtl/memory/build/" | grep -v "/rtl/instr_buffer/build/" | grep -v "_definitions.v" | sed -e 's/\\\(.*\\\)/& \\\\/g'`;
#chomp(@part_of_list);
@common_file_list = (@common_file_list, @part_of_list);

#Finally push the trailer line
push(@common_file_list, "]\n");
########################################################

########################################################
#Synthesize each module
foreach $module (keys %$module_hash_ref)
{
  if($module_hash_ref->{$module}->{"synthesize"} eq "yes")
  {
    #Copy of file list for this module
    @custom_file_list = @common_file_list;
    $list_size = scalar(@custom_file_list);

    #Create stubs for children and replace verilog file of children in file list with the stub name
    if(exists $module_hash_ref->{$module}->{"children"})
    {
      foreach $child (keys %{$module_hash_ref->{$module}->{"children"}})
      {
        for($i=0; $i<$list_size; $i=$i+1)
        {
          if($custom_file_list[$i] =~ m/\/$child.v \\\s*$/)
          {
            $custom_file_list[$i] =~ s/ \\\s*$//;
            $custom_file_list[$i] =~ s/^\.\.\///;
            create_stub($custom_file_list[$i],"$outdir/$child.stub.v");
            $custom_file_list[$i] = "$child.stub.v \\\n";
            last;
          }
        }
        if($i == $list_size)
        {
          print STDERR "$script_name: Child $child of module $module not found in file list\n";
          die;
        }
      }
    }

    #Generate the file list
    open(LISTFILE,">$outdir/$module.filelist.tcl");
    print LISTFILE "@custom_file_list";
    close(LISTFILE);

    #Generate the synthesis script
    open(SCRIPTTEMPLATE,"synthscr.tcl");
    @synth_script = <SCRIPTTEMPLATE>;
    close(SCRIPTTEMPLATE);
    $script_size = scalar(@synth_script);
    for($i=0; $i<$script_size; $i=$i+1)
    {
      $synth_script[$i] =~ s/#CUESYNTHSCR_SAIFMAPSTART/saif_map -start/;
      if($backsaif ne "")
      {
        $synth_script[$i] =~ s/#CUESYNTHSCR_SAIFORNOT/set saif_analysis yes/;
        $synth_script[$i] =~ s/#CUESYNTHSCR_SAIFREADDDC/read_file -format ddc $ddcfolder\/$module.syn.ddc/;
        $synth_script[$i] =~ s/#CUESYNTHSCR_READSAIF/read_saif -auto_map_names -input $saiffile -instance_name $module_hash_ref->{$module}->{"hierarchy"} -verbose/;
        $synth_script[$i] =~ s/#CUESYNTHSCR_REPORTSAIF/report_saif -hier -rtl_saif -missing > \$filename/;
      }
      else
      {
        $synth_script[$i] =~ s/#CUESYNTHSCR_SAIFORNOT/set saif_analysis no/;
      }
      $synth_script[$i] =~ s/#CUESYNTHSCR_TOPLEVEL/$module/;
      $synth_script[$i] =~ s/#CUESYNTHSCR_FILELIST/$module.filelist.tcl/;
      if(($synth_script[$i] =~ m/#CUESYNTHSCR_STUBDONTTOUCH/) && (exists $module_hash_ref->{$module}->{"children"}))
      {
        foreach $child (keys %{$module_hash_ref->{$module}->{"children"}})
        {
          $synth_script[$i] = "$synth_script[$i]set_dont_touch $child true\n";
        }
      }
    }
    open(SYNTHSCRIPT,">$outdir/$module.synth.scr");
    print SYNTHSCRIPT "@synth_script";
    close(SYNTHSCRIPT);

    #Synthesize module and remove synthesized stubs if any
    if(0 == $allbutsynth)
    {
      $starttime = time;
      system("cd $outdir && dc_shell-t -f $module.synth.scr |& tee $module.synth.log");
      $endtime = time;
      $elapsedtime = $endtime - $starttime;
      system("echo \"Elapsed wall time in $hostname: $elapsedtime\"");
      system("echo \"Elapsed wall time in $hostname: $elapsedtime\" >> $outdir/$module.synth.log");
      if(exists $module_hash_ref->{$module}->{"children"})
      {
        `rm -rf $outdir/$module.syn.v.bak`;
        foreach $child (keys %{$module_hash_ref->{$module}->{"children"}})
        {
          if(-e "$outdir/$module.syn.v")
          {
            remove_module("$outdir/$module.syn.v", $child);
          }
        }
      }
    }
  }
}
########################################################

########################################################
##Parse area reports and Generate overall area report

#Find standalone areas of each module
find_myareaPower();

#Find cumulative areas, based on recursive calls
open(AREASUMMARY,">$outdir/area.summary");
#the following line fixes a weird alignment bug; each push to an array except the first one insets a space!
push(@area_summary,"");
calculate_area("compute_unit","");
push(@area_summary,"\n");
print AREASUMMARY "@area_summary";
close(AREASUMMARY);

#Summarize power in a file
open(POWERSUMMARY,">$outdir/power.summary");
#the following line fixes a weird alignment bug; each push to an array except the first one insets a space!
push(@power_summary,"");
calculate_power("compute_unit","");
push(@power_summary,"\n");
print POWERSUMMARY "@power_summary";
close(POWERSUMMARY);
########################################################

########################################################
#subroutine for creating a stub
sub create_stub
{
  my ($infile,$outfile) = @_;
  my @in_file;
  my @out_file;
  my $infile_size;
  my $i;
  my $line = 0;
  my $outputs;
  my @output_list;
  my $out;
  my @tieoffs = ();

  open(INFILE,"$infile");
  @in_file = <INFILE>;
  close(INFILE);

  $infile_size = scalar(@in_file);
  for($i=0; $i<$infile_size; $i=$i+1)
  {
    if($in_file[$i] =~ m/^\s*(module|input|output)\s*/)
    {
      $out_file[$line] = $in_file[$i];
      while($out_file[$line] !~ m/;\s*$/)
      {
        $i = $i + 1;
        $out_file[$line] = "$out_file[$line]$in_file[$i]";
      }
      if($out_file[$line] =~ m/^\s*output\s*/)
      {
        $outputs = $out_file[$line];
        $outputs =~ s/^\s*output\s*//;
        $outputs =~ s/\s*//g;
        $outputs =~ s/^\[.*\]//g;
        $outputs =~ s/;$//g;
        @output_list = split(",",$outputs);
        foreach $out (@output_list)
        {
          #Removed
          #There is no need to tie off outputs to 0!
          #push(@tieoffs, "assign $out = 'd0;\n");
        }
      }
      $line = $line + 1;
    }
    elsif($in_file[$i] =~ m/^\s*endmodule\s*/)
    {
      @out_file = (@out_file,@tieoffs);
      push(@out_file,$in_file[$i]);
      last;
    }
  }

  open(OUTFILE,">$outfile");
  print OUTFILE @out_file;
  close(OUTFILE);
}
########################################################

########################################################
#subroutine for removing a module
sub remove_module
{
  my ($infile,$module) = @_;
  my @in_file;
  my @out_file = ();
  my $infile_size;
  my $i;

  open(INFILE,"$infile");
  @in_file = <INFILE>;
  close(INFILE);

  $infile_size = scalar(@in_file);
  for($i=0; $i<$infile_size; $i=$i+1)
  {
    if($in_file[$i] =~ m/^\s*module\s+$module\s*\(/)
    {
      while($in_file[$i] !~ m/\s*endmodule\s*$/)
      {
        $i = $i + 1;
      }
    }
    else
    {
      push(@out_file, $in_file[$i]);
    }
  }
  if(!(-e "$infile.bak"))
  {
    `mv $infile $infile.bak`;
  }
  else
  {
    `rm -rf $infile`;
  }
  open(OUTFILE,">$infile");
  print OUTFILE "@out_file";
  close(OUTFILE);
}
########################################################

########################################################
#Find standalone area,power of all modules
sub find_myareaPower
{
  my $module;
  our $outdir;
  my $i;
  my $j;
  my @area_file;
  my $area_file_size;
  my @power_file;
  my $power_file_size;
  my @line_parts;
  my $raw_power;
  my $power_exponent;

  foreach $module (keys %$module_hash_ref)
  {
    if(-e "$outdir/$module.area.rpt")
    {
      open(AREAFILE,"$outdir/$module.area.rpt");
      @area_file = <AREAFILE>;
      close(AREAFILE);
      $area_file_size = scalar(@area_file);
      for($i=0; $i<$area_file_size; $i=$i+1)
      {
        if($area_file[$i] =~ m/^Total area:\s*(.*)/)
        {
          $module_hash_ref->{$module}->{"myarea"} = $1;
          $module_hash_ref->{$module}->{"myarea"} =~ s/undefined/0/;
          last;
        }
      }
      if($i == $area_file_size)
      {
        $module_hash_ref->{$module}->{"myarea"} = 0;
      }
    }
    else
    {
      $module_hash_ref->{$module}->{"myarea"} = 0;
    }
    #Find power
    if(-e "$outdir/$module.power.rpt")
    {
      open(POWERFILE,"$outdir/$module.power.rpt");
      @power_file = <POWERFILE>;
      close(POWERFILE);
      $power_file_size = scalar(@power_file);
      for($i=$power_file_size-1; $i>=0; $i=$i-1)
      {
        if($power_file[$i] =~ m/^$module\s+/)
        {
          @line_parts = split(" ",$power_file[$i]);
          $raw_power = $line_parts[4];
          if( $raw_power =~ m/^((\d|\.)+)e\+(\d+)$/)
          {
            $raw_power = $1;
            $power_exponent = $3;
            for($j=1; $j<=$power_exponent; $j=$j+1)
            {
              $raw_power = $raw_power * 10;
            }
          }
          $module_hash_ref->{$module}->{"mypower"} = $raw_power;
          last;
        }
      }    
      if($i == 0)
      {
        $module_hash_ref->{$module}->{"mypower"} = 0;
      }
    }
    else
    {
      $module_hash_ref->{$module}->{"mypower"} = 0;
    }
  }
}
########################################################

########################################################
#Subroutine to calculate area of a module, by means of recursive calls
sub calculate_area
{
  my ($module,$alignment) = @_;
  our $module_hash_ref;
  my $child;
  my $child_area;
  my $effective_child_area;
  our @area_summary;

  if( exists $module_hash_ref->{$module}->{"cactii_area"} )
  {
    $module_hash_ref->{$module}->{"area"} = $module_hash_ref->{$module}->{"cactii_area"};
  }
  else
  {
    $module_hash_ref->{$module}->{"area"} = $module_hash_ref->{$module}->{"myarea"};
  }

  if (exists $module_hash_ref->{$module}->{"children"})
  {
    foreach $child (keys %{$module_hash_ref->{$module}->{"children"}})
    {
      $child_area = calculate_area($child,"$alignment   ");
      $effective_child_area = $module_hash_ref->{$module}->{"children"}->{$child} * $child_area;
      push(@area_summary,"$module_hash_ref->{$module}->{\"children\"}->{$child}*$child_area = $effective_child_area\n");
      $module_hash_ref->{$module}->{"area"} =  $module_hash_ref->{$module}->{"area"} + $effective_child_area;
    }
  }
  push(@area_summary,"$alignment$module = $module_hash_ref->{$module}->{\"area\"};");
  return $module_hash_ref->{$module}->{"area"};
}
########################################################

########################################################
sub calculate_power
{
#  our @power_summary;
#  our $module_hash_ref;
#  my $module;

#  foreach $module (keys %$module_hash_ref)
#  {
#    push(@power_summary, "$module  $module_hash_ref->{$module}->{\"mypower\"}\n");
#  }
  my ($module,$alignment) = @_;
  our $module_hash_ref;
  my $child;
  my $child_power;
  my $effective_child_power;
  our @power_summary;

  if( exists $module_hash_ref->{$module}->{"cactii_power"} )
  {
    $module_hash_ref->{$module}->{"power"} = $module_hash_ref->{$module}->{"cactii_power"};
  }
  else
  {
    $module_hash_ref->{$module}->{"power"} = $module_hash_ref->{$module}->{"mypower"};
  }
  
  if (exists $module_hash_ref->{$module}->{"children"})
  {
    foreach $child (keys %{$module_hash_ref->{$module}->{"children"}})
    {
      $child_power = calculate_power($child,"$alignment   ");
      $effective_child_power = $module_hash_ref->{$module}->{"children"}->{$child} * $child_power;
      push(@power_summary,"$module_hash_ref->{$module}->{\"children\"}->{$child}*$child_power = $effective_child_power\n");
      $module_hash_ref->{$module}->{"power"} =  $module_hash_ref->{$module}->{"power"} + $effective_child_power;
    }
  }
  push(@power_summary,"$alignment$module = $module_hash_ref->{$module}->{\"power\"};");
  return $module_hash_ref->{$module}->{"power"};
}
########################################################

########################################################
#Subroutine for help message
sub print_help
{
print STDOUT qq{$script_name:

DESCRIPTION:
	This script synthesizes MIAOW rtl using synopsys DC compiler. Since the design is large and cannot synthesize as one piece due to excessive memory consumtion during the elaborate phase, it is broken down into chunks (called "modules" henceforth) and the synthesized netlist is stitched together.

FIXME:
	The script does not set the timing constraints correctly for paths that are crossing two "modules".

HARDCODED INPUTS:
	Hardcoded into the script, is a tree of "module" hierarchy which defines the way in which the MIAOW design should be broken down for synthesis. You dont have to change this unless synthesis fails after running out of memory. If you want to change this, search for "#FINDME_MODULE_HIERARCHY" in the script. "children" of a "module" defines the hierarchy.

FUNCTIONALITY:
-Cleans and builds MIAOW rtl
-Generates the verilog file list for each "module" chosen (using -m/-p/-d) for synthesis. See <outdir>/<module>.filelist.tcl 
-Creates stubs for children of each selected module. See <outdir>/<child>.filelist.tcl
-Generates the synthesis script for each module. See <outdir>/<module>.synth.scr. [These are generated based on /miaow/syn/synopsys/synthscr.tcl
-Synthesize each chosen "module". See .syn.bak.v, .synth.log, .area.rpt and .timing.rpt
-Cleans up the synthesized stubs present in .syn.bak.v and generates .syn.v
-Creates an area summary showing the area split-up. See area.summary.

USAGE and COMMAND LINE ARGUMENTS:
	$script_name [-o outputdir] [-f] [-m | -p <module list> | -d <module list>] [-l] [-a] [-s] [-h]

-o
-outdir <outputdir>		Specifies the path of the synthesis directory relative to /miaow/syn/synopsys. If not used, the default output directory is synth/

-m
-missing			Use this option to synthesize only the "modules" which failed synthesis in a previous synthesis attempt. Only one out of -m,-p,-d can be used.

-p
-pick <module list>		Use this option to synthesize only the list of specified modules. For specifying multiple modules, use a string in quotes with module names separated by spaces. eg, -p "vgpr rfa". Only one out of -m,-p,-d can be used.

-d
-dontpick <module list>		Use this option to synthesize all modules except the specified ones. Only one out of -m,-p,-d can be used.

-f
-force				This option serves TWO PURPOSES.
CASE1: -m/-p/-d is NOT used
	In this case -f will clean the output directory if it already exists.
CASE2: -m/-p/-d is used
	If -m/-p/-d is used, it is expected that the output directpry already does exist. So, the use of -f as in CASE1 is redundant. In this case -f is used to force overwriting an already existing netlist (.syn.v) from a previous synthesis.

-l
-list				If specified $script_name does not perform any synthesis. Instead, it will just list out the names of the "modules" which will be synthesized. This option is particularly useful, if you intend to use -m/-p/-d.

-a
-allbutsynth			This option performs everything except the actual synthesis using DC compiler. It creates the file lists for each "module", then goes on to create stubs for any sub-"modules" or children of the current "module". It also regenerates the area.sumamry. So this can be handy if you already have completed synthesis and just want to edit the script to report the area in a different format. This is also handy if you just want to check the generated synthesi scripts or the generated stub modules.

-s
-skiprtlbuild			By default, $script_name cleans and builds rtl before synthesis. This option can be used to skip this step. Can be handy if you want to try synthesis with a temporary fix in a .v file residing in a build folder.

-h
-help				Well, you know what this option is for! You couldn't be reading this otherwise.

EXAMPLE USAGE:
	$script_name -o synth_julgamento_1 -f
	The above launch will start a fresh synthesis overwriting the directory synth_julgamento_1 is it already exists

	$script_name -o synth_julgamento_1 -m -l
	The above launch will just list out the modules which are missing in the already existing synth_julgamento_1 synthesis directory

	$script_name -o synth_julgamento_1 -p "vgpr sgpr exec"
	The above launch will synthesize only the three listed modules. Will fail if a netlist for one of these modules already exists.

	$script_name -o synth_julgamento_1 -p "vgpr sgpr exec" -f
	The above launch will synthesize only the three listed modules. Will overwrit a netlist if it already exists.
};
}
########################################################
