#ifndef NOSTDLIB_CHAR_H_
#define NOSTDLIB_CHAR_H_

#include "nostdlib/macros.h"

NOC_INLINE bool
noc_is_digit(char c) {
    return INRANGE('0', c, '9');
}

NOC_INLINE bool
noc_is_alphabet(char c) {
    return INRANGE('a', c, 'Z');
}

NOC_INLINE bool
noc_is_upper(char c) {
    return INRANGE('A', c, 'Z');
}

NOC_INLINE bool
noc_is_lower(char c) {
    return INRANGE('a', c, 'z');
}

#endif // NOSTDLIB_CHAR_H_
