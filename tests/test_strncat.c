#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(STRNCAT_TEST_1) {
    char dest[20] = "1234";
    const char str[16] = "Hello, world";
    size_t n = strlen(str);
    ck_assert_str_eq(s21_strncat(dest, str, n), "1234Hello, world");
}
END_TEST

START_TEST(STRNCAT_TEST_2) {
    char dest[20] = "";
    const char str[16] = "Hello, world";
    size_t n = 8;
    ck_assert_str_eq(s21_strncat(dest, str, n), "Hello, w");
}
END_TEST

START_TEST(STRNCAT_TEST_3) {
    char dest[20] = "Hello";
    const char str[16] = "Ahahah";
    size_t n = 4;
    ck_assert_str_eq(s21_strncat(dest, str, n), "HelloAhah");
}
END_TEST

START_TEST(STRNCAT_TEST_4) {
    char dest[20] = "*_*&#";
    const char str[16] = "Hello, world";
    size_t n = 0;
    ck_assert_str_eq(s21_strncat(dest, str, n), "*_*&#");
}
END_TEST

START_TEST(STRNCAT_TEST_5) {
    char dest[20] = "Hello, world";
    const char str[16] = "";
    size_t n = 3;
    ck_assert_str_eq(s21_strncat(dest, str, n), "Hello, world");
}
END_TEST

Suite *
strncat_suite(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_strncat(x)");
    tc = tcase_create("strncat(x)");
    tcase_add_test(tc, STRNCAT_TEST_1);
    tcase_add_test(tc, STRNCAT_TEST_2);
    tcase_add_test(tc, STRNCAT_TEST_3);
    tcase_add_test(tc, STRNCAT_TEST_4);
    tcase_add_test(tc, STRNCAT_TEST_5);
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

    case_test(strncat_suite(), &fail);

    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
