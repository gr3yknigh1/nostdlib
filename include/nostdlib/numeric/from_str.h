#ifndef NOSTDLIB_NUMERIC_FROM_STR_H_
#define NOSTDLIB_NUMERIC_FROM_STR_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"
#include "nostdlib/rc.h"

#define NOC_FROM_STR(__X)                                                      \
    _Generic((__X),                                                            \
        i16: noc_i32_from_str,                                                 \
        i32: noc_i32_from_str,                                                 \
        i32: noc_i32_from_str,                                                 \
        default: noc_i32_from_str)(__X)
// FIXME: Add other generics.

NOC_DEF noc_rc noc_i32_from_str(const char *str, i32 *out);

#endif // NOSTDLIB_NUMERIC_FROM_STR_H_
