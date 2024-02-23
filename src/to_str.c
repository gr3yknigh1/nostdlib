#include "nostdlib/numeric/to_str.h"

#include "nostdlib/math/mod.h"
#include "nostdlib/math/round.h"
#include "nostdlib/numeric/abs.h"
#include "nostdlib/numeric/countdigits.h"

// TODO(gr3yknigh1): Remove ccount and replace with pointer
// arithmetic
#define _NOC_SINT_TO_STR_IMPL(__TYPE)                                          \
    _NOC_INT_TO_STR_DEF(__TYPE) {                                              \
        u64 ccount = 0;                                                        \
        bool isnegative = number < 0;                                          \
        char *write_ptr =                                                      \
            buffer + NOC_COUNTDIGITS(number) - 1 + (isnegative ? 1 : 0);       \
        number = NOC_ABS(number);                                              \
                                                                               \
        do {                                                                   \
            int digit = number % 10;                                           \
            *write_ptr-- = digit + '0';                                        \
            ccount++;                                                          \
        } while ((number /= 10) > 0);                                          \
                                                                               \
        if (isnegative) {                                                      \
            *write_ptr-- = '-';                                                \
            ccount++;                                                          \
        }                                                                      \
                                                                               \
        return ccount;                                                         \
    }

_NOC_SINT_TO_STR_IMPL(i16)
_NOC_SINT_TO_STR_IMPL(i32)
_NOC_SINT_TO_STR_IMPL(i64)

#undef _NOC_SINT_TO_STR_IMPL

#define _NOC_UINT_TO_STR_IMPL(__TYPE)                                          \
    _NOC_INT_TO_STR_DEF(__TYPE) {                                              \
        u64 ccount = 0;                                                        \
        char *write_ptr = buffer + NOC_COUNTDIGITS(number) - 1;                \
                                                                               \
        do {                                                                   \
            int digit = number % 10;                                           \
            *write_ptr-- = digit + '0';                                        \
            ccount++;                                                          \
        } while ((number /= 10) > 0);                                          \
                                                                               \
        return ccount;                                                         \
    }

_NOC_UINT_TO_STR_IMPL(u16)
_NOC_UINT_TO_STR_IMPL(u32)
_NOC_UINT_TO_STR_IMPL(u64)

#undef _NOC_UINT_TO_STR_IMPL

#define _NOC_FLT_TO_STR_IMPL(__TYPE)                                           \
    _NOC_FLT_TO_STR_DEF(__TYPE) {                                              \
        char *buffer_write_ptr = buffer;                                       \
                                                                               \
        __TYPE ipart = 0;                                                      \
        __TYPE fpart = NOC_MOD(number, &ipart);                                \
                                                                               \
        buffer_write_ptr += NOC_TO_STR((i64)ipart, buffer_write_ptr);          \
                                                                               \
        if (precision > 0) {                                                   \
            *buffer_write_ptr++ = '.';                                         \
                                                                               \
            while (precision-- > 0) {                                          \
                fpart *= 10;                                                   \
                NOC_MOD(fpart, &ipart);                                        \
                                                                               \
                if ((i64)ipart == 0 && precision > 0) {                        \
                    *buffer_write_ptr++ = '0';                                 \
                }                                                              \
            }                                                                  \
                                                                               \
            buffer_write_ptr +=                                                \
                NOC_TO_STR(NOC_ABS((i64)NOC_ROUND(fpart)), buffer_write_ptr);  \
        }                                                                      \
                                                                               \
        return buffer_write_ptr - buffer;                                      \
    }

_NOC_FLT_TO_STR_IMPL(f32)
_NOC_FLT_TO_STR_IMPL(f64)

#undef _NOC_FLT_TO_STR_IMPL
