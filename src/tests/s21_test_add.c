#include <stdio.h>
#include <stdlib.h>

#include "test.h"

START_TEST(test_add1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{-1, -1, -1, 0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{-1, -1, -1, 0}};
  set_sign(&decimal2, 1);
  // 0
  s21_decimal check = {{0, 0, 0, 0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add3) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  set_sign(&decimal1, 1);
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{-1, -1, -1, 0}};
  set_sign(&decimal2, 1);
  // -overflow
  int check = TEST_ARITHMETIC_SMALL;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  // 0.5
  s21_decimal decimal2 = {{5, 0, 0, 0}};
  set_scale(&decimal2, 1);
  // overflow

  int check = TEST_ARITHMETIC_BIG;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  // 0.499999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x0}};
  set_scale(&decimal2, 28);
  // 79228162514264337593543950335
  s21_decimal check = {{-1, -1, -1, 0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add6) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 0.500000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x0}};
  set_scale(&decimal2, 28);
  // 79228162514264337593543950335
  s21_decimal check = {{-1, -1, -1, 0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add7) {
  // 38
  s21_decimal decimal1 = {{38, 0, 0, 0}};
  // 59
  s21_decimal decimal2 = {{59, 0, 0, 0}};
  // 97
  s21_decimal check = {{97, 0, 0, 0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add8) {
  // 38
  s21_decimal decimal1 = {{38, 0, 0, 0}};
  // -59
  s21_decimal decimal2 = {{59, 0, 0, 0}};
  set_sign(&decimal2, 1);
  // -21
  s21_decimal check = {{21, 0, 0, 0}};
  set_sign(&check, 1);

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add9) {
  // 38,5
  s21_decimal decimal1 = {{385, 0, 0, 0}};
  set_scale(&decimal1, 1);
  // -59
  s21_decimal decimal2 = {{59, 0, 0, 0}};
  set_sign(&decimal2, 1);
  // -20.5
  s21_decimal check = {{205, 0, 0, 0}};
  set_sign(&check, 1);
  set_scale(&check, 1);

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add10) {
  // -38,5
  s21_decimal decimal1 = {{385, 0, 0, 0}};
  set_sign(&decimal1, 1);
  set_scale(&decimal1, 1);
  // 59
  s21_decimal decimal2 = {{59, 0, 0, 0}};
  // 20.5
  s21_decimal check = {{205, 0, 0, 0}};
  set_scale(&check, 1);

  test_add(decimal1, decimal2, check);
}

Suite *add_suite1(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("add1");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_add1);
  tcase_add_test(tc_core, test_add2);
  tcase_add_test(tc_core, test_add3);
  tcase_add_test(tc_core, test_add4);
  tcase_add_test(tc_core, test_add5);
  tcase_add_test(tc_core, test_add6);
  tcase_add_test(tc_core, test_add7);
  tcase_add_test(tc_core, test_add8);
  tcase_add_test(tc_core, test_add9);
  tcase_add_test(tc_core, test_add10);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, check);
}
