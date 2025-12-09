#define CX_IMPLEMENTATION
#define CX_ANSI_ENABLE
#include "../caylix.h"
#include <time.h>

int main() {
  const struct cx_vec2 *u = CX_VEC2_ONE;
  CX_PRINTLN("(%f, %f)", u->x, u->y);
}
