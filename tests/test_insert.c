#include <check.h>
#include <locale.h>
#include <stdlib.h>

#include "s21_string.h"

#define AMOUNT 1

START_TEST(insert_test) {
    const char *s1 = "School-21 test";
    const char *s2 = "insert ";
    const char *s3 = "amogus";
    const char *s4 = "is";
    const char *s5 = "shrek";
    char *res1 = s21_insert(s1, " ", 3);
    char *res2 = s21_insert(s5, s3, 5);
    char *res3 = s21_insert(s3, s5, 0);
    char *res4 = s21_insert(s5, s4, 5);
    char *res5 = s21_insert(s2, s1, 4);

    ck_assert_str_eq(res1, "Sch ool-21 test");
    ck_assert_str_eq(res2, "shrekamogus");
    ck_assert_str_eq(res3, "shrekamogus");
    ck_assert_str_eq(res4, "shrekis");
    ck_assert_str_eq(res5, "inseSchool-21 testrt ");

    free(res1);
    free(res2);
    free(res3);
    free(res4);
    free(res5);
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_insert] case");
    tcase_add_test(tc_a, insert_test);

    s = suite_create("[s21_insert] suite");
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

    for (int repeats = 0; repeats < AMOUNT; repeats++) {
        srunner_run_all(sr, CK_NORMAL);
    }
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
