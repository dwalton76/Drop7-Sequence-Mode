#!/usr/bin/perl

use strict;

my @columns;
my @delays;

my $input_file = $ARGV[0];
if (!$input_file) {
   die("\nERROR: You must specify the html file to parse on the command line\n\n");
}

open(FH, $input_file) || die("\nERROR: could not open $input_file\n");
my $curr_column = 0;
my $prev_column = 0;
my $chain = 0;
my $grid_cleared = 0;
my $levelup = 0;
my $first_disc = 1;
while(<FH>) {
   if (/CHAINx(\d+)/) {
      $chain = $1;

   } elsif (/GRID_CLEARED/) {
      $grid_cleared = 1;

   } elsif (/EOL - added new row/) {
      $levelup = 1;

   } elsif (/Adding DISC/) {
      if ($first_disc) {
         $first_disc = 0;
      } else {

         my $delay = 0;
         if (!$chain) {
           # if ($curr_column == $prev_column) {
           #    $delay = 1600;
           # } else {
           #    $delay = 0;
           # }
               $delay = 0;
         } else {
            $delay = $chain * 1600;
         }
         
         if ($grid_cleared) {
            $delay += 2500;
         }

         if ($levelup) {
            $delay += 2500;
         }

         push @delays, $delay;

         $chain = 0;
         $grid_cleared = 0;
         $levelup = 0;
      }

      <FH>;
      <FH>;
      <FH>;
      <FH>;
      $_ = <FH>;
      if (/COLUMN:\s+(\d)/) {
         push @columns, $1;
         $prev_column = $curr_column;
         $curr_column = $1;
      }
   }
}

# Loop through and put in a delay of 1000ms anytime there is 0 delay AND we aren't moving off the current column
for (my $i = 0; $i < $#columns; $i++) {
   if (!$delays[$i]) {
      if ($columns[$i] == $columns[$i + 1]) {
         $delays[$i] = 1000;
      }
   }
}

#print "COLUMNS: \n";
print "   unsigned char column_drop[] = {";
print join(",", @columns);
print "};\n\n";

#print "\nDELAYS: \n";
print "   unsigned int column_delay[] = {";
print join(",", @delays);
print "};\n\n";

close FH;
close OUTPUT;

