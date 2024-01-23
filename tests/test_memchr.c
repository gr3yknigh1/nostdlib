#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(MEMCHR_TEST_1) {
    const char *dest = "";
    char *sym2;
    sym2 = s21_memchr(dest, '1', s21_strlen(dest));
    ck_assert_ptr_null(sym2);
}
END_TEST

START_TEST(MEMCHR_TEST_2) {
    const char *dest = "";
    char *sym2;
    sym2 = s21_memchr(dest, '1', s21_strlen(dest));
    ck_assert_ptr_null(sym2);
}
END_TEST

START_TEST(MEMCHR_TEST_3) {
    const char *dest = "Hello";
    char *sym;
    char *sym2;
    sym = memchr(dest, 'l', strlen(dest));
    sym2 = s21_memchr(dest, 'l', s21_strlen(dest));
    ck_assert_str_eq(sym, sym2);
}
END_TEST

START_TEST(MEMCHR_TEST_4) {
    const char *dest = "12 8 0 23";
    char *sym;
    char *sym2;
    sym = memchr(dest, '0', strlen(dest));
    sym2 = s21_memchr(dest, '0', s21_strlen(dest));
    ck_assert_str_eq(sym, sym2);
}
END_TEST

START_TEST(MEMCHR_TEST_5) {
    const char *dest = "11111311";
    char *sym;
    char *sym2;
    sym = memchr(dest, '3', strlen(dest));
    sym2 = s21_memchr(dest, '3', s21_strlen(dest));
    ck_assert_str_eq(sym, sym2);
}
END_TEST

START_TEST(MEMCHR_TEST_6) {
    const char *dest = "123456789";
    char *sym;
    char *sym2;
    sym = memchr(dest, '1', strlen(dest));
    sym2 = s21_memchr(dest, '1', s21_strlen(dest));
    ck_assert_str_eq(sym, sym2);
}
END_TEST

Suite *
memchr_suite(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_memchr(x)");
    tc = tcase_create("memchr(x)");
    tcase_add_test(tc, MEMCHR_TEST_1);
    tcase_add_test(tc, MEMCHR_TEST_2);
    tcase_add_test(tc, MEMCHR_TEST_3);
    tcase_add_test(tc, MEMCHR_TEST_4);
    tcase_add_test(tc, MEMCHR_TEST_5);
    tcase_add_test(tc, MEMCHR_TEST_6);
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
    case_test(memchr_suite(), &fail);
    return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
