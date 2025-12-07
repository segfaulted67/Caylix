#ifndef CAYLIX_H
#define CAYLIX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <assert.h>

#ifdef CX_IMPLEMENTATION

#define CX_VERSION  "1.0.0"

#define CX_UNUSED_VAR(x)  ((void)(x))

#ifndef CX_FLOAT
#   ifdef CX_SINGLE_PRECISION_FLOAT
#     define CX_FLOAT float
#   else
#     define CX_FLOAT double
#   endif
#endif

#define CX_STR      char *
#define CX_CONST_STR    const char *

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

#ifndef CX_EPSILON
#   ifdef CX_SINGLE_PRECISION_FLOAT
#     define CX_EPSILON 1E-6f
#   else
#     define CX_EPSILON 1E-6
#   endif
#endif

#ifndef M_PI
#   ifdef CX_SINGLE_PRECISION_FLOAT
#     define M_PI  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f
#   else
#     define M_PI  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#   endif
#endif
#define CX_PI M_PI

#ifndef M_E
#   ifdef CX_SINGLE_PRECISION_FLOAT
#     define M_E   2.71828182845904523536028747135266249775724709369995f
#   else
#     define M_E   2.71828182845904523536028747135266249775724709369995
#   endif
#endif
#define CX_E M_E

#define CX_DA_INIT_CAP 8

#define CX_ABS(x)  _Generic((x), float: fabsf, double: fabs, default: fabs)(x)
#define CX_SQRT(x)  _Generic((x), float: sqrtf, double: sqrt, default: sqrt)(x)
#define CX_SIN(x)  _Generic((x), float: sinf, double: sin, default: sin)(x)
#define CX_COS(x)  _Generic((x), float: cosf, double: cos, default: cos)(x)
#define CX_TAN(x) _Generic((x), float: tanf, double: tan, default: tan)(x)
#define CX_COT(x) \
  ((CX_TAN(x) <= CX_EPSILON) ? INFINITY : 1.0 / CX_TAN(x))
#define CX_SEC(x) \
  ((CX_COS(x) <= CX_EPSILON) ? INFINITY : 1.0 / CX_COS(x))
#define CX_CSC(x) \
  ((CX_SIN(x) <= CX_EPSILON) ? INFINITY : 1.0 / CX_SIN(x))

#define CX_ASIN(x)  _Generic((x), float: asinf, double: asin, default: asin)(x)
#define CX_ACOS(x)  _Generic((x), float: acosf, double: acos, default: acos)(x)
#define CX_ATAN(x)  _Generic((x), float: atanf, double: atan, default: atan)(x)

#define CX_SAFE_DIVIDE(x, y)  (((y) == 0) ? INFINITY : (x) / (y))

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

#ifndef CX_API
#   ifdef CX_STATIC
#     define CX_API static
#   else
#     define CX_API extern
#   endif
#endif

#define CX_PRINTLN(fmt, ...)    printf(fmt "\n", ##__VA_ARGS__)
#define CX_FPRINTLN(stream, fmt, ...)    fprintf(stream, fmt "\n", ##__VA_ARGS__)


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

#define CX_ARR_LEN(arr)   (sizeof(arr)/sizeof(arr[0]))
#define CX_NUM_ARGS(type, ...)   sizeof((type []){ __VA_ARGS__ }) / sizeof(type)

#define CX_MIN(x, y)    ((x) < (y) ? (x) : (y))
#define CX_MAX(x, y)    ((x) > (y) ? (x) : (y))

#define CX_RANDOM(min, max)   \
  ((min) + (rand() % ((max) - (min) + 1)))
#define CX_RANDOMF(min, max)  \
  ((min) + ((rand()) / (RAND_MAX + 1.0f) * ((max) - (min))))



#endif

#ifdef __cplusplus
}
#endif

#endif // CAYLIX_H
