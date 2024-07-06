#ifndef NOSTDLIB_IO_H_
#define NOSTDLIB_IO_H_

#include "nostdlib/buf.h"
#include "nostdlib/macros.h"
#include "nostdlib/rc.h"
#include "nostdlib/types.h"

typedef int filefd;

extern const filefd stdfd_in;
extern const filefd stdfd_out;
extern const filefd stdfd_err;

NOC_NODISCARD NOC_DEF noc_rc noc_write(filefd fd, const byte *data, usize count,
                                       usize *written);
NOC_NODISCARD NOC_DEF noc_rc noc_write_buf(filefd fd, const noc_buf_t *buf,
                                           usize *written);
NOC_NODISCARD NOC_DEF noc_rc noc_write_cstr(filefd fd, const char *s,
                                            usize *written);
NOC_NODISCARD NOC_DEF noc_rc noc_write_char(filefd fd, char c);

NOC_DEF noc_rc noc_println(const char *s);
NOC_DEF noc_rc noc_printchar(char c);

#endif // NOSTDLIB_IO_H_
