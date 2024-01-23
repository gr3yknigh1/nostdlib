#ifndef NOSTDLIB_MATH_MOD_H_
#define NOSTDLIB_MATH_MOD_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

#define _NOC_MOD_NAME(__TYPE) noc_##__TYPE##_mod
#define _NOC_MOD_DEF(__TYPE)                                                   \
    __TYPE _NOC_MOD_NAME(__TYPE)(__TYPE x, __TYPE * out_ipart)

#define NOC_MOD(__X, __OUT_IPART_PTR)                                          \
    _Generic((__X),                                                            \
        f32: _NOC_MOD_NAME(f32),                                               \
        f64: _NOC_MOD_NAME(f64),                                               \
        default: _NOC_MOD_NAME(f32))(__X, __OUT_IPART_PTR)

NOC_DEF _NOC_MOD_DEF(f32);
NOC_DEF _NOC_MOD_DEF(f64);

#endif // NOSTDLIB_MATH_MOD_H_
