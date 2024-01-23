#include "nostdlib/numeric/abs.h"

#define _NOC_ABS_IMPL(__TYPE)                                                  \
    _NOC_ABS_DEF(__TYPE) { return x >= 0 ? x : x * -1; }

_NOC_ABS_IMPL(i16)
_NOC_ABS_IMPL(i32)
_NOC_ABS_IMPL(i64)
_NOC_ABS_IMPL(f32)
_NOC_ABS_IMPL(f64)
