#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(STRCHR_TEST_1) {
    const char *dest = "111112345";
    char *sym2;
    sym2 = s21_strchr(dest, 'z');
    ck_assert_ptr_null(sym2);
}
END_TEST

START_TEST(STRCHR_TEST_2) {
    const char *dest = "";
    char *sym2;
    sym2 = s21_strchr(dest, '1');
    ck_assert_ptr_null(sym2);
}
END_TEST

START_TEST(STRCHR_TEST_3) {
    const char *dest = "Hello";
    char *sym;
    char *sym2;
    sym = strchr(dest, 'l');
    sym2 = s21_strchr(dest, 'l');
    ck_assert_str_eq(sym, sym2);
}
END_TEST

START_TEST(STRCHR_TEST_4) {
    const char *dest = "12 8 0 23";
    char *sym;
    char *sym2;
    sym = strchr(dest, '0');
    sym2 = s21_strchr(dest, '0');
    ck_assert_str_eq(sym, sym2);
}
END_TEST

START_TEST(STRCHR_TEST_5) {
    const char *dest = "11111311";
    char *sym;
    char *sym2;
    sym = strchr(dest, '3');
    sym2 = s21_strchr(dest, '3');
    ck_assert_str_eq(sym, sym2);
}
END_TEST

START_TEST(STRCHR_TEST_6) {
    const char *dest = "123456789";
    char *sym;
    char *sym2;
    sym = strchr(dest, '1');
    sym2 = s21_strchr(dest, '1');
    ck_assert_str_eq(sym, sym2);
}
END_TEST

Suite *
strchr_suite(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_strchr(x)");
    tc = tcase_create("strchr(x)");
    tcase_add_test(tc, STRCHR_TEST_1);
    tcase_add_test(tc, STRCHR_TEST_2);
    tcase_add_test(tc, STRCHR_TEST_3);
    tcase_add_test(tc, STRCHR_TEST_4);
    tcase_add_test(tc, STRCHR_TEST_5);
    tcase_add_test(tc, STRCHR_TEST_6);
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

    case_test(strchr_suite(), &fail);
    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
