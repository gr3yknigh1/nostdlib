#include "nostdlib/io.h"
#include "nostdlib/macros.h"
#include "nostdlib/platform.h"
#include "nostdlib/string.h"

#if defined(NOC_PLATFORM_LINUX)
#include <unistd.h>

#include "nostdlib/sys/posix.h"
const FileDescriptor StdIn = NOC_POSIX_FD_STDIN;
const FileDescriptor StdOut = NOC_POSIX_FD_STDOUT;
const FileDescriptor StdErr = NOC_POSIX_FD_STDERR;
#endif

NOC_NODISCARD NOC_DEF noc_rc
noc_write(FileDescriptor fd, const byte *data, usize count, usize *written) {
#ifdef NOC_PLATFORM_LINUX
    ssize ret = write(fd, data, count);

    if (ret == -1) {
        return RC_UNABLE_TO_WRITE;
    }

    if (written != nullptr) {
        *written = (usize)ret;
    }

    return RC_OK;
#endif // NOC_PLATFORM_LINUX
}

NOC_NODISCARD NOC_DEF noc_rc
noc_write_buf(FileDescriptor fd, const noc_buf_t *buf, usize *written) {
    return noc_write(fd, buf->data, buf->size, written);
}

NOC_NODISCARD NOC_DEF noc_rc
noc_write_cstr(FileDescriptor fd, const char *s, usize *written) {
    return noc_write(fd, (const byte *)s, noc_string_len(s), written);
}

NOC_NODISCARD NOC_DEF noc_rc
noc_write_char(FileDescriptor fd, char c) {
    return noc_write(fd, (const byte *)&c, 1, nullptr);
}

NOC_NODISCARD NOC_DEF noc_rc
noc_print(const char *s) {
    return noc_write(StdOut, (const byte *)s, noc_string_len(s), nullptr);
}

NOC_DEF noc_rc
noc_printchar(char c) {
    noc_rc ret = noc_write_char(StdOut, c);
    if (ret == RC_OK) {
        return noc_write_char(StdOut, '\n');
    }
    return ret;
}

NOC_DEF noc_rc
noc_println(const char *s) {
    noc_rc ret =
        noc_write(StdOut, (const byte *)s, noc_string_len(s), nullptr);
    if (ret == RC_OK) {
        return noc_write_char(StdOut, '\n');
    }
    return ret;
}
