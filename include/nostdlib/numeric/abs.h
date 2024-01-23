#ifndef NOSTDLIB_NUMERIC_ABS_H_
#define NOSTDLIB_NUMERIC_ABS_H_

#include "nostdlib/types.h"

#define NOC_ABS(__X)                                                           \
    _Generic((__X),                                                            \
        i16: _NOC_ABS_NAME(i16),                                               \
        i32: _NOC_ABS_NAME(i32),                                               \
        i64: _NOC_ABS_NAME(i64),                                               \
        f32: _NOC_ABS_NAME(f32),                                               \
        f64: _NOC_ABS_NAME(f64),                                               \
        default: _NOC_ABS_NAME(i32))(__X)

#define _NOC_ABS_NAME(__TYPE) noc_##__TYPE##_abs
#define _NOC_ABS_DEF(__TYPE) __TYPE _NOC_ABS_NAME(__TYPE)(__TYPE x)

extern _NOC_ABS_DEF(i16);
extern _NOC_ABS_DEF(i32);
extern _NOC_ABS_DEF(i64);
extern _NOC_ABS_DEF(f32);
extern _NOC_ABS_DEF(f64);

#endif // NOSTDLIB_NUMERIC_ABS_H_
