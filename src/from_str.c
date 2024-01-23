#include "nostdlib/numeric/from_str.h"

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

// TODO: Handle empty string
NOC_DEF i32
noc_i32_from_str(const char *str) {
    i32 num = 0;
    i32 i = 0;
    bool isnegative = false;
    if (str[i] == '-') {
        isnegative = true;
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9')) {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if (isnegative)
        num = -1 * num;
    return num;
}
