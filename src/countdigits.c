#include "nostdlib/numeric/countdigits.h"

#define _NOC_COUNTDIGITS_IMPL(__TYPE)                                          \
    _NOC_COUNTDIGITS_DEF(__TYPE) {                                             \
        if (n == 0)                                                            \
            return 1;                                                          \
        u64 count = 0;                                                         \
        while (n != 0) {                                                       \
            n = n / 10;                                                        \
            ++count;                                                           \
        }                                                                      \
        return count;                                                          \
    }

_NOC_COUNTDIGITS_IMPL(i16)
_NOC_COUNTDIGITS_IMPL(i32)
_NOC_COUNTDIGITS_IMPL(i64)
_NOC_COUNTDIGITS_IMPL(u16)
_NOC_COUNTDIGITS_IMPL(u32)
_NOC_COUNTDIGITS_IMPL(u64)
