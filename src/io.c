#include "nostdlib/io.h"
#include "nostdlib/macros.h"
#include "nostdlib/platform.h"

#ifdef NOC_PLATFORM_LINUX
#include <unistd.h>
#endif

NOC_NODISCARD NOC_DEF noc_rc
noc_write(noc_fileno fd, const byte *data, usize count, usize *written) {
#ifdef NOC_PLATFORM_LINUX
    ssize ret = write(fd.value, data, count);

    if (ret == -1) {
        return RC_UNABLE_TO_WRITE;
    }

    if (written != nullptr) {
        *written = (usize)ret;
    }

    return RC_OK;
#endif // NOC_PLATFORM_LINUX
}
