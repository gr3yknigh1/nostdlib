#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

enum _strcmp_ret {
    _STRCMP_RET_EQ,
    _STRCMP_RET_LT,
    _STRCMP_RET_GT,
};

#define _MATCH_STRCMP_RET(__EXPR)                                              \
    ((__EXPR) == 0 ? _STRCMP_RET_EQ                                            \
                   : ((__EXPR) > 0 ? _STRCMP_RET_GT : _STRCMP_RET_LT))

START_TEST(STRNCMP_TEST_1) {
    const char *dest = "Hello, world";
    const char *str = "aribiderchi";
    size_t n = 3;
    ck_assert_int_eq(_MATCH_STRCMP_RET(s21_strncmp(dest, str, n)),
                     _MATCH_STRCMP_RET(strncmp(dest, str, n)));
}
END_TEST

START_TEST(STRNCMP_TEST_2) {
    const char *dest = "";
    const char *str = "Hello, world";
    size_t n = 8;
    ck_assert_int_eq(_MATCH_STRCMP_RET(s21_strncmp(dest, str, n)),
                     _MATCH_STRCMP_RET(strncmp(dest, str, n)));
}
END_TEST

START_TEST(STRNCMP_TEST_3) {
    const char *dest = "Hello";
    const char *str = "1111";
    size_t n = 4;
    ck_assert_int_eq(_MATCH_STRCMP_RET(s21_strncmp(dest, str, n)),
                     _MATCH_STRCMP_RET(strncmp(dest, str, n)));
}
END_TEST

START_TEST(STRNCMP_TEST_4) {
    const char *dest = "*_*&#";
    const char *str = "/_&";
    size_t n = 0;
    ck_assert_int_eq(_MATCH_STRCMP_RET(s21_strncmp(dest, str, n)),
                     _MATCH_STRCMP_RET(strncmp(dest, str, n)));
}
END_TEST

START_TEST(STRNCMP_TEST_5) {
    const char *dest = "Hello, world";
    const char *str = "";
    size_t n = 3;
    ck_assert_int_eq(_MATCH_STRCMP_RET(s21_strncmp(dest, str, n)),
                     _MATCH_STRCMP_RET(strncmp(dest, str, n)));
}
END_TEST

Suite *
strncmp_suite(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_strncmp(x)");
    tc = tcase_create("strncmp(x)");
    tcase_add_test(tc, STRNCMP_TEST_1);
    tcase_add_test(tc, STRNCMP_TEST_2);
    tcase_add_test(tc, STRNCMP_TEST_3);
    tcase_add_test(tc, STRNCMP_TEST_4);
    tcase_add_test(tc, STRNCMP_TEST_5);
    suite_add_tcase(s, tc);
    return s;
}

void
case_test(Suite *s, int *fail) {
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    *fail = srunner_ntests_failed(runner);
    srunner_free(runner);
}

int
main(void) {
    int fail = 0;

    case_test(strncmp_suite(), &fail);

    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
