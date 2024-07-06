#ifndef NOSTDLIB_BUF_H_
#define NOSTDLIB_BUF_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

typedef struct {
    byte *data;
    usize size;
} noc_buf_t;

/*
 * Initializes empty buffer.
 * */
NOC_DEF noc_buf_t noc_buf_init(void);

NOC_DEF noc_buf_t noc_buf_init_ex(byte *data, usize size);

#endif // NOSTDLIB_BUF_H_
