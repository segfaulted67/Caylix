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

#ifdef CX_IMPLEMENTATION

#define CX_VERSION  "1.0.1"

/* Suppress "unused variable" warning */
/* Example:                           */
/* void something(int a) {            */
/* ...                                */
/* CX_UNUSED_VAR(a);                  */
/* }                                  */
#define CX_UNUSED_VAR(x)  ((void)(x))

/* typecast float/double as cx_float */
#ifndef cx_float
#   ifdef CX_DOUBLE_PRECISION_FLOAT
#     define cx_float double
#   else
#     define cx_float float
#   endif
#endif

/* typecast cx_float complex as cx_complex */
#ifndef cx_complex
#   include <complex.h>
/* https://learn.microsoft.com/en-us/cpp/c-runtime-library/complex-math-support?view=msvc-170 */
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

/* A macro for absolute value. eg: CX_ABS(69.0) --> 69.0 , CX_ABS(-69.0) -> 69.0 */
#define CX_ABS(x)   ((cx_float)fabs(x))
/* A macro for complex absolute values */
#define CX_CABS(x)  cabs(x)
/* A macro for complex exponentials */
#define CX_CEXP(x)  cexp(x)
/* A macro for square root*/
#define CX_SQRT(x)  ((cx_float)sqrt(x))
/* A macro for sin */
#define CX_SIN(x)  ((cx_float)sin(x))
/* A macro for cos */
#define CX_COS(x)  ((cx_float)cos(x))
/* A macro for tan */
#define CX_TAN(x)  ((cx_float)tan(x))
/* A macro for cot */
#define CX_COT(x)  (1.0 / CX_TAN(x))
/* A macro for sec */
#define CX_SEC(x)  (1.0 / CX_COS(x))
/* A macro for cosec */
#define CX_CSC(x)  (1.0 / CX_SIN(x))

/* A macro for sin inverse or asin */
#define CX_ASIN(x)  ((cx_float)asin(x))
/* A macro for cos inverse or acos */
#define CX_ACOS(x)  ((cx_float)acos(x))
/* A macro for tan inverse or atan */
#define CX_ATAN(x)  ((cx_float)atan(x))

/* Safely divides x by y; returns INFINITY if y == 0 */
/* Example: CX_SAFE_DIVIDE(5.0, 0.0); --> inf        */
/*          CX_SAFE_DIVIDE(5.0, 5.0); --> 1.0        */
#define CX_SAFE_DIVIDE(x, y)  ((CX_ABS((y)) <= CX_EPSILON) ? (((x) > 0) ? INFINITY : -INFINITY) : (x) / (y))

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

static CX_API_INLINE cx_float cx_lerp(cx_float a, cx_float b, cx_float t)
{
	return a + t * (b - a);
}

static CX_API_INLINE cx_float cx_clamp(cx_float value, cx_float min, cx_float max)
{
	if(min == max)  return min;
	if(value < min) return min;
	if(value > max) return max;

	return value;
}

/* ------------------------------------------------------------------------------------------------------------ */
/* forward decleration ---------------------------------------------------------------------------------------- */
typedef struct cx_vec2 cx_vec2;
typedef struct cx_vec3 cx_vec3;
typedef struct cx_vec4 cx_vec4;
typedef struct cx_mat2 cx_mat2;
typedef struct cx_mat3 cx_mat3;
typedef struct cx_mat4 cx_mat4;
typedef struct cx_quaternion cx_quaternion;

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
CX_API CX_API_INLINE cx_vec2 cx_vec2_normalize(const cx_vec2 u);                               /* Returns the norm of a vec2 */
CX_API CX_API_INLINE cx_float cx_vec2_mag(const cx_vec2 u);                                    /* Returns the magnitude of a vec2 */

CX_API CX_API_INLINE cx_vec2 cx_vec2_rotate(const cx_vec2 u, cx_float angle);                  /* Returns the vector rotated with given angle */
CX_API CX_API_INLINE cx_float cx_vec2_angle(const cx_vec2 u, const cx_vec2 v);
CX_API CX_API_INLINE cx_vec2 cx_vec2_lerp(const cx_vec2 u, const cx_vec2 v, const cx_float t);
CX_API CX_API_INLINE cx_vec2 cx_vec2_proj(const cx_vec2 u, const cx_vec2 v);
CX_API CX_API_INLINE cx_vec2 cx_vec2_reflect(const cx_vec2 u, const cx_vec2 n);

CX_API CX_API_INLINE void cx_vec2_print(const cx_vec2 u);                                      /* Print vec2 */

/* cx_vec3 ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_vec3 cx_vec3_set(cx_float x, cx_float y, cx_float z);                  /* Set a vec3 with x, y */
CX_API CX_API_INLINE cx_vec3 cx_vec3_zero();                                                   /* Returns zero vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_random();                                                 /* Set vec3 with random vaules */

CX_API CX_API_INLINE cx_vec3 cx_vec3_negate(cx_vec3 u);                                        /* Returns the negation of a vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_add(const cx_vec3 u, const cx_vec3 v);                    /* Returns the addition of two vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_addf(const cx_vec3 u, const cx_float fT);                 /* Returns the addition of a vec3 with a scalar eg. cx_vec3 u = <9.0f, 10.0f, 0.5f>, fT = 10, -> <19.0f, 20.0f, 10.5f> */
CX_API CX_API_INLINE cx_vec3 cx_vec3_sub(const cx_vec3 u, const cx_vec3 v);                    /* Returns the subtraction of two vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_subf(const cx_vec3 u, const cx_float fT);                 /* Returns the subtraction of a vec3 with a scalar eg. cx_vec3 u = <9.0f, 10.0f, 0.5f>, fT = 10, -> <19.0f, 20.0f, 10.5f> */
CX_API CX_API_INLINE cx_vec3 cx_vec3_mulf(const cx_vec3 u, const cx_float fT);                 /* Returns the scalar multiplication of a vec3. eg: u = <1.0f, 3.0f, 0.5f> and f = 3.0f => <3.0f, 9.0f, 1.5f> */
CX_API CX_API_INLINE cx_vec3 cx_vec3_divf(const cx_vec3 u, const cx_float fT);                 /* Returns the scalar division of a vec3, eg: u = <0.0f, 10.0f, 50.0f> and f = 5.0f => <0.0f, 2.0f, 10.0f> */

CX_API CX_API_INLINE cx_float cx_vec3_dot(const cx_vec3 u, const cx_vec3 v);                   /* Returns the dot product b/w two vec3 */
CX_API CX_API_INLINE cx_vec3 cx_vec3_cross(const cx_vec3 u, const cx_vec3 v);                  /* Returns the cross product b/w two vec3 */

CX_API CX_API_INLINE cx_vec3 cx_vec3_normalize(const cx_vec3 u);                               /* Returns the norm of a vec3 */
CX_API CX_API_INLINE cx_float cx_vec3_mag(const cx_vec3 u);                                    /* Returns the magnitude of a vec3 */
CX_API CX_API_INLINE cx_float cx_vec3_mag_sq(const cx_vec3 u);                                 /* Returns the square of the magnitude of a vec3 */
CX_API CX_API_INLINE cx_float cx_vec3_angle(const cx_vec3 u, const cx_vec3 v);

CX_API CX_API_INLINE void cx_vec3_print(const cx_vec3 u);                                      /* Print vec3 */

/* cx_vec4 ---------------------------------------------------------------------------------------------------- */
CX_API CX_API_INLINE cx_vec4 cx_vec4_set(cx_float x, cx_float y, cx_float z, cx_float w);
CX_API CX_API_INLINE cx_vec4 cx_vec4_zero();
CX_API CX_API_INLINE cx_vec4 cx_vec4_random();
CX_API CX_API_INLINE cx_vec4 cx_vec4_negate(cx_vec4 u);
CX_API CX_API_INLINE cx_vec4 cx_vec4_add(const cx_vec4 u, const cx_vec4 v);
CX_API CX_API_INLINE cx_vec4 cx_vec4_addf(const cx_vec4 u, cx_float fT);
CX_API CX_API_INLINE cx_vec4 cx_vec4_sub(const cx_vec4 u, const cx_vec4 v);
CX_API CX_API_INLINE cx_vec4 cx_vec4_subf(const cx_vec4 u, cx_float fT);
CX_API CX_API_INLINE cx_vec4 cx_vec4_mulf(const cx_vec4 u, cx_float fT);
CX_API CX_API_INLINE cx_vec4 cx_vec4_divf(const cx_vec4 u, const cx_float fT);

CX_API CX_API_INLINE cx_float cx_vec4_dot(const cx_vec4 u, const cx_vec4 v);
CX_API CX_API_INLINE cx_vec4 cx_vec4_cross(const cx_vec4 u, const cx_vec4 v);

CX_API CX_API_INLINE cx_vec4 cx_vec4_normalize(const cx_vec4 u);
CX_API CX_API_INLINE cx_float cx_vec4_mag(const cx_vec4 u);

CX_API CX_API_INLINE void cx_vec4_print(const cx_vec4 u);



/* ------------------------------------------------------------------------------------------------------------ */
/* cx_vec2 ---------------------------------------------------------------------------------------------------- */
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
	return cx_vec3_set(0.0f, 0.0f, 0.0f);
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
CX_API CX_API_INLINE bool cx_mat2_is_orhtogonal(const cx_mat2 a);

CX_API CX_API_INLINE void cx_mat2_print(const cx_mat2 a);


CX_API CX_API_INLINE cx_mat2 cx_mat2_set(const cx_float m00, const cx_float m01,
										 const cx_float m10, const cx_float m11)
{
	return (cx_mat2) {
		m00, m01,
		m10, m11
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
	return (cx_mat2) {
		a.m00 * b.m00 + a.m01 * b.m10, a.m00 * b.m01 + a.m01 * b.m11,
		a.m10 * b.m00 + a.m11 * b.m10, a.m10 * b.m01 + a.m11 * b.m11
	};
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_mulf(const cx_mat2 a, const cx_float fT)
{
	return (cx_mat2) {
		a.m00 * fT, a.m01 * fT,
		a.m10 * fT, a.m11 * fT
	};
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_divf(const cx_mat2 a, const cx_float fT)
{
	if (fT == 0) {
		return cx_mat2_zero();
	}

	return (cx_mat2) {
		a.m00 / fT, a.m01 / fT,
		a.m10 / fT, a.m11 / fT
	};
}

CX_API CX_API_INLINE cx_vec2 cx_mat2_vec2_mul(const cx_mat2 a, const cx_vec2 u)
{
	return (cx_vec2) {
		a.m00 * u.x + a.m01 * u.y,
		a.m10 * u.x + a.m11 * u.y
	};
}

CX_API CX_API_INLINE cx_float cx_mat2_det(const cx_mat2 a)
{
	return a.m00 * a.m11 - a.m01 * a.m10;
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_transpose(const cx_mat2 a)
{
	return (cx_mat2) {
		a.m00, a.m10,
		a.m01, a.m11
	};
}

CX_API CX_API_INLINE cx_mat2 cx_mat2_inverse(const cx_mat2 a)
{
	const cx_float det = cx_mat2_det(a);
	if (det == 0) return cx_mat2_zero();

	return (cx_mat2) {
		 a.m11 / det, -a.m01 / det,
		-a.m10 / det,  a.m00 / det
	};
}

CX_API CX_API_INLINE cx_float cx_mat2_trace(const cx_mat2 a)
{
	return a.m00 + a.m11;
}

CX_API CX_API_INLINE cx_vec2 cx_mat2_rotate(const cx_vec2 u, const cx_float angle)
{
	const cx_float _sin = CX_SIN(angle);
	const cx_float _cos = CX_SIN(angle);

	cx_mat2 rotation_matrix = cx_mat2_set(_cos, -_sin,
										  _sin,  _cos);

	return cx_mat2_vec2_mul(rotation_matrix, u);
}

CX_API CX_API_INLINE cx_float cx_mat2_angle(const cx_mat2 a)
{
	return 2 * CX_ATAN(a.m10 / (1 + a.m00));
}

CX_API CX_API_INLINE bool cx_mat2_equals(const cx_mat2 a, const cx_mat2 b)
{
	return (CX_FLOAT_EQUALS(a.m00, b.m00) && CX_FLOAT_EQUALS(a.m01, b.m01) &&
			CX_FLOAT_EQUALS(a.m10, b.m10) && CX_FLOAT_EQUALS(a.m11, b.m11));
}

CX_API CX_API_INLINE bool cx_mat2_is_orhtogonal(const cx_mat2 a)
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

CX_API CX_API_INLINE void cx_mat3_print(const cx_mat3 a);


CX_API CX_API_INLINE void cx_mat3_print(const cx_mat3 a)
{
	printf("mat3: ⎡%-6.2f  %6.2f %6.2f⎤\n"
		   "      ⎢%-6.2f  %6.2f %6.2f⎥\n"
		   "      ⎣%-6.2f  %6.2f %6.2f⎦\n",
		   a.m00, a.m01, a.m02,
		   a.m10, a.m11, a.m12,
		   a.m20, a.m21, a.m22);
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
#define cx_inv_fft	cx_inv_fft_bit

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

CX_API void cx_inv_fft_rec(cx_complex in[], cx_complex out[], int N)
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

  cx_inv_fft_rec(in_a0, out_a0, N/2);
  cx_inv_fft_rec(in_a1, out_a1, N/2);

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

CX_API void cx_inv_fft_bit(cx_complex in[], cx_complex out[], int N)
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
