#include <check.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define AMOUNT 1

START_TEST(test_trim_1) {
    const char *s1 = "-?hello, world!";
    const char *s3 = "!?-";
    const char *s4 = "hello, world";
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_2) {
    const char *s1 = "";
    const char *s3 = "";
    const char *s4 = "";
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_3) {
    const char *s1 = NULL;
    const char *s3 = "";
    const char *s4 = NULL;
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_4) {
    const char *s1 = "!!!abcdefghij!?!";
    const char *s3 = "!?";
    const char *s4 = "abcdefghij";
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_5) {
    const char *s1 = "abc";
    const char *s3 = "333";
    const char *s4 = "abc";
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_6) {
    const char *s1 = "hello, world!";
    const char *s3 = "?!";
    const char *s4 = "hello, world";
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_7) {
    const char *s1 = NULL;
    const char *s3 = NULL;
    const char *s4 = NULL;
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_8) {
    const char *s1 = "";
    const char *s3 = "";
    const char *s4 = "";
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_9) {
    const char *s1 = " wtf ";
    const char *s3 = NULL;
    const char *s4 = "wtf";
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

START_TEST(test_trim_10) {
    const char *s1 = " wtf ";
    const char *s3 = "";
    const char *s4 = "wtf";
    char *s2 = s21_trim(s1, s3);
    ck_assert_pstr_eq(s4, s2);
    if (s2)
        free(s2);
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_trim] case");
    tcase_add_test(tc_a, test_trim_1);
    tcase_add_test(tc_a, test_trim_2);
    tcase_add_test(tc_a, test_trim_3);
    tcase_add_test(tc_a, test_trim_4);
    tcase_add_test(tc_a, test_trim_5);
    tcase_add_test(tc_a, test_trim_6);
    tcase_add_test(tc_a, test_trim_7);
    tcase_add_test(tc_a, test_trim_8);
    tcase_add_test(tc_a, test_trim_9);
    tcase_add_test(tc_a, test_trim_10);

    s = suite_create("[s21_trim] suite");
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
