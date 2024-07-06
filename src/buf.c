#include "nostdlib/buf.h"

NOC_DEF noc_buf_t
noc_buf_init(void) {
    return LITERAL(noc_buf_t){
        .data = nullptr,
        .size = 0,
    };
}

NOC_DEF noc_buf_t
noc_buf_init_ex(byte *data, usize size) {
    return LITERAL(noc_buf_t){
        .data = data,
        .size = size,
    };
}
