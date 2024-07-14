#include "nostdlib/buf.h"

NOC_DEF NOC_Buffer
NOC_BufferMake(void) {
    return LITERAL(NOC_Buffer){
        .Data = nullptr,
        .Size = 0,
    };
}

NOC_DEF NOC_Buffer
NOC_BufferMakeEx(byte *data, usize size) {
    return LITERAL(NOC_Buffer){
        .Data = data,
        .Size = size,
    };
}
