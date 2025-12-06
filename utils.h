#ifndef CX_UTILS_H
#define CX_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define NUM_ARGS(type, ...)   (sizeof((type []){ __VA_ARGS__ }) / sizeof(type))


#endif // CX_UTILS_H
