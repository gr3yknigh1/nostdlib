#define _CRT_SECURE_NO_WARNINGS
#include <check.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

// NOTE(gr3yknigh1): Suppress cppcheck warnings
static int (*_original_function)(char *restrict, const char *, ...) = sprintf;

// NOTE(gr3yknigh1): Helper macro for output comparison
#define SHOULD_MATCH_OUTPUT(__BUFFER_SIZE, ...)                                \
    do {                                                                       \
        char *__BUFFER_0 = calloc((__BUFFER_SIZE), sizeof(char));              \
        char *__BUFFER_1 = calloc((__BUFFER_SIZE), sizeof(char));              \
                                                                               \
        s21_sprintf(__BUFFER_0, __VA_ARGS__);                                  \
        _original_function(__BUFFER_1, __VA_ARGS__);                           \
                                                                               \
        bool __IS_EQ = strcmp(__BUFFER_0, __BUFFER_1) == 0;                    \
        ck_assert_msg(__IS_EQ, "orig: [%s] s21: [%s]", __BUFFER_1,             \
                      __BUFFER_0);                                             \
        free(__BUFFER_0);                                                      \
        free(__BUFFER_1);                                                      \
    } while (0)

START_TEST(test_without_fmt) { SHOULD_MATCH_OUTPUT(1024, "helloworld"); }
END_TEST

START_TEST(test_char) { SHOULD_MATCH_OUTPUT(1024, "%c %c", 'c', 1); }
END_TEST

START_TEST(test_char_padding) {
    SHOULD_MATCH_OUTPUT(1024, "%12c %-12c", 'c', 1);
}
END_TEST

START_TEST(test_decimal_and_int) {
    SHOULD_MATCH_OUTPUT(1024, "%i %i", 1232, -12323);
    SHOULD_MATCH_OUTPUT(1024, " %i %i", 0, 0);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %i %i", 12932190, 109);
    SHOULD_MATCH_OUTPUT(1024, "%i %i", INT_MAX, 1093282);
}
END_TEST

START_TEST(test_short_decimal_and_int) {
    SHOULD_MATCH_OUTPUT(1024, "%hi %hi", 1232, -123);
    SHOULD_MATCH_OUTPUT(1024, " %hi %hi", 0, 0);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %hi %hi", 12, 109);
    SHOULD_MATCH_OUTPUT(1024, "%hi %hi", SHRT_MAX, 10);
}
END_TEST

START_TEST(test_long_decimal_and_int) {
    SHOULD_MATCH_OUTPUT(1024, "%li %li", 1232, -123);
    SHOULD_MATCH_OUTPUT(1024, " %li %li", 0, 0);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %li %li", 12, 109);
    SHOULD_MATCH_OUTPUT(1024, "%li %li", LONG_MAX, 10);
}
END_TEST

START_TEST(test_float) {
    SHOULD_MATCH_OUTPUT(1024, "%f %f", 1232.3, -12323.12);
    SHOULD_MATCH_OUTPUT(1024, "%f", -12323.12);
    SHOULD_MATCH_OUTPUT(1024, " %f %f", 0.2, 0.1);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %f %f", 12932190.123, 109.03);
}
END_TEST

START_TEST(test_float_precision) {
    SHOULD_MATCH_OUTPUT(1024, "%f %f", 1232.3, -12323.12);
    SHOULD_MATCH_OUTPUT(1024, "%.3f", -12323.12);
    SHOULD_MATCH_OUTPUT(1024, " %.0f %f", 0.2, 0.1);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %.13f %f", 129.123, 109.03);
}
END_TEST

START_TEST(test_double) {
    SHOULD_MATCH_OUTPUT(1024, "%lf %lf", 1232.3, -12323.12);
    SHOULD_MATCH_OUTPUT(1024, "%lf", -12323.12);
    SHOULD_MATCH_OUTPUT(1024, " %lf %lf", 0.2, 0.1);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %lf %lf", 12932190.123, 109.03);
}
END_TEST

START_TEST(test_double_precision) {
    SHOULD_MATCH_OUTPUT(1024, "%lf %lf", 1232.3, -12323.12);
    SHOULD_MATCH_OUTPUT(1024, "%.3lf", -12323.12);
    SHOULD_MATCH_OUTPUT(1024, " %.0lf %lf", 0.2, 0.1);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %.13lf %lf", 129.123, 109.03);
}
END_TEST

START_TEST(test_unsigned_int) {
    SHOULD_MATCH_OUTPUT(1024, "%u %u", 1232, 123231290);
    SHOULD_MATCH_OUTPUT(1024, " %u %u", 0, 0);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %u %u", 12932190, 109);
    SHOULD_MATCH_OUTPUT(1024, "%u %u", UINT_MAX, 1093282);
}
END_TEST

START_TEST(test_unsigned_short) {
    SHOULD_MATCH_OUTPUT(1024, "%hu %hu", 123, 123);
    SHOULD_MATCH_OUTPUT(1024, " %hu %hu", 0, 0);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %hu %hu", 1, 10);
    SHOULD_MATCH_OUTPUT(1024, "%hu %hu", USHRT_MAX, 10);
}
END_TEST

START_TEST(test_unsigned_long) {
    SHOULD_MATCH_OUTPUT(1024, "%lu %lu", 12321394, 12312093);
    SHOULD_MATCH_OUTPUT(1024, " %lu %lu", 0, 123);
    SHOULD_MATCH_OUTPUT(1024, "asldkj %lu %lu", 1, 12310);
    SHOULD_MATCH_OUTPUT(1024, "%lu %lu", ULONG_MAX, 100123);
}
END_TEST

START_TEST(test_string) {
    SHOULD_MATCH_OUTPUT(1024, "%i %s %i", 1232, "helloworld", -12323);
    SHOULD_MATCH_OUTPUT(1024, " %i %s", 0, "ilya");
    SHOULD_MATCH_OUTPUT(1024, "asldkj %s %i", "popopopo", 109);
    SHOULD_MATCH_OUTPUT(1024, "%s", "goodbye");
}
END_TEST

START_TEST(test_string_padding) {
    SHOULD_MATCH_OUTPUT(1024, "%i %-2s %i", 1232, "helloworld", -12323);
    SHOULD_MATCH_OUTPUT(1024, " %i %12s", 0, "ilya");
    SHOULD_MATCH_OUTPUT(1024, "asldkj %s %i", "popopopo", 109);
    SHOULD_MATCH_OUTPUT(1024, "%40s", "goodbye");
}
END_TEST

START_TEST(test_percent) {
    SHOULD_MATCH_OUTPUT(1024, "%% %i %%", 1232, -12323);
    SHOULD_MATCH_OUTPUT(1024, " %i %% %i", 0, 0);
}
END_TEST

START_TEST(test_padding) {
    SHOULD_MATCH_OUTPUT(1024, "%% %-10i %%", 1232, -12323);
    SHOULD_MATCH_OUTPUT(1024, " %20i %% %i", 0, 0);
}
END_TEST

START_TEST(test_sign_precede) {
    SHOULD_MATCH_OUTPUT(1024, "%i % i", 1232, -12323);
    SHOULD_MATCH_OUTPUT(1024, "%i % i", -1234, 12323);
    SHOULD_MATCH_OUTPUT(1024, " %+2i %% %+1i", -123, 5443);
    SHOULD_MATCH_OUTPUT(1024, " %+2i %% %+i", -123, 5443);
}
END_TEST

Suite *
test_suite(void) {
    Suite *s = suite_create("sprintf");
    TCase *tc_core = tcase_create("sprintf");

    tcase_add_test(tc_core, test_without_fmt);

    tcase_add_test(tc_core, test_char);
    tcase_add_test(tc_core, test_char_padding);

    tcase_add_test(tc_core, test_decimal_and_int);
    tcase_add_test(tc_core, test_short_decimal_and_int);
    tcase_add_test(tc_core, test_long_decimal_and_int);

    tcase_add_test(tc_core, test_unsigned_int);
    tcase_add_test(tc_core, test_unsigned_long);
    tcase_add_test(tc_core, test_unsigned_short);

    tcase_add_test(tc_core, test_float);
    tcase_add_test(tc_core, test_float_precision);

    tcase_add_test(tc_core, test_double);
    tcase_add_test(tc_core, test_double_precision);

    tcase_add_test(tc_core, test_string);
    tcase_add_test(tc_core, test_string_padding);

    tcase_add_test(tc_core, test_padding);
    tcase_add_test(tc_core, test_sign_precede);

    // FIXME: Add `n` unittest

    tcase_add_test(tc_core, test_percent);

    suite_add_tcase(s, tc_core);
    return s;
}

int
main(void) {
    Suite *s = test_suite();

    SRunner *srunner = srunner_create(s);
    srunner_run_all(srunner, CK_NORMAL);

    size_t number_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
