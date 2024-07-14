#ifndef NOSTDLIB_IO_H_
#define NOSTDLIB_IO_H_

#include "nostdlib/buf.h"
#include "nostdlib/macros.h"
#include "nostdlib/rc.h"
#include "nostdlib/types.h"

typedef int NOC_FileDescriptor;

extern const NOC_FileDescriptor StdIn;
extern const NOC_FileDescriptor StdOut;
extern const NOC_FileDescriptor StdErr;

NOC_NODISCARD NOC_DEF noc_rc noc_write(NOC_FileDescriptor fd, const byte *data,
                                       usize count, usize *written);
NOC_NODISCARD NOC_DEF noc_rc noc_write_buf(NOC_FileDescriptor fd,
                                           const NOC_Buffer *buf,
                                           usize *written);
NOC_NODISCARD NOC_DEF noc_rc noc_write_cstr(NOC_FileDescriptor fd,
                                            const char *s, usize *written);
NOC_NODISCARD NOC_DEF noc_rc noc_write_char(NOC_FileDescriptor fd, char c);

NOC_DEF noc_rc noc_println(const char *s);
NOC_DEF noc_rc noc_printchar(char c);

#endif // NOSTDLIB_IO_H_
