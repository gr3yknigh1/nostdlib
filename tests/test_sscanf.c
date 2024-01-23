#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(s21_sscanf_func_01) {
    char s21_buf[32] = {0};
    char buf[32] = {0};
    int s21_result;
    int result;
    int s21_i = 0;
    int i = 0;
    const char *str = "s21_string func 1 2 3 4 5 6 7 8 9 0";
    const char *opt = "%s%d";

    s21_result = s21_sscanf(str, opt, s21_buf, &s21_i);
    result = sscanf(str, opt, buf, &i);
    ck_assert_int_eq(s21_result, result);
    ck_assert_int_eq(s21_i, i);
    ck_assert_str_eq(s21_buf, buf);
}

END_TEST

START_TEST(s21_sscanf_func_02) {
    char s21_buf[64] = {0};
    char buf[64] = {0};
    int s21_result;
    int result;
    int s21_i1 = 0;
    int s21_i2 = 0;
    int s21_i3 = 0;
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    const char *str = "s21_string func \t 1        2    \n\t\t\t\n\t\n 3 4";
    const char *opt = "%s%d %d %d";

    s21_result = s21_sscanf(str, opt, s21_buf, &s21_i1, &s21_i2, &s21_i3);
    result = sscanf(str, opt, buf, &i1, &i2, &i3);
    ck_assert_int_eq(s21_result, result);
    ck_assert_int_eq(s21_i1, i1);
    ck_assert_int_eq(s21_i2, i2);
    ck_assert_int_eq(s21_i3, i3);
    ck_assert_str_eq(s21_buf, buf);
}

END_TEST

START_TEST(test_sscanf_int) {
    int x, y;
    int result = s21_sscanf("123 456", "%d %d", &x, &y);
    ck_assert_int_eq(result, 2);
    ck_assert_int_eq(x, 123);
    ck_assert_int_eq(y, 456);
}

END_TEST

START_TEST(test_sscanf_string) {
    const char x[20], y[20];
    int result = s21_sscanf("hello world", "%s %s", x, y);
    ck_assert_int_eq(result, 2);
    ck_assert_str_eq(x, "hello");
    ck_assert_str_eq(y, "world");
}

END_TEST

START_TEST(test_sscanf_skip_whitespaces) {
    const char x[20];
    int result = s21_sscanf(" abc ", "%s", x);
    ck_assert_int_eq(result, 1);
    ck_assert_str_eq(x, "abc");
}

END_TEST

START_TEST(test_sscanf_mixed_type) {
    int x;
    char z[20];
    int result = s21_sscanf("123 hello", "%d %s", &x, z);
    ck_assert_int_eq(result, 2);
    ck_assert_int_eq(x, 123);
    ck_assert_str_eq(z, "hello");
}

END_TEST

START_TEST(test_sscanf_width_specifier) {
    char x[20], y[20];
    int result = s21_sscanf("hello world", "%5s %5s", x, y);
    ck_assert_int_eq(result, 2);
    ck_assert_str_eq(x, "hello");
    ck_assert_str_eq(y, "world");
}

END_TEST

START_TEST(test_sscanf_n_assignment) {
    int x, y;
    int result = s21_sscanf("123 456", "%d%n %d", &x, &y, &y);
    ck_assert_int_eq(result, 2);
    ck_assert_int_eq(x, 123);
    ck_assert_int_eq(y, 456);
}

END_TEST

START_TEST(s21_sscanf_test_19) {
    int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char *str = "17 21 58 30";
    const char *fstr = "%i %i %i %i";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(test_sscanf_spec_i_int1) {
    long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char *str = "100 500 -600 +700";
    const char *fstr = "%li %li %li %li";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(test_sscanf_spec_i_int2) {
    long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    const char *str = "100500 -600 +700 123";
    const char *fstr = "%li %li %li %li";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(test_sscanf_spec_i_int3) {
    long a1 = 0, a2 = 0, c1 = 0, c2 = 0;
    char b1 = 0, b2 = 0, d1 = 0, d2 = 0;
    const char *str = "100500-600+700+400";
    const char *fstr = "%li %c %li %c";

    int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
    int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}

END_TEST

Suite *
sscanf_suite(void) {
    Suite *suite;
    TCase *tc_s;

    tc_s = tcase_create("[sscanf] case");
    tcase_add_test(tc_s, s21_sscanf_func_01);
    tcase_add_test(tc_s, s21_sscanf_func_02);
    tcase_add_test(tc_s, test_sscanf_int);
    tcase_add_test(tc_s, test_sscanf_string);
    tcase_add_test(tc_s, test_sscanf_skip_whitespaces);
    tcase_add_test(tc_s, test_sscanf_mixed_type);
    tcase_add_test(tc_s, test_sscanf_width_specifier);
    tcase_add_test(tc_s, test_sscanf_n_assignment);
    tcase_add_test(tc_s, test_sscanf_spec_i_int1);
    tcase_add_test(tc_s, test_sscanf_spec_i_int2);
    tcase_add_test(tc_s, test_sscanf_spec_i_int3);
    tcase_add_test(tc_s, s21_sscanf_test_19);

    suite = suite_create("[sscanf] suite");
    suite_add_tcase(suite, tc_s);

    return suite;
}

int
main(void) {
    SRunner *runner = srunner_create(sscanf_suite());
    srunner_run_all(runner, CK_NORMAL);
    int fail = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
