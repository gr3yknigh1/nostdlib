/*
 * nostdlib's charlib.
 * */
#if !defined(NOSTDLIB_CHAR_H_)
#define NOSTDLIB_CHAR_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

NOC_NODISCARD NOC_DEF bool NOC_IsDigit(char c);
NOC_NODISCARD NOC_DEF bool NOC_IsAlphabet(char c);
NOC_NODISCARD NOC_DEF bool NOC_IsUpper(char c);
NOC_NODISCARD NOC_DEF bool NOC_IsLower(char c);

#endif // NOSTDLIB_CHAR_H_
