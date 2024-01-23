#include <check.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define AMOUNT 1

START_TEST(strspn_test) {
    const char *s1 = "School-21";
    const char *s2 = "ho";
    const char *s3 = "";

    ck_assert_msg(s21_strspn(s1, s2) == strspn(s1, s2),
                  "1st strspn test failed");
    ck_assert_msg(s21_strspn(s3, s2) == strspn(s3, s2),
                  "2nd strspn test failed");
    ck_assert_msg(s21_strspn(s2, s3) == strspn(s2, s3),
                  "3rd strspn test failed");
    ck_assert_msg(s21_strspn(s1, s3) == strspn(s1, s3),
                  "4th strspn test failed");
    ck_assert_msg(s21_strspn(s3, s1) == strspn(s3, s1),
                  "5th strspn test failed");
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_strspn] case");
    tcase_add_test(tc_a, strspn_test);

    s = suite_create("[s21_strspn] suite");
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
