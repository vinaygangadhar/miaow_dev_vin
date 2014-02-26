#!/usr/bin/perl -w

use strict;

my @errors = (0,10,20,100,1000);
my @runtimes;
my $output;

`rm -rf results/with_error*`;
print "\n";

foreach my $curr_error (@errors){
    print "Running with 1/$curr_error\n";
    `./run.pl -r 6 -t with_barriers -k 100000 -e $curr_error -o with_error_$curr_error`;
    print "grep -r \"\$finish at simulation time\" results/with_error_$curr_error/with_barriers/run.log\n";
    $output = 
	`grep -r "\$finish at simulation time" results/with_error_$curr_error/with_barriers/run.log `;

    $output =~ /finish at simulation time\s*(\d+)/;
    push(@runtimes,$1);
    
}

foreach (@runtimes){
    print "$_\n"
}
