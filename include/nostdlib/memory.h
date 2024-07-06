#if !defined(NOSTDLIB_MEMORY_H_)
#define NOSTDLIB_MEMORY_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

NOC_DEF void noc_memory_zero(void *dst, usize size);

NOC_DEF void noc_memory_set(void *dst, usize size, i8 value);

NOC_DEF void noc_memory_copy(void *restrict dst, const void *src, usize size);

NOC_DEF const void *noc_memory_find(const void *p, usize size, i8 value);

#endif // NOSTDLIB_MEMORY_H_
