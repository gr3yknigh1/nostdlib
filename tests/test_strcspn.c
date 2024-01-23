#include <check.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define AMOUNT 1

START_TEST(strcspn_test) {
    const char *str1 = "0123456789";
    const char *str2 = "9876";
    ck_assert_msg(s21_strcspn(str1, str2) == strcspn(str1, str2),
                  "1st strcspn test failed");

    const char *str3 = "0123456789";
    const char *str4 = "";
    ck_assert_msg(s21_strcspn(str3, str4) == strcspn(str3, str4),
                  "2nd strcspn test failed");

    const char *str5 = "";
    const char *str6 = "123";
    ck_assert_msg(s21_strcspn(str5, str6) == strcspn(str5, str6),
                  "3rd strcspn test failed");

    const char *str7 = "1337";
    const char *str8 = "228";
    ck_assert_msg(s21_strcspn(str7, str8) == strcspn(str7, str8),
                  "4rth strcspn test failed");

    const char *str9 = "19642";
    const char *str10 = "64";
    ck_assert_msg(s21_strcspn(str9, str10) == strcspn(str9, str10),
                  "5th strcspn test failed");
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_strcspn] case");
    tcase_add_test(tc_a, strcspn_test);

    s = suite_create("[s21_strcspn] suite");
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
