#define CX_IMPLEMENTATION
#define CX_ANSI_ENABLE
#include "../caylix.h"

int main()
{
    struct cx_vec2 a;
    struct cx_vec2 b;
    const struct cx_vec2 zero = *CX_VEC2_ZERO;
    const struct cx_vec2 one  = *CX_VEC2_ONE;
    const struct cx_vec2 unit_x = *CX_VEC2_UNIT_X;
    const struct cx_vec2 unit_y = *CX_VEC2_UNIT_Y;
    const struct cx_vec2 unit_neg_x = *CX_VEC2_UNIT_X_NEGATIVE;
    const struct cx_vec2 unit_neg_y = *CX_VEC2_UNIT_Y_NEGATIVE;

    cx_vec2_set(&a, 3.0, 4.0);
    cx_vec2_set(&b, 1.0, 2.0);

    cx_vec2_print(&a);
    cx_vec2_print(&b);
    cx_vec2_print(&zero);
    cx_vec2_print(&one);
    cx_vec2_print(&unit_x);
    cx_vec2_print(&unit_y);
    cx_vec2_print(&unit_neg_x);
    cx_vec2_print(&unit_neg_y);

    return 0;
}
