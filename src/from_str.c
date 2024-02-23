#include "nostdlib/numeric/from_str.h"

#include "nostdlib/macros.h"
#include "nostdlib/types.h"
#include "nostdlib/rc.h"

// TODO: Handle empty string.
NOC_DEF noc_rc
noc_i32_from_str(const char *str, i32 *out) {
    if (str == nullptr || str[0] == '\0') {
        return RC_UNABLE_TO_READ;
    }

    if (out == nullptr) {
        return RC_UNABLE_TO_WRITE;
    }

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

    *out = num;
    return RC_OK;
}
