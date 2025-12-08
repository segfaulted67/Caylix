#ifndef CAYLIX_H
#define CAYLIX_H

#ifdef __cplusplus
extern "C" {
#endif

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
#   define CX_PI_HALF 1.5707963267948966f
#endif

/* Square of PI */
#ifndef CX_PI_SQUARED
#   define CX_PI_SQUARED 9.8696044010893586f
#endif

/* Two PI(2 * PI) */
#ifndef CX_PI_TAU
#   define CX_TAU 6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696506842341359f
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
#   define CX_RAD_PER_DEG 0.0174532925199432957692369076848861f
#endif

/* Degree per Radian = 180/PI */
#ifndef CX_DEG_PER_RAD
#   define CX_DEG_PER_RAD 57.2957795130823208767981548141052f
#endif

/* Default initial capacity for Dynamic Array */
#define CX_DA_INIT_CAP 8

/* A macro for absolute value. eg: CX_ABS(69.0) --> 69.0 , CX_ABS(-69.0) -> 69.0 */
#define CX_ABS(x)   _Generic((x), float: fabsf, double: fabs, default: fabs)(x)
/* A macro for square root*/
#define CX_SQRT(x)  _Generic((x), float: sqrtf, double: sqrt, default: sqrt)(x)
/* A macro for sin */
#define CX_SIN(x)   _Generic((x), float: sinf, double: sin, default: sin)(x)
/* A macro for cos */
#define CX_COS(x)   _Generic((x), float: cosf, double: cos, default: cos)(x)
/* A macro for tan */
#define CX_TAN(x)   _Generic((x), float: tanf, double: tan, default: tan)(x)
/* A macro for cot */
#define CX_COT(x) \
  ((CX_TAN(x) <= CX_EPSILON) ? INFINITY : 1.0 / CX_TAN(x))
/* A macro for sec */
#define CX_SEC(x) \
  ((CX_COS(x) <= CX_EPSILON) ? INFINITY : 1.0 / CX_COS(x))
/* A macro for cosec */
#define CX_CSC(x) \
  ((CX_SIN(x) <= CX_EPSILON) ? INFINITY : 1.0 / CX_SIN(x))

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
/* Macro returns the number of arguments. eg: CX_NUM_ARGS(int/* type */, 1, 0, 6, 7, 9, 3) -- returns 6 */
#define CX_NUM_ARGS(type, ...)   sizeof((type []){ __VA_ARGS__ }) / sizeof(type)

/* Macros returns the min/max between two numbers */
#define CX_MIN(x, y)    ((x) < (y) ? (x) : (y))
#define CX_MAX(x, y)    ((x) > (y) ? (x) : (y))

/* Degree to Radian/Radian to Degree Conversion */
#define CX_DEG_TO_RAD(x)  ((x) * CX_DEG_PER_RAD)
#define CX_RAD_TO_DEG(x)  ((x) * CX_RAD_PER_DEG)

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
static CX_API_INLINE void cx_swap(CX_FLOAT *x, CX_FLOAT *y) {
  CX_FLOAT t = *x;
  *x = *y;
  *y = t;
}

#endif // CX_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // CAYLIX_H
