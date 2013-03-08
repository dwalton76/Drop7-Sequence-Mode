
typedef struct {
   unsigned long score;
   unsigned char level;
   char disc_left_in_level;
   unsigned int gameover;
   unsigned int gameover_cd_index;
   unsigned int gameover_disc;
   unsigned int gameover_column;
   unsigned int gameover_levelup;
   unsigned long long step;
   unsigned int grid_cleared;
   unsigned int disc_exploded;
   int trigger_disc;
   int eps;
   int chain_length;
   int max_chain_length;
   int max_chain_length_this_workset;
   char permutation[685];
   int grid[7][7];
   char vertical_count[7];
   char vertical_index[7][8];
} getscore_result;


extern unsigned long long get_score_calls;
extern unsigned long long add_disc_calls;
extern unsigned long long permutations_skipped;
extern int max_chain_length;
extern unsigned long long gameovercount;
extern int debug;
extern int eps_above_threshold;

extern int levelup_disc[75][7];

extern int future_disc[685];

// The formula is 7*n^2.5
extern int chain_scores[51];
int initial_grid[7][7];
extern int getDiscForLevel(int level);
extern char* getClass(int i);
extern int prettyNumber(int i);
extern void printPermutation(char *desc, getscore_result *gsr);
extern void printGrid(getscore_result *gsr, char* context, int level, int score, int disc, int dropcolumn, int grid_is_empty);
extern unsigned long long power(int a, int b);
extern int addDiscToGrid(getscore_result *gsr, int disc, int column, int level, int score, int cd_index);
extern int getDiscHorizontalCount(getscore_result *gsr, int x, int y);
extern int findDiscsToExplodeVertically(getscore_result *gsr, int column, int fast_return, int disc_to_explode[][2], int *disc_to_explode_count);
extern void findDiscsToExplodeHorizontally(getscore_result *gsr, int look_at_one_spot, int column, int row, int disc_to_explode[][2], int *disc_to_explode_count);
extern void explodeDisc(getscore_result *gsr, int x, int y);
extern void removeDisc(getscore_result *gsr, int x, int init_y);
extern void getScore(getscore_result *gsr, unsigned long long step, int worksize, int *current_disc, char *perm_array, char valid_cache_spots, char need_to_update_cache_spots, getscore_result cache_gsr[]);
extern void printArray(char *array, int last_x);
extern void appendPermutation(getscore_result *gsr, char *permutation, int worksize, int debug);
extern int getExplosionPotentialScore(getscore_result *gsr);

