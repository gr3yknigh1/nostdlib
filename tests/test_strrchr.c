#include <check.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define AMOUNT 1

START_TEST(strrchr_test) {
    const char *s1 = "School-21";
    const char *s2 = "";
    const char *s3 = "amogus";

    ck_assert_msg(s21_strrchr(s1, 'm') == strrchr(s1, 'm'),
                  "1st strrchr test failed");
    ck_assert_msg(s21_strrchr(s1, 'o') == strrchr(s1, 'o'),
                  "2nd strrchr test failed");
    ck_assert_msg(s21_strrchr(s2, 'o') == strrchr(s2, 'o'),
                  "3rd strrchr test failed");
    ck_assert_msg(s21_strrchr(s3, ' ') == strrchr(s3, ' '),
                  "4rth strrchr test failed");
    ck_assert_msg(s21_strrchr(s3, 's') == strrchr(s3, 's'),
                  "5th strrchr test failed");
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_strrchr] case");
    tcase_add_test(tc_a, strrchr_test);

    s = suite_create("[s21_strrchr] suite");
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
