#include "nostdlib/math/round.h"

#define _NOC_ROUND_IMPL(__TYPE)                                                \
    _NOC_ROUND_DEF(__TYPE) { return }

/*
 * .. note::
 *    Source:
 * https://sourceware.org/git/?p=newlib-cygwin.git;a=blob;f=newlib/libm/common/fdlibm.h
 * */

typedef union {
    float value;
    word word;
} ieee_float_shape_type;

/*
 * Get a 32 bit int from a float.
 * */
#define GET_FLOAT_WORD(i, d)                                                   \
    do {                                                                       \
        ieee_float_shape_type gf_u;                                            \
        gf_u.value = (d);                                                      \
        (i) = gf_u.word;                                                       \
    } while (0)

/*
 * Set a float from a 32 bit int.
 * */
#define SET_FLOAT_WORD(d, i)                                                   \
    do {                                                                       \
        ieee_float_shape_type sf_u;                                            \
        sf_u.word = (i);                                                       \
        (d) = sf_u.value;                                                      \
    } while (0)

/*
 * .. note::
 *     Source:
 * <https://stackoverflow.com/questions/4572556/concise-way-to-implement-round-in-c>
 * */
NOC_DEF f32
noc_f32_round(f32 x) {
    i32 signbit;
    word w;

    /* Most significant word, least significant word. */
    i32 exponent_less_127;

    GET_FLOAT_WORD(w, x);

    /* Extract sign bit. */
    signbit = w & 0x80000000;

    /* Extract exponent field. */
    exponent_less_127 = (i32)((w & 0x7f800000) >> 23) - 127;

    if (exponent_less_127 < 23) {
        if (exponent_less_127 < 0) {
            w &= 0x80000000;
            if (exponent_less_127 == -1) {
                /* Result is +1.0 or -1.0. */
                w |= ((word)127 << 23);
            }
        } else {
            u32 exponent_mask = 0x007fffff >> exponent_less_127;
            if ((w & exponent_mask) == 0)
                /* x has an integral value. */
                return x;

            w += 0x00400000 >> exponent_less_127;
            w &= ~exponent_mask;
        }
    } else {
        if (exponent_less_127 == 128) {
            /* x is NaN or infinite. */
            return x + x;
        } else {
            return x;
        }
    }

    SET_FLOAT_WORD(x, w);
    KEEP(signbit);
    return x;
}
