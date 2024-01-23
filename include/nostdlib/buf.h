#ifndef NOSTDLIB_BUF_H_
#define NOSTDLIB_BUF_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

typedef struct {
    byte *data;
    usize size;
} noc_buf;

NOC_INLINE noc_buf
noc_buf_init(byte *data, usize size) {
    return LITERAL(noc_buf){
        .data = data,
        .size = size,
    };
}

NOC_INLINE noc_buf
noc_buf_init_0(void) {
    return LITERAL(noc_buf){
        .data = nullptr,
        .size = 0,
    };
}

#endif // NOSTDLIB_BUF_H_
