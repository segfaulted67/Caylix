#define CX_IMPLEMENTATION
#define CX_SINGLE_PRECISION_FLOAT
#define CX_ANSI_ENABLE
#include "../caylix.h"

#include <stdio.h>
#include <stdlib.h>


CX_FLOAT function(CX_FLOAT x, CX_FLOAT y)
{
  return 2 * x * y;
}

int main()
{
  float xn = 0.0f;
  float yn1 = 1.0f;
  float h = 0.1f;
  for(int i = 0; i < 10; i++) {
    CX_PRINTLN("rk4: v(%f) ≈ %f", xn, yn1);
    yn1 = cx_rk4(function, xn, yn1, h);
    xn += h;
  }

  return 0;
}
