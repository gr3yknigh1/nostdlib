#include "nostdlib/char.h"
#include "nostdlib/macros.h"

NOC_NODISCARD NOC_DEF bool
noc_is_digit(char c) {
    return INRANGE('0', c, '9');
}

NOC_NODISCARD NOC_DEF bool
noc_is_alphabet(char c) {
    return INRANGE('a', c, 'Z');
}

NOC_NODISCARD NOC_DEF bool
noc_is_upper(char c) {
    return INRANGE('A', c, 'Z');
}

NOC_NODISCARD NOC_DEF bool
noc_is_lower(char c) {
    return INRANGE('a', c, 'z');
}

