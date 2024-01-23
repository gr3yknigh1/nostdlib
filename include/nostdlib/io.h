#ifndef NOSTDLIB_IO_H_
#define NOSTDLIB_IO_H_

#include "nostdlib/buf.h"
#include "nostdlib/macros.h"
#include "nostdlib/rc.h"
#include "nostdlib/string.h"
#include "nostdlib/types.h"

typedef struct {
    int value;
} noc_fileno;

NOC_DEF noc_rc noc_write(noc_fileno fd, const byte *data, usize count,
                         usize *written);

NOC_INLINE noc_rc
noc_write_buf(noc_fileno fd, const noc_buf *buf, usize *written) {
    return noc_write(fd, buf->data, buf->size, written);
}

NOC_INLINE noc_rc
noc_write_cstr(noc_fileno fd, const char *s, usize *written) {
    return noc_write(fd, (const byte *)s, noc_string_len(s), written);
}

#endif // NOSTDLIB_IO_H_
