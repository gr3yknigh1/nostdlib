#include "nostdlib/numeric/flt_charcount.h"

#include "nostdlib/math/mod.h"
#include "nostdlib/numeric/countdigits.h"

#define _NOC_FLT_CHARCOUNT_IMPL(__TYPE)                                        \
    _NOC_FLT_CHARCOUNT_DEF(__TYPE) {                                           \
        u16 count = 0;                                                         \
        __TYPE ipart = 0;                                                      \
        NOC_MOD(number, &ipart);                                               \
        count += NOC_COUNTDIGITS((i64)ipart);                                  \
        if (precision > 0) {                                                   \
            count += 1;                                                        \
            count += precision;                                                \
        }                                                                      \
        return count;                                                          \
    }

_NOC_FLT_CHARCOUNT_IMPL(f32)
_NOC_FLT_CHARCOUNT_IMPL(f64)
