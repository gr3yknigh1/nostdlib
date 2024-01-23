#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(MEMSET_TEST_1) {
    char dest[20] = "1234";
    char dest2[20] = "1234";
    int c = 2;
    size_t n = 3;
    s21_memset(dest, c, n);
    memset(dest2, c, n);
    ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(MEMSET_TEST_2) {
    char dest[20] = "     ";
    char dest2[20] = "     ";
    int c = 5;
    size_t n = 8;
    s21_memset(dest, c, n);
    memset(dest2, c, n);
    ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(MEMSET_TEST_3) {
    char dest[20] = "Hello, world!";
    char dest2[20] = "Hello, world!";
    int c = ' ';
    size_t n = 4;
    s21_memset(dest, c, n);
    memset(dest2, c, n);
    ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(MEMSET_TEST_4) {
    char dest[20] = "*_*&#";
    char dest2[20] = "*_*&#";
    int c = 'c';
    size_t n = 0;
    s21_memset(dest, c, n);
    memset(dest2, c, n);
    ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(MEMSET_TEST_5) {
    char dest[20] = "__";
    char dest2[20] = "__";
    int c = 1;
    size_t n = 3;
    s21_memset(dest, c, n);
    memset(dest2, c, n);
    ck_assert_str_eq(dest, dest2);
}
END_TEST

Suite *
memset_suite(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_memset(x)");
    tc = tcase_create("memset(x)");
    tcase_add_test(tc, MEMSET_TEST_1);
    tcase_add_test(tc, MEMSET_TEST_2);
    tcase_add_test(tc, MEMSET_TEST_3);
    tcase_add_test(tc, MEMSET_TEST_4);
    tcase_add_test(tc, MEMSET_TEST_5);
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

    case_test(memset_suite(), &fail);

    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
