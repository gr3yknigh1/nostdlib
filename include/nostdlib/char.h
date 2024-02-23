#ifndef NOSTDLIB_CHAR_H_
#define NOSTDLIB_CHAR_H_

#include "nostdlib/macros.h"

NOC_NODISCARD NOC_DEF bool noc_is_digit(char c);
NOC_NODISCARD NOC_DEF bool noc_is_alphabet(char c);
NOC_NODISCARD NOC_DEF bool noc_is_upper(char c);
NOC_NODISCARD NOC_DEF bool noc_is_lower(char c);

#endif // NOSTDLIB_CHAR_H_
