#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drop7core.h"

/*
 * To compile:
 * gcc -o drop7.cgi drop7.c drop7core.c
 */

int main(int argc, char *argv[]) {
   int worksize = 7;
   char one_set_only = 0;
   unsigned long long start_permutation_index = 0;
   unsigned long long end_permutation_index = 0;
   char seq_to_load[4096];
   memset(seq_to_load, 0, sizeof(seq_to_load));

   // 0 = Nothing special
   // 1 = parsing seq
   // 2 = parsing starting permutation
   int state = 0;

   int i;
   int z = 0;
   int future_disc_start = 0;

   unsigned char starting_permutation[20];
   memset(starting_permutation, 0, sizeof(starting_permutation));

   for (i = 0; i < argc; i++) {
      if (!strcmp(argv[i], "-ws")) {
         worksize = atoi(argv[++i]);
         state = 0;
         z = 0;

      } else if (!strcmp(argv[i], "-fds")) {
         future_disc_start = atoi(argv[++i]);
         one_set_only = 1;
         state = 0;
         z = 0;

      } else if (!strcmp(argv[i], "-seq")) {
         state = 1;

      } else if (!strcmp(argv[i], "-starti")) {
         start_permutation_index = strtoull(argv[++i], NULL, 10);
         state = 0;
         z = 0;

      } else if (!strcmp(argv[i], "-startperm")) {
         state = 2;
         z = 0;

      } else if (!strcmp(argv[i], "-endi")) {
         end_permutation_index = strtoull(argv[++i], NULL, 10);
         state = 0;
         z = 0;

      // If we get to here then we should be looking at a digit
      } else {
         if (state == 1) {
            seq_to_load[z] = atoi(argv[i]);
            z++;

         } else if (state == 2) {
            starting_permutation[z] = atoi(argv[i]);
            z++;
         }
      }
   }

   // Assume that 15 is the largest worksize we will ever have
   if (worksize > 15) {
      printf("ERROR: The max supported worksize is 15\n");
      return 0;
   }

   printf("Content-type: text/html\r\n\r\n");
   printf("<!DOCTYPE>\n");
   printf("<head>\n");
   printf("<link rel='stylesheet' type='text/css' href='/drop7.css'>\n");
   printf("</head>\n");
   printf("<body>\n");
   printf("<pre>\n");

   /*
    * The number of permutations grows exponentially and after you get above 11 discs
    * you get into the billions and trillions of combinations to try.  Needless to say
    * this doesn't scale.  For now what I'm doing is taking all of the disc that we know
    * about and breaking them down into 'worksize' chunks.  I then find the optimal
    * permutation to place each set of 'worksize' discs. This will not find the highest
    * scoring combination possible but it will find combinations that produce high scores.
    */
   int num_future_disc = sizeof(future_disc)/sizeof(future_disc[0]);
   getscore_result gsr;
   getscore_result max_score_gsr;
   memset(&max_score_gsr, 0, sizeof(getscore_result));

   // Load the initial grid
   int initial_grid[7][7] = {{26, 0, 0, 0, 0, 0, 0}, {24, 0, 0, 0, 0, 0, 0}, {25, 0, 0, 0, 0, 0, 0}, {27, 0, 0, 0, 0, 0, 0}, {25, 0, 0, 0, 0, 0, 0}, {21, 0, 0, 0, 0, 0, 0}, {23, 0, 0, 0, 0, 0, 0}};
   memcpy(&max_score_gsr.grid, &initial_grid, sizeof(initial_grid));

   // Initially all columns have a height of 1
   for (i = 0; i < 7; i++) {
      max_score_gsr.vertical_count[i] = 1;
   }

   // We start out on Level 1
   max_score_gsr.level = 1;
   max_score_gsr.disc_left_in_level = getDiscForLevel(1);

   getscore_result baseline_gsr;
   getscore_result cache_gsr[20];
   memset(&cache_gsr, 0, sizeof(cache_gsr[0]) * 20);

   /*
    * It doesn't scale to build all of the permutations and store them in memory (we are talking
    * gigs and gigs of memory) so instead we compute them on the fly everytime through this main
    * loop of worksize chunks of discs.
    */
   int permutation_init_value = 1;
   int permutation_max_value = 7;
   unsigned long long permutation_max_i = power(permutation_max_value, worksize);

   // If this is true then we already know the optimal permutation for some of the starting discs.
   // Load the permuation we've been given, call getScore and store the result in max_score_gsr.
   if (future_disc_start) {

      int current_disc[4096];
      memset(current_disc, 0, sizeof(current_disc));

      memcpy(&gsr, &max_score_gsr, sizeof(getscore_result));

      int k;
      for (k = 0; k < future_disc_start; k++) {
         current_disc[k] = future_disc[k];
         gsr.permutation[k] = seq_to_load[k];
      }

      getScore(&gsr,
               0,
               future_disc_start,
               current_disc,
               seq_to_load,
               0, 0, 0);

      if (gsr.trigger_disc > worksize) {
         printf("NOTE: trigger_disc %d is > worksize %d\n", gsr.trigger_disc, worksize);
         gsr.trigger_disc = gsr.trigger_disc % worksize;
         printf("Changed to %d\n", gsr.trigger_disc);
      }

      if (gsr.max_chain_length > max_chain_length) {
         max_chain_length = gsr.max_chain_length;
      }

      memcpy(&max_score_gsr, &gsr, sizeof(getscore_result));
      printf("DEBUG_MAX_SCORE: %lu\n", max_score_gsr.score);
      printf("DEBUG_MAX_SCORE_PERMUTATION[%llu]:", max_score_gsr.step);
      printArray(max_score_gsr.permutation, 0);
      printf("\n");
   }

   unsigned char max_score_permutation[20];
   memset(max_score_permutation, 0, sizeof(max_score_permutation));

   int future_disc_index;
   int next_future_disc_index;
   for (future_disc_index = future_disc_start; future_disc_index < num_future_disc; future_disc_index = next_future_disc_index) {
      memcpy(&baseline_gsr, &max_score_gsr, sizeof(getscore_result));

      // Extract the current set of 'worksize' discs out of future_disc[] and save them in current_disc[]
      printf("<div class='disc_set_sequence'>\n");
      printf("<h1>DISC SET[%d]:", future_disc_index);
      int current_disc[20];
      int k;
      for (k = 0; k < worksize; k++) {
         current_disc[k] = future_disc[future_disc_index + k];
         printf(" %d", current_disc[k]);
      }
      printf("</h1>\n");

      //======================================================================================
      // Start of permuation
      //======================================================================================
      unsigned char permutation[20];
      memset(permutation, 0, sizeof(permutation));

      unsigned long long permutation_index;
      if (start_permutation_index) {
         for (permutation_index = 0; permutation_index < worksize; permutation_index++) {
            permutation[permutation_index] = starting_permutation[permutation_index];
         }

      // This sets the first permutation to be all 1s
      } else {
         for (permutation_index = 0; permutation_index < worksize; permutation_index++) {
            permutation[permutation_index] = permutation_init_value;
         }
      }

      int valid_option = 0;
      char invalidate_the_cache = 1;
      for (permutation_index = start_permutation_index; permutation_index < permutation_max_i; permutation_index++) {
         if (end_permutation_index) {
            if (permutation_index > end_permutation_index) {
               break;
            }
         }

         // Print the permuation
         if (debug) {
            printf("DISC SET PERMUTATION[%llu]: ", permutation_index);
            int k;
            for (k = 0; k < worksize; k++) {
               printf("%d", permutation[k]);
            }
            printf("\n");
        }

         char valid_cache_spots = worksize - 1;
         char need_to_update_cache_spots = 0;
         if (permutation_index % 7 == 0) { // Divisible by 7

            // Now go through all the multiples of 7^x
            // To follow how this works read through the original comments/code below.
            // It is from when I hardcoded a solution for a worksize of 4...just to
            // figure things out.
            int z;
            for (z = worksize - 1; z >= 1; z--) {
               if (permutation_index % power(7, z) == 0) {
                  valid_cache_spots -= z;
                  need_to_update_cache_spots = worksize - 1 - valid_cache_spots;
                  break;
               }
            }

            // // Divisible by 343 so with WS4 we need to update everything
            // // 1777
            // // 2111
            // // ***
            // if (permutation_index % 343 == 0) {
            //    valid_cache_spots = 0;
            //    need_to_update_cache_spots = 3;

            // // Divisible by 49 so with WS4 the first cache entry is good but need to update the 2nd and 3rd
            // // 1177
            // // 1211
            // // ^**
            // } else if (permutation_index % 49 == 0) {
            //    valid_cache_spots = 1;
            //    need_to_update_cache_spots = 2;

            // // Only divisible by 7 so with WS4 the first 2 cache entries are good but need to update the 3rd
            // // Example:
            // // 1117
            // // 1121
            // // ^^*
            // } else {
            //    valid_cache_spots = 2;
            //    need_to_update_cache_spots = 1;
            // }
         }

         if (invalidate_the_cache) {
            valid_cache_spots = 0;
            need_to_update_cache_spots = worksize - 1;
            memset(&cache_gsr, 0, sizeof(cache_gsr[0]) * 20);
            invalidate_the_cache = 0;
         }

         memcpy(&gsr, &baseline_gsr, sizeof(getscore_result));
         gsr.max_chain_length = 0;
         getScore(&gsr,
                  permutation_index,
                  worksize,
                  current_disc,
                  permutation,
                  valid_cache_spots,
                  need_to_update_cache_spots,
                  cache_gsr);

         if (gsr.gameover) {
            gameovercount++;

         } else if (gsr.score > max_score_gsr.score) {
            valid_option = 1;

            if (debug) {
               printf("<div class='new_max_score'>NEW MAX SCORE(child): %lu -> %lu</div>\n", max_score_gsr.score, gsr.score);
            }

            memcpy(max_score_permutation, permutation, sizeof(permutation));

            // save the current gsr structure since this one has the highest score so far
            appendPermutation(&gsr, permutation, worksize, 0);
            memcpy(&max_score_gsr, &gsr, sizeof(getscore_result));

            if (gsr.max_chain_length > max_chain_length) {
               max_chain_length = gsr.max_chain_length;
            }
         } else {
            // printf("GSR SCORE %d < MAX SCORE %d, BASELINE %d\n", gsr.score, max_score_gsr.score, baseline_gsr.score);
         }

         // Compute the next permutation...store it in permutation[]
         int permutation_j;
         for (permutation_j = worksize - 1; permutation_j >= 0; permutation_j--) {
            permutation[permutation_j]++;

            if (permutation[permutation_j] <= permutation_max_value) {
               break;
            }
            permutation[permutation_j] = permutation_init_value;
         }

         if (debug) {
               printf("</div>\n");
         }
      } // End of permutation loop

      printf("<div class='disc_set_summary'>\n");
      if (valid_option) {
         printf("DISC[%d]: CHAIN POTENTIAL SCORE:  %lu\n", future_disc_index, max_score_gsr.score);
         printf("DISC[%d]: CHAIN POTENTIAL LENGTH: %d\n", future_disc_index, max_score_gsr.max_chain_length);
         printf("DISC[%d]: CHAIN POTENTIAL PERMUTATION: '", future_disc_index);
         printArray(max_score_gsr.permutation, worksize);
         printf("'\n");
         printf("DISC[%d]: CHAIN POTENTIAL TRIGGER: #%d\n", future_disc_index, max_score_gsr.trigger_disc+1);

         if (max_score_gsr.trigger_disc > 0) {

            // If our ws is 7 and the last disc in the set of 7 is the trigger disc
            // then max_score_gsr.trigger_disc will have a value of 6.  We want to
            // rebuild the grid but stop just before placing the trigger disc so we
            // do the little formula below to come up with a tmp_worksize of 6 (down from 7).

            int tmp_worksize = worksize - (worksize - max_score_gsr.trigger_disc);
            int tmp_permutation_index = max_score_gsr.step;
            printf("TRIGGER_DISC: %d, WORKSIZE: %d, TMP_WORKSIZE: %d\n",
                    max_score_gsr.trigger_disc, worksize, tmp_worksize);

            int current_disc[20];
            memset(current_disc, 0, sizeof(current_disc));
            int k;
            for (k = 0; k < tmp_worksize; k++) {
               current_disc[k] = future_disc[future_disc_index + k];
            }


            memcpy(&gsr, &baseline_gsr, sizeof(getscore_result));
            gsr.max_chain_length = 0;
            getScore(&gsr,
                     tmp_permutation_index,
                     tmp_worksize,
                     current_disc,
                     max_score_permutation,
                     0, 0, 0);

            appendPermutation(&gsr, max_score_permutation, tmp_worksize, 0);
            memcpy(&max_score_gsr, &gsr, sizeof(getscore_result));

            printf("DISC[%d]: CHAIN SETUP SCORE:  %lu\n", future_disc_index, max_score_gsr.score);
            printf("DISC[%d]: CHAIN SETUP LENGTH: %d\n", future_disc_index, max_score_gsr.max_chain_length);
            printf("DISC[%d]: CHAIN SETUP PERMUTATION: '", future_disc_index);
            printArray(max_score_gsr.permutation, 0);
            printf("'\n");

            next_future_disc_index = future_disc_index + tmp_worksize;

         // This means that the first disc in the set is the one that triggers the longest possible chain
         } else {

            int tmp_worksize = 1;
            int tmp_permutation_index = max_score_gsr.step;

            int current_disc[20];
            memset(current_disc, 0, sizeof(current_disc));
            current_disc[0] = future_disc[future_disc_index];

            memcpy(&gsr, &baseline_gsr, sizeof(getscore_result));
            gsr.max_chain_length = 0;
            getScore(&gsr,
                     tmp_permutation_index,
                     tmp_worksize,
                     current_disc,
                     max_score_permutation,
                     0, 0, 0);
            appendPermutation(&gsr, max_score_permutation, tmp_worksize, 0);
            memcpy(&max_score_gsr, &gsr, sizeof(getscore_result));

            printf("DISC[%d]: CHAIN EXECUTE SCORE:  %lu\n", future_disc_index, max_score_gsr.score);
            printf("DISC[%d]: CHAIN EXECUTE LENGTH: %d\n", future_disc_index, max_score_gsr.max_chain_length);
            printf("DISC[%d]: CHAIN EXECUTE PERMUTATION: '", future_disc_index);
            printArray(max_score_gsr.permutation, 0);
            printf("'\n");

            next_future_disc_index = future_disc_index + 1;
         }

         printf("<hr>");
         printf("</div>\n");
      } else {
         printf("There were no permutations that resulted in a higher score.  This happens when the board is very near the end of the game.\n</div>\n");
         exit(0);
      }

      printf("</div>\n\n\n");

      if (one_set_only) {
         break;
      }
   }

   printf("MAX_SCORE: %lu\n", max_score_gsr.score);
   printf("MAX_SCORE_PERMUTATION[%llu]:", max_score_gsr.step);
   printArray(max_score_gsr.permutation, 0);
   printf("\n");

   printf("MAX_CHAIN          : %d\n", max_chain_length);
   printf("GRID_CLEARED       : %d\n", max_score_gsr.grid_cleared);
   printf("gameovercount      : %llu\n", gameovercount);
   printf("permutations skip  : %llu\n", permutations_skipped);
   printf("addDiscToGrid calls: %llu\n", add_disc_calls);
   printf("getScore      calls: %llu\n", get_score_calls);
   printf("</pre>\n");
   printf("</body>\n");
   printf("</html>\n");

   return 1;
}
