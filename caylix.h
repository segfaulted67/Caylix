/**
 * @file caylix.h
 * @version 1.0.1
 * @date 2026-02-09
 * @author segfaulted67
 */

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
#include <stdbool.h>
#include <assert.h>

#include <time.h>


#define CX_VERSION  "1.0.1"

/** Suppress "unused variable" warning */
/** Example:                           */
/** void something(int a) {            */
/** ...                                */
/** CX_UNUSED_VAR(a);                  */
/** }                                  */
#define CX_UNUSED_VAR(x)  ((void)(x))

/** typecast float/double as cx_float */
#ifndef cx_float
#   ifdef CX_DOUBLE_PRECISION_FLOAT
#     define cx_float double
#   else
#     define cx_float float
#   endif
#endif

/** typecast cx_float complex as cx_complex */
#ifndef cx_complex
#   include <complex.h>
/** https://learn.microsoft.com/en-us/cpp/c-runtime-library/complex-math-support?view=msvc-170 */
#   ifdef _MSC_VER
#     ifdef CX_DOUBLE_PRECISION_FLOAT
#       define cx_complex _Dcomplex
#     else
#       define cx_complex _Fcomplex
#     endif
#   else
#     define cx_complex _Complex cx_float
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
#   ifdef CX_DOUBLE_PRECISION_FLOAT
#     define CX_EPSILON 1E-7
#   else
#     define CX_EPSILON 1E-7f
#   endif
#endif

/* PI to 100 digits */
#ifndef CX_PI
#   ifdef CX_DOUBLE_PRECISION_FLOAT
#     define CX_PI  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#   else
#     define CX_PI  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f
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
#   ifdef CX_DOUBLE_PRECISION_FLOAT
#     define CX_E   2.71828182845904523536028747135266249775724709369995
#   else
#     define CX_E   2.71828182845904523536028747135266249775724709369995f
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

#define CX_DYNAMIC_ARRAY(type)					\
	struct {									\
		type *buffer;							\
		size_t size;							\
		size_t capacity;						\
	}

#define CX_DYNAMIC_ARRAY_INIT(arr)											\
	do {																	\
		(arr).size = 0, (arr).capacity = CX_DA_INIT_CAP;					\
		(arr).buffer = CX_MALLOC((arr).capacity * sizeof *((arr).buffer));	\
	} while (0)

#define CX_DYNAMIC_ARRAY_FREE(arr)											\
	do {																	\
		CX_FREE(((arr).buffer));											\
		((arr).buffer) = NULL;												\
		((arr).size) = 0;													\
		((arr).capacity) = 0;												\
	} while (0)

#define CX_DYNAMIC_ARRAY_GET_SIZE(arr)										\
	((arr).size)

#define CX_DYNAMIC_ARRAY_GET_CAPACITY(arr)									\
	((arr).capacity)

#define CX_DYNAMIC_ARRAY_GET_VALUE(arr, i)									\
	((arr).buffer[i])

#define CX_DYNAMIC_ARRAY_SET_CAP(arr, new_capacity)							\
	do {																	\
		if ((arr).buffer == NULL) {											\
			CX_DYNAMIC_ARRAY_INIT((arr));									\
	    }																	\
																			\
		void *new_buffer = CX_REALLOC((arr).buffer, (new_capacity) * sizeof *((arr).buffer));	\
		if (new_buffer != NULL) {																\
			(arr).buffer = new_buffer;															\
			if ((arr).size > new_capacity) {													\
				(arr).size = new_capacity;														\
			}																					\
			(arr).capacity = new_capacity;														\
		}																						\
	} while (0)

#define CX_DYNAMIC_ARRAY_PUSH(arr, new_value)													\
	do {																						\
		if ((arr).size >= (arr).capacity) {														\
			CX_DYNAMIC_ARRAY_SET_CAP((arr), (arr).capacity * 2);								\
		}																						\
		(arr).buffer[(arr).size] = (new_value);													\
		(arr).size++;																			\
	} while (0)

#define CX_DYNAMIC_ARRAY_POP(arr)																\
	do {																						\
		if ((arr).size > 0)  																	\
			(arr).size--;																		\
	} while (0)

#ifdef CX_DOUBLE_PRECISION_FLOAT
/* A macro for complex absolute values */
#	define CX_CABS(x)  cabs(x)
/* A macro for complex exponentials */
#	define CX_CEXP(x)  cexp(x)
/* A macro for square root*/
#	define CX_SQRT(x)  (sqrt(x))
/* A macro for sin */
#	define CX_SIN(x)  (sin(x))
/* A macro for cos */
#	define CX_COS(x)  (cos(x))
/* A macro for tan */
#	define CX_TAN(x)  (tan(x))
/* A macro for sin inverse or asin */
#define CX_ASIN(x)  (asin(x))
/* A macro for cos inverse or acos */
#define CX_ACOS(x)  (acos(x))
/* A macro for tan inverse or atan */
#define CX_ATAN(x)  (atan(x))
#else
/* A macro for complex absolute values */
#	define CX_CABS(x)  cabsf(x)
/* A macro for complex exponentials */
#	define CX_CEXP(x)  cexpf(x)
/* A macro for square root*/
#	define CX_SQRT(x)  (sqrtf(x))
/* A macro for sin */
#	define CX_SIN(x)  (sinf(x))
/* A macro for cos */
#	define CX_COS(x)  (cosf(x))
/* A macro for tan */
#	define CX_TAN(x)  (tanf(x))
/* A macro for sin inverse or asin */
#define CX_ASIN(x)  (asinf(x))
/* A macro for cos inverse or acos */
#define CX_ACOS(x)  (acosf(x))
/* A macro for tan inverse or atan */
#define CX_ATAN(x)  (atanf(x))
#endif

/* A macro for cot */
#define CX_COT(x)  (1.0 / CX_TAN(x))
/* A macro for sec */
#define CX_SEC(x)  (1.0 / CX_COS(x))
/* A macro for cosec */
#define CX_CSC(x)  (1.0 / CX_SIN(x))
/* A macro for absolute value. eg: CX_ABS(69.0) --> 69.0 , CX_ABS(-69.0) -> 69.0 */
#define CX_ABS(x)   (((x) < 0) ? (-(x)) : (x))


/* Safely divides x by y; returns INFINITY if y == 0 */
/* Example: CX_SAFE_DIVIDE(5.0, 0.0); --> 0.0		 */
/*          CX_SAFE_DIVIDE(5.0, 5.0); --> 1.0        */
#define CX_SAFE_DIVIDE(x, y)  ((CX_ABS((y)) <= CX_EPSILON) ? 0.0 : (x) / (y))

#define CX_FLOAT_EQUALS(x, y)	((CX_ABS(x-y) <= CX_EPSILON) ? 1 : 0)

/* typecast inline for different compilers */
#ifndef CX_API_INLINE
#	ifdef _MSC_VER
#		define CX_API_INLINE __forceinline
#	elif defined(__GNUC__)
#		if defined(__STRICT_ANSI__)
#			define CX_API_INLINE __inline __attribute__((always_inline))
#		else
#			define CX_API_INLINE inline __attribute__((always_inline))
#		endif
#	else
#		define CX_API_INLINE inline
#	endif
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
#define CX_RANDOM_FLOAT   (((cx_float)rand() - (cx_float)rand()) / (cx_float)RAND_MAX)
/* CX_SRAND: Set seed for random numbers */
#define CX_SRAND()      (srand(time(NULL)))


/* Swaps the values of two cx_float variables */
/* Example:                                   */
/* cx_float a = 6, b = 7;                     */
/* cx_swap(&a, &b); --> a = 7, b = 6          */
static CX_API_INLINE void cx_swap(cx_float *x, cx_float *y)
{
	cx_float t = *x;
	*x = *y;
	*y = t;
}

/* lerp: a + t(b - a) */
static CX_API_INLINE cx_float cx_lerp(cx_float a, cx_float b, cx_float t)
{
	return a + t * (b - a);
}

/* clamp: given a max and min it will return min if value is smaller than min and return max if value if larger than max */
static CX_API_INLINE cx_float cx_clamp(cx_float value, cx_float min, cx_float max)
{
	if(min == max)  return min;
	if(value < min) return min;
	if(value > max) return max;

	return value;
}

#ifdef CX_IMPLEMENTATION

/* ------------------------------------------------------------------------------------------------------------ */
/* forward decleration ---------------------------------------------------------------------------------------- */
typedef struct cx_vec2 cx_vec2;
typedef struct cx_vec3 cx_vec3;
typedef struct cx_vec4 cx_vec4;
typedef struct cx_mat2 cx_mat2;
typedef struct cx_mat3 cx_mat3;
typedef struct cx_mat4 cx_mat4;
typedef struct cx_quat cx_quat;

#define CX_REF_VEC2_ZERO              0
#define CX_REF_VEC2_UNIT_X            1
#define CX_REF_VEC2_UNIT_Y            2
#define CX_REF_VEC2_UNIT_X_NEGATIVE   3
#define CX_REF_VEC2_UNIT_Y_NEGATIVE   4
#define CX_REF_VEC2_ONE               5

CX_API const cx_vec2 *cx_get_reference_vec2(int id);

#define CX_REF_VEC3_ZERO              0
#define CX_REF_VEC3_UNIT_X            1
#define CX_REF_VEC3_UNIT_Y            2
#define CX_REF_VEC3_UNIT_Z            3
#define CX_REF_VEC3_UNIT_X_NEGATIVE   4
#define CX_REF_VEC3_UNIT_Y_NEGATIVE   5
#define CX_REF_VEC3_UNIT_Z_NEGATIVE   6
#define CX_REF_VEC3_ONE               7

CX_API const cx_vec3 *cx_get_reference_vec3(int id);

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

CX_API const cx_vec4 *cx_get_reference_vec4(int id);

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
/* API list --------------------------------------------------------------------------------------------------- */
/* cx_vec2 ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_vec2 cx_vec2_set(cx_float x, cx_float y);                              /* Set vec2 with x, y */
CX_API CX_API_INLINE cx_vec2 cx_vec2_zero();                                                   /* Returns zero vec2 */
CX_API CX_API_INLINE cx_vec2 cx_vec2_random();                                                 /* Set vec2 with random values */
CX_API CX_API_INLINE cx_vec2 cx_vec2_negate(cx_vec2 u);                                        /* Returns the negation of a vec2 */
CX_API CX_API_INLINE cx_vec2 cx_vec2_add(const cx_vec2 u, const cx_vec2 v);                    /* Returns the addition of two vec2 */
CX_API CX_API_INLINE cx_vec2 cx_vec2_addf(const cx_vec2 u, const cx_float fT);                 /* Returns the addition of a vec2 with a scalar eg. cx_vec2 u = <9.0f, 10.0f>, fT = 10, -> <19.0f, 20.0f> */
CX_API CX_API_INLINE cx_vec2 cx_vec2_sub(const cx_vec2 u, const cx_vec2 v);                    /* Returns the subtraction of two vec2 */
CX_API CX_API_INLINE cx_vec2 cx_vec2_subf(const cx_vec2 u, const cx_float fT);                 /* Returns the addition of a vec2 with a scalar eg. cx_vec2 u = <9.0f, 10.0f>, fT = 10, -> <19.0f, 20.0f> */
CX_API CX_API_INLINE cx_vec2 cx_vec2_mulf(const cx_vec2 u, const cx_float fT);                 /* Returns the scalar multiplication of a vec2. eg: u = <1.0f, 3.0f> and f = 3.0f => <3.0f, 9.0f> */
CX_API CX_API_INLINE cx_vec2 cx_vec2_divf(const cx_vec2 u, const cx_float fT);                 /* Returns the scalar division of a vec2, eg: u = <10.0f, 50.0f> and f = 5.0f => <2.0f, 10.0f> */
CX_API CX_API_INLINE bool cx_vec2_equals(const cx_vec2 u, const cx_vec2 v);

CX_API CX_API_INLINE cx_float cx_vec2_dot(const cx_vec2 u, const cx_vec2 v);                   /* Returns the dot product b/w two vec2 */
CX_API CX_API_INLINE cx_float cx_vec2_cross(const cx_vec2 u, const cx_vec2 v);                 /* Returns the cross product b/w two vec2 */
CX_API CX_API_INLINE cx_vec2 cx_vec2_normalize(const cx_vec2 u);                               /* Returns the unit vector of a vec2 */
CX_API CX_API_INLINE cx_float cx_vec2_mag(const cx_vec2 u);                                    /* Returns the magnitude of a vec2 */

CX_API CX_API_INLINE cx_vec2 cx_vec2_rotate(const cx_vec2 u, cx_float angle);                  /* Returns the vector rotated with given angle */
CX_API CX_API_INLINE cx_float cx_vec2_angle(const cx_vec2 u, const cx_vec2 v);
CX_API CX_API_INLINE cx_vec2 cx_vec2_lerp(const cx_vec2 u, const cx_vec2 v, const cx_float t);
CX_API CX_API_INLINE cx_vec2 cx_vec2_proj(const cx_vec2 u, const cx_vec2 v);
CX_API CX_API_INLINE cx_vec2 cx_vec2_reflect(const cx_vec2 u, const cx_vec2 n);

CX_API CX_API_INLINE void cx_vec2_print(const cx_vec2 u);                                      /* Print vec2 */

/* cx_vec3 ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_vec3 cx_vec3_set(cx_float x, cx_float y, cx_float z);                  /* Set a vec3 with x, y, z */
CX_API CX_API_INLINE cx_vec3 cx_vec3_zero();                                                   /* Returns zero vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_random();                                                 /* Set vec3 with random vaules */

CX_API CX_API_INLINE cx_vec3 cx_vec3_negate(cx_vec3 u);                                        /* Returns the negation of a vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_add(const cx_vec3 u, const cx_vec3 v);                    /* Returns the addition of two vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_addf(const cx_vec3 u, const cx_float fT);                 /* Returns the addition of a vec3 with a scalar eg. cx_vec3 u = <9.0f, 10.0f, 0.5f>, fT = 10, -> <19.0f, 20.0f, 10.5f> */
CX_API CX_API_INLINE cx_vec3 cx_vec3_sub(const cx_vec3 u, const cx_vec3 v);                    /* Returns the subtraction of two vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_subf(const cx_vec3 u, const cx_float fT);                 /* Returns the subtraction of a vec3 with a scalar eg. cx_vec3 u = <9.0f, 10.0f, 0.5f>, fT = 10, -> <19.0f, 20.0f, 10.5f> */
CX_API CX_API_INLINE cx_vec3 cx_vec3_mulf(const cx_vec3 u, const cx_float fT);                 /* Returns the scalar multiplication of a vec3. eg: u = <1.0f, 3.0f, 0.5f> and f = 3.0f => <3.0f, 9.0f, 1.5f> */
CX_API CX_API_INLINE cx_vec3 cx_vec3_divf(const cx_vec3 u, const cx_float fT);                 /* Returns the scalar division of a vec3, eg: u = <0.0f, 10.0f, 50.0f> and f = 5.0f => <0.0f, 2.0f, 10.0f> */

CX_API CX_API_INLINE cx_float cx_vec3_dot(const cx_vec3 u, const cx_vec3 v);                   /* Returns the dot product/scalar product b/w two vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_cross(const cx_vec3 u, const cx_vec3 v);                  /* Returns the cross product/vector product b/w two vec3 */

CX_API CX_API_INLINE cx_vec3 cx_vec3_normalize(const cx_vec3 u);                               /* Returns the unit vector of a vec3 */
CX_API CX_API_INLINE cx_float cx_vec3_mag(const cx_vec3 u);                                    /* Returns the magnitude of a vec3 */
CX_API CX_API_INLINE cx_float cx_vec3_mag_sq(const cx_vec3 u);                                 /* Returns the square of the magnitude of a vec3 */
CX_API CX_API_INLINE cx_float cx_vec3_angle(const cx_vec3 u, const cx_vec3 v);

CX_API CX_API_INLINE void cx_vec3_print(const cx_vec3 u);                                      /* Print vec3 */

/* cx_vec4 ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_vec4 cx_vec4_set(cx_float x, cx_float y, cx_float z, cx_float w);      /* Set vec4 with x, y, z, w */
CX_API CX_API_INLINE cx_vec4 cx_vec4_zero();                                                   /* Set vec4 with 0 */
CX_API CX_API_INLINE cx_vec4 cx_vec4_random();                                                 /* Set vec4 with random values */

CX_API CX_API_INLINE cx_vec4 cx_vec4_negate(cx_vec4 u);                                        /* Returns the negation of a vec4 */
CX_API CX_API_INLINE cx_vec4 cx_vec4_add(const cx_vec4 u, const cx_vec4 v);                    /* Returns the addition of two vec4 */
CX_API CX_API_INLINE cx_vec4 cx_vec4_addf(const cx_vec4 u, cx_float fT);                       /* Returns the addition of a vec4 with a scalar */
CX_API CX_API_INLINE cx_vec4 cx_vec4_sub(const cx_vec4 u, const cx_vec4 v);                    /* Returns the subtraction of two vec4 */
CX_API CX_API_INLINE cx_vec4 cx_vec4_subf(const cx_vec4 u, cx_float fT);                       /* Returns the subtraction of a vec4 with a scalar */
CX_API CX_API_INLINE cx_vec4 cx_vec4_mulf(const cx_vec4 u, cx_float fT);                       /* Returns the multiplication of a vec4 with a scalar */
CX_API CX_API_INLINE cx_vec4 cx_vec4_divf(const cx_vec4 u, const cx_float fT);                 /* Returns the division of a vec4 with a scalar */

CX_API CX_API_INLINE cx_float cx_vec4_dot(const cx_vec4 u, const cx_vec4 v);                   /* Returns the dot product/scalar product of a vec4 */
CX_API CX_API_INLINE cx_vec4 cx_vec4_cross(const cx_vec4 u, const cx_vec4 v);                  /* Returns the cross product/vector product of vec4 with w = 1.0 */

CX_API CX_API_INLINE cx_vec4 cx_vec4_normalize(const cx_vec4 u);                               /* Returns the unit vector of a vec4 */
CX_API CX_API_INLINE cx_float cx_vec4_mag(const cx_vec4 u);                                    /* Returns the magnitude of a vec4 */

CX_API CX_API_INLINE void cx_vec4_print(const cx_vec4 u);                                      /* Print vec4 */


/* cx_mat2 ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_mat2 cx_mat2_set(const cx_float m00, const cx_float m01,
										 const cx_float m10, const cx_float m11);
CX_API CX_API_INLINE cx_mat2 cx_mat2_zero(void);
CX_API CX_API_INLINE cx_mat2 cx_mat2_identity(void);
CX_API CX_API_INLINE cx_mat2 cx_mat2_rotation(const cx_float angle);

CX_API CX_API_INLINE cx_mat2 cx_mat2_add(const cx_mat2 a, const cx_mat2 b);
CX_API CX_API_INLINE cx_mat2 cx_mat2_sub(const cx_mat2 a, const cx_mat2 b);
CX_API CX_API_INLINE cx_mat2 cx_mat2_mulf(const cx_mat2 a, const cx_float fT);
CX_API CX_API_INLINE cx_mat2 cx_mat2_divf(const cx_mat2 a, const cx_float fT);
CX_API CX_API_INLINE cx_mat2 cx_mat2_mul(const cx_mat2 a, const cx_mat2 b);
CX_API CX_API_INLINE cx_vec2 cx_mat2_vec2_mul(const cx_mat2 a, const cx_vec2 u);

CX_API CX_API_INLINE cx_float cx_mat2_det(const cx_mat2 a);
CX_API CX_API_INLINE cx_mat2 cx_mat2_transpose(const cx_mat2 a);
CX_API CX_API_INLINE cx_mat2 cx_mat2_inverse(const cx_mat2 a);
CX_API CX_API_INLINE cx_float cx_mat2_trace(const cx_mat2 a);

CX_API CX_API_INLINE cx_vec2 cx_mat2_rotate(const cx_vec2 u, const cx_float angle);
CX_API CX_API_INLINE cx_float cx_mat2_angle(const cx_mat2 a);

CX_API CX_API_INLINE bool cx_mat2_equals(const cx_mat2 a, const cx_mat2 b);
CX_API CX_API_INLINE bool cx_mat2_is_orthogonal(const cx_mat2 a);

CX_API CX_API_INLINE void cx_mat2_print(const cx_mat2 a);


/* cx_mat3 ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_mat3 cx_mat3_set(const cx_float m00, const cx_float m01, const cx_float m02,
                                         const cx_float m10, const cx_float m11, const cx_float m12,
                                         const cx_float m20, const cx_float m21, const cx_float m22);
CX_API CX_API_INLINE cx_mat3 cx_mat3_zero();
CX_API CX_API_INLINE cx_mat3 cx_mat3_identity();
CX_API CX_API_INLINE cx_mat3 cx_mat3_translation(const cx_float tx, const cx_float ty);
CX_API CX_API_INLINE cx_mat3 cx_mat3_scaling(const cx_float sx, const cx_float sy, const cx_float sz);
CX_API CX_API_INLINE cx_mat3 cx_mat3_shear_x(const cx_float shx);
CX_API CX_API_INLINE cx_mat3 cx_mat3_shear_y(const cx_float shx);
CX_API CX_API_INLINE cx_mat3 cx_mat3_shear(const cx_float shx, const cx_float shy);
CX_API CX_API_INLINE cx_mat3 cx_mat3_reflection_x();
CX_API CX_API_INLINE cx_mat3 cx_mat3_reflection_y();
CX_API CX_API_INLINE cx_mat3 cx_mat3_reflection_z();


CX_API CX_API_INLINE cx_mat3 cx_mat3_add(const cx_mat3 a, const cx_mat3 b);
CX_API CX_API_INLINE cx_mat3 cx_mat3_sub(const cx_mat3 a, const cx_mat3 b);
CX_API CX_API_INLINE cx_mat3 cx_mat3_mulf(const cx_mat3 a, const cx_float fT);
CX_API CX_API_INLINE cx_mat3 cx_mat3_divf(const cx_mat3 a, const cx_float fT);
CX_API CX_API_INLINE cx_mat3 cx_mat3_mul(const cx_mat3 a, const cx_mat3 b);
CX_API CX_API_INLINE cx_vec3 cx_mat3_vec3_mul(const cx_mat3 a, const cx_vec3 u);

CX_API CX_API_INLINE cx_float cx_mat3_det(const cx_mat3 a);
CX_API CX_API_INLINE cx_mat3 cx_mat3_transpose(const cx_mat3 a);
CX_API CX_API_INLINE cx_mat3 cx_mat3_cofactor_matrix(const cx_mat3 a);
CX_API CX_API_INLINE cx_mat3 cx_mat3_inverse(const cx_mat3 a);
CX_API CX_API_INLINE cx_float cx_mat3_trace(const cx_mat3 a);

CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_z(const cx_float angle);
CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_y(const cx_float angle);
CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_x(const cx_float angle);
CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_euler_zyx(const cx_float psi, const cx_float theta, const cx_float phi);
CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_euler_xyz(const cx_float phi, const cx_float theta, const cx_float psi);
CX_API CX_API_INLINE cx_vec3 cx_mat3_rotate_z(const cx_vec3 u, const cx_float angle);
CX_API CX_API_INLINE cx_vec3 cx_mat3_rotate_y(const cx_vec3 u, const cx_float angle);
CX_API CX_API_INLINE cx_vec3 cx_mat3_rotate_x(const cx_vec3 u, const cx_float angle);
CX_API CX_API_INLINE cx_vec3 cx_mat3_rotate(const cx_vec3 u, const cx_float psi, const cx_float theta, const cx_float phi);

CX_API CX_API_INLINE void cx_mat3_print(const cx_mat3 a);


/* cx_mat4 ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_mat4 cx_mat4_set(const cx_float m00, const cx_float m01, const cx_float m02, const cx_float m03,
                                         const cx_float m10, const cx_float m11, const cx_float m12, const cx_float m13,
                                         const cx_float m20, const cx_float m21, const cx_float m22, const cx_float m23,
                                         const cx_float m30, const cx_float m31, const cx_float m32, const cx_float m33);
CX_API CX_API_INLINE cx_mat4 cx_mat4_zero();
CX_API CX_API_INLINE cx_mat4 cx_mat4_identity();
CX_API CX_API_INLINE cx_mat4 cx_mat4_translation(const cx_float tx, const cx_float ty, const cx_float tz);
CX_API CX_API_INLINE cx_mat4 cx_mat4_scaling(const cx_float sx, const cx_float sy, const cx_float sz);
CX_API CX_API_INLINE cx_mat4 cx_mat4_shear_x(const cx_float sy, const cx_float sz);
CX_API CX_API_INLINE cx_mat4 cx_mat4_shear_y(const cx_float sx, const cx_float sz);
CX_API CX_API_INLINE cx_mat4 cx_mat4_shear_z(const cx_float sx, const cx_float sy);
CX_API CX_API_INLINE cx_mat4 cx_mat4_shear(const cx_float sxy, const cx_float sxz,
										   const cx_float syx, const cx_float syz,
										   const cx_float szx, const cx_float szy);
CX_API CX_API_INLINE cx_mat4 cx_mat4_perspectiveLH_NO(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar);
CX_API CX_API_INLINE cx_mat4 cx_mat4_perspectiveRH_NO(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar);
CX_API CX_API_INLINE cx_mat4 cx_mat4_perspectiveLH_ZO(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar);
CX_API CX_API_INLINE cx_mat4 cx_mat4_perspectiveRH_ZO(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar);
CX_API CX_API_INLINE cx_mat4 cx_mat4_perspective(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar);
CX_API CX_API_INLINE cx_mat4 cx_mat4_lookAtLH(const cx_vec3 eye, const cx_vec3 center, const cx_vec3 up);
CX_API CX_API_INLINE cx_mat4 cx_mat4_lookAtRH(const cx_vec3 eye, const cx_vec3 center, const cx_vec3 up);
CX_API CX_API_INLINE cx_mat4 cx_mat4_lookAt(const cx_vec3 eye, const cx_vec3 center, const cx_vec3 up);

CX_API CX_API_INLINE cx_mat4 cx_mat4_add(const cx_mat4 a, const cx_mat4 b);
CX_API CX_API_INLINE cx_mat4 cx_mat4_sub(const cx_mat4 a, const cx_mat4 b);
CX_API CX_API_INLINE cx_mat4 cx_mat4_mulf(const cx_mat4 a, const cx_float fT);
CX_API CX_API_INLINE cx_mat4 cx_mat4_divf(const cx_mat4 a, const cx_float fT);
CX_API CX_API_INLINE cx_mat4 cx_mat4_mul(const cx_mat4 a, const cx_mat4 b);
CX_API CX_API_INLINE cx_vec4 cx_mat4_vec4_mul(const cx_mat4 a, const cx_vec4 u);
CX_API CX_API_INLINE cx_vec4 cx_mat4_vec4_project(const cx_mat4 a, const cx_vec4 u);

CX_API CX_API_INLINE cx_float cx_mat4_det(const cx_mat4 a);
CX_API CX_API_INLINE cx_mat4 cx_mat4_transpose(const cx_mat4 a);
CX_API CX_API_INLINE cx_mat4 cx_mat4_inverse(const cx_mat4 a);
CX_API CX_API_INLINE cx_float cx_mat4_trace(const cx_mat4 a);

CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_z(const cx_float angle);
CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_y(const cx_float angle);
CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_x(const cx_float angle);
CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_euler_zyx(const cx_float psi, const cx_float theta, const cx_float phi);
CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_euler_xyz(const cx_float phi, const cx_float theta, const cx_float psi);
CX_API CX_API_INLINE cx_vec4 cx_mat4_rotate_z(const cx_vec4 u, const cx_float angle);
CX_API CX_API_INLINE cx_vec4 cx_mat4_rotate_y(const cx_vec4 u, const cx_float angle);
CX_API CX_API_INLINE cx_vec4 cx_mat4_rotate_x(const cx_vec4 u, const cx_float angle);
CX_API CX_API_INLINE cx_vec4 cx_mat4_rotate(const cx_vec4 u, const cx_float psi, const cx_float theta, const cx_float phi);

CX_API CX_API_INLINE cx_mat4 cx_mat4_from_quat(const cx_quat p);

CX_API CX_API_INLINE void cx_mat4_print(const cx_mat4 a);



/* cx_quat ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_quat cx_quat_set(const cx_float w, const cx_float x, const cx_float y, const cx_float z);
CX_API CX_API_INLINE cx_quat cx_quat_vec3_set(const cx_float w, const cx_vec3 u);
CX_API CX_API_INLINE cx_quat cx_quat_vec4_set(const cx_float w, const cx_vec4 u);
CX_API CX_API_INLINE cx_quat cx_quat_zero();
CX_API CX_API_INLINE cx_quat cx_quat_identity();
CX_API CX_API_INLINE cx_quat cx_quat_negate(const cx_quat p);
CX_API CX_API_INLINE cx_quat cx_quat_set_from_axis_anglef3(const cx_float x, const cx_float y, const cx_float z, const cx_float angle);
CX_API CX_API_INLINE cx_quat cx_quat_set_from_axis_anglev3(const cx_vec3 axis, const cx_float angle);
CX_API CX_API_INLINE cx_quat cx_quat_set_from_axis_anglev4(const cx_vec4 axis, const cx_float angle);

CX_API CX_API_INLINE cx_quat cx_quat_add(const cx_quat p, const cx_quat q);
CX_API CX_API_INLINE cx_quat cx_quat_sub(const cx_quat p, const cx_quat q);
CX_API CX_API_INLINE cx_quat cx_quat_mulf(const cx_quat p, const cx_float fT);
CX_API CX_API_INLINE cx_quat cx_quat_divf(const cx_quat p, const cx_float fT);
CX_API CX_API_INLINE cx_quat cx_quat_mul(const cx_quat p, const cx_quat q);

CX_API CX_API_INLINE cx_quat cx_quat_normalize(const cx_quat p);
CX_API CX_API_INLINE cx_float cx_quat_mag(const cx_quat p);
CX_API CX_API_INLINE cx_quat cx_quat_conjugate(const cx_quat p);
CX_API CX_API_INLINE cx_quat cx_quat_inverse(const cx_quat p);
CX_API CX_API_INLINE cx_quat cx_quat_lerp(const cx_quat p, const cx_quat q, const cx_float t);
CX_API CX_API_INLINE cx_quat cx_quat_nlerp(const cx_quat p, const cx_quat q, const cx_float t);
CX_API CX_API_INLINE cx_quat cx_quat_slerp(const cx_quat p, const cx_quat q, const cx_float t);

CX_API CX_API_INLINE cx_float cx_quat_dot(const cx_quat p, const cx_quat q);

CX_API CX_API_INLINE cx_vec3 cx_quat_vec3_rotate(const cx_quat p, const cx_vec3 u);
CX_API CX_API_INLINE cx_vec4 cx_quat_vec4_rotate(const cx_quat p, const cx_vec4 u);

CX_API CX_API_INLINE void cx_quat_print(const cx_quat p);

/* structs */
struct cx_vec2 {
	union {
		cx_float vec[2];
		struct {
      		cx_float x, y;
    	};
		struct {
    	  	cx_float v1, v2;
    	};
		struct {
      		cx_float X, Y;
    	};
  	};
};

struct cx_vec3 {
	union {
		cx_float vec[3];
		struct {
			cx_float x, y, z;
		};
		struct {
			cx_float v1, v2, v3;
		};
		struct {
			cx_float X, Y, Z;
		};
	};
};

struct cx_vec4 {
	union {
		cx_float vec[4];
		struct {
			cx_float x, y, z, w;
		};
		struct {
			cx_float X, Y, Z, W;
		};
	};
};


struct cx_mat2 {
	union {
		cx_float m[4];
		struct {
			cx_float m00, m01;
			cx_float m10, m11;
		};
		struct {
			cx_float c00, c01;
			cx_float c10, c11;
		};
		struct {
			cx_float i00, i01;
			cx_float i10, i11;
		};
	};
};


struct cx_mat3 {
	union {
		cx_float m[9];
		struct {
			cx_float m00, m01, m02;
			cx_float m10, m11, m12;
			cx_float m20, m21, m22;
		};
	};
};

struct cx_mat4 {
	union {
		cx_float m[16];
		struct {
			cx_float m00, m01, m02, m03;
			cx_float m10, m11, m12, m13;
			cx_float m20, m21, m22, m23;
			cx_float m30, m31, m32, m33;
		};
	};
};


struct cx_quat {
	union {
		cx_float v[4];
		struct {
			cx_float r, i, j, k;
		};
		struct {
			cx_float w, x, y, z;
		};
		struct {
			cx_float a, b, c, d;
		};
		struct {
			cx_float re;
			cx_vec3 im;
		};
	};
};


/* ------------------------------------------------------------------------------------------------------------ */
/* cx_vec2 ---------------------------------------------------------------------------------------------------- */
static const cx_vec2 _cx_vec2_zero             = { { { 0.0f, 0.0f  } } };
static const cx_vec2 _cx_vec2_unit_x           = { { { 1.0f, 0.0f  } } };
static const cx_vec2 _cx_vec2_unit_y           = { { { 0.0f, 1.0f  } } };
static const cx_vec2 _cx_vec2_unit_x_negative  = { { { -1.0f, 0.0f } } };
static const cx_vec2 _cx_vec2_unit_y_negative  = { { { 0.0f, -1.0f } } };
static const cx_vec2 _cx_vec2_one              = { { { 1.0f, 1.0f  } } };

CX_API const cx_vec2 *cx_get_reference_vec2(int id)
{
	switch(id) {
	case CX_REF_VEC2_ZERO:                	return &_cx_vec2_zero;
	case CX_REF_VEC2_ONE:                 	return &_cx_vec2_one;
	case CX_REF_VEC2_UNIT_X:              	return &_cx_vec2_unit_x;
	case CX_REF_VEC2_UNIT_Y:              	return &_cx_vec2_unit_y;
	case CX_REF_VEC2_UNIT_X_NEGATIVE:     	return &_cx_vec2_unit_x_negative;
	case CX_REF_VEC2_UNIT_Y_NEGATIVE:     	return &_cx_vec2_unit_y_negative;
	default:
												return &_cx_vec2_zero;
  }
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_set(cx_float x, cx_float y)
{
  	return (cx_vec2) {
		.x = x,
		.y = y
	};
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_zero()
{
  	return cx_vec2_set(0.0f, 0.0f);
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_random()
{
  	return cx_vec2_set(CX_RANDOM_FLOAT, CX_RANDOM_FLOAT);
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_negate(cx_vec2 u)
{
  	return cx_vec2_set(-u.x, -u.y);
}
CX_API CX_API_INLINE cx_vec2 cx_vec2_add(const cx_vec2 u, const cx_vec2 v)
{
  	return (struct cx_vec2) {   .x = u.x + v.x,
  	                            .y = u.y + v.y
  	};
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_addf(const cx_vec2 u, const cx_float fT)
{
  	return (struct cx_vec2) {   .x = u.x + fT,
  	                            .y = u.y + fT
  	};
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_sub(const cx_vec2 u, const cx_vec2 v)
{
  	return (struct cx_vec2) {   .x = u.x - v.x,
  	                            .y = u.y - v.y
  	};
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_subf(const cx_vec2 u, const cx_float fT)
{
  	return (struct cx_vec2) {   .x = u.x - fT,
  	                            .y = u.y - fT
  	};
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_mulf(const cx_vec2 u, const cx_float fT)
{
  	return (struct cx_vec2) {   .x = fT * u.x,
  	                            .y = fT * u.y
  	};
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_divf(const cx_vec2 u, const cx_float fT)
{
	CX_ASSERT(CX_FLOAT_EQUALS(fT, 0.0) == 0 && "Assert: given fT is equals to '0'");
	return (struct cx_vec2) {		.x = u.x / fT,
									.y = u.y / fT
	};
}

CX_API CX_API_INLINE bool cx_vec2_equals(const cx_vec2 u, const cx_vec2 v)
{
	return (CX_ABS(u.x - v.x) <= CX_EPSILON) && (CX_ABS(u.y - v.y) <= CX_EPSILON);
}

CX_API CX_API_INLINE cx_float cx_vec2_dot(const cx_vec2 u, const cx_vec2 v)
{
  	return (u.x * v.x + u.y * v.y);
}

CX_API CX_API_INLINE cx_float cx_vec2_cross(const cx_vec2 u, const cx_vec2 v)
{
  	return (u.x * v.y - u.y * v.x);
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_normalize(const cx_vec2 u)
{
  	cx_float mag = cx_vec2_mag(u);
  	cx_float mag_inv = (mag > 0) ? 1 / mag : 0.0f;
  	return (struct cx_vec2) {   .x = u.x * mag_inv,
  	                            .y = u.y * mag_inv
  	};
}

CX_API CX_API_INLINE cx_float cx_vec2_mag(const cx_vec2 u)
{
  	return (CX_SQRT(CX_SQ(u.x) + CX_SQ(u.y)));
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_rotate(const cx_vec2 u, cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_COS(angle);

	return (cx_vec2) {
		.x = u.x * _cos - u.y * _sin,
		.y = u.x * _sin + u.y * _cos
	};
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_lerp(const cx_vec2 u, const cx_vec2 v, const cx_float t)
{
	return (cx_vec2) {
		.x = cx_lerp(u.x, v.x, t),
		.y = cx_lerp(u.y, v.y, t)
	};
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_proj(const cx_vec2 u, const cx_vec2 v)
{
	const cx_float mag = cx_vec2_mag(v);
	const cx_float inv_mag_sq = (mag <= CX_EPSILON) ? 0.0 : 1.0 / (mag * mag);
	const cx_float dot = cx_vec2_dot(u, v);

	return cx_vec2_mulf(v, dot * inv_mag_sq);
}

CX_API CX_API_INLINE cx_float cx_vec2_angle(const cx_vec2 u, const cx_vec2 v)
{
	const cx_float dot = cx_vec2_dot(u, v);
	const cx_float mag = cx_vec2_mag(u) * cx_vec2_mag(v);
	if (mag <= CX_EPSILON) return 0.0;

	return CX_ACOS(cx_clamp(dot / mag, -1.0, 1.0));
}

CX_API CX_API_INLINE cx_vec2 cx_vec2_reflect(const cx_vec2 u, const cx_vec2 n)
{
	const cx_vec2 proj_n = cx_vec2_proj(u, n);
	const cx_vec2 proj = cx_vec2_mulf(proj_n, 2.0f);

	return cx_vec2_sub(u, proj);
}

CX_API CX_API_INLINE void cx_vec2_print(const cx_vec2 u)
{
  	CX_PRINTLN("vec2: (x: %.2f,y: %.2f)", u.x, u.y);
}


/* ------------------------------------------------------------------------------------------------------------ */
/* cx_vec3 ---------------------------------------------------------------------------------------------------- */
static const cx_vec3 _cx_vec3_zero             = { { { 0.0f, 0.0f, 0.0f  } } };
static const cx_vec3 _cx_vec3_unit_x           = { { { 1.0f, 0.0f, 0.0f  } } };
static const cx_vec3 _cx_vec3_unit_y           = { { { 0.0f, 1.0f, 0.0f  } } };
static const cx_vec3 _cx_vec3_unit_z           = { { { 0.0f, 0.0f, 1.0f  } } };
static const cx_vec3 _cx_vec3_unit_x_negative  = { { { -1.0f, 0.0f, 0.0f } } };
static const cx_vec3 _cx_vec3_unit_y_negative  = { { { 0.0f, -1.0f, 0.0f } } };
static const cx_vec3 _cx_vec3_unit_z_negative  = { { { 0.0f, 0.0f, -1.0f } } };
static const cx_vec3 _cx_vec3_one              = { { { 1.0f, 1.0f, 1.0f  } } };

CX_API const cx_vec3 *cx_get_reference_vec3(int id)
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

CX_API CX_API_INLINE cx_vec3 cx_vec3_set(cx_float x, cx_float y, cx_float z)
{
  	return (cx_vec3) {
		.x = x,
		.y = y,
		.z = z
	};
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_zero()
{
	return cx_vec3_set(0.0, 0.0, 0.0);
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_random()
{
  	return cx_vec3_set(CX_RANDOM_FLOAT, CX_RANDOM_FLOAT, CX_RANDOM_FLOAT);
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_negate(cx_vec3 u)
{
	return cx_vec3_set(-u.x, -u.y, -u.z);
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_add(const cx_vec3 u, const cx_vec3 v)
{
  	return (cx_vec3) {   .x = u.x + v.x,
                         .y = u.y + v.y,
                         .z = u.z + v.z
  	};
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_addf(const cx_vec3 u, const cx_float fT)
{
  	return (cx_vec3) {   .x = u.x + fT,
						 .y = u.y + fT,
                         .z = u.z + fT
  	};
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_sub(const cx_vec3 u, const cx_vec3 v)
{
  	return (cx_vec3) {   .x = u.x - v.x,
                         .y = u.y - v.y,
                         .z = u.z - v.z
  	};
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_subf(const cx_vec3 u, const cx_float fT)
{
  	return (cx_vec3) {   .x = u.x - fT,
                         .y = u.y - fT,
                         .z = u.z - fT
 	};
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_mulf(const cx_vec3 u, const cx_float fT)
{
  	return (cx_vec3) {   .x = fT * u.x,
                         .y = fT * u.y,
                         .z = fT * u.z
  	};
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_divf(const cx_vec3 u, const cx_float fT)
{
	CX_ASSERT(CX_FLOAT_EQUALS(fT, 0) == 0 && "Assert: given fT is equals to '0'");
	return (cx_vec3) {		.x = u.x / fT,
							.y = u.y / fT,
							.z = u.z / fT
	};
}

CX_API CX_API_INLINE cx_float cx_vec3_dot(const cx_vec3 u, const cx_vec3 v)
{
  	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_cross(const cx_vec3 u, const cx_vec3 v)
{
  	return (cx_vec3) {   .x = u.y * v.z - u.z * v.y,
                         .y = u.z * v.x - u.x * v.z,
                         .z = u.x * v.y - u.y * v.x
  	};
}

CX_API CX_API_INLINE cx_vec3 cx_vec3_normalize(const cx_vec3 u)
{
  	cx_float mag = cx_vec3_mag(u);
  	cx_float mag_inv = (mag > 0) ? 1 / mag : 0.0f;
  	return (cx_vec3) {   .x = mag_inv * u.x,
                         .y = mag_inv * u.y,
                         .z = mag_inv * u.z
  	};
}

CX_API CX_API_INLINE cx_float cx_vec3_mag(const cx_vec3 u)
{
  	return CX_SQRT(CX_SQ(u.x) + CX_SQ(u.y) + CX_SQ(u.z));
}

CX_API CX_API_INLINE cx_float cx_vec3_mag_sq(const cx_vec3 u)
{
	return CX_SQ(u.x) + CX_SQ(u.y) + CX_SQ(u.z);
}

CX_API CX_API_INLINE cx_float cx_vec3_angle(const cx_vec3 u, const cx_vec3 v)
{
	const cx_float dot = cx_vec3_dot(u, v);
	const cx_float mag = cx_vec3_mag(u) * cx_vec3_mag(v);
	if (mag <= CX_EPSILON) return 0.0;

	return CX_ACOS(cx_clamp(dot / mag, -1.0, 1.0));
}

CX_API CX_API_INLINE void cx_vec3_print(const cx_vec3 u)
{
  	CX_PRINTLN("vec3: (x: %.2f, y: %.2f, z: %.2f)", u.x, u.y, u.z);
}

/* ------------------------------------------------------------------------------------------------------------ */
/* cx_vec4 functions ------------------------------------------------------------------------------------------ */

static const cx_vec4 _cx_vec4_zero             = { { { 0.0f, 0.0f, 0.0f, 0.0f  } } };
static const cx_vec4 _cx_vec4_unit_x           = { { { 1.0f, 0.0f, 0.0f, 0.0f  } } };
static const cx_vec4 _cx_vec4_unit_y           = { { { 0.0f, 1.0f, 0.0f, 0.0f  } } };
static const cx_vec4 _cx_vec4_unit_z           = { { { 0.0f, 0.0f, 1.0f, 0.0f  } } };
static const cx_vec4 _cx_vec4_unit_w           = { { { 0.0f, 0.0f, 0.0f, 1.0f  } } };
static const cx_vec4 _cx_vec4_unit_x_negative  = { { { -1.0f, 0.0f, 0.0f, 0.0f } } };
static const cx_vec4 _cx_vec4_unit_y_negative  = { { { 0.0f, -1.0f, 0.0f, 0.0f } } };
static const cx_vec4 _cx_vec4_unit_z_negative  = { { { 0.0f, 0.0f, -1.0f, 0.0f } } };
static const cx_vec4 _cx_vec4_unit_w_negative  = { { { 0.0f, 0.0f, 0.0f, -1.0f } } };
static const cx_vec4 _cx_vec4_one              = { { { 1.0f, 1.0f, 1.0f, 1.0f  } } };

CX_API const cx_vec4 *cx_get_reference_vec4(int id)
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

CX_API CX_API_INLINE cx_vec4 cx_vec4_set(cx_float x, cx_float y, cx_float z, cx_float w)
{
  	return (cx_vec4) {
		.x = x,
		.y = y,
		.z = z,
		.w = w
	};
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_zero()
{
	return cx_vec4_set(0.0f, 0.0f, 0.0f, 0.0f);
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_random()
{
	return cx_vec4_set(CX_RANDOM_FLOAT, CX_RANDOM_FLOAT, CX_RANDOM_FLOAT, CX_RANDOM_FLOAT);
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_negate(cx_vec4 u)
{
  	return cx_vec4_set(-u.x, -u.y, -u.z, -u.w);
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_add(const cx_vec4 u, const cx_vec4 v)
{
	return (cx_vec4) {		.x = u.x + v.x,
							.y = u.y + v.y,
							.z = u.z + v.z,
							.w = u.w + v.w
	};
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_addf(const cx_vec4 u, cx_float fT)
{
	return (cx_vec4) {		.x = u.x + fT,
							.y = u.y + fT,
							.z = u.z + fT,
							.w = u.w + fT
	};
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_sub(const cx_vec4 u, const cx_vec4 v)
{
	return (cx_vec4) {		.x = u.x - v.x,
							.y = u.y - v.y,
							.z = u.z - v.z,
							.w = u.w - v.w
	};
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_subf(const cx_vec4 u, cx_float fT)
{
	return (cx_vec4) {		.x = u.x - fT,
							.y = u.y - fT,
							.z = u.z - fT,
							.w = u.w - fT
	};
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_mulf(const cx_vec4 u, cx_float fT)
{
	return (cx_vec4) {		.x = u.x * fT,
							.y = u.y * fT,
							.z = u.z * fT,
							.w = u.w * fT
	};
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_divf(const cx_vec4 u, const cx_float fT)
{
	CX_ASSERT(CX_FLOAT_EQUALS(fT, 0) == 0 && "Assert: given fT is equals to '0'");
	return (cx_vec4) {		.x = u.x / fT,
							.y = u.y / fT,
							.z = u.z / fT,
							.w = u.w / fT
	};
}

CX_API CX_API_INLINE cx_float cx_vec4_dot(const cx_vec4 u, const cx_vec4 v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_cross(const cx_vec4 u, const cx_vec4 v)
{
	return (cx_vec4) {		.x = (u.y * v.z) - (u.z * v.y),
							.y = (u.z * v.x) - (u.x * v.z),
							.z = (u.x * v.y) - (u.y * v.x),
							.w = 0.0
	};
}

CX_API CX_API_INLINE cx_vec4 cx_vec4_normalize(const cx_vec4 u)
{
  	cx_float mag = cx_vec4_mag(u);
  	cx_float mag_inv = (mag > 0) ? 1 / mag : 0.0f;

  	return (cx_vec4) {   .x = u.x * mag_inv,
                         .y = u.y * mag_inv,
                         .z = u.z * mag_inv,
                         .w = u.w * mag_inv,
  	};
}

CX_API CX_API_INLINE cx_float cx_vec4_mag(const cx_vec4 u)
{
  	return CX_SQRT(CX_SQ(u.x) + CX_SQ(u.y) + CX_SQ(u.z) + CX_SQ(u.w));
}

CX_API CX_API_INLINE void cx_vec4_print(const cx_vec4 u)
{
  	CX_PRINTLN("vec4: (x: %f, y: %f, z: %f, w: %f)", u.x, u.y, u.z, u.w);
}

/* ------------------------------------------------------------------------------------------------------------ */
/* 2x2 matrix --------------------------------------------------------------------------------------------------*/

CX_API CX_API_INLINE cx_mat2 cx_mat2_set(const cx_float m00, const cx_float m01,
										 const cx_float m10, const cx_float m11)
{
	return (cx_mat2) {
		{
			{
				m00, m01,
				m10, m11
			}
		}
	};
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_zero(void)
{
	return cx_mat2_set(0.0, 0.0,
					   0.0, 0.0);
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_identity(void)
{
	return cx_mat2_set(1.0, 0.0,
					   0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_rotation(const cx_float angle)
{

	const cx_float _sin = sin(angle);
	const cx_float _cos = cos(angle);

	return cx_mat2_set(_cos, -_sin,
					   _sin,  _cos);
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_add(const cx_mat2 a, const cx_mat2 b)
{
	cx_mat2 result = { 0 };
	for (int i = 0; i < 4; i++) {
		result.m[i] = a.m[i] + b.m[i];
	}

	return result;
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_sub(const cx_mat2 a, const cx_mat2 b)
{
	cx_mat2 result = { 0 };
	for (int i = 0; i < 4; i++) {
		result.m[i] = a.m[i] - b.m[i];
	}

	return result;
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_mul(const cx_mat2 a, const cx_mat2 b)
{
	return cx_mat2_set(a.m00 * b.m00 + a.m01 * b.m10, a.m00 * b.m01 + a.m01 * b.m11,
	 	               a.m10 * b.m00 + a.m11 * b.m10, a.m10 * b.m01 + a.m11 * b.m11);
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_mulf(const cx_mat2 a, const cx_float fT)
{
	return cx_mat2_set(a.m00 * fT, a.m01 * fT,
		               a.m10 * fT, a.m11 * fT);
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_divf(const cx_mat2 a, const cx_float fT)
{
	if (fT == 0) {
		return cx_mat2_zero();
	}

	return cx_mat2_set(a.m00 / fT, a.m01 / fT,
		               a.m10 / fT, a.m11 / fT);
}

CX_API CX_API_INLINE cx_vec2 cx_mat2_vec2_mul(const cx_mat2 a, const cx_vec2 u)
{
	return cx_vec2_set(a.m00 * u.x + a.m01 * u.y,
		               a.m10 * u.x + a.m11 * u.y);
}

CX_API CX_API_INLINE cx_float cx_mat2_det(const cx_mat2 a)
{
	return a.m00 * a.m11 - a.m01 * a.m10;
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_transpose(const cx_mat2 a)
{
	return cx_mat2_set(a.m00, a.m10,
		               a.m01, a.m11);
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_inverse(const cx_mat2 a)
{
	const cx_float det = cx_mat2_det(a);
	if (det == 0) return cx_mat2_zero();

	return cx_mat2_set(a.m11 / det, -a.m01 / det,
		               -a.m10 / det,  a.m00 / det);
}

CX_API CX_API_INLINE cx_float cx_mat2_trace(const cx_mat2 a)
{
	return a.m00 + a.m11;
}

CX_API CX_API_INLINE cx_vec2 cx_mat2_rotate(const cx_vec2 u, const cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_COS(angle);

	cx_mat2 rotation_matrix = cx_mat2_set(_cos, -_sin,
										  _sin,  _cos);

	return cx_mat2_vec2_mul(rotation_matrix, u);
}

CX_API CX_API_INLINE cx_float cx_mat2_angle(const cx_mat2 a)
{
	if (a.m00 == -1.0)	return CX_PI;
	return 2 * CX_ATAN(a.m10 / (1 + a.m00));
}

CX_API CX_API_INLINE bool cx_mat2_equals(const cx_mat2 a, const cx_mat2 b)
{
	return (CX_FLOAT_EQUALS(a.m00, b.m00) && CX_FLOAT_EQUALS(a.m01, b.m01) &&
			CX_FLOAT_EQUALS(a.m10, b.m10) && CX_FLOAT_EQUALS(a.m11, b.m11));
}

CX_API CX_API_INLINE bool cx_mat2_is_orthogonal(const cx_mat2 a)
{
	const cx_mat2 trans = cx_mat2_transpose(a);
	const cx_mat2 inv = cx_mat2_inverse(a);

	return cx_mat2_equals(trans, inv);
}

CX_API CX_API_INLINE void cx_mat2_print(const cx_mat2 a)
{
	printf("mat2: ⎡%-6.2f  %6.2f⎤\n"
		   "      ⎣%-6.2f  %6.2f⎦\n",
		   a.m00, a.m01,
		   a.m10, a.m11);
}


CX_API CX_API_INLINE cx_mat3 cx_mat3_set(const cx_float m00, const cx_float m01, const cx_float m02,
                                         const cx_float m10, const cx_float m11, const cx_float m12,
                                         const cx_float m20, const cx_float m21, const cx_float m22)
{
	return (cx_mat3) {
		{
			{
				m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22
			}
		}
	};
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_zero()
{
	return cx_mat3_set(0.0, 0.0, 0.0,
				       0.0, 0.0, 0.0,
					   0.0, 0.0, 0.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_identity()
{
	return cx_mat3_set(1.0, 0.0, 0.0,
                       0.0, 1.0, 0.0,
				       0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_translation(const cx_float tx, const cx_float ty)
{
	return cx_mat3_set(1.0, 0.0, tx,
                       0.0, 1.0, ty,
				       0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_scaling(const cx_float sx, const cx_float sy, const cx_float sz)
{
	return cx_mat3_set(sx,  0.0, 0.0,
					   0.0, sy,  0.0,
					   0.0, 0.0, sz);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_shear_x(const cx_float shx)
{
	return cx_mat3_set(1.0, shx, 0.0,
					   0.0, 1.0, 0.0,
					   0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_shear_y(const cx_float shy)
{
	return cx_mat3_set(1.0, 0.0, 0.0,
					   shy, 1.0, 0.0,
					   0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_shear(const cx_float shx, const cx_float shy)
{
	return cx_mat3_set(1.0, shx, 0.0,
					   shy, 1.0, 0.0,
					   0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_reflection_x()
{
	return cx_mat3_set(-1.0, 0.0, 0.0,
                       0.0, 1.0, 0.0,
				       0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_reflection_y()
{
	return cx_mat3_set(1.0, 0.0, 0.0,
                       0.0, -1.0, 0.0,
				       0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_reflection_z()
{
	return cx_mat3_set(1.0, 0.0, 0.0,
                       0.0, 1.0, 0.0,
				       0.0, 0.0, -1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_add(const cx_mat3 a, const cx_mat3 b)
{
	return cx_mat3_set(a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02,
		               a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12,
		               a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_sub(const cx_mat3 a, const cx_mat3 b)
{
	return cx_mat3_set(a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02,
		               a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12,
		               a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_mulf(const cx_mat3 a, const cx_float fT)
{
	return cx_mat3_set(a.m00 * fT, a.m01 * fT, a.m02 * fT,
		               a.m10 * fT, a.m11 * fT, a.m12 * fT,
		               a.m20 * fT, a.m21 * fT, a.m22 * fT);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_divf(const cx_mat3 a, const cx_float fT)
{
	if (fT == 0) return cx_mat3_zero();
	return cx_mat3_set(a.m00 / fT, a.m01 / fT, a.m02 / fT,
		               a.m10 / fT, a.m11 / fT, a.m12 / fT,
		               a.m20 / fT, a.m21 / fT, a.m22 / fT);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_mul(const cx_mat3 a, const cx_mat3 b)
{
	return cx_mat3_set(a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20, a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21, a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22,
		               a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20, a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21, a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22,
		               a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20, a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21, a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22);
}

CX_API CX_API_INLINE cx_vec3 cx_mat3_vec3_mul(const cx_mat3 a, const cx_vec3 u)
{
	return (cx_vec3) {
		.x = a.m00 * u.x + a.m01 * u.y + a.m02 * u.z,
		.y = a.m10 * u.x + a.m11 * u.y + a.m12 * u.z,
		.z = a.m20 * u.x + a.m21 * u.y + a.m22 * u.z
	};
}

CX_API CX_API_INLINE cx_float cx_mat3_det(const cx_mat3 a)
{
	return a.m00 * (a.m11 * a.m22 - a.m21 * a.m12) - a.m01 * (a.m10 * a.m22 - a.m12 * a.m20) + a.m02 * (a.m10 * a.m21 - a.m11 * a.m20);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_cofactor_matrix(const cx_mat3 a)
{
	const cx_float C00 = a.m11 * a.m22 - a.m12 * a.m21;
	const cx_float C01 = a.m10 * a.m22 - a.m12 * a.m20;
	const cx_float C02 = a.m10 * a.m21 - a.m11 * a.m20;

	const cx_float C10 = a.m01 * a.m22 - a.m02 * a.m21;
	const cx_float C11 = a.m00 * a.m22 - a.m02 * a.m20;
	const cx_float C12 = a.m00 * a.m21 - a.m01 * a.m20;

	const cx_float C20 = a.m01 * a.m12 - a.m02 * a.m11;
	const cx_float C21 = a.m00 * a.m12 - a.m02 * a.m10;
	const cx_float C22 = a.m00 * a.m11 - a.m01 * a.m10;

	return cx_mat3_set(C00,  -C01, C02,
					   -C10, C11,  -C12,
					   C20,  -C21, C22);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_inverse(const cx_mat3 a)
{
	cx_float det = cx_mat3_det(a);
	if (det == 0.0)	return cx_mat3_zero();

	const cx_mat3 cofactor = cx_mat3_transpose(cx_mat3_cofactor_matrix(a));

	return cx_mat3_divf(cofactor, det);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_transpose(const cx_mat3 a)
{
	return cx_mat3_set(a.m00, a.m10, a.m20,
		               a.m01, a.m11, a.m21,
		               a.m02, a.m12, a.m22);
}

CX_API CX_API_INLINE cx_float cx_mat3_trace(const cx_mat3 a)
{
	return a.m00 + a.m11 + a.m22;
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_z(const cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_COS(angle);

	return cx_mat3_set(_cos, -_sin, 0.0,
		               _sin,  _cos, 0.0,
		               0.0,   0.0,  1.0);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_y(const cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_COS(angle);

	return cx_mat3_set(_cos,  0.0, _sin,
		               0.0,   1.0,  0.0,
		               -_sin, 0.0, _cos);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_x(const cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_COS(angle);

	return cx_mat3_set(1.0,   0.0,   0.0,
		               0.0, _cos,  -_sin,
		               0.0, _sin,   _cos);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_euler_zyx(const cx_float psi, const cx_float theta, const cx_float phi)
{
	const cx_mat3 rot_z = cx_mat3_rotation_z(psi);
	const cx_mat3 rot_y = cx_mat3_rotation_y(theta);
	const cx_mat3 rot_x = cx_mat3_rotation_x(phi);

	return cx_mat3_mul(cx_mat3_mul(rot_z, rot_y), rot_x);
}

CX_API CX_API_INLINE cx_mat3 cx_mat3_rotation_euler_xyz(const cx_float phi, const cx_float theta, const cx_float psi)
{
	const cx_mat3 rot_x = cx_mat3_rotation_x(phi);
	const cx_mat3 rot_y = cx_mat3_rotation_y(theta);
	const cx_mat3 rot_z = cx_mat3_rotation_z(psi);

	return cx_mat3_mul(cx_mat3_mul(rot_x, rot_y), rot_z);
}

CX_API CX_API_INLINE cx_vec3 cx_mat3_rotate_z(const cx_vec3 u, const cx_float angle)
{
	const cx_mat3 rot_z = cx_mat3_rotation_z(angle);

	return cx_mat3_vec3_mul(rot_z, u);
}

CX_API CX_API_INLINE cx_vec3 cx_mat3_rotate_y(const cx_vec3 u, const cx_float angle)
{
	const cx_mat3 rot_y = cx_mat3_rotation_y(angle);

	return cx_mat3_vec3_mul(rot_y, u);
}

CX_API CX_API_INLINE cx_vec3 cx_mat3_rotate_x(const cx_vec3 u, const cx_float angle)
{
	const cx_mat3 rot_x = cx_mat3_rotation_x(angle);

	return cx_mat3_vec3_mul(rot_x, u);
}

CX_API CX_API_INLINE cx_vec3 cx_mat3_rotate(const cx_vec3 u, const cx_float psi, const cx_float theta, const cx_float phi)
{
	const cx_mat3 rot_z = cx_mat3_rotation_z(psi);
	const cx_mat3 rot_y = cx_mat3_rotation_y(theta);
	const cx_mat3 rot_x = cx_mat3_rotation_x(phi);

	const cx_mat3 rot = cx_mat3_mul(cx_mat3_mul(rot_z, rot_y), rot_x);

	return cx_mat3_vec3_mul(rot, u);
}

CX_API CX_API_INLINE void cx_mat3_print(const cx_mat3 a)
{
	printf("mat3: ⎡%-6.2f  %6.2f  %6.2f⎤\n"
		   "      ⎢%-6.2f  %6.2f  %6.2f⎥\n"
		   "      ⎣%-6.2f  %6.2f  %6.2f⎦\n",
		   a.m00, a.m01, a.m02,
		   a.m10, a.m11, a.m12,
		   a.m20, a.m21, a.m22);
}




CX_API CX_API_INLINE cx_mat4 cx_mat4_set(const cx_float m00, const cx_float m01, const cx_float m02, const cx_float m03,
                                         const cx_float m10, const cx_float m11, const cx_float m12, const cx_float m13,
                                         const cx_float m20, const cx_float m21, const cx_float m22, const cx_float m23,
                                         const cx_float m30, const cx_float m31, const cx_float m32, const cx_float m33)
{
	return (cx_mat4) {
		{
			{
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33
			}
		}
	};
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_zero()
{
	return cx_mat4_set(0.0, 0.0, 0.0, 0.0,
				       0.0, 0.0, 0.0, 0.0,
					   0.0, 0.0, 0.0, 0.0,
					   0.0, 0.0, 0.0, 0.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_identity()
{
	return cx_mat4_set(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
				       0.0, 0.0, 1.0, 0.0,
					   0.0, 0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_translation(const cx_float tx, const cx_float ty, const cx_float tz)
{
	return cx_mat4_set(1.0, 0.0, 0.0, tx,
                       0.0, 1.0, 0.0, ty,
					   0.0, 0.0, 1.0, tz,
				       0.0, 0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_scaling(const cx_float sx, const cx_float sy, const cx_float sz)
{
	return cx_mat4_set(sx,  0.0, 0.0, 0.0,
					   0.0, sy,  0.0, 0.0,
					   0.0, 0.0, sz,  0.0,
					   0.0, 0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_shear_x(const cx_float sy, const cx_float sz)
{
	return cx_mat4_set(1.0,  sy,  sz,  0.0,
					   0.0,  1.0, 0.0, 0.0,
					   0.0,  0.0, 1.0, 0.0,
					   0.0,  0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_shear_y(const cx_float sx, const cx_float sz)
{
	return cx_mat4_set(1.0,  0.0, 0.0, 0.0,
					   sx,   1.0, sz,  0.0,
					   0.0,  0.0, 1.0, 0.0,
					   0.0,  0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_shear_z(const cx_float sx, const cx_float sy)
{
	return cx_mat4_set(1.0,  0.0, 0.0, 0.0,
					   0.0,  1.0, 0.0, 0.0,
					   sx,   sy,  1.0, 0.0,
					   0.0,  0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_shear(const cx_float sxy, const cx_float sxz,
										   const cx_float syx, const cx_float syz,
										   const cx_float szx, const cx_float szy)
{
	return cx_mat4_set(1.0,  sxy,  sxz,  0.0,
					   syx,  1.0,  syz,  0.0,
					   szx,  szy,  1.0,  0.0,
					   0.0,  0.0,  0.0,  1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_perspectiveLH_NO(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar)
{
	const cx_float _tan = tan(fov * 0.5);
	const cx_float zfn = zfar - znear;

	return cx_mat4_set(1.0 / (aspect * _tan), 0.0,        0.0,                  0.0,
					   0.0,                   1.0 / _tan, 0.0,                  0.0,
					   0.0,                   0.0,        (zfar + znear) / zfn, -(2.0 * zfar * znear) / zfn,
					   0.0,                   0.0,        1.0,                  0.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_perspectiveRH_NO(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar)
{
	const cx_float _tan = tan(fov * 0.5);
	const cx_float zfn = zfar - znear;

	return cx_mat4_set(1.0 / (aspect * _tan), 0.0,        0.0,                   0.0,
					   0.0,                   1.0 / _tan, 0.0,                   0.0,
					   0.0,                   0.0,        -(zfar + znear) / zfn, -(2.0 * zfar * znear) / zfn,
					   0.0,                   0.0,        -1.0,                  0.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_perspectiveLH_ZO(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar)
{
	const cx_float _tan = tan(fov * 0.5);
	const cx_float zfn = zfar / (zfar - znear);

	return cx_mat4_set(1.0 / (aspect * _tan), 0.0,        0.0, 0.0,
					   0.0,                   1.0 / _tan, 0.0, 0.0,
					   0.0,                   0.0,        zfn, -zfn * znear,
					   0.0,                   0.0,        1.0, 0.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_perspectiveRH_ZO(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar)
{
	const cx_float _tan = tan(fov * 0.5);
	const cx_float zfn1 = zfar / (znear - zfar);
	const cx_float zfn2 = zfar / (zfar - znear);

	return cx_mat4_set(1.0 / (aspect * _tan), 0.0,        0.0,  0.0,
					   0.0,                   1.0 / _tan, 0.0,  0.0,
					   0.0,                   0.0,        zfn1, -zfn2 * znear,
					   0.0,                   0.0,        -1.0, 0.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_perspective(const cx_float fov, const cx_float aspect, const cx_float znear, const cx_float zfar)
{
	#if    defined(CX_PERSPECTIVE_LH_NO)
		return cx_mat4_perspectiveLH_NO(fov, aspect, znear, zfar);
	#elif  defined(CX_PERSPECTIVE_RH_NO)
		return cx_mat4_perspectiveRH_NO(fov, aspect, znear, zfar);
	#elif  defined(CX_PERSPECTIVE_LH_ZO)
		return cx_mat4_perspectiveLH_ZO(fov, aspect, znear, zfar);
	#elif  defined(CX_PERSPECTIVE_RH_ZO)
		return cx_mat4_perspectiveRH_ZO(fov, aspect, znear, zfar);
	#else
		return cx_mat4_perspectiveLH_NO(fov, aspect, znear, zfar);
	#endif
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_lookAtLH(const cx_vec3 eye, const cx_vec3 center, const cx_vec3 up)
{
	const cx_vec3 f = cx_vec3_normalize(cx_vec3_sub(center, eye));
	const cx_vec3 s = cx_vec3_normalize(cx_vec3_cross(up, f));
	const cx_vec3 u = cx_vec3_cross(f, s);

	return cx_mat4_set(s.x, s.y, s.z, -cx_vec3_dot(s, eye),
					   u.x, u.y, u.z, -cx_vec3_dot(u, eye),
					   f.x, f.y, f.z, -cx_vec3_dot(f, eye),
					   0.0, 0.0, 0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_lookAtRH(const cx_vec3 eye, const cx_vec3 center, const cx_vec3 up)
{
	const cx_vec3 f = cx_vec3_normalize(cx_vec3_sub(center, eye));
	const cx_vec3 s = cx_vec3_normalize(cx_vec3_cross(f, up));
	const cx_vec3 u = cx_vec3_cross(s, f);

	return cx_mat4_set(s.x,  s.y,  s.z,  -cx_vec3_dot(s, eye),
					   u.x,  u.y,  u.z,  -cx_vec3_dot(u, eye),
					   -f.x, -f.y, -f.z, cx_vec3_dot(f, eye),
					   0.0,  0.0,  0.0,  1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_lookAt(const cx_vec3 eye, const cx_vec3 center, const cx_vec3 up)
{
	#if defined(CX_LOOKAT_LH)
		return cx_mat4_lookAtLH(eye, center, up);
	#elif defined(CX_LOOKAT_RH)
		return cx_mat4_lookAtRH(eye, center, up);
	#else
		return cx_mat4_lookAtLH(eye, center, up);
	#endif
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_add(const cx_mat4 a, const cx_mat4 b)
{
	return cx_mat4_set(a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02, a.m03 + b.m03,
		               a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13,
		               a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23,
		               a.m30 + b.m30, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_sub(const cx_mat4 a, const cx_mat4 b)
{
	return cx_mat4_set(a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02, a.m03 - b.m03,
		               a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13,
		               a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23,
		               a.m30 - b.m30, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_mulf(const cx_mat4 a, const cx_float fT)
{
	return cx_mat4_set(a.m00 * fT, a.m01 * fT, a.m02 * fT, a.m03 * fT,
		               a.m10 * fT, a.m11 * fT, a.m12 * fT, a.m13 * fT,
		               a.m20 * fT, a.m21 * fT, a.m22 * fT, a.m23 * fT,
		               a.m30 * fT, a.m31 * fT, a.m32 * fT, a.m33 * fT);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_divf(const cx_mat4 a, const cx_float fT)
{
	if (fT == 0) return cx_mat4_zero();
	return cx_mat4_set(a.m00 / fT, a.m01 / fT, a.m02 / fT, a.m03 / fT,
		               a.m10 / fT, a.m11 / fT, a.m12 / fT, a.m13 / fT,
		               a.m20 / fT, a.m21 / fT, a.m22 / fT, a.m23 / fT,
		               a.m30 / fT, a.m31 / fT, a.m32 / fT, a.m33 / fT);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_mul(const cx_mat4 a, const cx_mat4 b)
{
	return cx_mat4_set(a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30, a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31, a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32, a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33,
		               a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30, a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31, a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32, a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,
		               a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30, a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31, a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32, a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,
		               a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30, a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31, a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32, a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33);
}

CX_API CX_API_INLINE cx_vec4 cx_mat4_vec4_mul(const cx_mat4 a, const cx_vec4 u)
{
	return cx_vec4_set(a.m00 * u.x + a.m01 * u.y + a.m02 * u.z + a.m03 * u.w,
		               a.m10 * u.x + a.m11 * u.y + a.m12 * u.z + a.m13 * u.w,
		               a.m20 * u.x + a.m21 * u.y + a.m22 * u.z + a.m23 * u.w,
		               a.m30 * u.x + a.m31 * u.y + a.m32 * u.z + a.m33 * u.w);
}

CX_API CX_API_INLINE cx_vec4 cx_mat4_vec4_project(const cx_mat4 a, const cx_vec4 u)
{
	cx_vec4 result = cx_mat4_vec4_mul(a, u);

	if (result.w != 0.0) {
		result.x /= result.w;
		result.y /= result.w;
		result.z /= result.w;
	}
	return result;
}

CX_API CX_API_INLINE cx_float cx_mat4_det(const cx_mat4 a)
{
	/* TODO: Implement determinent for mat4 */
	(void) a;
	return 0.0;
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_transpose(const cx_mat4 a)
{
	return cx_mat4_set(a.m00, a.m10, a.m20, a.m30,
		               a.m01, a.m11, a.m21, a.m31,
		               a.m02, a.m12, a.m22, a.m32,
		               a.m03, a.m13, a.m23, a.m33);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_inverse(const cx_mat4 a)
{
	/* TODO: Implement inverse for mat4 */
	(void) a;
	return cx_mat4_identity();
}

CX_API CX_API_INLINE cx_float cx_mat4_trace(const cx_mat4 a)
{
	return a.m00 + a.m11 + a.m22 + a.m33;
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_z(const cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_COS(angle);

	return cx_mat4_set(_cos, -_sin, 0.0, 0.0,
		               _sin,  _cos, 0.0, 0.0,
		               0.0,   0.0,  1.0, 0.0,
		               0.0,   0.0,  0.0, 1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_y(const cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_COS(angle);

	return cx_mat4_set(_cos,  0.0, _sin, 0.0,
                       0.0,   1.0,  0.0, 0.0,
		               -_sin, 0.0, _cos, 0.0,
		               0.0,   0.0, 0.0,  1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_x(const cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_COS(angle);

	return cx_mat4_set(1.0,   0.0,   0.0, 0.0,
                       0.0, _cos,  -_sin, 0.0,
                       0.0, _sin,   _cos, 0.0,
                       0.0, 0.0,    0.0,  1.0);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_euler_zyx(const cx_float psi, const cx_float theta, const cx_float phi)
{
	const cx_mat4 rot_z = cx_mat4_rotation_z(psi);
	const cx_mat4 rot_y = cx_mat4_rotation_y(theta);
	const cx_mat4 rot_x = cx_mat4_rotation_x(phi);

	return cx_mat4_mul(cx_mat4_mul(rot_z, rot_y), rot_x);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_rotation_euler_xyz(const cx_float phi, const cx_float theta, const cx_float psi)
{
	const cx_mat4 rot_x = cx_mat4_rotation_x(phi);
	const cx_mat4 rot_y = cx_mat4_rotation_y(theta);
	const cx_mat4 rot_z = cx_mat4_rotation_z(psi);

	return cx_mat4_mul(cx_mat4_mul(rot_x, rot_y), rot_z);
}

CX_API CX_API_INLINE cx_vec4 cx_mat4_rotate_z(const cx_vec4 u, const cx_float angle)
{
	const cx_mat4 rot_z = cx_mat4_rotation_z(angle);

	return cx_mat4_vec4_mul(rot_z, u);
}

CX_API CX_API_INLINE cx_vec4 cx_mat4_rotate_y(const cx_vec4 u, const cx_float angle)
{
	const cx_mat4 rot_y = cx_mat4_rotation_y(angle);

	return cx_mat4_vec4_mul(rot_y, u);
}

CX_API CX_API_INLINE cx_vec4 cx_mat4_rotate_x(const cx_vec4 u, const cx_float angle)
{
	const cx_mat4 rot_x = cx_mat4_rotation_x(angle);

	return cx_mat4_vec4_mul(rot_x, u);
}

CX_API CX_API_INLINE cx_vec4 cx_mat4_rotate(const cx_vec4 u, const cx_float psi, const cx_float theta, const cx_float phi)
{
	const cx_mat4 rot_z = cx_mat4_rotation_z(psi);
	const cx_mat4 rot_y = cx_mat4_rotation_y(theta);
	const cx_mat4 rot_x = cx_mat4_rotation_x(phi);

	const cx_mat4 rot = cx_mat4_mul(cx_mat4_mul(rot_z, rot_y), rot_x);

	return cx_mat4_vec4_mul(rot, u);
}

CX_API CX_API_INLINE cx_mat4 cx_mat4_from_quat(const cx_quat p)
{
	const cx_float p0 = p.w;
	const cx_float p1 = p.x;
	const cx_float p2 = p.y;
	const cx_float p3 = p.z;

	return cx_mat4_set(2 * (CX_SQ(p0) + CX_SQ(p1)) - 1, 2 * (p1 * p2 - p0 * p3),         2 * (p1 * p3 + p0 * p2),         0.0,
					   2 * (p1 * p2 + p0 * p3),         2 * (CX_SQ(p0) + CX_SQ(p2)) - 1, 2 * (p2 * p3 - p0 * p1),         0.0,
					   2 * (p1 * p3 - p0 * p2),         2 * (p2 * p3 + p0 * p1),         2 * (CX_SQ(p0) + CX_SQ(p3)) - 1, 0.0,
					   0.0,                             0.0,                             0.0,                             1.0);
}

CX_API CX_API_INLINE void cx_mat4_print(const cx_mat4 a)
{
	printf("mat4: ⎡%-6.2f  %6.2f  %6.2f  %6.2f⎤\n"
		   "      ⎢%-6.2f  %6.2f  %6.2f  %6.2f⎥\n"
		   "      ⎢%-6.2f  %6.2f  %6.2f  %6.2f⎥\n"
		   "      ⎣%-6.2f  %6.2f  %6.2f  %6.2f⎦\n",
		   a.m00, a.m01, a.m02, a.m03,
		   a.m10, a.m11, a.m12, a.m13,
		   a.m20, a.m21, a.m22, a.m23,
		   a.m30, a.m31, a.m32, a.m33);
}


CX_API CX_API_INLINE cx_quat cx_quat_set(const cx_float w, const cx_float x, const cx_float y, const cx_float z)
{
	return (cx_quat) {
		.w = w,
		.x = x,
		.y = y,
		.z = z
	};
}

CX_API CX_API_INLINE cx_quat cx_quat_vec3_set(const cx_float w, const cx_vec3 u)
{
	return cx_quat_set(w, u.x, u.y, u.z);
}

CX_API CX_API_INLINE cx_quat cx_quat_vec4_set(const cx_float w, const cx_vec4 u)
{
	return cx_quat_set(w, u.x, u.y, u.z);
}

CX_API CX_API_INLINE cx_quat cx_quat_zero()
{
	return cx_quat_set(0.0, 0.0, 0.0, 0.0);
}

CX_API CX_API_INLINE cx_quat cx_quat_identity()
{
	return cx_quat_set(1.0, 0.0, 0.0, 0.0);
}

CX_API CX_API_INLINE cx_quat cx_quat_negate(const cx_quat p)
{
	return cx_quat_set(-p.w, -p.x, -p.y, -p.z);
}

CX_API CX_API_INLINE cx_quat cx_quat_set_from_axis_anglef3(const cx_float x, const cx_float y, const cx_float z, const cx_float angle)
{
	const cx_vec3 n = cx_vec3_normalize(cx_vec3_set(x, y, z));
	const cx_float _sin = CX_SIN(angle * 0.5);
	const cx_float _cos = CX_COS(angle * 0.5);

	cx_quat q = cx_quat_set(_cos, n.x * _sin, n.y * _sin, n.z * _sin);

	return q;
}

CX_API CX_API_INLINE cx_quat cx_quat_set_from_axis_anglev3(const cx_vec3 axis, const cx_float angle)
{
	return cx_quat_set_from_axis_anglef3(axis.x, axis.y, axis.z, angle);
}

CX_API CX_API_INLINE cx_quat cx_quat_set_from_axis_anglev4(const cx_vec4 axis, const cx_float angle)
{
	return cx_quat_set_from_axis_anglef3(axis.x, axis.y, axis.z, angle);
}

CX_API CX_API_INLINE cx_quat cx_quat_add(const cx_quat p, const cx_quat q)
{
	return (cx_quat) {
		.w = p.w + q.w,
		.x = p.x + q.x,
		.y = p.y + q.y,
		.z = p.z + q.z,
	};
}

CX_API CX_API_INLINE cx_quat cx_quat_sub(const cx_quat p, const cx_quat q)
{
	return (cx_quat) {
		.w = p.w - q.w,
		.x = p.x - q.x,
		.y = p.y - q.y,
		.z = p.z - q.z,
	};
}

CX_API CX_API_INLINE cx_quat cx_quat_mulf(const cx_quat p, const cx_float fT)
{
	return (cx_quat) {
		.w = p.w * fT,
		.x = p.x * fT,
		.y = p.y * fT,
		.z = p.z * fT,
	};
}

CX_API CX_API_INLINE cx_quat cx_quat_divf(const cx_quat p, const cx_float fT)
{
	if (fT == 0.0)	return cx_quat_zero();
	return (cx_quat) {
		.w = p.w / fT,
		.x = p.x / fT,
		.y = p.y / fT,
		.z = p.z / fT,
	};
}

CX_API CX_API_INLINE cx_quat cx_quat_mul(const cx_quat p, const cx_quat q)
{
	return (cx_quat) {
		.w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z,
		.x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y,
		.y = p.w * q.y - p.x * q.z + p.y * q.w + p.z * q.x,
		.z = p.w * q.z + p.x * q.y - p.y * q.x + p.z * q.w
	};
}

CX_API CX_API_INLINE cx_quat cx_quat_normalize(const cx_quat p)
{
  	cx_float mag = cx_quat_mag(p);
  	cx_float mag_inv = (mag > 0) ? 1 / mag : 0.0f;

  	return (cx_quat) {   .w = p.w * mag_inv,
                         .x = p.x * mag_inv,
                         .y = p.y * mag_inv,
                         .z = p.z * mag_inv
  	};
}

CX_API CX_API_INLINE cx_float cx_quat_mag(const cx_quat p)
{
	return CX_SQRT(CX_SQ(p.w) + CX_SQ(p.x) + CX_SQ(p.y) + CX_SQ(p.z));
}

CX_API CX_API_INLINE cx_quat cx_quat_conjugate(const cx_quat p)
{
	return (cx_quat) {
		.w = p.w,
		.x = -p.x,
		.y = -p.y,
		.z = -p.z,
	};
}

CX_API CX_API_INLINE cx_quat cx_quat_inverse(const cx_quat p)
{
	const cx_float mag = cx_quat_mag(p);
	const cx_float mag_inv_sq = (mag == 0.0) ? 0.0 : 1.0 / (mag * mag);

	const cx_quat conj = cx_quat_conjugate(p);

	return cx_quat_mulf(conj, mag_inv_sq);

}

CX_API CX_API_INLINE cx_quat cx_quat_lerp(const cx_quat p, const cx_quat q, const cx_float t)
{
	return cx_quat_add(cx_quat_mulf(p, 1-t), cx_quat_mulf(q, t));
}

CX_API CX_API_INLINE cx_quat cx_quat_nlerp(const cx_quat p, const cx_quat q, const cx_float t)
{
	return cx_quat_normalize(cx_quat_lerp(p, (cx_quat_dot(p, q) < 0) ? cx_quat_negate(q) : q, t));
}

CX_API CX_API_INLINE cx_quat cx_quat_slerp(const cx_quat p, const cx_quat q, const cx_float t)
{
	const cx_float omega = CX_ACOS(cx_quat_dot(p, q));
	const cx_float _sin = CX_SIN(omega);

	const cx_float s0 = CX_SIN((1 - t) * omega) / _sin;
	const cx_float s1 = CX_SIN(t * omega) / _sin;
	return cx_quat_add(cx_quat_mulf(p, s0), cx_quat_mulf(q, s1));
}

CX_API CX_API_INLINE cx_float cx_quat_dot(const cx_quat p, const cx_quat q)
{
	return (p.w * q.w + p.x * q.x + p.y * q.y + p.z * q.z);
}

CX_API CX_API_INLINE cx_vec3 cx_quat_vec3_rotate(const cx_quat p, const cx_vec3 u)
{
	const cx_quat q = cx_quat_vec3_set(0.0, u);
	const cx_quat p_inv = cx_quat_inverse(p);
	const cx_quat r = cx_quat_mul(cx_quat_mul(p, q), p_inv);

	return (cx_vec3) {
		.x = r.x,
		.y = r.y,
		.z = r.z
	};
}

CX_API CX_API_INLINE cx_vec4 cx_quat_vec4_rotate(const cx_quat p, const cx_vec4 u)
{
	const cx_quat q = cx_quat_vec4_set(0.0, u);
	const cx_quat q_inv = cx_quat_inverse(q);
	const cx_quat r = cx_quat_mul(cx_quat_mul(q, p), q_inv);

	return (cx_vec4) {
		.x = r.x,
		.y = r.y,
		.z = r.z,
		.w = 0.0
	};
}

CX_API CX_API_INLINE void cx_quat_print(const cx_quat p)
{
	printf("quat: (%.2f, %.2f, %.2f, %.2f)\n", p.w, p.x, p.y, p.z);
}


/* ------------------------------------------------------------------------------------------------------------ */
/* dft and fft ------------------------------------------------------------------------------------------------ */
/* DFT implementation                                                                                           */
/* eg. say we have a set of signals x[t] then                                                                   */
/* DFT and FFT transforms that signal from time domain x[n] to frequency domain X[k]                            */
/* X[k] = \sum_{n = 0}^{N - 1} x[n] * \exp{\frac{-2πkni}{N}}                                                     */
/* Here: N    = total numbers of samples                                                                        */
/*       x[N] = input signal in time domain                                                                     */
/*       X[N] = output signal in frequency domain                                                               */

CX_API void cx_dft(cx_complex in[], cx_complex out[], int N)
{
  	for (int k = 0; k < N; k++) {
  		cx_complex sum = 0.0f;
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
CX_API void cx_dft_inverse(cx_complex in[], cx_complex out[], int N)
{
  for (int k = 0; k < N; k++) {
    cx_float N_inv = 1.0 / N;
    cx_complex sum = 0.0f;
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
#define cx_ifft	cx_ifft_bit

/* source: https://cp-algorithms.com/algebra/fft.html                                                             */
CX_API void cx_fft_rec(cx_complex in[], cx_complex out[], int N)
{
  CX_ASSERT((N & (N-1)) == 0 && "This fft(Cooley-Tukey FFT) only works for power of two");
  if (N == 1) {
    out[0] = in[0];
    return;
  }

  cx_complex in_a0[N/2];
  cx_complex in_a1[N/2];

  cx_complex out_a0[N/2];
  cx_complex out_a1[N/2];

  for (int k = 0; k < N / 2; k++) {
    in_a0[k] = in[2 * k];
    in_a1[k] = in[2 * k + 1];
  }

  cx_fft_rec(in_a0, out_a0, N/2);
  cx_fft_rec(in_a1, out_a1, N/2);

  cx_float angle = -2.0 * CX_PI / N;
  cx_complex w = 1.0 + I * 0.0;
  // cx_complex wn = CX_CEXP(I * angle);
  cx_complex wn = cos(angle) + I * sin(angle);

  for (int n = 0; n < N / 2; n++) {
    out[n] = out_a0[n] + w * out_a1[n];
    out[n + N/2] = out_a0[n] - w * out_a1[n];
    w *= wn;
  }
}

CX_API void cx_ifft_rec(cx_complex in[], cx_complex out[], int N)
{
  CX_ASSERT((N & (N-1)) == 0 && "This fft inverse only works for power of two");
  if (N == 1) {
    out[0] = in[0];
    return;
  }

  cx_complex in_a0[N/2];
  cx_complex in_a1[N/2];

  cx_complex out_a0[N/2];
  cx_complex out_a1[N/2];

  for (int k = 0; k < N / 2; k++) {
    in_a0[k] = in[2 * k];
    in_a1[k] = in[2 * k + 1];
  }

  cx_ifft_rec(in_a0, out_a0, N/2);
  cx_ifft_rec(in_a1, out_a1, N/2);

  cx_float angle = 2.0 * CX_PI / N;
  cx_complex w = 1.0 + I * 0.0;
  // cx_complex wn = CX_CEXP(I * angle);
  cx_complex wn = cos(angle) + I * sin(angle);

  for (int n = 0; n < N / 2; n++) {
    out[n] = out_a0[n] + w * out_a1[n];
    out[n + N/2] = out_a0[n] - w * out_a1[n];
	out[n] /= 2;
	out[n + N/2] /= 2;
    w *= wn;
  }
}

/* Iterative Cooley–Tukey FFT with Bit-Reversal: https://cp-algorithms.com/algebra/fft.html*/
CX_API void cx_fft_bit(cx_complex in[], cx_complex out[], int N)
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
			cx_complex temp = out[i];
			out[i] = out[j];
			out[j] = temp;
		}
	}

	for (int len = 2; len <= N; len <<= 1) {
		cx_float angle = -2.0f * CX_PI / len;
		/* cx_complex wlen = cexpf(angle * I); */
		cx_complex wlen = cosf(angle) + sinf(angle) * I;
		for (int i = 0; i < N; i += len) {
			cx_complex w = 1.0f + 0.0f * I;
			for (int j = 0; j < len / 2; j++) {
				cx_complex u = out[i + j], v = out[i + j + len/2] * w;
				out[i + j] = u + v;
				out[i + j + len/2] = u - v;
				w = w * wlen;
			}
		}
	}
}

CX_API void cx_ifft_bit(cx_complex in[], cx_complex out[], int N)
{
	CX_ASSERT((N & (N-1)) == 0 && "This fft inverse only works for power of two");
	for (int i = 0; i < N; i++) {
		out[i] = in[i];
	}
	for (int i = 1, j = 0; i < N; i++) {
		int bit = N >> 1;
		for (; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;
		if (i < j) {
			cx_complex temp = out[i];
			out[i] = out[j];
			out[j] = temp;
		}
	}

	for (int len = 2; len <= N; len <<= 1) {
		cx_float angle = 2.0f * CX_PI / len;
		/* cx_complex wlen = CX_CEXP(angle * I); */
		cx_complex wlen = cosf(angle) + sinf(angle) * I;
		for (int i = 0; i < N; i += len) {
			cx_complex w = 1.0f + 0.0f * I;
			for (int j = 0; j < len / 2; j++) {
				cx_complex u = out[i + j], v = out[i + j + len/2] * w;
				out[i + j] = u + v;
				out[i + j + len/2] = u - v;
				w = w * wlen;
			}
		}
	}
	for (int n = 0; n < N; n++) {
		out[n] /= N;
	}
}

/* ------------------------------------------------------------------------------------------------------------ */
/* Numerical ODE solver --------------------------------------------------------------------------------------- */
/* implicit euler  */
CX_API cx_float cx_explicit_euler(cx_float (* f)(cx_float, cx_float), cx_float x, cx_float y, cx_float h)
{
  	cx_float fxy = f(x, y);
  	return (y + h * fxy);
}

/* runge-kutta 2th order -------------------------------------------------------------------------------------- */
CX_API cx_float cx_rk2(cx_float (* f)(cx_float, cx_float), cx_float x, cx_float y, cx_float h)
{
  	cx_float y1 = f(x, y);
  	cx_float y_star = y + h * y1;
  	cx_float y2 = f(x + h, y_star);

  	return y + (0.5 * h * (y1 + y2));
}

/* runge-kutta 4th order -------------------------------------------------------------------------------------- */
CX_API cx_float cx_rk4(cx_float (* f)(cx_float, cx_float), cx_float x, cx_float y, cx_float h)
{
  	cx_float k1 = f(x, y);
  	cx_float k2 = f(x + h/2, y + ((h/2) * k1));
  	cx_float k3 = f(x + h/2, y + ((h/2) * k2));
  	cx_float k4 = f(x + h, y + h * k3);

  	return y + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
}

#endif /* CX_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CAYLIX_H */
