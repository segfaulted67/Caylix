#ifndef CAYLIX_H
#define CAYLIX_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* Included standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <assert.h>

#ifdef CX_IMPLEMENTATION

#define CX_VERSION  "1.0.0"

/* Suppress "unused variable" warning */
/* Example:                           */
/* void something(int a) {            */
/* ...                                */
/* CX_UNUSED_VAR(a);                  */
/* }                                  */
#define CX_UNUSED_VAR(x)  ((void)(x))

/* typecast float/double as CX_FLOAT */
#ifndef CX_FLOAT
#   ifdef CX_SINGLE_PRECISION_FLOAT
#     define CX_FLOAT float
#   else
#     define CX_FLOAT double
#   endif
#endif

/* typecast char * /const char * as CX_STR/CX_CONST_STR */
#define CX_STR      char *
#define CX_CONST_STR    const char *

/* Optionally Enable ANSI Colors for Log */
#ifdef CX_ANSI_ENABLE
#       define CX_RESET   "\033[0m"
#       define CX_RED     "\033[31m"
#       define CX_GREEN   "\033[32m"
#       define CX_YELLOW  "\033[33m"
#       define CX_BLUE    "\033[34m"
#       define CX_MAGENTA "\033[35m"
#       define CX_CYAN    "\033[36m"
#       define CX_WHITE   "\033[37m"
#       define CX_BOLD    "\033[1m"
#       define CX_BRED    "\033[91m"
#       define CX_BYELLOW "\033[93m"
#       define CX_BBLUE   "\033[94m"
#endif

/* Value of epsilon */
#ifndef CX_EPSILON
#   ifdef CX_SINGLE_PRECISION_FLOAT
#     define CX_EPSILON 1E-6f
#   else
#     define CX_EPSILON 1E-6
#   endif
#endif

/* PI to 100 digits */
#ifndef CX_PI
#   ifdef CX_SINGLE_PRECISION_FLOAT
#     define CX_PI  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f
#   else
#     define CX_PI  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#   endif
#endif

/* Half of PI */
#ifndef CX_PI_HALF
#   define CX_PI_HALF 1.5707963267948966
#endif

/* Square of PI */
#ifndef CX_PI_SQUARED
#   define CX_PI_SQUARED 9.8696044010893586
#endif

/* Two PI(2 * PI) */
#ifndef CX_TAU
#   define CX_TAU 6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696506842341359
#endif

/* Value of e(euler's number) */
#ifndef CX_E
#   ifdef CX_SINGLE_PRECISION_FLOAT
#     define CX_E   2.71828182845904523536028747135266249775724709369995f
#   else
#     define CX_E   2.71828182845904523536028747135266249775724709369995
#   endif
#endif

/* Radians per Degree = PI/180 */
#ifndef CX_RAD_PER_DEG
#   define CX_RAD_PER_DEG 0.0174532925199432957692369076848861
#endif

/* Degree per Radian = 180/PI */
#ifndef CX_DEG_PER_RAD
#   define CX_DEG_PER_RAD 57.2957795130823208767981548141052
#endif

/* Default initial capacity for Dynamic Array */
#define CX_DA_INIT_CAP 8

/* A macro for absolute value. eg: CX_ABS(69.0) --> 69.0 , CX_ABS(-69.0) -> 69.0 */
#define CX_ABS(x)  ((x) < 0) ? -(x) : (x)
/* A macro for square root*/
#define CX_SQRT(x)  _Generic((x), float: sqrtf, double: sqrt, default: sqrt)(x)
/* A macro for sin */
#define CX_SIN(x)   _Generic((x), float: sinf, double: sin, default: sin)(x)
/* A macro for cos */
#define CX_COS(x)   _Generic((x), float: cosf, double: cos, default: cos)(x)
/* A macro for tan */
#define CX_TAN(x)   _Generic((x), float: tanf, double: tan, default: tan)(x)
/* A macro for cot */
#define CX_COT(x)  (1.0 / CX_TAN(x))
/* A macro for sec */
#define CX_SEC(x)  (1.0 / CX_COS(x))
/* A macro for cosec */
#define CX_CSC(x)  (1.0 / CX_SIN(x))

/* A macro for sin inverse or asin */
#define CX_ASIN(x)  _Generic((x), float: asinf, double: asin, default: asin)(x)
/* A macro for cos inverse or acos */
#define CX_ACOS(x)  _Generic((x), float: acosf, double: acos, default: acos)(x)
/* A macro for tan inverse or atan */
#define CX_ATAN(x)  _Generic((x), float: atanf, double: atan, default: atan)(x)

/* Safely divides x by y; returns INFINITY if y == 0 */
/* Example: CX_SAFE_DIVIDE(5.0, 0.0); --> inf        */
/*          CX_SAFE_DIVIDE(5.0, 5.0); --> 1.0        */
#define CX_SAFE_DIVIDE(x, y)  (((y) == 0) ? INFINITY : (x) / (y))

/* typecast inline for different compilers */
#ifndef CX_API_INLINE
  #ifdef _MSC_VER
    #define CX_API_INLINE __forceinline
  #elif defined(__GNUC__)
    #if defined(__STRICT_ANSI__)
      #define CX_API_INLINE __inline __attribute__((always_inline))
    #else
      #define CX_API_INLINE inline __attribute__((always_inline))
    #endif
  #else
    #define CX_API_INLINE inline
  #endif
#endif

/* typecast static/extern to CX_API */
#ifndef CX_API
#   ifdef CX_STATIC
#     define CX_API static
#   else
#     define CX_API extern
#   endif
#endif

/* Small macro for printf with new line */
#define CX_PRINTLN(fmt, ...)    printf(fmt "\n", ##__VA_ARGS__)
#define CX_FPRINTLN(stream, fmt, ...)    fprintf(stream, fmt "\n", ##__VA_ARGS__)


/* Logging system for error handeling */
/* Optionally can Enable ANSI colors */
#ifdef CX_ANSI_ENABLE
#       define CX_LOG(stream, color, level, fmt, ...)   CX_FPRINTLN(stream, color "[" level "] " CX_RESET fmt, ##__VA_ARGS__)
#       define CX_ERROR(fmt, ...)                       CX_LOG(stderr, CX_RED, "ERROR", "%s:%d (%s()): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#       define CX_INFO(fmt, ...)                        CX_LOG(stdout, CX_BLUE, "INFO", fmt, ##__VA_ARGS__)
#       define CX_WARN(fmt, ...)                        CX_LOG(stdout, CX_YELLOW, "WARN", "%s:%d (%s()): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#       define CX_DEBUG(fmt, ...)                       CX_LOG(stdout, CX_GREEN, "DEBUG", "%s:%d (%s()): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
#       define CX_LOG(stream, level, fmt, ...)          CX_FPRINTLN(stream, "[" level "] " fmt, ##__VA_ARGS__)
#       define CX_ERROR(fmt, ...)                       CX_LOG(stderr, "ERROR", "%s:%d (%s()): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#       define CX_INFO(fmt, ...)                        CX_LOG(stdout, "INFO", fmt, ##__VA_ARGS__)
#       define CX_WARN(fmt, ...)                        CX_LOG(stdout, "WARN", "%s:%d (%s()): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#       define CX_DEBUG(fmt, ...)                       CX_LOG(stdout, "DEBUG", "%s:%d (%s()): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#endif
#define CX_ERROR_RET(ret, fmt, ...)                     do { CX_ERROR(fmt, ##__VA_ARGS__);  return ret; } while (0)
#define CX_ASSERT   assert

#define CX_MALLOC   malloc
#define CX_REALLOC  realloc
#define CX_CALLOC   calloc
#define CX_FREE     free

/* Macro returns the length of an array */
#define CX_ARR_LEN(arr)   (sizeof(arr)/sizeof(arr[0]))
/* Macro returns the number of arguments. eg: CX_NUM_ARGS(int, 1, 0, 6, 7, 9, 3) -- returns 6 */
#define CX_NUM_ARGS(type, ...)   sizeof((type []){ __VA_ARGS__ }) / sizeof(type)

/* Macros returns the min/max between two numbers */
#define CX_MIN(x, y)    ((x) < (y) ? (x) : (y))
#define CX_MAX(x, y)    ((x) > (y) ? (x) : (y))

/* Degree to Radian/Radian to Degree Conversion */
#define CX_DEG_TO_RAD(x)  ((x) * CX_DEG_PER_RAD)
#define CX_RAD_TO_DEG(x)  ((x) * CX_RAD_PER_DEG)

/* A Macro returns the square of number */
#define CX_SQUARE(x)  ((x) * (x))

/* CX_RANDOM: Random number generator between two numbers [min, max](int) */
#define CX_RANDOM(min, max)   \
  ((min) + (rand() % ((max) - (min) + 1)))
/* CX_RANDOMF: Random number generator between two numbers [min, max](float) */
#define CX_RANDOMF(min, max)  \
  ((min) + ((rand()) / (RAND_MAX + 1.0f) * ((max) - (min))))


/* Swaps the values of two CX_FLOAT variables */
/* Example:                                   */
/* CX_FLOAT a = 6, b = 7;                     */
/* cx_swap(&a, &b); --> a = 7, b = 6          */
static CX_API_INLINE void cx_swap(CX_FLOAT *x, CX_FLOAT *y)
{
  CX_FLOAT t = *x;
  *x = *y;
  *y = t;
}


/* ------------------------------------------------------------------------------------------------------------ */
/* forward decleration ---------------------------------------------------------------------------------------- */
struct cx_vec2;
struct cx_vec3;
struct cx_vec4;
struct cx_mat2;
struct cx_mat3;
struct cx_mat4;
struct cx_quaternion;

#define CX_REF_VEC2_ZERO              0
#define CX_REF_VEC2_UNIT_X            1
#define CX_REF_VEC2_UNIT_Y            2
#define CX_REF_VEC2_UNIT_X_NEGATIVE   3
#define CX_REF_VEC2_UNIT_Y_NEGATIVE   4
#define CX_REF_VEC2_ONE               5

CX_API const struct cx_vec2 *cx_get_reference_vec2(int id);

#define CX_REF_VEC3_ZERO              0
#define CX_REF_VEC3_UNIT_X            1
#define CX_REF_VEC3_UNIT_Y            2
#define CX_REF_VEC3_UNIT_Z            3
#define CX_REF_VEC3_UNIT_X_NEGATIVE   4
#define CX_REF_VEC3_UNIT_Y_NEGATIVE   5
#define CX_REF_VEC3_UNIT_Z_NEGATIVE   6
#define CX_REF_VEC3_ONE               7

CX_API const struct cx_vec3 *cx_get_reference_vec3(int id);

#define CX_REF_VEC4_ZERO              0
#define CX_REF_VEC4_UNIT_X            1
#define CX_REF_VEC4_UNIT_Y            2
#define CX_REF_VEC4_UNIT_Z            3
#define CX_REF_VEC4_UNIT_X_NEGATIVE   4
#define CX_REF_VEC4_UNIT_Y_NEGATIVE   5
#define CX_REF_VEC4_UNIT_Z_NEGATIVE   6
#define CX_REF_VEC4_ONE               7

CX_API const struct cx_vec4 *cx_get_reference_vec4(int id);
/* ------------------------------------------------------------------------------------------------------------ */
/* reference_vec2---------------------------------------------------------------------------------------------- */
/* {0, 0}                                                                                                       */
#define CX_VEC2_ZERO              cx_get_reference_vec2(CX_REF_VEC2_ZERO)
/* {1, 0}                                                                                                       */
#define CX_VEC2_UNIT_X            cx_get_reference_vec2(CX_REF_VEC2_UNIT_X)
/* {0, 1}                                                                                                       */
#define CX_VEC2_UNIT_Y            cx_get_reference_vec2(CX_REF_VEC2_UNIT_Y)
/* {-1, 0}                                                                                                      */
#define CX_VEC2_UNIT_X_NEGATIVE   cx_get_reference_vec2(CX_REF_VEC2_UNIT_X_NEGATIVE)
/* {0, -1}                                                                                                      */
#define CX_VEC2_UNIT_Y_NEGATIVE   cx_get_reference_vec2(CX_REF_VEC2_UNIT_Y_NEGATIVE)
/* {1, 1}                                                                                                       */
#define CX_VEC2_ONE               cx_get_reference_vec2(CX_REF_VEC2_ONE)

/* ------------------------------------------------------------------------------------------------------------ */
/* reference_vec3---------------------------------------------------------------------------------------------- */
/* {0, 0, 0}                                                                                                    */
#define CX_VEC3_ZERO              cx_get_reference_vec3(CX_REF_VEC3_ZERO)
/* {1, 0, 0}                                                                                                    */
#define CX_VEC3_UNIT_X            cx_get_reference_vec3(CX_REF_VEC3_UNIT_X)
/* {0, 1, 0}                                                                                                    */
#define CX_VEC3_UNIT_Y            cx_get_reference_vec3(CX_REF_VEC3_UNIT_Y)
/* {0, 0, 1}                                                                                                    */
#define CX_VEC3_UNIT_Z            cx_get_reference_vec3(CX_REF_VEC3_UNIT_Z)
/* {-1, 0, 0}                                                                                                   */
#define CX_VEC3_UNIT_X_NEGATIVE   cx_get_reference_vec3(CX_REF_VEC3_UNIT_X_NEGATIVE)
/* {0, -1, 0}                                                                                                   */
#define CX_VEC3_UNIT_Y_NEGATIVE   cx_get_reference_vec3(CX_REF_VEC3_UNIT_Y_NEGATIVE)
/* {0, 0, -1}                                                                                                   */
#define CX_VEC3_UNIT_Z_NEGATIVE   cx_get_reference_vec3(CX_REF_VEC3_UNIT_Z_NEGATIVE)
/* {1, 1, 1}                                                                                                    */
#define CX_VEC3_ONE               cx_get_reference_vec3(CX_REF_VEC3_ONE)

/* ------------------------------------------------------------------------------------------------------------ */
/* cx_vec2 functions ------------------------------------------------------------------------------------------ */
struct cx_vec2 {
  union {
    CX_FLOAT v[2];
    struct {
      CX_FLOAT x, y;
    };
  };
} cx_vec2;

CX_API struct cx_vec2 *cx_vec2_zero(struct cx_vec2 *u);                                               /* Returns zero vec2 */
CX_API struct cx_vec2 *cx_vec2_set(struct cx_vec2 *u, CX_FLOAT x, CX_FLOAT y);                        /* Set a vec2 with x, y */
CX_API struct cx_vec2 *cx_vec2_negate(struct cx_vec2 *u);                                             /* Returns the negation of a vec2 */
CX_API struct cx_vec2 *cx_vec2_add(struct cx_vec2 *u, struct cx_vec2 *v);                             /* Returns the addition of two vec2 */
CX_API struct cx_vec2 *cx_vec2_subtract(struct cx_vec2 *u, struct cx_vec2 *v);                        /* Returns the subtraction of two vec2 */
CX_API struct cx_vec2 *cx_vec2_scalar_multiply(struct cx_vec2 *u, CX_FLOAT f);                        /* Returns the scalar multiplication of a vec2. eg: u = <1.0f, 3.0f> and f = 3.0f => <3.0f, 9.0f> */
CX_API struct cx_vec2 *cx_vec2_dot_product(struct cx_vec2 *u, struct cx_vec2 *v);                     /* Returns the dot product b/w two vec2 */
CX_API struct cx_vec2 *cx_vec2_cross_product(struct cx_vec2 *u, struct cx_vec2 *v);                   /* Returns the cross product b/w two vec2 */
CX_API struct cx_vec2 *cx_vec2_normalize(struct cx_vec2 *u);                                          /* Returns the norm of a vec2 */
CX_API struct cx_vec2 *cx_vec2_magnitude(struct cx_vec2 *u);                                          /* Returns the magnitude of a vec2 */


static struct cx_vec2 _cx_vec2_zero             = { { { 0.0f, 0.0f } } };
static struct cx_vec2 _cx_vec2_unit_x           = { { { 1.0f, 0.0f } } };
static struct cx_vec2 _cx_vec2_unit_y           = { { { 0.0f, 1.0f } } };
static struct cx_vec2 _cx_vec2_unit_x_negative  = { { { -1.0f, 0.0f } } };
static struct cx_vec2 _cx_vec2_unit_y_negative  = { { { 0.0f, -1.0f } } };
static struct cx_vec2 _cx_vec2_one              = { { { 1.0f, 1.0f } } };

CX_API const struct cx_vec2 *cx_get_reference_vec2(int id)
{
  switch(id) {
    case CX_REF_VEC2_ZERO:                return &_cx_vec2_zero;
    case CX_REF_VEC2_ONE:                 return &_cx_vec2_one;
    case CX_REF_VEC2_UNIT_X:              return &_cx_vec2_unit_x;
    case CX_REF_VEC2_UNIT_Y:              return &_cx_vec2_unit_y;
    case CX_REF_VEC2_UNIT_X_NEGATIVE:     return &_cx_vec2_unit_x_negative;
    case CX_REF_VEC2_UNIT_Y_NEGATIVE:     return &_cx_vec2_unit_y_negative;
    default:
      return &_cx_vec2_zero;
  }
}



#endif // CX_IMPLEMENTATION

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CAYLIX_H
