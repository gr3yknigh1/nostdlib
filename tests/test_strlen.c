#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(STRLEN_TEST_1) {
    const char str[16] = "Hello, world";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(STRLEN_TEST_2) {
    const char str[16] = "";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(STRLEN_TEST_3) {
    const char str[16] = "***";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(STRLEN_TEST_4) {
    const char str[16] = "1";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *
strlen_suite(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_strlen(x)");
    tc = tcase_create("strlen(x)");
    tcase_add_test(tc, STRLEN_TEST_1);
    tcase_add_test(tc, STRLEN_TEST_2);
    tcase_add_test(tc, STRLEN_TEST_3);
    tcase_add_test(tc, STRLEN_TEST_4);
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

    case_test(strlen_suite(), &fail);

    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
