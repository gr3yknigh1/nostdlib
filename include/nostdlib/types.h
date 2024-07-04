#if !defined(NOSTDLIB_TYPES_H)
#define NOSTDLIB_TYPES_H

#include "nostdlib/macros.h"
#include "nostdlib/limits.h"

#if !defined (__cplusplus)
typedef _Bool bool;
#endif

typedef unsigned char byte;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;
typedef signed long ssize;

static_assert(sizeof(i8) == I8_BYTES, "");
static_assert(sizeof(i16) == I16_BYTES, "");
static_assert(sizeof(i32) == I32_BYTES, "");
static_assert(sizeof(i64) == I64_BYTES, "");
static_assert(sizeof(ssize) == SSIZE_BYTES, "");

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned long usize;

static_assert(sizeof(u8) == U8_BYTES, "");
static_assert(sizeof(u16) == U16_BYTES, "");
static_assert(sizeof(u32) == U32_BYTES, "");
static_assert(sizeof(u64) == U64_BYTES, "");
static_assert(sizeof(usize) == USIZE_BYTES, "");

typedef float f32;
typedef double f64;

static_assert(sizeof(f32) == F32_BYTES, "");
static_assert(sizeof(f64) == F64_BYTES, "");

typedef unsigned int word;

static_assert(sizeof(word) == WORD_SIZE, "");

#endif // NOSTDLIB_TYPES_H
