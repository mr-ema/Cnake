#ifndef CNAKE_TYPES_H
#define CNAKE_TYPES_H

/* Zig like types */

#include <stddef.h>
#include <stdint.h>

/* Redefined types */
#define nil ((void *)0)

/* Unsigned int types */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t ui64;
typedef size_t usize;

/* Signed int types */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef long isize;

/* Floats */
typedef float f32;
typedef double f64;

#endif
