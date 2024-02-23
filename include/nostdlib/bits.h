#ifndef NOSTDLIB_BITS_H_
#define NOSTDLIB_BITS_H_

#include <stdio.h>

#include "nostdlib/io.h"
#include "nostdlib/limits.h"
#include "nostdlib/macros.h"
#include "nostdlib/types.h"

#define NOC_WRITEBITS(__X, __FD)                                               \
    do {                                                                       \
        for (u64 __index = sizeof(__X) * CHAR_BITS; __index > 0; --__index) {  \
            noc_write_char(__FD, (__X) & (1 << (__index - 1)) ? '1' : '0');    \
        }                                                                      \
    } while (0)

#define NOC_PRINTBITS(__X) NOC_WRITEBITS(noc_stdout_fileno, (__X))

#define NOC_PUTBITS(__X)                                                       \
    do {                                                                       \
        NOC_PRINTBITS(__X);                                                    \
        noc_write_char(noc_stdout_fileno, '\n');                               \
    } while (0)

#define MKFLAG(__X) EXPAND(1 << (__X))
#define HASFLAG(__MASK, __X) EXPAND((__MASK) & (__X))
#define ADDFLAG(__MASK, __X) EXPAND((__MASK) |= (__X))
#define RMFLAG(__MASK, __X) ((__MASK) ^= (__X))

#endif // NOCTDLIB_BITS_H_
