#include <nocheck/nocheck.h>

#include <nostdlib/memory.h>
#include <nostdlib/sys.h>

TEST_PACK(Memory);

TEST(ArenaMake) {
    usize expectedArenaSize = NOC_GetPageSize();

    NOC_Arena arena = NOC_ArenaMake(expectedArenaSize);
    ASSERT_NOT_NULL(arena.Data);
    ASSERT_EQ(arena.Capacity, expectedArenaSize);
    ASSERT_EQ(arena.Occupied, 0);

    NOC_ArenaFree(&arena);
}

TEST(ArenaFree) {
    usize expectedArenaSize = NOC_GetPageSize();

    NOC_Arena arena = NOC_ArenaMake(expectedArenaSize);
    ASSERT_NOT_NULL(arena.Data);
    ASSERT_EQ(arena.Capacity, expectedArenaSize);
    ASSERT_EQ(arena.Occupied, 0);

    NOC_ArenaFree(&arena);

    ASSERT_IS_NULL(arena.Data);
    ASSERT_EQ(arena.Capacity, 0);
    ASSERT_EQ(arena.Occupied, 0);
}

TEST(ArenaAlloc_0_SimpleAndCheckReadWrite) {
    usize expectedArenaSize = NOC_GetPageSize();

    NOC_Arena arena = NOC_ArenaMake(expectedArenaSize);

    static usize bufferSize = 8;
    static i8 bufferElementValue = 9;

    byte *buffer = NOC_ArenaAlloc(&arena, bufferSize);
    ASSERT_NOT_NULL(buffer);

    NOC_MemorySet(buffer, bufferSize, bufferElementValue);

    for (usize i = 0; i < bufferSize; ++i) {
        ASSERT_EQ(buffer[i], bufferElementValue);
    }

    ASSERT_EQ(arena.Occupied, bufferSize);

    NOC_ArenaFree(&arena);
}

TEST(ArenaAlloc_1_SeveralAllocationsInARow) {
    usize expectedArenaSize = NOC_GetPageSize();
    NOC_Arena arena = NOC_ArenaMake(expectedArenaSize);

    {
        usize bufferSize = 8;
        byte *buffer = NOC_ArenaAlloc(&arena, bufferSize);
        ASSERT_NOT_NULL(buffer);
        ASSERT_EQ(arena.Occupied, 8);
    }

    {
        usize bufferSize = 16;
        byte *buffer = NOC_ArenaAlloc(&arena, bufferSize);
        ASSERT_NOT_NULL(buffer);
        ASSERT_EQ(arena.Occupied, 8 + 16);
    }

    {
        usize bufferSize = 32;
        byte *buffer = NOC_ArenaAlloc(&arena, bufferSize);
        ASSERT_NOT_NULL(buffer);
        ASSERT_EQ(arena.Occupied, 8 + 16 + 32);
    }

    {
        usize bufferSize = 8;
        byte *buffer = NOC_ArenaAlloc(&arena, bufferSize);
        ASSERT_NOT_NULL(buffer);
        ASSERT_EQ(arena.Occupied, 8 + 16 + 32 + 8);
    }

    NOC_ArenaFree(&arena);
}

TEST(ArenaAlloc_2_Overflow) {
    usize expectedArenaSize = NOC_GetPageSize();
    NOC_Arena arena = NOC_ArenaMake(expectedArenaSize);

    {
        usize bufferSize = expectedArenaSize;
        byte *buffer = NOC_ArenaAlloc(&arena, bufferSize);
        ASSERT_NOT_NULL(buffer);
        ASSERT_EQ(arena.Occupied, expectedArenaSize);
    }

    {
        usize bufferSize = 32;
        byte *buffer = NOC_ArenaAlloc(&arena, bufferSize);
        ASSERT_IS_NULL(buffer);
        ASSERT_EQ(arena.Occupied, expectedArenaSize);
    }

    NOC_ArenaFree(&arena);
}
