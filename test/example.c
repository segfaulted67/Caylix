#define CX_IMPLEMENTATION
#define CX_ANSI_ENABLE
#include "../caylix.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    printf("===== Testing cx_vec2 =====\n");

    struct cx_vec2 v2a, v2b, v2c;

    cx_vec2_set(&v2a, 3.0f, 4.0f);
    cx_vec2_set_random(&v2b);
    cx_vec2_print(&v2a);
    cx_vec2_print(&v2b);

    v2c = cx_vec2_add(&v2a, &v2b);
    printf("v2a + v2b = ");
    cx_vec2_print(&v2c);

    v2c = cx_vec2_subtract(&v2a, &v2b);
    printf("v2a - v2b = ");
    cx_vec2_print(&v2c);

    v2c = cx_vec2_scalar_multiplyf(&v2a, 2.0f);
    printf("v2a * 2 = ");
    cx_vec2_print(&v2c);

    CX_FLOAT dot2 = cx_vec2_dot_product(&v2a, &v2b);
    CX_FLOAT cross2 = cx_vec2_cross_product(&v2a, &v2b);
    printf("v2a . v2b = %.2f\n", dot2);
    printf("v2a x v2b = %.2f\n", cross2);

    CX_FLOAT mag2 = cx_vec2_magnitude(&v2a);
    printf("|v2a| = %.2f\n", mag2);
    v2c = cx_vec2_normalize(&v2a);
    printf("Normalized v2a = ");
    cx_vec2_print(&v2c);

    printf("\n===== Testing cx_vec3 =====\n");

    struct cx_vec3 v3a, v3b, v3c;

    cx_vec3_set(&v3a, 1.0f, 2.0f, 3.0f);
    cx_vec3_set_random(&v3b);
    cx_vec3_print(&v3a);
    cx_vec3_print(&v3b);

    v3c = cx_vec3_add(&v3a, &v3b);
    printf("v3a + v3b = ");
    cx_vec3_print(&v3c);

    v3c = cx_vec3_subtract(&v3a, &v3b);
    printf("v3a - v3b = ");
    cx_vec3_print(&v3c);

    v3c = cx_vec3_scalar_multiplyf(&v3a, 3.0f);
    printf("v3a * 3 = ");
    cx_vec3_print(&v3c);

    CX_FLOAT dot3 = cx_vec3_dot_product(&v3a, &v3b);
    struct cx_vec3 cross3 = cx_vec3_cross_product(&v3a, &v3b);
    printf("v3a . v3b = %.2f\n", dot3);
    printf("v3a x v3b = ");
    cx_vec3_print(&cross3);

    CX_FLOAT mag3 = cx_vec3_magnitude(&v3a);
    printf("|v3a| = %.2f\n", mag3);
    v3c = cx_vec3_normalize(&v3a);
    printf("Normalized v3a = ");
    cx_vec3_print(&v3c);

    printf("\n===== Testing Reference Vectors =====\n");
    const struct cx_vec2 ref2 = *CX_VEC2_UNIT_X;
    const struct cx_vec3 ref3 = *CX_VEC3_UNIT_Z;
    printf("Reference vec2 UNIT_X = ");
    cx_vec2_print(&ref2);
    printf("Reference vec3 UNIT_Z = ");
    cx_vec3_print(&ref3);

    return 0;
}
