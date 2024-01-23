
#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "_internal/memory.h"

START_TEST(test_memory_set_0) {
    char s[] = "Hello world!";
    int expected_value = 0;
    s21_memory_set(s, sizeof(s), expected_value);

    for (size_t i = 0; i < sizeof(s); ++i) {
        ck_assert_msg(s[i] == expected_value, "%c", s[i]);
    }
}
END_TEST

START_TEST(test_memory_set_1) {
    char s[] = "Hello world!";
    int expected_value = 1;
    s21_memory_set(s, sizeof(s), expected_value);

    for (size_t i = 0; i < sizeof(s); ++i) {
        ck_assert_msg(s[i] == expected_value, "%c", s[i]);
    }
}
END_TEST

START_TEST(test_memory_set_2) {
    char s[] = "Hello world!";
    int expected_value = -1;
    s21_memory_set(s, sizeof(s), expected_value);

    for (size_t i = 0; i < sizeof(s); ++i) {
        ck_assert_msg(s[i] == expected_value, "%c", s[i]);
    }
}
END_TEST

START_TEST(test_memory_copy_0) {
    const char s[] = "hello world!";
    char buf[sizeof(s)] = {0};
    s21_memory_copy(buf, s, sizeof(s));
    ck_assert_mem_eq(buf, s, sizeof(s));
}
END_TEST

START_TEST(test_memory_copy_1) {
    const char s[] = "";
    char buf[64] = {0};
    s21_memory_copy(buf, s, 1);
    ck_assert_mem_eq(buf, s, 1);
}
END_TEST

START_TEST(test_string_copy_0) {
    const char s[] = "hello world!";
    size_t s_length = strlen(s);

    char buf[s_length + 1];
    s21_string_copy(buf, s);
    ck_assert_mem_eq(buf, s, s_length);
}
END_TEST

START_TEST(test_string_copy_1) {
    const char s[] = "";
    size_t s_length = strlen(s);

    char buf[s_length + 1];
    s21_string_copy(buf, s);
    ck_assert_mem_eq(buf, s, s_length);
}
END_TEST

Suite *
test_suite(void) {
    Suite *s = suite_create("memory");

    TCase *tc_memory_set = tcase_create("memory_set");
    tcase_add_test(tc_memory_set, test_memory_set_0);
    tcase_add_test(tc_memory_set, test_memory_set_1);
    tcase_add_test(tc_memory_set, test_memory_set_2);

    TCase *tc_memory_copy = tcase_create("memory_copy");
    tcase_add_test(tc_memory_copy, test_memory_copy_0);
    tcase_add_test(tc_memory_copy, test_memory_copy_1);

    TCase *tc_string_copy = tcase_create("string_copy");
    tcase_add_test(tc_string_copy, test_string_copy_0);
    tcase_add_test(tc_string_copy, test_string_copy_1);

    suite_add_tcase(s, tc_memory_set);
    suite_add_tcase(s, tc_memory_copy);
    suite_add_tcase(s, tc_string_copy);
    return s;
}

int
main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
