#if !defined(NOSTDLIB_MEMORY_H_)
#define NOSTDLIB_MEMORY_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

#define KILOBYTES(X) (1024 * (X))
#define MEGABYTES(X) (1024 * 1024 * (X))
#define GIGABYTES(X) (1024 * 1024 * 1024 * (X))

// NOTE(gr3yknigh1): Source https://stackoverflow.com/a/45213645/12456897
// [2024/07/14]
#define NOC_ALIGN_TO(X, ALIGNMENT)                                             \
    (((X) + ((ALIGNMENT) - 1)) & ~((ALIGNMENT) - 1))

NOC_DEF void noc_memory_zero(void *dst, usize size);

NOC_DEF void noc_memory_set(void *dst, usize size, i8 value);

NOC_DEF void noc_memory_copy(void *restrict dst, const void *src, usize size);

NOC_DEF const void *noc_memory_find(const void *p, usize size, i8 value);

NOC_DEF usize NOC_AlignToPageSize(usize size);

/*
 * @breaf Arena Allocator (aka bump allocator).
 * */
typedef struct {
    void *Data;
    usize Capacity;
    usize Occupied;
} NOC_Arena;

#define NOC_ARENA_HAS_SPACE(ARENAPTR, SIZE)                                    \
    ((ARENAPTR)->Occupied + (SIZE) <= (ARENAPTR)->Capacity)

/*
 * @breaf Initializes memory arena. Maps memory for you.
 * @param size Minimum amount of bytes to allocate. Size will be aligned with
 * platform's page size.
 * */
NOC_DEF NOC_Arena NOC_ArenaMake(usize size);

/*
 * @breaf "Allocates" some memory. Pushes inner pointer inside arena.
 * @param arena Your arena.
 * @param size Amount of bytes you need.
 * */
NOC_DEF void *NOC_ArenaAlloc(NOC_Arena *arena, usize size);

/*
 * @breaf Unmaps pages, which was allolcated for you.
 * @param arena Your arena.
 * */
NOC_DEF void NOC_ArenaFree(NOC_Arena *arena);

#endif // NOSTDLIB_MEMORY_H_
