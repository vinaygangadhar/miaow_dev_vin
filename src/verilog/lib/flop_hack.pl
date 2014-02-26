#!/usr/bin/perl -w
use warnings "all";
use strict;

my $raw_lib = "saed32nm.v";
my $flop_hack = "flop_hack.v";
my $out_lib = "saed32nm_modified.v";
my @rawfile;
my $rawsize;
my @hackfile;
my @outfile = ();
my $i;
my $in_dff;

open(RAWFILE,"$raw_lib");
@rawfile = <RAWFILE>;
#chomp(@rawfile);
close(RAWFILE);
$rawsize = scalar(@rawfile);

open(HACKFILE,"$flop_hack");
@hackfile = <HACKFILE>;
#chomp(@hackfile);
close(HACKFILE);

$in_dff = 0;
for($i=0; $i<$rawsize; $i=$i+1)
{
  if(($rawfile[$i] =~ m/^module \w*DFF\w* \(/) && ($in_dff == 0))
  {
    $in_dff = 1;
  }
  elsif(($rawfile[$i] =~ m/^endmodule/) && ($in_dff == 1))
  {
    @outfile = (@outfile, @hackfile);
    $in_dff = 0;
  }
  if($rawfile[$i] !~ m/^`timescale/)
  {
    push(@outfile,$rawfile[$i]);
  }
}

open(OUTFILE,">$out_lib");
print OUTFILE @outfile;
close(OUTFILE);
