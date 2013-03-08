#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drop7core.h"

//
// gcc -o drop7display.cgi drop7display.c drop7core.c
//

main(int argc, char *argv[]) {
   unsigned long long start_permutation_index = 0;
   unsigned long long end_permutation_index = 0;
   char seq_to_load[4096];
   memset(seq_to_load, 0, sizeof(seq_to_load));

   // 0 = Nothing special
   // 1 = parsing seq
   // 2 = parsing starting permutation 
   int state = 0;
   int worksize = 0;
   int i;
   int z = 0;
   for (i = 0; i < argc; i++) {
      if (!strcmp(argv[i], "-seq")) {
         state = 1;

      // If we get to here then we should be looking at a digit
      } else {
         if (state == 1) {
            seq_to_load[z] = atoi(argv[i]);
            worksize++;
            z++;
         }
      }
   }

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
    * about and breaking them down into 'parent_worksize' chunks.  I then find the optimal
    * permutation to place each set of 'parent_worksize' discs. This will not find the highest
    * scoring combination possible but it will find combinations that produce high scores.
    */
   int j;
   int num_future_disc = sizeof(future_disc)/sizeof(future_disc[0]);
   getscore_result gsr;
   getscore_result max_score_gsr;
   memset(&max_score_gsr, 0, sizeof(getscore_result));
   memset(&gsr, 0, sizeof(getscore_result));

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

   /*
    * It doesn't scale to build all of the permutations and store them in memory (we are talking
    * gigs and gigs of memory) so instead we compute them on the fly everytime through this main
    * loop of parent_worksize chunks of discs.
    */
   int permutation_init_value = 1;
   int permutation_max_value = 7;
   unsigned long long permutation_max_i = power(permutation_max_value, worksize);

 
   int current_disc[4096];
   memset(current_disc, 0, sizeof(current_disc));
   memcpy(&gsr, &max_score_gsr, sizeof(getscore_result));

   int k;
   for (k = 0; k < worksize; k++) {
         current_disc[k] = future_disc[k];
         gsr.permutation[k] = seq_to_load[k];
   }

   debug = 1;
   getScore(&gsr,
            0,
            worksize,
            current_disc, // fix
            seq_to_load,
            0, 0, 0); // disable caching

   
   printf("<div id='final_score'>\n");
   printf("MAX CHAIN   : %d\n", gsr.max_chain_length);
   printf("GRID CLEARED: %d\n", gsr.grid_cleared);
   printf("SCORE       : %lu\n", gsr.score);
   printf("WORKSIZE    : %d\n", worksize);
   printf("PERMUTATION:");
   printArray(gsr.permutation, 0);
   printf("\n");
   printf("</div>\n");

   printf("</pre>\n");
   printf("</body>\n");
   printf("</html>\n");
}
