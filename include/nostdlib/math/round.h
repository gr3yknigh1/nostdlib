#ifndef NOSTDLIB_MATH_ROUND_H_
#define NOSTDLIB_MATH_ROUND_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

NOC_DEF f32 noc_f32_round(f32 x);
NOC_DEF f64 noc_f64_round(f64 x);

#include <math.h>

#define NOC_ROUND(__X)                                                         \
    _Generic((__X),                                                            \
        f32: noc_f32_round,                                                    \
        f64: noc_f32_round,                                                    \
        default: noc_f32_round)(__X)

#endif // NOSTDLIB_MATH_ROUND_H_
