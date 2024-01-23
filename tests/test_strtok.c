#include <check.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define AMOUNT 1

START_TEST(strtok_test) {
    char test1[50] = "aboba,hello,world,trim";
    char test2[50] = "aboba,hello,world,trim";
    const char delim1[10] = "123,";
    char *orig1 = NULL, *copy1 = NULL;
    orig1 = strtok(test1, delim1);
    copy1 = s21_strtok(test2, delim1);
    char orig_res1[1000] = {0};
    char copy_res1[1000] = {0};
    while (orig1 != NULL) {
        strcat(orig_res1, orig1);
        orig1 = strtok(NULL, delim1);
    }
    while (copy1 != NULL) {
        strcat(copy_res1, copy1);
        copy1 = s21_strtok(NULL, delim1);
    }
    ck_assert_str_eq(orig_res1, copy_res1);

    char str[] = "School-21";
    const char *tok1 = s21_strtok(str, "-");
    const char *tok2 = strtok(str, "-");
    const char *tok3 = s21_strtok(str, "");
    const char *tok4 = strtok(str, "");
    const char *tok5 = s21_strtok(str, "oo");
    const char *tok6 = strtok(str, "oo");
    const char *tok7 = s21_strtok(str, "Sc");
    const char *tok8 = strtok(str, "Sc");
    const char *tok9 = s21_strtok(str, "21");
    const char *tok10 = strtok(str, "21");

    ck_assert_msg(!strcmp(tok1, tok2), "1st strtok test failed");
    ck_assert_msg(!strcmp(tok3, tok4), "2nd strtok test failed");
    ck_assert_msg(!strcmp(tok5, tok6), "3rd strtok test failed");
    ck_assert_msg(!strcmp(tok7, tok8), "4rth strtok test failed");
    ck_assert_msg(!strcmp(tok9, tok10), "5th strtok test failed");
}

END_TEST

START_TEST(test_strtok) {
    char input[] = "This is a test string";
    char *result;
    const char *delimiter = " ";
    result = strtok(input, delimiter);
    ck_assert_str_eq(result, "This");
    result = strtok(NULL, delimiter);
    ck_assert_str_eq(result, "is");
    result = strtok(NULL, delimiter);
    ck_assert_str_eq(result, "a");
    result = strtok(NULL, delimiter);
    ck_assert_str_eq(result, "test");
    result = strtok(NULL, delimiter);
    ck_assert_str_eq(result, "string");
    result = strtok(NULL, delimiter);
    ck_assert_ptr_eq(result, NULL);
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_strtok] case");
    tcase_add_test(tc_a, strtok_test);
    tcase_add_test(tc_a, test_strtok);

    s = suite_create("[s21_strtok] suite");
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
