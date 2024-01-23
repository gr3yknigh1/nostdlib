#ifndef NOSTDLIB_TYPES_H_
#define NOSTDLIB_TYPES_H_

#include "nostdlib/limits.h"

typedef unsigned char byte;

static_assert(sizeof(byte) == NOC_BYTE_SIZE);

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;
typedef signed long ssize;

static_assert(sizeof(i8) == NOC_I8_BYTES);
static_assert(sizeof(i16) == NOC_I16_BYTES);
static_assert(sizeof(i32) == NOC_I32_BYTES);
static_assert(sizeof(i64) == NOC_I64_BYTES);
static_assert(sizeof(ssize) == NOC_SSIZE_BYTES);

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned long usize;

static_assert(sizeof(u8) == NOC_U8_BYTES);
static_assert(sizeof(u16) == NOC_U16_BYTES);
static_assert(sizeof(u32) == NOC_U32_BYTES);
static_assert(sizeof(u64) == NOC_U64_BYTES);
static_assert(sizeof(usize) == NOC_USIZE_BYTES);

typedef float f32;
typedef double f64;

static_assert(sizeof(f32) == NOC_F32_BYTES);
static_assert(sizeof(f64) == NOC_F64_BYTES);

typedef unsigned int word;

static_assert(sizeof(word) == NOC_WORD_SIZE);

#endif // NOSTDLIB_TYPES_H_
