#include <stdio.h>
#include <stdlib.h>

#include "test.h"

START_TEST(test_mul1) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul2) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  set_sign(&decimal2, 1);
  // -overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul3) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul4) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 52818775009509558395695964249
  s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul5) {
  // -7055.820576069728775806815669
  s21_decimal decimal1 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // -49784604.001688959238158904099
  s21_decimal decimal_check = {
      {0x40136B23, 0xBF8285B9, 0xA0DCDBF6, 0x80150000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul6) {
  // 7055.820576069728775806815669
  s21_decimal decimal1 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000007056
  s21_decimal decimal_check = {{0x1B90, 0x0, 0x0, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul7) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

Suite *mul_suite1(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("mul1");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_mul1);
  tcase_add_test(tc_core, test_mul2);
  tcase_add_test(tc_core, test_mul3);
  tcase_add_test(tc_core, test_mul4);
  tcase_add_test(tc_core, test_mul5);
  tcase_add_test(tc_core, test_mul6);
  tcase_add_test(tc_core, test_mul7);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
}

void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}