#include "nostdlib/char.h"
#include "nostdlib/macros.h"

NOC_NODISCARD NOC_DEF bool
NOC_IsDigit(char c) {
    return INRANGE('0', c, '9');
}

NOC_NODISCARD NOC_DEF bool
NOC_IsAlphabet(char c) {
    return INRANGE('a', c, 'Z');
}

NOC_NODISCARD NOC_DEF bool
NOC_IsUpper(char c) {
    return INRANGE('A', c, 'Z');
}

NOC_NODISCARD NOC_DEF bool
NOC_IsLower(char c) {
    return INRANGE('a', c, 'z');
}
