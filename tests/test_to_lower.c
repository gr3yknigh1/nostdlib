#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(TO_LOWER_TEST_1) {
    const char *str = "Hello, world";
    char *str2 = s21_to_lower(str);
    ck_assert_str_eq(str2, "hello, world");
    free(str2);
}
END_TEST

START_TEST(TO_LOWER_TEST_2) {
    const char *str = "";
    char *str2 = s21_to_lower(str);
    ck_assert_str_eq(str2, "");
    free(str2);
}
END_TEST

START_TEST(TO_LOWER_TEST_3) {
    const char *str = "HEY";
    char *str2 = s21_to_lower(str);
    ck_assert_str_eq((const char *)str2, "hey");
    free(str2);
}
END_TEST

START_TEST(TO_LOWER_TEST_4) {
    const char *str = "*1_2&^35 8 MaY**&&))";
    char *str2 = s21_to_lower(str);
    ck_assert_str_eq((const char *)str2, "*1_2&^35 8 may**&&))");
    free(str2);
}
END_TEST

Suite *
to_lower_suite(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_to_lower(x)");
    tc = tcase_create("to_lower(x)");
    tcase_add_test(tc, TO_LOWER_TEST_1);
    tcase_add_test(tc, TO_LOWER_TEST_2);
    tcase_add_test(tc, TO_LOWER_TEST_3);
    tcase_add_test(tc, TO_LOWER_TEST_4);
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

    case_test(to_lower_suite(), &fail);

    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
