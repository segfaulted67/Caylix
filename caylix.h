#ifndef CAYLIX_H
#define CAYLIX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Included standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <assert.h>

#include <time.h>

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

/* typecast CX_FLOAT complex as CX_COMPLEX */
#ifndef CX_COMPLEX
#   include <complex.h>
/* https://learn.microsoft.com/en-us/cpp/c-runtime-library/complex-math-support?view=msvc-170 */
#   ifdef _MSC_VER
#     ifdef CX_SINGLE_PRECISION_FLOAT
#       define CX_COMPLEX _Fcomplex
#     else
#       define CX_COMPLEX _Dcomplex
#     endif
#   else
#     define CX_COMPLEX _Complex CX_FLOAT
#   endif
#endif

/* typecast char and const char * as CX_STR and CX_CONST_STR */
#define CX_STR          char *
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
#define CX_ABS(x)   ((CX_FLOAT)fabs(x))
/* A macro for complex absolute values */
#define CX_CABS(x)  cabs(x)
/* A macro for complex exponentials */
#define CX_CEXP(x)  cexp(x)
/* A macro for square root*/
#define CX_SQRT(x)  ((CX_FLOAT)sqrt(x))
/* A macro for sin */
#define CX_SIN(x)  ((CX_FLOAT)sin(x))
/* A macro for cos */
#define CX_COS(x)  ((CX_FLOAT)cos(x))
/* A macro for tan */
#define CX_TAN(x)  ((CX_FLOAT)tan(x))
/* A macro for cot */
#define CX_COT(x)  (1.0 / CX_TAN(x))
/* A macro for sec */
#define CX_SEC(x)  (1.0 / CX_COS(x))
/* A macro for cosec */
#define CX_CSC(x)  (1.0 / CX_SIN(x))

/* A macro for sin inverse or asin */
#define CX_ASIN(x)  ((CX_FLOAT)asin(x))
/* A macro for cos inverse or acos */
#define CX_ACOS(x)  ((CX_FLOAT)acos(x))
/* A macro for tan inverse or atan */
#define CX_ATAN(x)  ((CX_FLOAT)atan(x))

/* Safely divides x by y; returns INFINITY if y == 0 */
/* Example: CX_SAFE_DIVIDE(5.0, 0.0); --> inf        */
/*          CX_SAFE_DIVIDE(5.0, 5.0); --> 1.0        */
#define CX_SAFE_DIVIDE(x, y)  ((CX_ABS((y)) <= CX_EPSILON) ? (((x) > 0) ? INFINITY : -INFINITY) : (x) / (y))

#define CX_FLOAT_EQUALS(x, y)	((CX_ABS(x-y) <= CX_EPSILON) ? 1 : 0)

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

/* Macro returns the length of an array eg. arr[] = { 0, 1, 2 }; CX_ARR_LEN(arr); -> 3 */
#define CX_ARR_LEN(arr)   (sizeof(arr)/sizeof(arr[0]))
/* Macro returns the number of arguments. eg: CX_NUM_ARGS(int, 1, 0, 6, 7, 9, 3) -- returns 6 */
#define CX_NUM_ARGS(type, ...)   (sizeof((type []){ __VA_ARGS__ }) / sizeof(type))

/* Macros returns the min/max between two numbers */
#define CX_MIN(x, y)    ((x) < (y) ? (x) : (y))
#define CX_MAX(x, y)    ((x) > (y) ? (x) : (y))

/* Degree to Radian/Radian to Degree Conversion */
#define CX_DEG_TO_RAD(x)  ((x) * CX_RAD_PER_DEG)
#define CX_RAD_TO_DEG(x)  ((x) * CX_DEG_PER_RAD)

/* A Macro returns the square of number */
#define CX_SQ(x)  ((x) * (x))

/* CX_RANDOM: Random number generator between two numbers [min, max](int) */
#define CX_RANDOM(min, max)   \
  ((min) + (rand() % ((max) - (min) + 1)))
/* CX_RANDOMF: Random number generator between two numbers [min, max](float) */
#define CX_RANDOMF(min, max)  \
  ((min) + ((rand()) / (RAND_MAX + 1.0f) * ((max) - (min))))
/* CX_RANDOM_FLOAT: Generates a random float */
#define CX_RANDOM_FLOAT   (((CX_FLOAT)rand() - (CX_FLOAT)rand()) / (CX_FLOAT)RAND_MAX)
/* CX_SRAND: Set seed for random numbers */
#define CX_SRAND()      (srand(time(NULL)))


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

static CX_API_INLINE CX_FLOAT cx_lerp(CX_FLOAT a, CX_FLOAT b, CX_FLOAT t)
{
  return a + t * (b - a);
}

static CX_API_INLINE CX_FLOAT cx_clamp(CX_FLOAT value, CX_FLOAT min, CX_FLOAT max)
{
  if(min == max)  return min;
  if(value < min) return min;
  if(value > max) return max;

  return value;
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
#define CX_REF_VEC4_UNIT_W            4
#define CX_REF_VEC4_UNIT_X_NEGATIVE   5
#define CX_REF_VEC4_UNIT_Y_NEGATIVE   6
#define CX_REF_VEC4_UNIT_Z_NEGATIVE   7
#define CX_REF_VEC4_UNIT_W_NEGATIVE   8
#define CX_REF_VEC4_ONE               9

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
/* reference_vec4---------------------------------------------------------------------------------------------- */
/* {0, 0, 0, 0}                                                                                                 */
#define CX_VEC4_ZERO              cx_get_reference_vec4(CX_REF_VEC4_ZERO)
/* {1, 0, 0, 0}                                                                                                 */
#define CX_VEC4_UNIT_X            cx_get_reference_vec4(CX_REF_VEC4_UNIT_X)
/* {0, 1, 0, 0}                                                                                                 */
#define CX_VEC4_UNIT_Y            cx_get_reference_vec4(CX_REF_VEC4_UNIT_Y)
/* {0, 0, 1, 0}                                                                                                 */
#define CX_VEC4_UNIT_Z            cx_get_reference_vec4(CX_REF_VEC4_UNIT_Z)
/* {0, 0, 0, 1}                                                                                                 */
#define CX_VEC4_UNIT_W            cx_get_reference_vec4(CX_REF_VEC4_UNIT_W)
/* {-1, 0, 0, 0}                                                                                                */
#define CX_VEC4_UNIT_X_NEGATIVE   cx_get_reference_vec4(CX_REF_VEC4_UNIT_X_NEGATIVE)
/* {0, -1, 0, 0}                                                                                                */
#define CX_VEC4_UNIT_Y_NEGATIVE   cx_get_reference_vec4(CX_REF_VEC4_UNIT_Y_NEGATIVE)
/* {0, 0, -1, 0}                                                                                                */
#define CX_VEC4_UNIT_Z_NEGATIVE   cx_get_reference_vec4(CX_REF_VEC4_UNIT_Z_NEGATIVE)
/* {0, 0, 0, -1}                                                                                                */
#define CX_VEC4_UNIT_W_NEGATIVE   cx_get_reference_vec4(CX_REF_VEC4_UNIT_W_NEGATIVE)
/* {1, 1, 1, 1}                                                                                                 */
#define CX_VEC4_ONE               cx_get_reference_vec4(CX_REF_VEC4_ONE)

/* ------------------------------------------------------------------------------------------------------------ */
/* cx_vec2 functions ------------------------------------------------------------------------------------------ */
struct cx_vec2 {
  union {
    CX_FLOAT vec[2];
    struct {
      CX_FLOAT x, y;
    };
  };
};

CX_API CX_API_INLINE struct cx_vec2 *cx_vec2_set_zero(struct cx_vec2 *u);                                           /* Returns zero vec2 */
CX_API CX_API_INLINE struct cx_vec2 *cx_vec2_set(struct cx_vec2 *u, CX_FLOAT x, CX_FLOAT y);                        /* Set vec2 with x, y */
CX_API CX_API_INLINE struct cx_vec2 *cx_vec2_set_random(struct cx_vec2 *u);                                         /* Set vec2 with random values */
CX_API CX_API_INLINE struct cx_vec2 *cx_vec2_negate(struct cx_vec2 *u);                                             /* Returns the negation of a vec2 */
CX_API CX_API_INLINE struct cx_vec2 cx_vec2_add(const struct cx_vec2 *u, const struct cx_vec2 *v);                  /* Returns the addition of two vec2 */
CX_API CX_API_INLINE struct cx_vec2 cx_vec2_addf(const struct cx_vec2 *u, const CX_FLOAT fT);                       /* Returns the addition of a vec2 with a scalar eg. cx_vec2 u = <9.0f, 10.0f>, fT = 10, -> <19.0f, 20.0f> */
CX_API CX_API_INLINE struct cx_vec2 cx_vec2_subtract(const struct cx_vec2 *u, const struct cx_vec2 *v);             /* Returns the subtraction of two vec2 */
CX_API CX_API_INLINE struct cx_vec2 cx_vec2_subtractf(const struct cx_vec2 *u, const CX_FLOAT fT);                  /* Returns the addition of a vec2 with a scalar eg. cx_vec2 u = <9.0f, 10.0f>, fT = 10, -> <19.0f, 20.0f> */
CX_API CX_API_INLINE struct cx_vec2 cx_vec2_scalar_multiplyf(const struct cx_vec2 *u, const CX_FLOAT fT);           /* Returns the scalar multiplication of a vec2. eg: u = <1.0f, 3.0f> and f = 3.0f => <3.0f, 9.0f> */
CX_API CX_API_INLINE struct cx_vec2 cx_vec2_dividef(const struct cx_vec2 *u, const CX_FLOAT fT);

CX_API CX_API_INLINE CX_FLOAT cx_vec2_dot_product(const struct cx_vec2 *u, const struct cx_vec2 *v);                /* Returns the dot product b/w two vec2 */
CX_API CX_API_INLINE CX_FLOAT cx_vec2_cross_product(const struct cx_vec2 *u, const struct cx_vec2 *v);              /* Returns the cross product b/w two vec2 */

CX_API CX_API_INLINE struct cx_vec2 cx_vec2_normalize(const struct cx_vec2 *u);                                     /* Returns the norm of a vec2 */
CX_API CX_API_INLINE CX_FLOAT cx_vec2_magnitude(const struct cx_vec2 *u);                                           /* Returns the magnitude of a vec2 */

CX_API CX_API_INLINE void cx_vec2_print(const struct cx_vec2 *u);                                                   /* Print vec2 */

static const struct cx_vec2 _cx_vec2_zero             = { { { 0.0f, 0.0f  } } };
static const struct cx_vec2 _cx_vec2_unit_x           = { { { 1.0f, 0.0f  } } };
static const struct cx_vec2 _cx_vec2_unit_y           = { { { 0.0f, 1.0f  } } };
static const struct cx_vec2 _cx_vec2_unit_x_negative  = { { { -1.0f, 0.0f } } };
static const struct cx_vec2 _cx_vec2_unit_y_negative  = { { { 0.0f, -1.0f } } };
static const struct cx_vec2 _cx_vec2_one              = { { { 1.0f, 1.0f  } } };

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

CX_API CX_API_INLINE struct cx_vec2 *cx_vec2_set(struct cx_vec2 *u, CX_FLOAT x, CX_FLOAT y)
{
  u->x = x;
  u->y = y;
  return u;
}

CX_API CX_API_INLINE struct cx_vec2 *cx_vec2_set_random(struct cx_vec2 *u)
{
  u->x = CX_RANDOM_FLOAT;
  u->y = CX_RANDOM_FLOAT;
  return u;
}

CX_API CX_API_INLINE struct cx_vec2 *cx_vec2_set_zero(struct cx_vec2 *u)
{
  return cx_vec2_set(u, 0.0f, 0.0f);
}
CX_API CX_API_INLINE struct cx_vec2 *cx_vec2_negate(struct cx_vec2 *u)
{
  return cx_vec2_set(u, -u->x, -u->y);
}
CX_API CX_API_INLINE struct cx_vec2 cx_vec2_add(const struct cx_vec2 *u, const struct cx_vec2 *v)
{
  return (struct cx_vec2) {   .x = u->x + v->x,
                              .y = u->y + v->y
  };
}

CX_API CX_API_INLINE struct cx_vec2 cx_vec2_addf(const struct cx_vec2 *u, const CX_FLOAT fT)
{
  return (struct cx_vec2) {   .x = u->x + fT,
                              .y = u->y + fT
  };
}

CX_API CX_API_INLINE struct cx_vec2 cx_vec2_subtract(const struct cx_vec2 *u, const struct cx_vec2 *v)
{
  return (struct cx_vec2) {   .x = u->x - v->x,
                              .y = u->y - v->y
  };
}

CX_API CX_API_INLINE struct cx_vec2 cx_vec2_subtractf(const struct cx_vec2 *u, const CX_FLOAT fT)
{
  return (struct cx_vec2) {   .x = u->x - fT,
                              .y = u->y - fT
  };
}

CX_API CX_API_INLINE struct cx_vec2 cx_vec2_scalar_multiplyf(const struct cx_vec2 *u, const CX_FLOAT fT)
{
  return (struct cx_vec2) {   .x = fT * u->x,
                              .y = fT * u->y
  };
}

CX_API CX_API_INLINE struct cx_vec2 cx_vec2_dividef(const struct cx_vec2 *u, const CX_FLOAT fT)
{
	CX_ASSERT(CX_FLOAT_EQUALS(fT, 0) == 0 && "Assert: given fT is equals to '0'");
	return (struct cx_vec2) {		.x = u->x / fT,
															.y = u->y / fT
	};
}

CX_API CX_API_INLINE CX_FLOAT cx_vec2_dot_product(const struct cx_vec2 *u, const struct cx_vec2 *v)
{
  return (u->x * v->x + u->y * v->y);
}

CX_API CX_API_INLINE CX_FLOAT cx_vec2_cross_product(const struct cx_vec2 *u, const struct cx_vec2 *v)
{
  return (u->x * v->y - u->y * v->x);
}

CX_API CX_API_INLINE struct cx_vec2 cx_vec2_normalize(const struct cx_vec2 *u)
{
  CX_FLOAT mag = cx_vec2_magnitude(u);
  CX_FLOAT mag_inv = (mag > 0) ? 1 / mag : 0.0f;
  return (struct cx_vec2) {   .x = u->x * mag_inv,
                              .y = u->y * mag_inv
  };
}

CX_API CX_API_INLINE CX_FLOAT cx_vec2_magnitude(const struct cx_vec2 *u)
{
  return (CX_SQRT(CX_SQ(u->x) + CX_SQ(u->y)));
}

CX_API CX_API_INLINE void cx_vec2_print(const struct cx_vec2 *u)
{
  CX_PRINTLN("vec2: (x: %.2f,y: %.2f)", u->x, u->y);
}


/* ------------------------------------------------------------------------------------------------------------ */
/* cx_vec3 functions ------------------------------------------------------------------------------------------ */
struct cx_vec3 {
  union {
    CX_FLOAT vec[3];
    struct {
      CX_FLOAT x, y, z;
    };
  };
};

CX_API CX_API_INLINE struct cx_vec3 *cx_vec3_set_zero(struct cx_vec3 *u);                                           /* Returns zero vec3 */
CX_API CX_API_INLINE struct cx_vec3 *cx_vec3_set(struct cx_vec3 *u, CX_FLOAT x, CX_FLOAT y, CX_FLOAT z);            /* Set a vec3 with x, y */
CX_API CX_API_INLINE struct cx_vec3 *cx_vec3_set_random(struct cx_vec3 *u);                                         /* Set vec3 with random vaules */
CX_API CX_API_INLINE struct cx_vec3 *cx_vec3_negate(struct cx_vec3 *u);                                             /* Returns the negation of a vec3 */
CX_API CX_API_INLINE struct cx_vec3 cx_vec3_add(const struct cx_vec3 *u, const struct cx_vec3 *v);                  /* Returns the addition of two vec3 */
CX_API CX_API_INLINE struct cx_vec3 cx_vec3_addf(const struct cx_vec3 *u, const CX_FLOAT fT);                       /* Returns the addition of a vec3 with a scalar eg. cx_vec3 u = <9.0f, 10.0f, 0.5f>, fT = 10, -> <19.0f, 20.0f, 10.5f> */
CX_API CX_API_INLINE struct cx_vec3 cx_vec3_subtract(const struct cx_vec3 *u, const struct cx_vec3 *v);             /* Returns the subtraction of two vec3 */
CX_API CX_API_INLINE struct cx_vec3 cx_vec3_subtractf(const struct cx_vec3 *u, const CX_FLOAT fT);                  /* Returns the subtraction of a vec3 with a scalar eg. cx_vec3 u = <9.0f, 10.0f, 0.5f>, fT = 10, -> <19.0f, 20.0f, 10.5f> */
CX_API CX_API_INLINE struct cx_vec3 cx_vec3_scalar_multiplyf(const struct cx_vec3 *u, const CX_FLOAT fT);           /* Returns the scalar multiplication of a vec3. eg: u = <1.0f, 3.0f, 0.5f> and f = 3.0f => <3.0f, 9.0f, 1.5f> */
CX_API CX_API_INLINE struct cx_vec3 cx_vec3_dividef(const struct cx_vec3 *u, const CX_FLOAT fT);

CX_API CX_API_INLINE CX_FLOAT cx_vec3_dot_product(const struct cx_vec3 *u, const struct cx_vec3 *v);                /* Returns the dot product b/w two vec3 */
CX_API CX_API_INLINE struct cx_vec3 cx_vec3_cross_product(const struct cx_vec3 *u, const struct cx_vec3 *v);        /* Returns the cross product b/w two vec3 */

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_normalize(const struct cx_vec3 *u);                                     /* Returns the norm of a vec3 */
CX_API CX_API_INLINE CX_FLOAT cx_vec3_magnitude(const struct cx_vec3 *u);                                           /* Returns the magnitude of a vec3 */

CX_API CX_API_INLINE void cx_vec3_print(const struct cx_vec3 *u);                                                   /* Print vec3 */

static const struct cx_vec3 _cx_vec3_zero             = { { { 0.0f, 0.0f, 0.0f  } } };
static const struct cx_vec3 _cx_vec3_unit_x           = { { { 1.0f, 0.0f, 0.0f  } } };
static const struct cx_vec3 _cx_vec3_unit_y           = { { { 0.0f, 1.0f, 0.0f  } } };
static const struct cx_vec3 _cx_vec3_unit_z           = { { { 0.0f, 0.0f, 1.0f  } } };
static const struct cx_vec3 _cx_vec3_unit_x_negative  = { { { -1.0f, 0.0f, 0.0f } } };
static const struct cx_vec3 _cx_vec3_unit_y_negative  = { { { 0.0f, -1.0f, 0.0f } } };
static const struct cx_vec3 _cx_vec3_unit_z_negative  = { { { 0.0f, 0.0f, -1.0f } } };
static const struct cx_vec3 _cx_vec3_one              = { { { 1.0f, 1.0f, 1.0f  } } };

CX_API const struct cx_vec3 *cx_get_reference_vec3(int id)
{
  switch(id) {
    case CX_REF_VEC3_ZERO:                return &_cx_vec3_zero;
    case CX_REF_VEC3_ONE:                 return &_cx_vec3_one;
    case CX_REF_VEC3_UNIT_X:              return &_cx_vec3_unit_x;
    case CX_REF_VEC3_UNIT_Y:              return &_cx_vec3_unit_y;
    case CX_REF_VEC3_UNIT_Z:              return &_cx_vec3_unit_z;
    case CX_REF_VEC3_UNIT_X_NEGATIVE:     return &_cx_vec3_unit_x_negative;
    case CX_REF_VEC3_UNIT_Y_NEGATIVE:     return &_cx_vec3_unit_y_negative;
    case CX_REF_VEC3_UNIT_Z_NEGATIVE:     return &_cx_vec3_unit_z_negative;
    default:
                                          return &_cx_vec3_zero;
  }
}

CX_API CX_API_INLINE struct cx_vec3 *cx_vec3_set_zero(struct cx_vec3 *u)
{
  u->x = 0;
  u->y = 0;
  u->z = 0;
  return u;
}

CX_API CX_API_INLINE struct cx_vec3 *cx_vec3_set(struct cx_vec3 *u, CX_FLOAT x, CX_FLOAT y, CX_FLOAT z)
{
  u->x = x;
  u->y = y;
  u->z = z;
  return u;
}

CX_API CX_API_INLINE struct cx_vec3 *cx_vec3_set_random(struct cx_vec3 *u)
{
  u->x = CX_RANDOM_FLOAT;
  u->y = CX_RANDOM_FLOAT;
  u->z = CX_RANDOM_FLOAT;
  return u;
}

CX_API CX_API_INLINE struct cx_vec3 *cx_vec3_negate(struct cx_vec3 *u)
{
  u->x = -u->x;
  u->y = -u->y;
  u->z = -u->z;
  return u;
}

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_add(const struct cx_vec3 *u, const struct cx_vec3 *v)
{
  return (struct cx_vec3) {   .x = u->x + v->x,
                              .y = u->y + v->y,
                              .z = u->z + v->z
  };
}

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_addf(const struct cx_vec3 *u, const CX_FLOAT fT)
{
  return (struct cx_vec3) {   .x = u->x + fT,
                              .y = u->y + fT,
                              .z = u->z + fT
  };
}

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_subtract(const struct cx_vec3 *u, const struct cx_vec3 *v)
{
  return (struct cx_vec3) {   .x = u->x - v->x,
                              .y = u->y - v->y,
                              .z = u->z - v->z
  };
}

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_subtractf(const struct cx_vec3 *u, const CX_FLOAT fT)
{
  return (struct cx_vec3) {   .x = u->x - fT,
                              .y = u->y - fT,
                              .z = u->z - fT
  };
}

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_scalar_multiplyf(const struct cx_vec3 *u, const CX_FLOAT fT)
{
  return (struct cx_vec3) {   .x = fT * u->x,
                              .y = fT * u->y,
                              .z = fT * u->z
  };
}

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_dividef(const struct cx_vec3 *u, const CX_FLOAT fT)
{
	CX_ASSERT(CX_FLOAT_EQUALS(fT, 0) == 0 && "Assert: given fT is equals to '0'");
	return (struct cx_vec3) {		.x = u->x / fT,
															.y = u->y / fT,
															.z = u->z / fT
	};
}

CX_API CX_API_INLINE CX_FLOAT cx_vec3_dot_product(const struct cx_vec3 *u, const struct cx_vec3 *v)
{
  return (u->x * v->x + u->y * v->y + u->z * v->z);
}

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_cross_product(const struct cx_vec3 *u, const struct cx_vec3 *v)
{
  return (struct cx_vec3) {   .x = u->y * v->z - u->z * v->y,
                              .y = u->z * v->x - u->x * v->z,
                              .z = u->x * v->y - u->y * v->x
  };
}

CX_API CX_API_INLINE struct cx_vec3 cx_vec3_normalize(const struct cx_vec3 *u)
{
  CX_FLOAT mag = cx_vec3_magnitude(u);
  CX_FLOAT mag_inv = (mag > 0) ? 1 / mag : 0.0f;
  return (struct cx_vec3) {   .x = mag_inv * u->x,
                              .y = mag_inv * u->y,
                              .z = mag_inv * u->z
  };
}

CX_API CX_API_INLINE CX_FLOAT cx_vec3_magnitude(const struct cx_vec3 *u)
{
  return CX_SQRT(CX_SQ(u->x) + CX_SQ(u->y) + CX_SQ(u->z));
}

CX_API CX_API_INLINE void cx_vec3_print(const struct cx_vec3 *u)
{
  CX_PRINTLN("vec3: (x: %.2f, y: %.2f, z: %.2f)", u->x, u->y, u->z);
}

/* ------------------------------------------------------------------------------------------------------------ */
/* cx_vec4 functions ------------------------------------------------------------------------------------------ */
struct cx_vec4 {
  union {
    CX_FLOAT vec[4];
    struct {
      CX_FLOAT x, y, z, w;
    };
  };
};

CX_API CX_API_INLINE struct cx_vec4 *cx_vec4_set_zero(struct cx_vec4 *u);
CX_API CX_API_INLINE struct cx_vec4 *cx_vec4_set(struct cx_vec4 *u, CX_FLOAT x, CX_FLOAT y, CX_FLOAT z, CX_FLOAT w);
CX_API CX_API_INLINE struct cx_vec4 *cx_vec4_set_random(struct cx_vec4 *u);
CX_API CX_API_INLINE struct cx_vec4 *cx_vec4_negate(struct cx_vec4 *u);
CX_API CX_API_INLINE struct cx_vec4 cx_vec4_add(const struct cx_vec4 *u, const struct cx_vec4 *v);
CX_API CX_API_INLINE struct cx_vec4 cx_vec4_addf(const struct cx_vec4 *u, CX_FLOAT fT);
CX_API CX_API_INLINE struct cx_vec4 cx_vec4_subtract(const struct cx_vec4 *u, const struct cx_vec4 *v);
CX_API CX_API_INLINE struct cx_vec4 cx_vec4_subtractf(const struct cx_vec4 *u, CX_FLOAT fT);
CX_API CX_API_INLINE struct cx_vec4 cx_vec4_scalar_multiplyf(const struct cx_vec4 *u, CX_FLOAT fT);
CX_API CX_API_INLINE struct cx_vec4 cx_vec4_dividef(const struct cx_vec4 *u, const CX_FLOAT fT);

CX_API CX_API_INLINE CX_FLOAT cx_vec4_dot_product(const struct cx_vec4 *u, const struct cx_vec4 *v);
CX_API CX_API_INLINE struct cx_vec4 cx_vec4_cross_product(const struct cx_vec4 *u, const struct cx_vec4 *v);

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_normalize(const struct cx_vec4 *u);
CX_API CX_API_INLINE CX_FLOAT cx_vec4_magnitude(const struct cx_vec4 *u);

CX_API CX_API_INLINE void cx_vec4_print(const struct cx_vec4 *u);


static const struct cx_vec4 _cx_vec4_zero             = { { { 0.0f, 0.0f, 0.0f, 0.0f  } } };
static const struct cx_vec4 _cx_vec4_unit_x           = { { { 1.0f, 0.0f, 0.0f, 0.0f  } } };
static const struct cx_vec4 _cx_vec4_unit_y           = { { { 0.0f, 1.0f, 0.0f, 0.0f  } } };
static const struct cx_vec4 _cx_vec4_unit_z           = { { { 0.0f, 0.0f, 1.0f, 0.0f  } } };
static const struct cx_vec4 _cx_vec4_unit_w           = { { { 0.0f, 0.0f, 0.0f, 1.0f  } } };
static const struct cx_vec4 _cx_vec4_unit_x_negative  = { { { -1.0f, 0.0f, 0.0f, 0.0f } } };
static const struct cx_vec4 _cx_vec4_unit_y_negative  = { { { 0.0f, -1.0f, 0.0f, 0.0f } } };
static const struct cx_vec4 _cx_vec4_unit_z_negative  = { { { 0.0f, 0.0f, -1.0f, 0.0f } } };
static const struct cx_vec4 _cx_vec4_unit_w_negative  = { { { 0.0f, 0.0f, 0.0f, -1.0f } } };
static const struct cx_vec4 _cx_vec4_one              = { { { 1.0f, 1.0f, 1.0f, 1.0f  } } };

CX_API const struct cx_vec4 *cx_get_reference_vec4(int id)
{
  switch(id) {
    case CX_REF_VEC4_ZERO:                return &_cx_vec4_zero;
    case CX_REF_VEC4_ONE:                 return &_cx_vec4_one;
    case CX_REF_VEC4_UNIT_X:              return &_cx_vec4_unit_x;
    case CX_REF_VEC4_UNIT_Y:              return &_cx_vec4_unit_y;
    case CX_REF_VEC4_UNIT_Z:              return &_cx_vec4_unit_z;
    case CX_REF_VEC4_UNIT_W:              return &_cx_vec4_unit_w;
    case CX_REF_VEC4_UNIT_X_NEGATIVE:     return &_cx_vec4_unit_x_negative;
    case CX_REF_VEC4_UNIT_Y_NEGATIVE:     return &_cx_vec4_unit_y_negative;
    case CX_REF_VEC4_UNIT_Z_NEGATIVE:     return &_cx_vec4_unit_z_negative;
    case CX_REF_VEC4_UNIT_W_NEGATIVE:     return &_cx_vec4_unit_w_negative;
    default:
                                          return &_cx_vec4_zero;
  }
}

CX_API CX_API_INLINE struct cx_vec4 *cx_vec4_set_zero(struct cx_vec4 *u)
{
  for (int i = 0; i < 4; i++) {
    u->vec[i] = 0;
  }
  return u;
}

CX_API CX_API_INLINE struct cx_vec4 *cx_vec4_set(struct cx_vec4 *u, CX_FLOAT x, CX_FLOAT y, CX_FLOAT z, CX_FLOAT w)
{
  u->x = x;
  u->y = y;
  u->z = z;
  u->w = w;

  return u;
}

CX_API CX_API_INLINE struct cx_vec4 *cx_vec4_set_random(struct cx_vec4 *u)
{
  for (int i = 0; i < 4; i++) {
    u->vec[i] = CX_RANDOM_FLOAT;
  }

  return u;
}

CX_API CX_API_INLINE struct cx_vec4 *cx_vec4_negate(struct cx_vec4 *u)
{
  for (int i = 0; i < 4; i++) {
    u->vec[i] = -u->vec[i];
  }

  return u;
}

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_add(const struct cx_vec4 *u, const struct cx_vec4 *v)
{
	return (struct cx_vec4) {		.x = u->x + v->x,
															.y = u->y + v->y,
															.z = u->z + v->z,
															.w = u->w + v->w
	};
}

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_addf(const struct cx_vec4 *u, CX_FLOAT fT)
{
	return (struct cx_vec4) {		.x = u->x + fT,
															.y = u->y + fT,
															.z = u->z + fT,
															.w = u->w + fT
	};
}

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_subtract(const struct cx_vec4 *u, const struct cx_vec4 *v)
{
	return (struct cx_vec4) {		.x = u->x - v->x,
															.y = u->y - v->y,
															.z = u->z - v->z,
															.w = u->w - v->w
	};
}

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_subtractf(const struct cx_vec4 *u, CX_FLOAT fT)
{
	return (struct cx_vec4) {		.x = u->x - fT,
															.y = u->y - fT,
															.z = u->z - fT,
															.w = u->w - fT
	};
}

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_scalar_multiplyf(const struct cx_vec4 *u, CX_FLOAT fT)
{
	return (struct cx_vec4) {		.x = u->x * fT,
															.y = u->y * fT,
															.z = u->z * fT,
															.w = u->w * fT
	};
}

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_dividef(const struct cx_vec4 *u, const CX_FLOAT fT)
{
	CX_ASSERT(CX_FLOAT_EQUALS(fT, 0) == 0 && "Assert: given fT is equals to '0'");
	return (struct cx_vec4) {		.x = u->x / fT,
															.y = u->y / fT,
															.z = u->z / fT,
															.w = u->w / fT
	};
}

CX_API CX_API_INLINE CX_FLOAT cx_vec4_dot_product(const struct cx_vec4 *u, const struct cx_vec4 *v)
{
	return u->x * v->x + u->y * v->y + u->z * v->z + u->w * v->w;
}

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_cross_product(const struct cx_vec4 *u, const struct cx_vec4 *v)
{
	return (struct cx_vec4) {		.x = (u->y * v->z) - (u->z * v->y),
															.y = (u->z * v->x) - (u->x * v->z),
															.z = (u->x * v->y) - (u->y * v->x),
															.w = 0.0
	};
}

CX_API CX_API_INLINE struct cx_vec4 cx_vec4_normalize(const struct cx_vec4 *u)
{
  CX_FLOAT mag = cx_vec4_magnitude(u);
  CX_FLOAT mag_inv = (mag > 0) ? 1 / mag : 0.0f;

  return (struct cx_vec4) {   .x = u->x * mag_inv,
                              .y = u->y * mag_inv,
                              .z = u->z * mag_inv,
                              .w = u->w * mag_inv,
  };
}

CX_API CX_API_INLINE CX_FLOAT cx_vec4_magnitude(const struct cx_vec4 *u)
{
  return CX_SQRT(CX_SQ(u->x) + CX_SQ(u->y) + CX_SQ(u->z) + CX_SQ(u->w));
}

CX_API CX_API_INLINE void cx_vec4_print(const struct cx_vec4 *u)
{
  CX_PRINTLN("vec4: (x: %f, y: %f, z: %f, w: %f)", u->x, u->y, u->z, u->w);
}

/* ------------------------------------------------------------------------------------------------------------ */
/* dft and fft ------------------------------------------------------------------------------------------------ */
/* DFT implementation                                                                                           */
/* eg. say we have a set of signals x[t] then                                                                   */
/* DFT and FFT transforms that signal from time domain x[n] to frequency domain X[k]                            */
/* X[k] = \sum_{k = 0}^{N - 1} x[k] * \exp{\frac{-2πni}{N}}                                                     */
/* Here: N    = total numbers of samples                                                                        */
/*       x[n] = input signal in time domain                                                                     */
/*       X[k] = output signal in frequency domain                                                               */

CX_API void cx_dft(CX_COMPLEX in[], CX_COMPLEX out[], int N)
{
  for (int k = 0; k < N; k++) {
    CX_COMPLEX sum = 0.0f;
    for(int n = 0;n < N; n++) {
      float angle = CX_TAU * k * n / N;
      sum += in[n] * CX_CEXP(-1.0f * I * angle);
    }
    out[k] = sum;
    if (CX_CABS(out[k]) < CX_EPSILON) {
      out[k] = 0.0;
    }
  }
}

/* DFT inverse implementation --------------------------------------------------------------------------------- */
CX_API void cx_dft_inverse(CX_COMPLEX in[], CX_COMPLEX out[], int N)
{
  for (int k = 0; k < N; k++) {
    CX_FLOAT N_inv = 1.0 / N;
    CX_COMPLEX sum = 0.0f;
    for (int n = 0;n < N; n++) {
      float angle = CX_TAU * k * n / N;
      sum += in[n] * CX_CEXP(1.0f * I * angle);
    }
    out[k] = N_inv * sum;
    if (CX_CABS(out[k]) < CX_EPSILON) {
      out[k] = 0.0;
    }
  }
}


/* FFT implementation ------------------------------------------------------------------------------------------- */
#define cx_fft	cx_fft_bit

/* source: https://cp-algorithms.com/algebra/fft.html                                                             */
CX_API void cx_fft_rec(CX_COMPLEX in[], CX_COMPLEX out[], int N)
{
  CX_ASSERT((N & (N-1)) == 0 && "This fft(Cooley-Tukey FFT) only works for power of two");
  if (N == 1) {
    out[0] = in[0];
    return;
  }

  CX_COMPLEX in_a0[N/2];
  CX_COMPLEX in_a1[N/2];

  CX_COMPLEX out_a0[N/2];
  CX_COMPLEX out_a1[N/2];

  for (int k = 0; k < N / 2; k++) {
    in_a0[k] = in[2 * k];
    in_a1[k] = in[2 * k + 1];
  }

  cx_fft_rec(in_a0, out_a0, N/2);
  cx_fft_rec(in_a1, out_a1, N/2);

  CX_FLOAT angle = -2.0 * CX_PI / N;
  CX_COMPLEX w = 1.0 + I * 0.0;
  // CX_COMPLEX wn = cos(angle) + I * sin(angle);
  CX_COMPLEX wn = CX_CEXP(I * angle);

  for (int n = 0; n < N / 2; n++) {
    out[n] = out_a0[n] + w * out_a1[n];
    out[n + N/2] = out_a0[n] - w * out_a1[n];
    w *= wn;
  }
}

/* Iterative Cooley–Tukey FFT with Bit-Reversal: https://cp-algorithms.com/algebra/fft.html*/
CX_API void cx_fft_bit(CX_COMPLEX in[], CX_COMPLEX out[], int N)
{
  CX_ASSERT((N & (N-1)) == 0 && "This fft(Cooley-Tukey FFT) only works for power of two");
	for (int i = 0; i < N; i++) {
		out[i] = in[i];
	}
	for (int i = 1, j = 0; i < N; i++) {
		int bit = N >> 1;
		for (; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;
		if (i < j) {
			CX_COMPLEX temp = out[i];
			out[i] = out[j];
			out[j] = temp;
		}
	}

	for (int len = 2; len <= N; len <<= 1) {
		CX_FLOAT angle = -2.0f * CX_PI / len;
		/* CX_COMPLEX wlen = cexpf(angle * I); */
		CX_COMPLEX wlen = cosf(angle) + sinf(angle) * I;
		for (int i = 0; i < N; i += len) {
			CX_COMPLEX w = 1.0f + 0.0f * I;
			for (int j = 0; j < len / 2; j++) {
				CX_COMPLEX u = out[i + j], v = out[i + j + len/2] * w;
				out[i + j] = u + v;
				out[i + j + len/2] = u - v;
				w = w * wlen;
			}
		}
	}
}

/* ------------------------------------------------------------------------------------------------------------ */
/* Numerical ODE solver --------------------------------------------------------------------------------------- */
/* implicit euler  */
CX_API CX_FLOAT cx_explicit_euler(CX_FLOAT (* f)(CX_FLOAT, CX_FLOAT), CX_FLOAT x, CX_FLOAT y, CX_FLOAT h)
{
  CX_FLOAT fxy = f(x, y);
  return (y + h * fxy);
}

/* runge-kutta 2th order -------------------------------------------------------------------------------------- */
CX_API CX_FLOAT cx_rk2(CX_FLOAT (* f)(CX_FLOAT, CX_FLOAT), CX_FLOAT x, CX_FLOAT y, CX_FLOAT h)
{
  CX_FLOAT y1 = f(x, y);
  CX_FLOAT y_star = y + h * y1;
  CX_FLOAT y2 = f(x + h, y_star);

  return y + (0.5 * h * (y1 + y2));
}

/* runge-kutta 4th order -------------------------------------------------------------------------------------- */
CX_API CX_FLOAT cx_rk4(CX_FLOAT (* f)(CX_FLOAT, CX_FLOAT), CX_FLOAT x, CX_FLOAT y, CX_FLOAT h)
{
  CX_FLOAT k1 = f(x, y);
  CX_FLOAT k2 = f(x + h/2, y + ((h/2) * k1));
  CX_FLOAT k3 = f(x + h/2, y + ((h/2) * k2));
  CX_FLOAT k4 = f(x + h, y + h * k3);

  return y + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
}

#endif /* CX_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CAYLIX_H */
