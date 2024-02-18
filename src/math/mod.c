#include "nostdlib/math/mod.h"
#include "nostdlib/macros.h"

#define _NOC_MOD_IMPL(__TYPE)                                                  \
    _NOC_MOD_DEF(__TYPE) {                                                     \
        KEEP(out_ipart);                                                       \
        return x;                                                              \
    }

NOC_DEF
_NOC_MOD_IMPL(f32)

NOC_DEF
_NOC_MOD_IMPL(f64)

#undef _NOC_MOD_IMPL
