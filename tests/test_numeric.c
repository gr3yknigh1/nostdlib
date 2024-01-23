#include <check.h>
#include <stdlib.h>

#include "_internal/memory.h"
#include "_internal/numeric/abs.h"
#include "_internal/numeric/countdigits.h"
#include "_internal/numeric/flt_charcount.h"
#include "_internal/numeric/from_str.h"
#include "_internal/numeric/to_str.h"

/////////////////
/// ABS TESTS ///
/////////////////

#define ASSERT_FLOAT_IN_RANGE(__EXPR, __GT_THAN, __LS_THAN)                    \
    ck_assert_msg((__EXPR) > (__GT_THAN) && (__EXPR) < (__LS_THAN),            \
                  "%f gt %f ls %f", (__EXPR), (__GT_THAN), (__LS_THAN));

#define MAKE_TEST_FOR_INT_ABS(__TYPE)                                          \
    START_TEST(test_##__TYPE##_abs) {                                          \
        ck_assert(_S21_ABS_NAME(__TYPE)(0) == 0);                              \
        ck_assert(_S21_ABS_NAME(__TYPE)(-1) == 1);                             \
        ck_assert(_S21_ABS_NAME(__TYPE)(2) == 2);                              \
        ck_assert(_S21_ABS_NAME(__TYPE)(-12923) == 12923);                     \
    }                                                                          \
    END_TEST

#define MAKE_TEST_FOR_FLT_ABS(__TYPE)                                          \
    START_TEST(test_##__TYPE##_abs) {                                          \
        ASSERT_FLOAT_IN_RANGE(_S21_ABS_NAME(__TYPE)(0.12f), 0.1199f, 0.1299f); \
        ASSERT_FLOAT_IN_RANGE(_S21_ABS_NAME(__TYPE)(0.0f), -0.9999f, 0.9999f); \
        ASSERT_FLOAT_IN_RANGE(_S21_ABS_NAME(__TYPE)(-0.12f), 0.1199f,          \
                              0.1299f);                                        \
        ASSERT_FLOAT_IN_RANGE(_S21_ABS_NAME(__TYPE)(-12.0f), 11.9999f,         \
                              12.9999f);                                       \
    }                                                                          \
    END_TEST

MAKE_TEST_FOR_INT_ABS(i16)
MAKE_TEST_FOR_INT_ABS(i32)
MAKE_TEST_FOR_INT_ABS(i64)

MAKE_TEST_FOR_FLT_ABS(f32)
MAKE_TEST_FOR_FLT_ABS(f64)

/////////////////////////
/// COUNTDIGITS TESTS ///
/////////////////////////

#define MAKE_TEST_FOR_SINT_COUNTDIGITS(__TYPE)                                 \
    START_TEST(test_##__TYPE##_countdigits) {                                  \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(10) == 2);                     \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(100) == 3);                    \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(12039) == 5);                  \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(-10) == 2);                    \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(-100) == 3);                   \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(-12039) == 5);                 \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(0) == 1);                      \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(1) == 1);                      \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(-1) == 1);                     \
    }                                                                          \
    END_TEST

#define MAKE_TEST_FOR_UINT_COUNTDIGITS(__TYPE)                                 \
    START_TEST(test_##__TYPE##_countdigits) {                                  \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(10) == 2);                     \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(100) == 3);                    \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(12039) == 5);                  \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(0) == 1);                      \
        ck_assert(_S21_COUNTDIGITS_NAME(__TYPE)(1) == 1);                      \
    }                                                                          \
    END_TEST

MAKE_TEST_FOR_SINT_COUNTDIGITS(i16)
MAKE_TEST_FOR_SINT_COUNTDIGITS(i32)
MAKE_TEST_FOR_SINT_COUNTDIGITS(i64)
MAKE_TEST_FOR_UINT_COUNTDIGITS(u16)
MAKE_TEST_FOR_UINT_COUNTDIGITS(u32)
MAKE_TEST_FOR_UINT_COUNTDIGITS(u64)

///////////////////////////
/// FLT_CHARCOUNT TESTS ///
///////////////////////////

#define MAKE_TEST_FOR_FLT_CHARCOUNT(__TYPE)                                    \
    START_TEST(test_##__TYPE##_flt_charcount) {                                \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(10.0, 1) == 4);              \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(100.0, 1) == 5);             \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(12039.0, 1) == 7);           \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(0.0, 1) == 3);               \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(1.0, 1) == 3);               \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(10.123, 3) == 6);            \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(100.302, 3) == 7);           \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(-12039.120, 3) == 9);        \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(0.1234, 4) == 6);            \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(1.99, 2) == 4);              \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(10.0, 2) == 5);              \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(100.0, 0) == 3);             \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(12039.0, 3) == 9);           \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(0.0, 1) == 3);               \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(1.0, 1) == 3);               \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(10.123, 3) == 6);            \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(100.302, 3) == 7);           \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(-12039.120, 3) == 9);        \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(0.1234, 4) == 6);            \
        ck_assert(_S21_FLT_CHARCOUNT_NAME(__TYPE)(1.99, 3) == 5);              \
    }                                                                          \
    END_TEST

MAKE_TEST_FOR_FLT_CHARCOUNT(f32)
MAKE_TEST_FOR_FLT_CHARCOUNT(f64)

//////////////////////
/// FROM_STR TESTS ///
//////////////////////

// TODO: Replace with generic, when generic version of *_from_str will be
// implemented
START_TEST(test_i32_from_str) {
    ck_assert_int_eq(s21_i32_from_str("3"), 3);
    ck_assert_int_eq(s21_i32_from_str("-3"), -3);
    ck_assert_int_eq(s21_i32_from_str("123"), 123);
    ck_assert_int_eq(s21_i32_from_str("99999"), 99999);
    ck_assert_int_eq(s21_i32_from_str("0003"), 3);
}
END_TEST

////////////////////
/// TO_STR TESTS ///
////////////////////

#define ASSERT_TO_STR_SUCCESS(__BUFSIZE, __TYPE, __VALUE, __EXPECTED, ...)     \
    do {                                                                       \
        char __buffer[__BUFSIZE] = {0};                                        \
        s21_memory_set(__buffer, (__BUFSIZE), 0);                              \
                                                                               \
        _S21_TO_STR_NAME(__TYPE)((__VALUE), __buffer __VA_ARGS__);             \
        ck_assert_msg(strcmp(__buffer, (__EXPECTED)) == 0,                     \
                      "buffer: %s, expected: %s", __buffer, (__EXPECTED));     \
    } while (0)

// TODO: Add test for MAX and MIN values
#define MAKE_TEST_SINT_FOR_TO_STR(__TYPE)                                      \
    START_TEST(test_##__TYPE##_to_str) {                                       \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)0, "0", );                 \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)10, "10", );               \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)1290, "1290", );           \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)-10, "-10", );             \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)-1290, "-1290", );         \
    }                                                                          \
    END_TEST

MAKE_TEST_SINT_FOR_TO_STR(i16)
MAKE_TEST_SINT_FOR_TO_STR(i32)
MAKE_TEST_SINT_FOR_TO_STR(i64)

#define MAKE_TEST_UINT_FOR_TO_STR(__TYPE)                                      \
    START_TEST(test_##__TYPE##_to_str) {                                       \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)0, "0", );                 \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)10, "10", );               \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)1290, "1290", );           \
    }                                                                          \
    END_TEST

MAKE_TEST_UINT_FOR_TO_STR(u16)
MAKE_TEST_UINT_FOR_TO_STR(u32)
MAKE_TEST_UINT_FOR_TO_STR(u64)

// NOTE: Replace `ASSERT_TO_STR_SUCCESS` with FLT specific, because of need to
// pass `precision` in function call
#define MAKE_TEST_FLT_TO_STR(__TYPE)                                           \
    START_TEST(test_##__TYPE##_to_str) {                                       \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)0, "0", , 0);              \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)10.3, "10.3", , 1);        \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)1290.3912, "1290.3912", ,  \
                              4);                                              \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)-129039.12, "-129039.12",  \
                              , 2);                                            \
        ASSERT_TO_STR_SUCCESS(1024, __TYPE, (__TYPE)-10.234, "-10.234", , 3);  \
    }                                                                          \
    END_TEST

MAKE_TEST_FLT_TO_STR(f32)
MAKE_TEST_FLT_TO_STR(f64)

Suite *
test_suite(void) {
    TCase *tc_abs = tcase_create("abs");
    tcase_add_test(tc_abs, test_i16_abs);
    tcase_add_test(tc_abs, test_i32_abs);
    tcase_add_test(tc_abs, test_i64_abs);
    tcase_add_test(tc_abs, test_f32_abs);
    tcase_add_test(tc_abs, test_f64_abs);

    TCase *tc_countdigits = tcase_create("countdigits");
    tcase_add_test(tc_countdigits, test_i16_countdigits);
    tcase_add_test(tc_countdigits, test_i32_countdigits);
    tcase_add_test(tc_countdigits, test_i64_countdigits);
    tcase_add_test(tc_countdigits, test_u16_countdigits);
    tcase_add_test(tc_countdigits, test_u32_countdigits);
    tcase_add_test(tc_countdigits, test_u64_countdigits);

    TCase *tc_flt_charcount = tcase_create("flt_charcount");
    tcase_add_test(tc_flt_charcount, test_f32_flt_charcount);
    tcase_add_test(tc_flt_charcount, test_f64_flt_charcount);

    TCase *tc_from_str = tcase_create("from_str");
    tcase_add_test(tc_from_str, test_i32_from_str);

    TCase *tc_to_str = tcase_create("to_str");
    tcase_add_test(tc_to_str, test_i16_to_str);
    tcase_add_test(tc_to_str, test_i32_to_str);
    tcase_add_test(tc_to_str, test_i64_to_str);
    tcase_add_test(tc_to_str, test_u16_to_str);
    tcase_add_test(tc_to_str, test_u32_to_str);
    tcase_add_test(tc_to_str, test_u64_to_str);
    tcase_add_test(tc_to_str, test_f32_to_str);
    tcase_add_test(tc_to_str, test_f64_to_str);

    Suite *s = suite_create("numeric");
    suite_add_tcase(s, tc_abs);
    suite_add_tcase(s, tc_countdigits);
    suite_add_tcase(s, tc_flt_charcount);
    suite_add_tcase(s, tc_from_str);
    suite_add_tcase(s, tc_to_str);
    return s;
}

int
main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
