#include <check.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "s21_string.h"

#define NMAX 1024
#define AMOUNT 1

START_TEST(strstr_test) {
    char *s1 = "School-21";
    char *s2 = "ho";
    char *s3 = "";

    ck_assert_msg(s21_strstr(s1, s2) == strstr(s1, s2),
                  "1st strstr test failed");
    ck_assert_msg(s21_strstr(s1, s3) == strstr(s1, s3),
                  "2nd strstr test failed");
    ck_assert_msg(s21_strstr(s3, s2) == strstr(s3, s2),
                  "3rd strstr test failed");
    ck_assert_msg(s21_strstr(s2, s3) == strstr(s2, s3),
                  "4rth strstr test failed");
    ck_assert_msg(s21_strstr(s3, s1) == strstr(s3, s1),
                  "5th strstr test failed");
}

END_TEST

char *
get_random_str(void) {
    srand(time(NULL));
    int len = rand() % (NMAX - 1) + 1;
    char *str = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        str[i] = (char)(rand() % ('z' - 'a' + 1) + 'a');
    }
    str[len] = '\0';
    return str;
}

START_TEST(test_strstr) {
    char *haystack = get_random_str();
    char *needle = get_random_str();
    ck_assert_ptr_eq(strstr(haystack, needle), s21_strstr(haystack, needle));
    free(haystack);
    free(needle);
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_strstr] case");
    tcase_add_test(tc_a, strstr_test);
    tcase_add_test(tc_a, test_strstr);

    s = suite_create("[s21_strstr] suite");
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
