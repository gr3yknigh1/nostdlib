#include <check.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define AMOUNT 1

START_TEST(strpbrk_test) {
    const char *str1 = "hello";
    const char *str2 = "hel";
    char *res1, *res2;
    res1 = s21_strpbrk(str1, str2);
    res2 = strpbrk(str1, str2);
    ck_assert_str_eq(res1, res2);

    const char *str4 = "ab";
    res1 = s21_strpbrk(str1, str4);
    res2 = strpbrk(str1, str4);
    ck_assert_ptr_eq(res1, res2);

    const char *str5 = "o";
    res1 = s21_strpbrk(str1, str5);
    res2 = strpbrk(str1, str5);
    ck_assert_str_eq(res1, res2);

    const char *str6 = "abcdefghjkl";
    const char *str7 = "abcd";
    res1 = s21_strpbrk(str6, str7);
    res2 = strpbrk(str6, str7);
    ck_assert_str_eq(res1, res2);

    const char *str8 = "amogus is shrek?";
    const char *str9 = "is";
    res1 = s21_strpbrk(str8, str9);
    res2 = s21_strpbrk(str8, str9);
    ck_assert_str_eq(res1, res2);
}

END_TEST

Suite *
s21_string_suite(void) {
    Suite *s;
    TCase *tc_a;

    tc_a = tcase_create("[s21_strpbrk] case");
    tcase_add_test(tc_a, strpbrk_test);

    s = suite_create("[s21_strpbrk] suite");
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
