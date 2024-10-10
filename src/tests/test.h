#ifndef TESTS_S21_TESTS_H
#define TESTS_S21_TESTS_H

#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../big_decimal.h"
#include "../s21_decimal.h"

#define TEST_ARITHMETIC_OK 0
#define TEST_ARITHMETIC_BIG 1
#define TEST_ARITHMETIC_SMALL 2
#define TEST_ARITHMETIC_ZERO_DIV 3

Suite *add_suite1(void);
Suite *sub_suite1(void);
Suite *mul_suite1(void);
Suite *div_suite1(void);

Suite *s21_from_int_to_decimal_test(void);
Suite *s21_from_decimal_to_int_test(void);
Suite *s21_from_float_to_decimal_test(void);
Suite *s21_from_decimal_to_float_test(void);

Suite *s21_floor_test(void);
Suite *s21_round_test(void);
Suite *s21_truncate_test(void);
Suite *s21_negate_test(void);

Suite *s21_is_less_test(void);
Suite *s21_is_less_or_equal_test(void);
Suite *s21_is_greater_test(void);
Suite *s21_is_greater_or_equal_test(void);
Suite *s21_is_equal_test(void);
Suite *s21_is_not_equal_test(void);

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);

#endif  // TESTS_S21_TESTS_H
