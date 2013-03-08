#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc -o permutations.cgi permutations.c

// power(2, 4) returns 16
unsigned long long power(int a, int b) {
   unsigned long long c=a;

   int i;
   for (i = 0; i < b-1; i++){
      c *= a;
   }

   return c;
}


void
main(int argc, char *argv[]) {
   unsigned long long of_interest[100];
   memset(of_interest, 0, sizeof(of_interest));

   int worksize = 0;
   int of_interest_index = 0;
   int i;
   for (i = 1; i < argc; i++) {
      if (!strcmp(argv[i], "-ws")) {
         worksize = atoi(argv[++i]);
      } else {
         of_interest[of_interest_index++] = strtoull(argv[i], NULL, 10);
      }
   }

   if (!worksize) {
      printf("\nERROR: You must specify the worksize via '-ws X'\n");
      exit(1);
   }

   int permutation_init_value = 1;
   int permutation_max_value = 7;
   unsigned long long permutation_max_i = power(permutation_max_value, worksize);

   unsigned char permutation[20];
   memset(permutation, 0, sizeof(permutation));

   // This sets the first permutation to be all 1s
   unsigned long long permutation_index;
   for (permutation_index = 0; permutation_index < worksize; permutation_index++) {
      permutation[permutation_index] = permutation_init_value;
   }
 
   unsigned long long loop_count = 0;
   of_interest_index = 0;
   for (permutation_index = 0; permutation_index < permutation_max_i; permutation_index++) {
      loop_count++;

      if (permutation_index == of_interest[of_interest_index]) {
         printf("%llu:", of_interest[of_interest_index]);
         int k;
         for (k = 0; k < worksize; k++) {
            printf("%d ", permutation[k]);
         }
         printf("\n");

         of_interest_index++;
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
   }
}
