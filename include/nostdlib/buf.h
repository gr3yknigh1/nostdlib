#if !defined(NOSTDLIB_BUF_H_)
#define NOSTDLIB_BUF_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

typedef struct {
    byte *Data;
    usize Size;
} NOC_Buffer;

NOC_DEF NOC_Buffer NOC_BufferMake(void);

NOC_DEF NOC_Buffer NOC_BufferMakeEx(byte *data, usize size);

#endif // NOSTDLIB_BUF_H_
