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

/*
 * @breaf Sets buffer to zero.
 * @param buffer Buffer to make zero.
 * @param size Size of buffer.
 * */
NOC_DEF void NOC_MemoryZero(void *buffer, usize size);

/*
 * @breaf Sets buffer to specified value.
 * @param buffer Buffer to set value.
 * @param size Size of buffer.
 * @param value Value to set.
 * */
NOC_DEF void NOC_MemorySet(void *buffer, usize size, i8 value);

/*
 * @breaf Copyies from one buffer to another.
 * @param destination Buffer in which will be copied source buffer.
 * @param source Buffer from which will be copy values.
 * @param size Size of source buffer.
 * */
NOC_DEF void NOC_MemoryCopy(void *restrict destination, const void *source, usize size);

/*
 * @breaf Finds and returns a pointer to first byte with specified value in
 * buffer.
 * @param buffer Buffer in which it should search value.
 * @param size Size of buffer.
 * @param value Value which should be find.
 * */
NOC_DEF const void *NOC_MemoryFind(const void *buffer, usize size, i8 value);

/*
 * @breaf Aligns specified size to page size of platform.
 * @param size Size which should be aligned.
 * @returns Aligned to page size value.
 * */
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
