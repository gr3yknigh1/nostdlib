#include <nocheck/nocheck.h>

TEST_PACK(basic); // One per translation unit.

TEST(test0) {
    ASSERT(1 == 1);
    ASSERT(true);
}

TEST(test1) {
    ASSERT(false); // will fail.
}
