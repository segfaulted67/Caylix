#define CX_IMPLEMENTATION
#define CX_ANSI_ENABLE
#include "../caylix.h"
#include <time.h>

int main() {
  srand(time(NULL));
  CX_FLOAT a = 100;
  CX_FLOAT b = 500;
  printf("a: %f, b: %f\n", a, b);
  cx_swap(&a, &b);
  printf("a: %f, b: %f\n", a, b);
  for(int i = 0; i < 5; i++) {
    CX_PRINTLN("%d", CX_RANDOM(0, 10));
  }
}
