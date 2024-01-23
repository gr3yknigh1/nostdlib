#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(MEMCMP_TEST_1) {
    const char dest[20] = "Hello, world";
    const char str[16] = "aribiderchi";
    size_t n = 3;
    ck_assert_int_eq(s21_memcmp(dest, str, n), memcmp(dest, str, n));
}
END_TEST

START_TEST(MEMCMP_TEST_2) {
    const char dest[20] = "";
    const char str[16] = "Hello, world";
    size_t n = 8;
    ck_assert_int_eq(s21_memcmp(dest, str, n), memcmp(dest, str, n));
}
END_TEST

START_TEST(MEMCMP_TEST_3) {
    const char dest[20] = "Hello";
    const char str[16] = "1111";
    size_t n = 4;
    ck_assert_int_eq(s21_memcmp(dest, str, n), memcmp(dest, str, n));
}
END_TEST

START_TEST(MEMCMP_TEST_4) {
    const char dest[20] = "*_*&#";
    const char str[16] = "/_&";
    size_t n = 0;
    ck_assert_int_eq(s21_memcmp(dest, str, n), memcmp(dest, str, n));
}
END_TEST

START_TEST(MEMCMP_TEST_5) {
    const char dest[20] = "Hello, world";
    const char str[16] = "";
    size_t n = 3;
    ck_assert_int_eq(s21_memcmp(dest, str, n), memcmp(dest, str, n));
}
END_TEST

Suite *
memcmp_suite(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_memcmp(x)");
    tc = tcase_create("memcmp(x)");
    tcase_add_test(tc, MEMCMP_TEST_1);
    tcase_add_test(tc, MEMCMP_TEST_2);
    tcase_add_test(tc, MEMCMP_TEST_3);
    tcase_add_test(tc, MEMCMP_TEST_4);
    tcase_add_test(tc, MEMCMP_TEST_5);
    suite_add_tcase(s, tc);
    return s;
}

void
case_test(Suite *s, int *fail) {
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    *fail = srunner_ntests_failed(runner);
    srunner_free(runner);
}

int
main(void) {
    int fail = 0;

    case_test(memcmp_suite(), &fail);

    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
