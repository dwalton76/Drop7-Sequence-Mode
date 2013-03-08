#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drop7core.h"

int levelup_disc[75][7] = {{0, 0, 0, 0, 0, 0, 0},
                          {26, 24, 25, 27, 25, 21, 23}, // L1
                          {21, 23, 26, 23, 23, 24, 24}, // L2
                          {26, 24, 25, 27, 23, 23, 24}, // L3
                          {22, 22, 27, 21, 27, 21, 25}, // L4
                          {22, 23, 27, 21, 25, 24, 21}, // L5
                          {25, 22, 23, 26, 22, 27, 21}, // L6
                          {23, 26, 27, 21, 23, 27, 23}, // L7
                          {21, 25, 24, 21, 26, 23, 23}, // L8
                          {23, 27, 23, 21, 21, 21, 24}, // L9
                          {22, 21, 26, 23, 22, 23, 27}, // L10
                          {25, 23, 24, 25, 24, 25, 23}, // L11
                          {26, 21, 26, 26, 27, 23, 23}, // L12
                          {26, 24, 22, 25, 27, 27, 25}, // L13
                          {27, 27, 24, 22, 25, 21, 21}, // L14
                          {25, 21, 23, 23, 25, 23, 25}, // L15
                          {24, 27, 24, 25, 27, 26, 27}, // L16
                          {21, 24, 23, 23, 25, 22, 23}, // L17
                          {21, 25, 21, 23, 26, 24, 23}, // L18
                          {21, 25, 27, 24, 21, 27, 26}, // L19
                          {27, 23, 26, 27, 21, 26, 22}, // L20
                          {23, 22, 21, 22, 25, 25, 26}, // L21
                          {26, 24, 22, 22, 25, 25, 22}, // L22
                          {26, 22, 27, 23, 27, 23, 22}, // L23
                          {22, 23, 26, 26, 24, 26, 21}, // L24
                          {24, 25, 24, 27, 25, 26, 22}, // L25
                          {24, 24, 26, 26, 22, 25, 25}, // L26
                          {21, 23, 23, 25, 24, 24, 27}, // L27
                          {23, 24, 25, 22, 22, 23, 23}, // L28
                          {22, 25, 21, 24, 25, 25, 26}, // L29
                          {23, 23, 24, 26, 21, 22, 24}, // L30
                          {22, 25, 21, 22, 26, 22, 25}, // L31
                          {25, 21, 21, 25, 24, 22, 23}, // L32
                          {27, 22, 26, 24, 27, 23, 23}, // L33
                          {26, 23, 27, 22, 25, 26, 23}, // L34
                          {25, 24, 21, 26, 27, 24, 26}, // L35
                          {24, 26, 23, 27, 23, 23, 25}, // L36
                          {24, 27, 27, 26, 23, 27, 27}, // L37
                          {21, 25, 21, 21, 26, 25, 25}, // L38
                          {22, 22, 26, 24, 22, 21, 22}, // L39
                          {21, 26, 25, 24, 21, 22, 25}, // L40
                          {21, 21, 22, 22, 26, 21, 21}, // L41
                          {27, 24, 23, 27, 23, 23, 22}, // L42
                          {22, 26, 22, 26, 25, 22, 24}, // L43
                          {26, 24, 26, 23, 24, 24, 23}, // L44
                          {27, 22, 23, 24, 25, 24, 26}, // L45
                          {22, 23, 21, 27, 23, 27, 26}, // L46
                          {23, 27, 27, 25, 22, 21, 21}, // L47
                          {27, 24, 25, 26, 23, 23, 26}, // L48
                          {22, 22, 25, 21, 25, 27, 27}, // L49
                          {25, 26, 21, 27, 22, 27, 24}, // L50
                          {22, 24, 27, 23, 22, 26, 27}, // L51
                          {25, 23, 25, 27, 25, 24, 26}, // L52
                          {24, 22, 26, 26, 21, 25, 27}, // L53
                          {21, 21, 26, 23, 21, 26, 22}, // L54
                          {24, 22, 26, 24, 27, 21, 26}, // L55
                          {21, 23, 24, 21, 23, 22, 23}, // L56
                          {26, 24, 27, 27, 26, 25, 24}, // L57
                          {24, 25, 26, 27, 26, 27, 23}, // L58
                          {25, 22, 24, 27, 25, 23, 26}, // L59
                          {24, 25, 22, 26, 25, 21, 25}, // L60
                          {21, 26, 23, 25, 24, 27, 23}, // L61
                          {21, 27, 25, 22, 25, 26, 25}, // L62
                          {27, 26, 21, 24, 23, 24, 25}, // L63
                          {23, 22, 27, 26, 21, 25, 27}, // L64
                          {26, 26, 27, 25, 24, 22, 22}, // L65
                          {23, 26, 23, 23, 22, 24, 27}, // L66
                          {24, 22, 27, 25, 24, 26, 22}, // L67
                          {24, 23, 25, 25, 23, 23, 23}, // L68
                          {22, 27, 23, 21, 24, 25, 22}, // L69
                          {22, 23, 21, 23, 23, 23, 23}, // L70
                          {24, 27, 25, 25, 25, 26, 27}, // L71
                     //row5 {26, 27, 22, 22, 27, 21, ?c7}, // L72
                     //row4 {26, 26, 23, 23, ?c5, ?c6, ?c7}, // L73
                     //row3 {?c1, ?c2, ?c3, ?c4, ?c5, ?c6, ?c7}, // L74
                     //row2 {?c1, ?c2, ?c3, ?c4, ?c5, ?c6, ?c7}, // L75
                     //row1 {?c1, ?c2, ?c3, ?c4, ?c5, ?c6, ?c7}, // L76
                     //   {?c1, ?c2, ?c3, ?c4, ?c5, ?c6, ?c7}, // LXX
                          {0, 0, 0, 0, 0, 0, 0}};

int future_disc[685] = {
   // Level 1
   2, 1, 1, 26, 4, 5, 25, 25, 21, 6, 1, 5, 7, 5, 3, 6, 3, 22, 6, 24, 2, 5, 7, 1, 22, 5, 21, 23, 22, 4,

   // Level 2
   5, 5, 22, 21, 26, 22, 3, 2, 3, 22, 23, 6, 2, 7, 7, 6, 23, 22, 26, 4, 7, 4, 5, 4, 3, 6, 1, 26, 1,

   // Level 3
   5, 27, 4, 6, 3, 25, 7, 4, 3, 5, 2, 26, 2, 7, 2, 1, 4, 7, 24, 4, 2, 7, 3, 25, 5, 5, 21, 27,

   // Level 4
   7, 27, 2, 27, 2, 23, 2, 3, 22, 2, 26, 25, 24, 26, 5, 27, 2, 6, 27, 27, 25, 4, 2, 23, 7, 2, 3,

   // Level 5
   22, 1, 23, 4, 1, 23, 21, 1, 6, 21, 5, 7, 25, 2, 5, 5, 26, 3, 25, 24, 5, 7, 4, 1, 23, 5,

   // Level 6
   1, 6, 4, 27, 3, 7, 3, 7, 27, 4, 24, 1, 5, 21, 5, 1, 24, 4, 23, 4, 7, 4, 3, 1, 24,

   // Level 7
   5, 25, 27, 25, 25, 1, 3, 26, 22, 2, 3, 7, 5, 4, 5, 6, 1, 6, 27, 1, 1, 22, 7, 3,

   // Level 8
   7, 2, 22, 27, 7, 24, 26, 5, 7, 5, 7, 26, 7, 4, 6, 5, 1, 26, 3, 4, 27, 7, 5,

   // Level 9
   2, 6, 1, 3, 27, 6, 4, 7, 3, 7, 26, 5, 25, 6, 2, 4, 3, 3, 25, 7, 24, 7,

   // Level 10
   21, 25, 4, 23, 6, 5, 21, 27, 7, 1, 5, 6, 1, 7, 24, 6, 3, 6, 1, 1, 21,

   // Level 11
   5, 6, 4, 7, 7, 4, 24, 22, 25, 23, 24, 24, 24, 23, 4, 23, 3, 22, 1, 24,

   // Level 12
   7, 2, 7, 25, 23, 6, 23, 22, 4, 6, 2, 2, 5, 7, 1, 7, 25, 3, 7,

   // Level 13
   1, 4, 23, 2, 2, 27, 3, 2, 4, 22, 6, 7, 1, 3, 4, 6, 22, 24,

   // Level 14
   23, 22, 2, 7, 25, 5, 6, 27, 21, 21, 4, 23, 4, 23, 1, 6, 25,

   // Level 15
   2, 22, 25, 3, 21, 7, 2, 2, 1, 1, 7, 7, 27, 1, 4, 4,

   // Level 16
   1, 21, 24, 4, 4, 4, 4, 1, 4, 5, 27, 2, 2, 24, 7,

   // Level 17
   4, 5, 3, 2, 23, 7, 1, 24, 27, 27, 3, 22, 6, 2,

   // Level 18
   23, 2, 2, 25, 26, 4, 6, 2, 7, 23, 7, 6, 1,

   // Level 19
   22, 3, 5, 4, 6, 25, 26, 1, 3, 4, 1, 1,

   // Level 20
   21, 1, 3, 6, 24, 21, 21, 6, 7, 7, 23,

   // Level 21
   5, 3, 3, 4, 6, 3, 4, 22, 1, 21,

   // Level 22
   4, 25, 23, 6, 6, 25, 6, 2, 4,

   // Level 23
   1, 7, 7, 1, 5, 22, 2, 27,

   // Level 24
   5, 3, 2, 23, 2, 1, 2,

   // Level 25
   21, 25, 26, 3, 5, 26,

   // Level 26
   2, 27, 6, 1, 25,

   // Level 27
   24, 4, 3, 7, 1,

   // Level 28
   2, 2, 7, 7, 3,

   // Level 29
   6, 2, 1, 26, 7,

   // Level 30
   2, 3, 25, 1, 4,

   // Level 31
   4, 7, 3, 1, 1,

   // Level 32
   7, 1, 24, 4, 5,

   // Level 33
   26, 4, 24, 3, 4,

   // Level 34
   4, 6, 1, 7, 22,

   // Level 35
   5, 2, 25, 5, 1,

   // Level 36
   1, 5, 21, 6, 3,

   // Level 37
   6, 7, 3, 7, 4,

   // Level 38
   5, 2, 2, 24, 7,

   // Level 39
   4, 4, 4, 4, 25,

   // Level 40
    6, 5, 3, 4, 26,

   // Level 41
    21, 6, 6, 27, 2,

   // Level 42
   27, 6, 1, 3, 24,

   // Level 43
   2, 7, 27, 24, 6,

   // Level 44
   5, 3, 6, 23, 25,

   // Level 45
   1, 4, 4, 7, 2,

   // Level 46
   6, 25, 7, 2, 2,

   // Level 47
   4, 1, 27, 23, 7,

   // Level 48
   6, 5, 24, 2, 1,

   // Level 49
   5, 5, 3, 6, 22,

   // Level 50
   3, 26, 5, 2, 3,

   // Level 51
   6, 4, 1, 27, 7,

   // Level 52
   22, 1, 7, 7, 24,

   // Level 53
   4, 3, 1, 1, 24,

   // Level 54
   23, 27, 3, 21, 5,

   // Level 55
   6, 2, 24, 1, 26,

   // Level 56
   27, 7, 21, 24, 7,

   // Level 57
   7, 3, 21, 1, 1,

   // Level 58
   1, 3, 6, 27, 2,

   // Level 59
   4, 7, 7, 4, 21,

   // Level 60
   22, 23, 27, 7, 5,

   // Level 61
   2, 3, 27, 1, 7,

   // Level 62
   5, 2, 24, 4, 4,

   // Level 63
   7, 1, 2, 5, 22,

   // Level 64
   24, 4, 6, 24, 4,

   // Level 65
   22, 5, 7, 1, 3,

   // Level 66
   3, 23, 4, 5, 22,

   // Level 67
   3, 1, 4, 5, 1,

   // Level 68
   1, 23, 1, 27, 25,

   // Level 69
   3, 26, 24, 3, 3,

   // Level 70
   5, 2, 24, 7, 3,

   // Level 71
   1, 27, 24, 1, 6,

/*
   // Level 72
   1, 5, 2, ?, 7,

   // Level 73
   6, 3, 3, 2, ?,

   // Level 74
   24, 5, 1, ?, ?
   */
};

// The formula is 7*n^2.5
int chain_scores[51] = {0, 7, 39, 109, 224, 391, 617, 907, 1267, 1701, 2213, 2809, 3491, 4265, 5133, 6099, 7168, 8341, 9622, 11014, 12521, 14146, 15891, 17758, 19752, 21875, 24128, 26515, 29039, 31702, 34506, 37454, 40548, 43790, 47184, 50730, 54432, 58291, 62309, 66490, 70835, 75345, 80024, 84872, 89893, 95088, 100459, 106008, 111738, 117649};

int initial_grid[7][7] = {{26, 0, 0, 0, 0, 0, 0}, {24, 0, 0, 0, 0, 0, 0}, {25, 0, 0, 0, 0, 0, 0}, {27, 0, 0, 0, 0, 0, 0}, {25, 0, 0, 0, 0, 0, 0}, {21, 0, 0, 0, 0, 0, 0}, {23, 0, 0, 0, 0, 0, 0}};


unsigned long long get_score_calls = 0;
unsigned long long add_disc_calls = 0;
unsigned long long permutations_skipped = 0;
int max_chain_length = 0;
unsigned long long gameovercount = 0;
int debug = 0;
int eps_above_threshold = 0;


int getDiscForLevel(int level) {
          if (level == 1) { return 30;
   } else if (level == 2) { return 29;
   } else if (level == 3) { return 28;
   } else if (level == 4) { return 27;
   } else if (level == 5) { return 26;
   } else if (level == 6) { return 25;
   } else if (level == 7) { return 24;
   } else if (level == 8) { return 23;
   } else if (level == 9) { return 22;
   } else if (level == 10) { return 21;
   } else if (level == 11) { return 20;
   } else if (level == 12) { return 19;
   } else if (level == 13) { return 18;
   } else if (level == 14) { return 17;
   } else if (level == 15) { return 16;
   } else if (level == 16) { return 15;
   } else if (level == 17) { return 14;
   } else if (level == 18) { return 13;
   } else if (level == 19) { return 12;
   } else if (level == 20) { return 11;
   } else if (level == 21) { return 10;
   } else if (level == 22) { return 9;
   } else if (level == 23) { return 8;
   } else if (level == 24) { return 7;
   } else if (level == 25) { return 6;
   }

   return 5;
}

char* getClass(int i) {
   if (!i) {
      return "empty";
   }

   if (i >= 41 && i <= 47) {
      return "exploded";
   }

   if (i >= 31 && i <= 37) {
      return "explode";
   }

   if (i >= 21 && i <= 27) {
      return "solid";
   }

   if (i >= 11 && i <= 17) {
      return "crack";
   }

   if (i >= 1 && i <= 7) {
      return "clear";
   }

   return "error";
}

int prettyNumber(int i) {
   if (i >= 41) {
      return (i - 40);
   } else if (i >= 31) {
      return (i - 30);
   } else if (i >= 21) {
      return (i - 20);
   } else if (i >= 11) {
      return (i - 10);
   }

   return i;
}

void printPermutation(char *desc, getscore_result *gsr) {
   int z;
   printf("PERMUTATION %s\n", desc);
   for (z = 0; z < 685; z++) {
      if (gsr->permutation[z]) {
         printf(" %d", gsr->permutation[z]);
      } else {
         break;
      }
   }
   printf("\n\n");
}

void printGrid(getscore_result *gsr, char* context, int level, int score, int disc, int dropcolumn, int grid_is_empty) {

   printf("<div class='grid_with_score'>\n");
   printf("<b>%s</b>\n", context);
   printf("SCORE: %lu\n", gsr->score);
   printf("LEVEL: %d\n", gsr->level);
   printf("COLUMN: %d\n", dropcolumn + 1);
   printf("DISC LEFT: %d\n", gsr->disc_left_in_level);
   printf("CHAINx%d\n", gsr->chain_length);
   if (grid_is_empty) {
      printf("GRID_CLEARED\n");
   }
   printf("<table class='grid'>\n");

   // Print the disc to be dropped in the header.  We'll show this as green so it is easy to see.
   if (disc) {
      printf("<thead>\n");
      printf("<tr>\n");
      int x;
      for (x = 0; x <= 6; x++) {
         if (x == dropcolumn) {
            printf("<th class='dropcolumn'>%d</th>\n", prettyNumber(disc));
         } else {
            printf("<th></th>\n");
         }
      }
      printf("</tr>\n");
      printf("</thead>\n");
   }

   int y;
   printf("<tbody>\n");
   for (y = 6; y >= 0; y--) {
      printf("<tr><td class='%s'>%d</td><td class='%s'>%d</td><td class='%s'>%d</td><td class='%s'>%d</td><td class='%s'>%d</td><td class='%s'>%d</td><td class='%s'>%d</td></tr>\n",
             getClass(gsr->grid[0][y]),
             prettyNumber(gsr->grid[0][y]),
             getClass(gsr->grid[1][y]),
             prettyNumber(gsr->grid[1][y]),
             getClass(gsr->grid[2][y]),
             prettyNumber(gsr->grid[2][y]),
             getClass(gsr->grid[3][y]),
             prettyNumber(gsr->grid[3][y]),
             getClass(gsr->grid[4][y]),
             prettyNumber(gsr->grid[4][y]),
             getClass(gsr->grid[5][y]),
             prettyNumber(gsr->grid[5][y]),
             getClass(gsr->grid[6][y]),
             prettyNumber(gsr->grid[6][y]));
   }
   printf("</tbody>\n");
   printf("</table>\n");
   printf("</div>\n\n");
}

// power(2, 4) returns 16
unsigned long long power(int a, int b) {
   unsigned long long c=a;

   int i;
   for (i = 0; i < b-1; i++){
      c *= a;
   }

   return c;
}

int addDiscToGrid(getscore_result *gsr, int disc, int column, int level, int score, int cd_index) {
   add_disc_calls++;

   if (debug) {
      printf("<h2 id='disc%d'>Adding DISC #%d</h2>\n", cd_index+1, cd_index+1);
   }

   // If this is TRUE then it means the column is full and we were not able to add the disc
   if (gsr->vertical_count[column] == 7) {
      return 0;
   }

   // Adding a clear disc...keep track of how many of each number on in a column
   if (disc < 10) {
      gsr->vertical_index[column][disc]++;
   }

   int lowest_open_y = gsr->vertical_count[column]++;
   gsr->grid[column][lowest_open_y] = disc;
   gsr->disc_left_in_level--;
   return 1;
}

int getDiscHorizontalCount(getscore_result *gsr, int x, int y) {
   // Look to the left
   int i = 1;
   if (x > 0) {
      int tmp_x;
      for (tmp_x = x-1; tmp_x >= 0; tmp_x--) {
         if (gsr->grid[tmp_x][y]) {
            i++;
         } else {
            break;
         }
      }
   }

   // Look to the right
   if (x < 6) {
      int tmp_x;
      for (tmp_x = x+1; tmp_x <= 6; tmp_x++) {
         if (gsr->grid[tmp_x][y]) {
            i++;
         } else {
            break;
         }
      }
   }

   return i;
}

int findDiscsToExplodeVertically(getscore_result *gsr, int column, int fast_return, int disc_to_explode[][2], int *disc_to_explode_count) {
   int debug_count = 0;

   int vcount = gsr->vertical_count[column];
   if (debug_count) {
      printf("VERTICAL[%d]: has %d discs, there are %d #%d's.",
             column, vcount, gsr->vertical_index[column][vcount], vcount);
   }

   if (!vcount) {
      if (debug_count) {
         printf("\n");
      }

      return 0;
   }

  /*
   * Look for any disc whose value matches the vertical count
   * These are the disc that will explode. Remember that a disc cannot explode
   * if it is _SOLID or _CRACK.  vertical_index is used to keep track of how
   * many of a certain NUMBER disc in in a column.
   */
   if (gsr->vertical_index[column][vcount]) {
      int y;
      int target_discs = gsr->vertical_index[column][vcount];
      for (y = 0; y <= 6; y++) {
         if (gsr->grid[column][y] == vcount) {
            if (fast_return) {
               return 1;
            }

            disc_to_explode[*disc_to_explode_count][0] = column;
            disc_to_explode[*disc_to_explode_count][1] = y;
            (*disc_to_explode_count)++;

            if (debug_count) {
               printf(" DISC %d,", gsr->grid[column][y]);
            }
            gsr->grid[column][y] += 30;

            if (--target_discs == 0) {
               break;
            }
         } else {
            if (!gsr->grid[column][y]) {
               break;
            }
         }
      }
   }

   if (debug_count) {
      printf("\n");
   }

   return 0;
}

void findDiscsToExplodeHorizontally(getscore_result *gsr, int look_at_one_spot, int column, int row, int disc_to_explode[][2], int *disc_to_explode_count) {
   int debug_count = 0;

   // Look at one spot on the row
   if (look_at_one_spot) {
      int hcount = getDiscHorizontalCount(gsr, column, row);

      // Look at ourselves and to the left
      int tmp_x;
      for (tmp_x = column; tmp_x >= 0; tmp_x--) {
         int value = gsr->grid[tmp_x][row];
         if (value) {
            if (value == hcount) {
               disc_to_explode[*disc_to_explode_count][0] = tmp_x;
               disc_to_explode[*disc_to_explode_count][1] = row;
               (*disc_to_explode_count)++;

               if (debug_count) {
                  printf("findH HORIZONTAL DISC %d\n", gsr->grid[tmp_x][row]);
               }

               gsr->grid[tmp_x][row] += 30;
            }
         } else {
            break;
         }
      }

      // Look to the right
      if (column < 6) {
         int tmp_x;
         for (tmp_x = column+1; tmp_x <= 6; tmp_x++) {
            int value = gsr->grid[tmp_x][row];
            if (value) {
               if (value == hcount) {
                  disc_to_explode[*disc_to_explode_count][0] = tmp_x;
                  disc_to_explode[*disc_to_explode_count][1] = row;
                  (*disc_to_explode_count)++;

                  if (debug_count) {
                     printf("findH HORIZONTAL DISC %d\n", gsr->grid[tmp_x][row]);
                  }

                  gsr->grid[tmp_x][row] += 30;
               }
            } else {
               break;
            }
         }
      }

   // Look at the whole row
   } else {
      int h_counts[8];
      int h_index[8];
      int empty_row = 1;
      int min_x_with_disc = -1;
      int max_x_with_disc = -1;
      int horizontal_streak = 0;
      memset(h_counts, 0, sizeof(h_counts));
      memset(h_index, 0, sizeof(h_index));
      int h_count_index = 0;

      if (debug_count) {
         printf("HORIZONTAL_COUNT[%d]: ", row);
      }

      int x;
      for (x = 0; x <= 6; x++) {
         int value = gsr->grid[x][row];
         if (value) {
            empty_row = 0;
            max_x_with_disc = x;
            horizontal_streak++;
            if (min_x_with_disc == -1) {
               min_x_with_disc = x;
            }

            if (x == 6) {
               h_counts[h_count_index++] = horizontal_streak;
            }

            if (value < 10) {
               h_index[value]++;
            }

         } else {
            if (horizontal_streak) {
               h_counts[h_count_index++] = horizontal_streak;
               horizontal_streak = 0;
            }
         }
      } // End of the row

      if (!empty_row) {
         int tmp_h_count_index;
         for (tmp_h_count_index = 0; tmp_h_count_index < h_count_index; tmp_h_count_index++) {
            int horizontal_streak = h_counts[tmp_h_count_index];

            if (h_index[horizontal_streak]) {

               int target_discs = h_index[horizontal_streak];
               for (x = min_x_with_disc; x <= max_x_with_disc; x++) {
                  int value = gsr->grid[x][row];
                  if (value == horizontal_streak &&
                      getDiscHorizontalCount(gsr, x, row) == value) {
                     disc_to_explode[*disc_to_explode_count][0] = x;
                     disc_to_explode[*disc_to_explode_count][1] = row;
                     (*disc_to_explode_count)++;

                     if (debug_count) {
                        printf(" DISC %d,", gsr->grid[x][row]);
                     }

                     gsr->grid[x][row] += 30;

                     if (--target_discs == 0) {
                        break;
                     }
                  }
               }
            }
         }
      }

      if (debug_count) {
         printf("\n");
      }
   }
}

/*
 * Remember...
 *  1 -  7 = Visible Disc
 * 11 - 17 = CRACK Disc
 * 21 - 27 = SOLID Disc
 * 31 - 37 = EXPLODE Disc
 */
void explodeDisc(getscore_result *gsr, int x, int y) {

   // LEFT explode
   if (x > 0) {
      if (gsr->grid[x-1][y]) {
         // SOLID
         if (gsr->grid[x-1][y] >= 21 && gsr->grid[x-1][y] <= 27 ) {
            gsr->grid[x-1][y] -= 10; // SOLID -> CRACK

         // CRACK
         } else if (gsr->grid[x-1][y] >= 11 && gsr->grid[x-1][y] <= 17 ) {
            gsr->grid[x-1][y] -= 10; // CRACK -> CLEAR
            int disc = gsr->grid[x-1][y];
            gsr->vertical_index[x-1][disc]++;
         }
      }
   }

   // RIGHT explode
   if (x < 6) {
      if (gsr->grid[x+1][y]) {
         // SOLID
         if (gsr->grid[x+1][y] >= 21 && gsr->grid[x+1][y] <= 27 ) {
            gsr->grid[x+1][y] -= 10; // SOLID -> CRACK

         // CRACK
         } else if (gsr->grid[x+1][y] >= 11 && gsr->grid[x+1][y] <= 17 ) {
            gsr->grid[x+1][y] -= 10; // CRACK -> CLEAR
            int disc = gsr->grid[x+1][y];
            gsr->vertical_index[x+1][disc]++;
         }
      }
   }

   // ABOVE explode
   if (y > 0) {
      if (gsr->grid[x][y-1]) {
         // SOLID
         if (gsr->grid[x][y-1] >= 21 && gsr->grid[x][y-1] <= 27) {
            gsr->grid[x][y-1] -= 10; // SOLID -> CRACK

         // CRACK
         } else if (gsr->grid[x][y-1] >= 11 && gsr->grid[x][y-1] <= 17) {
            gsr->grid[x][y-1] -= 10; // CRACK -> CLEAR
            int disc = gsr->grid[x][y-1];
            gsr->vertical_index[x][disc]++;
         }
      }
   }

   // BELOW explode
   if (y < 6) {
      if (gsr->grid[x][y+1]) {
         // SOLID
         if (gsr->grid[x][y+1] >= 21 && gsr->grid[x][y+1] <= 27) {
            gsr->grid[x][y+1] -= 10; // SOLID -> CRACK

         // CRACK
         } else if (gsr->grid[x][y+1] >= 11 && gsr->grid[x][y+1] <= 17) {
            gsr->grid[x][y+1] -= 10; // CRACK -> CLEAR
            int disc = gsr->grid[x][y+1];
            gsr->vertical_index[x][disc]++;
         }
      }
   }
}


void removeDisc(getscore_result *gsr, int x, int init_y) {
   int disc = gsr->grid[x][init_y];

   // 30 was added to the disc value to signal that it needed to explode
   // Now that it has, subtract the 30 to get us back to the true disc number.
   // We need it later to compute the vertical_index for this column.
   disc -= 30;

   int y;
   for (y = init_y; y <= 6; y++) {
      if (y < 6) {
         if (gsr->grid[x][y]) {
            gsr->grid[x][y] = gsr->grid[x][y+1];

         // Everything above here is 0 so we can stop now
         } else {
            break;
         }
      } else {
         gsr->grid[x][y] = 0;
      }
   }

   gsr->vertical_index[x][disc]--;
   gsr->vertical_count[x]--;
}

void getScore(getscore_result *gsr,
              unsigned long long step,
              int worksize,
              int *current_disc,
              char *perm_array,
              char valid_cache_spots,
              char need_to_update_cache_spots,
              getscore_result cache_gsr[]) {

   int disc_to_explode[50][2];
   int disc_to_explode_count = 0;
   memset(disc_to_explode, 0, sizeof(disc_to_explode[0][0]) * 50 * 2);
   get_score_calls++;

   char local_need_to_update_cache_spots = need_to_update_cache_spots;

   //
   // Loop through all of the discs we have to drop
   //
   int cd_index;
   int start_cd_index;
   int honor_cache = 1;

   if (!honor_cache || !valid_cache_spots) {
      start_cd_index = 0;
      gsr->gameover = 0;
      gsr->chain_length = 0;

   // Use the existing cache
   } else {
      start_cd_index = valid_cache_spots;
      memcpy(gsr, &cache_gsr[valid_cache_spots], sizeof(getscore_result));
      if (debug) {
         printGrid(gsr, "Cached Baseline", gsr->level, gsr->score, 0, 0, 0);
      }
   }

   gsr->step = step;

   // If we are using the cache and the previous disc resulted in gameover then this disc must also be a gameover.
   if (gsr->gameover) {
      return;
   }

   for (cd_index = start_cd_index; cd_index < worksize; cd_index++) {
      int disc = current_disc[cd_index];
      int column = perm_array[cd_index] - 1;

      // This only happens at the very end if the worksize didn't divide into the number of future_disc evenly
      if (!disc) {
         return;
      }

      if (debug) {
         printf("<div class='sequence'>\n");
      }

      //
      // If addDiscToGrid returns FALSE it means the column is full
      //
      if (!addDiscToGrid(gsr, disc, column, gsr->level, gsr->score, cd_index)) {
         gsr->gameover++;
         gsr->gameover_cd_index = cd_index;
         gsr->gameover_disc = disc;
         gsr->gameover_column = column;

         if (honor_cache && cache_gsr && local_need_to_update_cache_spots) {
            memcpy(&cache_gsr[cd_index+1] , gsr, sizeof(getscore_result));
            local_need_to_update_cache_spots--;
         }

         if (debug) {
            printf("</div>\n");
         }
         return;
      }

      int columns_with_explosions[7];
      int rows_with_explosions[7];
      memset(columns_with_explosions, 0, sizeof(columns_with_explosions));
      memset(rows_with_explosions, 0, sizeof(rows_with_explosions));

      int disc_exploded = 1;
      int just_added_disc = 1;
      while (disc_exploded) {
         disc_exploded = 0;
         if (disc_to_explode_count) {
            memset(disc_to_explode, 0, sizeof(disc_to_explode[0][0]) * 50 * 2);
            disc_to_explode_count = 0;
         }

         // Find disc that need to explode
         if (just_added_disc) {
            findDiscsToExplodeVertically(gsr, column, 0, disc_to_explode, &disc_to_explode_count);
            findDiscsToExplodeHorizontally(gsr, 1, column, gsr->vertical_count[column]-1, disc_to_explode, &disc_to_explode_count);
         } else {

            // Call findV and findH for any rows/columns that were impacted by explosions
            // the last time around
            int x;
            for (x = 0; x <= 6; x++) {
               if (columns_with_explosions[x]) {
                  findDiscsToExplodeVertically(gsr, x, 0, disc_to_explode, &disc_to_explode_count);
               }
            }

            int y;
            for (y = 0; y <= 6; y++) {
               if (rows_with_explosions[y]) {
                  findDiscsToExplodeHorizontally(gsr, 0, 0, y, disc_to_explode, &disc_to_explode_count);
               }
            }

            memset(columns_with_explosions, 0, sizeof(columns_with_explosions));
            memset(rows_with_explosions, 0, sizeof(rows_with_explosions));
         }

         if (just_added_disc && debug) {
            printGrid(gsr, "Discs To Explode", gsr->level, gsr->score, disc, column, 0);
         }

         if (disc_to_explode_count) {
            if (!just_added_disc && debug) {
               printGrid(gsr, "Discs To Explode", gsr->level, gsr->score, 0, 0, 0);
            }

            just_added_disc = 0;
            int first_explosion = 1;
            int i;
            for (i = 0; i < disc_to_explode_count; i++) {
               int x = disc_to_explode[i][0];
               int y = disc_to_explode[i][1];
               columns_with_explosions[x] = 1;
               rows_with_explosions[y] = 1;

               // If there is a disc above us it will drop down so we'll need to do a horizontal
               // check on all of the rows above us that have disc
               if (y < 6 && gsr->grid[x][y+1]) {
                  int tmp_y;
                  for (tmp_y = y; tmp_y < gsr->vertical_count[x]; tmp_y++) {
                     rows_with_explosions[tmp_y] = 1;
                  }
               }

               // If the disc below us will CLEAR up we need to horizontal check that row
               if (y > 0 && gsr->grid[x][y-1] >= 11 && gsr->grid[x][y-1] <= 17) {
                  rows_with_explosions[y-1] = 1;
               }

               // If the disc to our left will CLEAR up we need to vertical check that column
               if (x > 0 && gsr->grid[x-1][y] >= 11 && gsr->grid[x-1][y]  <= 17) {
                  columns_with_explosions[x-1] = 1;
               }

               // If the disc to our right will CLEAR up we need to vertical check that column
               if (x < 6 && gsr->grid[x+1][y] >= 11 && gsr->grid[x+1][y]  <= 17) {
                  columns_with_explosions[x+1] = 1;
               }

               explodeDisc(gsr, x, y);
               gsr->disc_exploded++;

               if (first_explosion) {
                  gsr->chain_length++;
                  first_explosion = 0;

                  if (gsr->chain_length > gsr->max_chain_length) {
                     gsr->max_chain_length = gsr->chain_length;
                     gsr->trigger_disc = cd_index;
                     //printf("TRIGGER_DISC_SET: %d, WORKSIZE: %d, valid_cache_spots %d, chain_lenth %d\n",
                     //       cd_index, worksize, valid_cache_spots, gsr->max_chain_length);
                  }
               }

               gsr->score += chain_scores[gsr->chain_length];
               disc_exploded = 1;
            }

            // If exploding a disc cleared discs to our left or our right and if one of those
            // columns has the experimental "multiple of the same clear number" then we consider that game over.
            if (gsr->gameover) {
               gsr->gameover_cd_index = cd_index;
               gsr->gameover_disc = disc;
               gsr->gameover_column = column;

               if (honor_cache && cache_gsr && local_need_to_update_cache_spots) {
                  memcpy(&cache_gsr[cd_index+1] , gsr, sizeof(getscore_result));
                  local_need_to_update_cache_spots--;
               }

               if (debug) {
                  printf("</div>\n");
               }
               return;
            }

            // It is critical that you remove disc from the top down. This is a little
            // hack to traverse disc_to_explode from top row to bottom row.
            int bottom_y_to_remove = 7;
            int top_y_to_remove = 0;
            for (i = disc_to_explode_count-1; i >= 0; i--) {
               if (disc_to_explode[i][1] > top_y_to_remove) {
                  top_y_to_remove = disc_to_explode[i][1];
               }

               if (disc_to_explode[i][1] < bottom_y_to_remove) {
                  bottom_y_to_remove = disc_to_explode[i][1];
               }
            }

            int y;
            for (y = top_y_to_remove; y >= bottom_y_to_remove; y--) {
               for (i = disc_to_explode_count-1; i >= 0; i--) {
                  if (disc_to_explode[i][1] == y) {
                     removeDisc(gsr, disc_to_explode[i][0], disc_to_explode[i][1]);
                  }
               }
            }

            int grid_is_empty = 1;
            int x;
            for (x = 0; x <= 6; x++) {
               if (gsr->grid[x][0]) {
                  grid_is_empty = 0;
                  break;
               }
            }

            if (grid_is_empty) {
               gsr->score += 70000;
               gsr->grid_cleared++;
            }

            if (debug) {
               printGrid(gsr, "Post EXPLOSION", gsr->level, gsr->score, 0, 0, grid_is_empty);
            }

         // If we get to here then all of the explosions are over.
         } else {
            just_added_disc = 0;

            if (!gsr->disc_left_in_level) {
               if (debug) {
                  printGrid(gsr, "EOL - pre shift up", gsr->level, gsr->score, disc, column, 0);
               }

               // Add the new row...first shift everything up a row
               int y;
               for (y = 6; y >= 0; y--) {
                  int x;
                  for (x = 0; x <= 6; x++) {
                     if (gsr->grid[x][y]) {

                        // If this is TRUE then the game is over because a column will overflow when we add the new row
                        if (y == 6) {
                           gsr->gameover++;
                           gsr->gameover_cd_index = cd_index;
                           gsr->gameover_disc = disc;
                           gsr->gameover_column = column;
                           gsr->gameover_levelup = 1;

                           if (debug) {
                              printf("</div>\n");
                           }

                           if (honor_cache && cache_gsr && local_need_to_update_cache_spots) {
                              memcpy(&cache_gsr[cd_index+1] , gsr, sizeof(getscore_result));
                              local_need_to_update_cache_spots--;
                           }

                           return;
                        }

                        gsr->grid[x][y+1] = gsr->grid[x][y];
                     }
                  }
               }

               if (debug) {
                  printGrid(gsr, "EOL - post shift up", gsr->level, gsr->score, disc, column, 0);
               }

               gsr->level++;
               gsr->score += 7000;
               gsr->disc_left_in_level = getDiscForLevel(gsr->level);

               int x;
               for (x = 0; x <= 6; x++) {
                  gsr->grid[x][0] = levelup_disc[gsr->level][x];
                  gsr->vertical_count[x]++;
               }

               if (debug) {
                  printGrid(gsr, "EOL - added new row", gsr->level, gsr->score, disc, column, 0);
               }

               // See if that will trigger any new explosions, if not 0 out chain_length
               // But if it will, set disc_exploded to true to the while loop will run again
               disc_exploded = 0;
               for (x = 0; x <= 6; x++) {
                  if (findDiscsToExplodeVertically(gsr, x, 1, disc_to_explode, &disc_to_explode_count)) {
                     columns_with_explosions[x] = 1;
                     disc_exploded = 1;
                  }
               }

               if (!disc_exploded) {
                  gsr->chain_length = 0;
               }

            } else {
               gsr->chain_length = 0;
            }
         }
      } // end of while disc_exploded

      if (debug) {
         printf("</div>\n");
      }

      if (honor_cache && cache_gsr && local_need_to_update_cache_spots) {
         memcpy(&cache_gsr[cd_index+1] , gsr, sizeof(getscore_result));
         local_need_to_update_cache_spots--;
      }
   }
}

void printArray(char *array, int last_x) {
   int i;

   int first_i = 0;
   int last_i = 685;
   if (last_x) {

      int last_i_with_value = 0;
      for (i = 0; i <= 685; i++) {
         if (array[i]) {
            last_i_with_value = i;
         } else {
            break;
         }
      }

      last_i = last_i_with_value;
      first_i = last_i - last_x + 1;
   }

   for (i = first_i; i <= last_i; i++) {
      if (array[i]) {
         printf(" %d", array[i]);
      } else {
         return;
      }
   }
}

void appendPermutation(getscore_result *gsr, char *permutation, int worksize, int debug) {
   // append the current permutation to the current gsr structure
   int m;

   for (m = 0; m <= 685; m++) {
      if (gsr->permutation[m]) {
         continue;
      }

      int n;
      for (n = 0; n < worksize; n++, m++) {
         gsr->permutation[m] = permutation[n];
         if (debug) {
            printf("APPEND[%d] = permutation[%d] %d\n", m, n, permutation[n]);
         }
      }
      break;
   }
}

