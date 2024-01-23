#ifndef NOSTDLIB_NUMERIC_FLT_CHARCOUNT_H_
#define NOSTDLIB_NUMERIC_FLT_CHARCOUNT_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

/*
 * Returns count of characters which may occupy floating-point number
 * */
#define NOC_FLT_CHARCOUNT(__X, __PRECISION)                                    \
    _Generic((__X),                                                            \
        f32: _NOC_FLT_CHARCOUNT_NAME(f32),                                     \
        f64: _NOC_FLT_CHARCOUNT_NAME(f64),                                     \
        default: _NOC_FLT_CHARCOUNT_NAME(f32))(__X, __PRECISION)

#define _NOC_FLT_CHARCOUNT_NAME(__TYPE) noc_##__TYPE##_charcount

#define _NOC_FLT_CHARCOUNT_DEF(__TYPE)                                         \
    NOC_DEF u16 _NOC_FLT_CHARCOUNT_NAME(__TYPE)(__TYPE number, u8 precision)

_NOC_FLT_CHARCOUNT_DEF(f32);
_NOC_FLT_CHARCOUNT_DEF(f64);

#endif // NOSTDLIB_NUMERIC_FLT_CHARCOUNT_H_
