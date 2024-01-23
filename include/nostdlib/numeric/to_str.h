#ifndef NOSTDLIB_NUMERIC_TO_STR_H_
#define NOSTDLIB_NUMERIC_TO_STR_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

// noc_to_str :: (<number>, <buffer>, [precision])
#define NOC_TO_STR(__X, ...)                                                   \
    _Generic((__X),                                                            \
        i16: _NOC_TO_STR_NAME(i16),                                            \
        i32: _NOC_TO_STR_NAME(i32),                                            \
        i64: _NOC_TO_STR_NAME(i64),                                            \
        u16: _NOC_TO_STR_NAME(u16),                                            \
        u32: _NOC_TO_STR_NAME(u32),                                            \
        u64: _NOC_TO_STR_NAME(u64),                                            \
        f32: _NOC_TO_STR_NAME(f32),                                            \
        f64: _NOC_TO_STR_NAME(f64),                                            \
        default: _NOC_TO_STR_NAME(i32))(__X, __VA_ARGS__)

#define _NOC_TO_STR_NAME(__TYPE) noc_##__TYPE##_to_str

#define _NOC_INT_TO_STR_DEF(__TYPE)                                            \
    NOC_DEF usize _NOC_TO_STR_NAME(__TYPE)(__TYPE number, char *buffer)

#define _NOC_FLT_TO_STR_DEF(__TYPE)                                            \
    NOC_DEF usize _NOC_TO_STR_NAME(__TYPE)(__TYPE number, char *buffer,        \
                                           u8 precision)

_NOC_INT_TO_STR_DEF(i16);
_NOC_INT_TO_STR_DEF(i32);
_NOC_INT_TO_STR_DEF(i64);
_NOC_INT_TO_STR_DEF(u16);
_NOC_INT_TO_STR_DEF(u32);
_NOC_INT_TO_STR_DEF(u64);
_NOC_FLT_TO_STR_DEF(f32);
_NOC_FLT_TO_STR_DEF(f64);

#endif // NOSTDLIB_NUMERIC_TO_STR_H_
