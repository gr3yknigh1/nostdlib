#include "nostdlib/memory.h"

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

NOC_DEF void
noc_memory_set(void *dst, usize size, i8 c) {
    while (size-- > 0) {
        ((char *)dst)[size] = c;
    }
}

NOC_DEF void
noc_memory_copy(void *restrict dst, const void *src, usize size) {
    for (usize i = 0; i < size; ++i) {
        ((char *)dst)[i] = ((char *)src)[i];
    }
}

NOC_DEF const void *
noc_memory_find(const void *p, usize size, i8 value) {
    for (usize i = 0; i < size; ++i) {
        if (((i8 *)p)[i] == value) {
            return p;
        }
    }
    return nullptr;
}
