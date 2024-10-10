#include <stdio.h>
#include <stdlib.h>

#include "test.h"

START_TEST(test_div1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div4) {
  // 3.9614081257132168796771975168
  s21_decimal decimal1 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0000000000000000000000000005
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}
START_TEST(test_div5) {
  // 4294967297
  s21_decimal decimal1 = {{0x1, 0x1, 0x0, 0x0}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // 536870912.125
  s21_decimal decimal_check = {{0x7D, 0x7D, 0x0, 0x30000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div6) {
  // 3.9614081257132168796771975168
  s21_decimal decimal1 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0000000000000000000000000005
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div7) {
  // 1.9999999999999999999999999999
  s21_decimal decimal1 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 0.000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x90000}};
  // 0
  int code = TEST_ARITHMETIC_ZERO_DIV;

  test_div_fail1(decimal1, decimal2, code);
}

Suite *div_suite1(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("div1");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_div1);
  tcase_add_test(tc_core, test_div2);
  tcase_add_test(tc_core, test_div3);
  tcase_add_test(tc_core, test_div4);
  tcase_add_test(tc_core, test_div5);
  tcase_add_test(tc_core, test_div6);
  tcase_add_test(tc_core, test_div7);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
}

void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
