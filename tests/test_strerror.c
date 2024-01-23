#include <check.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "_internal/errors.h"
#include "s21_string.h"

#define AMOUNT 1

START_TEST(strerror_test) {
    const char *str1 = s21_strerror(20);
    const char *str2 = strerror(20);
    ck_assert_str_eq(str1, str2);

    const char *str3 = s21_strerror(12);
    const char *str4 = strerror(12);
    ck_assert_str_eq(str3, str4);

    const char *str5 = s21_strerror(1337);
    const char *str6 = strerror(1337);
    ck_assert_str_eq(str5, str6);

    const char *str7 = s21_strerror(1);
    const char *str8 = strerror(1);
    ck_assert_str_eq(str7, str8);

    const char *str9 = s21_strerror(25);
    const char *str10 = strerror(25);
    ck_assert_str_eq(str9, str10);
}

START_TEST(strerror_test_auto) {
    for (size_t i = 0; i < MAX_ERRLIST; ++i) {
        const char *str1 = s21_strerror(i);
        const char *str2 = strerror(i);
        ck_assert_str_eq(str1, str2);
    }
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_strerror] case");
    tcase_add_test(tc_a, strerror_test);
    tcase_add_test(tc_a, strerror_test_auto);

    s = suite_create("[s21_strerror] suite");
    suite_add_tcase(s, tc_a);

    return s;
}

int
main(void) {
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "C");
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = s21_string_suite();
    sr = srunner_create(s);

    for (int repeats = 0; repeats < AMOUNT; repeats++)
        srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
