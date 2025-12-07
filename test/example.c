#define CX_IMPLEMENTATION
#define CX_ANSI_ENABLE
#include "../caylix.h"
#include <time.h>

int main() {
  srand(time(NULL));
  // CX_PRINTLN("%f", CX_COT(0.0f) + 1);
  // CX_PRINTLN("%d", CX_NUM_ARGS(int, 0, 9, 2, 352, 4, 3, 36, 63, 6, 34, 643, 6, 43, 6, 34, 643, 63, 634, 6, 436, 43, 6,3 , 4, 43, 6, 2, 5, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0));
  // CX_ERROR_RET(69, " ");
  for(int i = 0; i < 500; i++) {
    float random = CX_RANDOMF(2, 3);
    CX_PRINTLN("%d", CX_RANDOM(0, 10));
    CX_PRINTLN("%f", random);
  }
}
