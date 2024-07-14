#include "nostdlib/memory.h"

#include "nostdlib/macros.h"
#include "nostdlib/platform.h"
#include "nostdlib/sys.h"
#include "nostdlib/types.h"

#if defined(NOC_PLATFORM_WINDOWS)
#include <Windows.h>
#endif

#if defined(NOC_PLATFORM_LINUX)
#include <sys/mman.h>
#endif

NOC_DEF void
noc_memory_zero(void *dst, usize size) {
    while (size-- > 0) {
        ((char *)dst)[size] = 0;
    }
}

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

NOC_DEF usize
NOC_AlignToPageSize(usize size) {
    usize pageSize = NOC_GetPageSize();
    usize aligned = NOC_ALIGN_TO(size, pageSize);
    return aligned;
}

NOC_DEF NOC_Arena
NOC_ArenaMake(usize size) {
    void *data = NULL;
    size = NOC_AlignToPageSize(size);

#if defined(NOC_PLATFORM_LINUX)
    data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
                -1, 0);
#elif defined(NOC_PLATFORM_WINDOWS)
    data = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#endif

    return (NOC_Arena){
        .Data = data,
        .Capacity = size,
        .Occupied = 0,
    };
}

NOC_DEF void *
NOC_ArenaAlloc(NOC_Arena *arena, usize size) {
    if (arena == NULL || arena->Data == NULL) {
        return NULL;
    }

    if (arena->Occupied + size > arena->Capacity) {
        return NULL;
    }

    void *data = ((byte *)arena->Data) + arena->Occupied;
    arena->Occupied += size;
    return data;
}

NOC_DEF void
NOC_ArenaFree(NOC_Arena *arena) {
    if (arena == NULL || arena->Data == NULL) {
        return;
    }

#if defined(NOC_PLATFORM_WINDOWS)
    VirtualFree(arena->Data, 0, MEM_RELEASE);
#elif defined(NOC_PLATFORM_LINUX)
    munmap(arena->Data, arena->Capacity);
#endif

    arena->Data = NULL;
    arena->Capacity = 0;
    arena->Occupied = 0;
}
