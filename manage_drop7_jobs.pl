#!/usr/bin/perl

use strict;

#
# This is a frontend for breaking up the work that is done by drop7.c so that
# we can call multiple instances of drop7.c to take advantage of multple CPUs.
# You tell this tool how many CPUs you have and what your drop7 'worksize' is
# (a ws of 10 means you run permutations on sets of 10 disc at a time).  This
# tool then calls $number_of_cpus drop7.c processes where each takes an equal
# number of permutations to analyze.
#

my $number_of_cpus = 4;
my $worksize = 10;

# L1 -> L71
my @known_disc = qw(2, 1, 1, 26, 4, 5, 25, 25, 21, 6, 1, 5, 7, 5, 3, 6, 3, 22, 6, 24, 2, 5, 7, 1, 22, 5, 21, 23, 22, 4, 5, 5, 22, 21, 26, 22, 3, 2, 3, 22, 23, 6, 2, 7, 7, 6, 23, 22, 26, 4, 7, 4, 5, 4, 3, 6, 1, 26, 1, 5, 27, 4, 6, 3, 25, 7, 4, 3, 5, 2, 26, 2, 7, 2, 1, 4, 7, 24, 4, 2, 7, 3, 25, 5, 5, 21, 27, 7, 27, 2, 27, 2, 23, 2, 3, 22, 2, 26, 25, 24, 26, 5, 27, 2, 6, 27, 27, 25, 4, 2, 23, 7, 2, 3, 22, 1, 23, 4, 1, 23, 21, 1, 6, 21, 5, 7, 25, 2, 5, 5, 26, 3, 25, 24, 5, 7, 4, 1, 23, 5, 1, 6, 4, 27, 3, 7, 3, 7, 27, 4, 24, 1, 5, 21, 5, 1, 24, 4, 23, 4, 7, 4, 3, 1, 24, 5, 25, 27, 25, 25, 1, 3, 26, 22, 2, 3, 7, 5, 4, 5, 6, 1, 6, 27, 1, 1, 22, 7, 3, 7, 2, 22, 27, 7, 24, 26, 5, 7, 5, 7, 26, 7, 4, 6, 5, 1, 26, 3, 4, 27, 7, 5, 2, 6, 1, 3, 27, 6, 4, 7, 3, 7, 26, 5, 25, 6, 2, 4, 3, 3, 25, 7, 24, 7, 21, 25, 4, 23, 6, 5, 21, 27, 7, 1, 5, 6, 1, 7, 24, 6, 3, 6, 1, 1, 21, 5, 6, 4, 7, 7, 4, 24, 22, 25, 23, 24, 24 , 24, 23, 4, 23, 3, 22, 1, 24, 7, 2, 7, 25, 23, 6, 23, 22, 4, 6, 2, 2, 5, 7, 1, 7, 25, 3, 7, 1, 4, 23, 2, 2, 27, 3, 2, 4, 22, 6, 7, 1, 3, 4, 6, 22, 24, 23, 22, 2, 7, 25, 5, 6, 27, 21, 21, 4, 23, 4, 33, 1, 6, 25, 2, 22, 25, 3, 21, 7, 2, 2, 1, 1, 7, 7, 27, 1, 4, 4, 1, 21, 24, 4, 4, 4, 4, 1, 4, 5, 27, 2, 2, 24, 7, 4, 5, 3, 2, 23, 7, 1, 24, 27, 27, 3, 22, 6, 2, 23, 2, 2, 25, 26, 4, 6, 2, 7, 23, 7, 6, 1, 22, 3, 5, 4, 6, 25, 26, 1, 3, 4, 1, 1, 21, 1, 3, 6, 24, 21, 21, 6, 7, 7, 23, 5, 3, 3, 4, 6, 3, 4, 22, 1, 21, 4, 25, 23, 6, 6, 25, 6, 2, 4, 1, 7, 7, 1, 5, 22, 2, 22, 5, 3, 2, 23, 2, 1, 2, 21, 25, 26, 3, 5, 26, 2, 27, 6, 1, 25, 24, 4, 3, 7, 1, 2, 2, 7, 7, 3, 6, 2, 1, 26, 7, 2, 3, 25, 1, 4, 4, 7, 3, 1, 1, 7, 1, 24, 4, 5, 26, 4, 24, 3, 4, 4, 6, 1, 7, 22, 5, 2, 25, 5, 1, 1, 5, 26, 6, 3, 6, 7, 3, 7, 4, 5, 2, 2, 24, 7, 4, 4, 4, 4, 25, 6, 5, 3, 4, 26, 21, 6, 6, 27, 2, 27, 6, 1, 3, 24, 2, 7, 27, 24, 6, 5, 3, 6, 23, 25, 1, 4, 4, 7, 2, 6, 25, 7, 2, 2, 4, 1, 27, 23, 7, 6, 5, 24, 2, 1, 5, 5, 3, 6, 22, 3, 26, 5, 2, 3, 6, 4, 1, 27, 7, 22, 1, 7, 7, 24, 4, 3, 1, 1, 24, 23, 27, 3, 21, 5, 6, 2, 24, 1, 26, 27, 7, 21, 24, 7, 7, 3, 21, 1, 1, 1, 3, 6, 27, 2, 4, 7, 7, 4, 21, 22, 23, 27, 7, 5, 2, 3, 27, 1, 7, 5, 2, 24, 4, 4, 7, 1, 2, 5, 22, 24, 4, 6, 24, 4, 22, 5, 7, 1, 3, 3, 23, 4, 5, 22, 3, 1, 4, 5, 1, 1, 23, 1, 27, 25, 3, 26, 24, 3, 3, 3, 26, 24, 3, 3, 1, 27, 24, 1, 6);

my $number_of_known_disc = $#known_disc;
my $total_number_of_permutations = 7 ** $worksize;
my $per_cpu_number_of_permutations = int($total_number_of_permutations/$number_of_cpus);

#
# Save the permutations that will act as starting points for the drop7.c process
# that we start.  We do this so that we don't have to recompute what the actual
# permutations everytime we start a new drop7.c process.
#
my $permutations_filename = "permutations_ws$worksize" . "_core$number_of_cpus" . ".txt";
if (!(-e $permutations_filename)) {
   my @wanted_permutations = ();
   for (my $i = 0; $i < $number_of_cpus; $i++) {
      push @wanted_permutations, $i == 0 ? 0 : ($i * $per_cpu_number_of_permutations) + 1;
   }

   my $wanted_permutations_string = join(" ", @wanted_permutations);
   print "./permutations.cgi -ws $worksize $wanted_permutations_string > $permutations_filename\n";
   system "./permutations.cgi -ws $worksize $wanted_permutations_string > $permutations_filename";
}


#
# Read all of the starting permutations from the file and put them in a hash.  There will be one
# for every $number_of_cpus
#
my %starting_permutations;
open(FH, $permutations_filename) || die("\nERROR: Could not open $permutations_filename\n\n");
while (<FH>) {
   chomp();
   (my $index, my $perm) = split(":", $_);
   $starting_permutations{$index} = $perm;
}

# Edit this to contain the starting permutation that gives you the best score you've been able to come up with
# This sequence will get you to the x29 chain at the end of Level 2.
my @answer_so_far = qw(1 3 3 2 3 5 5 6 3 7 6 5 4 2 3 1 7 4 1 6 5 2 7 1 2 3 2 3 2 4 6 6 3 2 4 3 1 4 3 7 4 5 5 6 6 3 1 5 2 3 2 7 2 7 5 3 7 5 6);

my $starting_disc = 0;
my $seq_to_load = "";

if ($#answer_so_far >= 0) {
   $starting_disc= $#answer_so_far+1;
   $seq_to_load = join(" ", @answer_so_far);
}


my $next_disc_index = 0;
for (my $disc_index = $starting_disc; $disc_index <= $number_of_known_disc; $disc_index = $next_disc_index) {

   printf("Finding MAX_SCORE for starting disc #%d\n", $disc_index);
   printf("===============================\n");

   my $fds = 0;
   if ($seq_to_load) {
      my @tmp = split(" ", $seq_to_load);
      $fds = $#tmp + 1;
      $seq_to_load = "-seq $seq_to_load";
   }

   #
   # Split up the work based on how many CPUs we have
   #
   for (my $i = 0; $i < $number_of_cpus; $i++) {
      my $starti = $i == 0 ? 0 : ($i * $per_cpu_number_of_permutations) + 1;
      if (!$starting_permutations{$starti}) {
         die("ERROR: starting_permutations{$starti} is NULL\n");
      }

      my $cmd = sprintf("./drop7.cgi -i%s -ws %d -fds %d -starti %d -startperm $starting_permutations{$starti} -endi %d $seq_to_load > /tmp/drop7_ws%d_DI%d_FDS%d_thread%d &",
                        $i,
                        $worksize,
                        $fds,
                        $starti,
                        $i == $number_of_cpus-1 ? $total_number_of_permutations : ($i+1) * $per_cpu_number_of_permutations,
                        $worksize,
                        $disc_index,
                        $fds,
                        $i);
      print "$cmd\n";
      system $cmd;
   }


   #
   # Wait for all of the C drop7 jobs to finish running
   #
   my $drop7s_running = 1;
   while($drop7s_running) {
      $drop7s_running = 0;
      foreach my $line (split(/\n/, `ps -ef | grep drop7.cgi`)) {
         next if ($line =~ /grep/);
         if ($line =~ /drop7/) {
            $drop7s_running = 1;
            print ".";
            last;
         }
      }
      sleep 1;
   }
   print "\n";


   #
   # Now that all of the drop7 jobs for this set have finished, parse through
   # their output and see which one found the permutation with the highest score.
   #
   my $max_score = 0;
   my $max_score_permutation_index = "";
   my $max_score_permutation_seq = "";
   $next_disc_index = 0;
   for (my $i = 0; $i < $number_of_cpus; $i++) {
      my $filename = sprintf("/tmp/drop7_ws%d_DI%d_FDS%d_thread%d", $worksize, $disc_index, $fds, $i);
      open(FH, $filename) || die("\nERROR: could not open $filename\n\n");
      while(<FH>) {
         if (/DISC\[(\d+)\]: CHAIN POTENTIAL SCORE:\s+(\d+)/) {
            if ($2 > $max_score) {
               $max_score_permutation_index = $1;
               $max_score = $2;
            } else {
               last;
            }

         } elsif (/CHAIN SETUP PERMUTATION: '\s*(.*?)\s*'$/ ||
                  /CHAIN EXECUTE PERMUTATION: '\s*(.*?)\s*'$/) {
            $max_score_permutation_seq = $1;
            my @tmp = split(" ", $max_score_permutation_seq);
            $next_disc_index = $#tmp;
         }
      }
      close FH;
   }

   print "DISC[$disc_index] MAX_SCORE $max_score, PERMUTATION[$max_score_permutation_index] $max_score_permutation_seq\n\n";
   $seq_to_load = $max_score_permutation_seq;

   if (!$max_score) {
      print "HMMM, you seem to be stuck in an end of game situation\n";
   }

   if (!$next_disc_index || $max_score_permutation_index >= $number_of_known_disc-1) {
      print "\nnext_disc_index is 0....our work here is done\n\n";
      exit();
   }

   if ($next_disc_index > $number_of_known_disc) {
      print "\nnext_disc_index $next_disc_index >= number_of_known_disc $number_of_known_disc\n\n";
      exit();
   }
}
