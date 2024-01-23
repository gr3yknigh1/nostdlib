#ifndef NOSTDLIB_NUMERIC_COUNTDIGITS_H_
#define NOSTDLIB_NUMERIC_COUNTDIGITS_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

#define NOC_COUNTDIGITS(__X)                                                   \
    _Generic((__X),                                                            \
        i16: _NOC_COUNTDIGITS_NAME(i16),                                       \
        i32: _NOC_COUNTDIGITS_NAME(i32),                                       \
        i64: _NOC_COUNTDIGITS_NAME(i64),                                       \
        u16: _NOC_COUNTDIGITS_NAME(u16),                                       \
        u32: _NOC_COUNTDIGITS_NAME(u32),                                       \
        u64: _NOC_COUNTDIGITS_NAME(u64),                                       \
        default: _NOC_COUNTDIGITS_NAME(i32))(__X)

#define _NOC_COUNTDIGITS_NAME(__TYPE) noc_##__TYPE##_countdigits
#define _NOC_COUNTDIGITS_DEF(__TYPE)                                           \
    NOC_DEF u64 _NOC_COUNTDIGITS_NAME(__TYPE)(__TYPE n)

_NOC_COUNTDIGITS_DEF(i16);
_NOC_COUNTDIGITS_DEF(i32);
_NOC_COUNTDIGITS_DEF(i64);
_NOC_COUNTDIGITS_DEF(u16);
_NOC_COUNTDIGITS_DEF(u32);
_NOC_COUNTDIGITS_DEF(u64);

#endif // NOSTDLIB_NUMERIC_COUNTDIGITS_H_
