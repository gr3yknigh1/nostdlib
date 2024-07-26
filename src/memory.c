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
NOC_MemoryZero(void *buffer, usize size) {
    while (size-- > 0) {
        ((char *)buffer)[size] = 0;
    }
}

NOC_DEF void
NOC_MemorySet(void *buffer, usize size, i8 value) {
    while (size-- > 0) {
        ((char *)buffer)[size] = value;
    }
}

NOC_DEF void
NOC_MemoryCopy(void *restrict destination, const void *source, usize size) {
    for (usize i = 0; i < size; ++i) {
        ((byte *)destination)[i] = ((byte *)source)[i];
    }
}

NOC_DEF const void *
NOC_MemoryFind(const void *buffer, usize size, i8 value) {
    for (usize i = 0; i < size; ++i) {
        if (((i8 *)buffer)[i] == value) {
            return buffer;
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

NOC_DEF NOC_ScratchArena
NOC_ScratchArenaMake(NOC_Arena *arena, usize size) {
    // TODO(gr3yknigh1): Assert `arena` be `NULL` and `size` be zero.

    void *data = NOC_ArenaAlloc(arena, size);

    NOC_ScratchArena ret = LITERAL(NOC_ScratchArena){
        .Data = data,
        .Capacity = size,
        .Occupied = 0,
    };

    return ret;
}

NOC_DEF NOC_ScratchArena
NOC_ScratchArenaMakeZero(NOC_Arena *arena, usize size) {
    NOC_ScratchArena scratch = NOC_ScratchArenaMake(arena, size);
    NOC_MemoryZero(scratch.Data, scratch.Capacity);
    return scratch;
}

NOC_DEF void
NOC_ScratchArenaClear(NOC_ScratchArena *scratchArena) {
    // TODO(gr3yknigh1): Assert `arena` be `NULL`.
    scratchArena->Occupied = 0;
}
