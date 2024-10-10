#include <stdio.h>
#include <stdlib.h>

#include "test.h"

START_TEST(test_sub1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{-1, -1, -1, 0}};
  // 0
  s21_decimal check = {{0, 0, 0, 0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{-1, -1, -1, 0}};
  set_sign(&decimal2, 1);
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub3) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  set_sign(&decimal1, 1);
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{-1, -1, -1, 0}};
  set_sign(&decimal2, 1);
  // 0
  s21_decimal check = {{0, 0, 0, 0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  // 0.5
  s21_decimal decimal2 = {{5, 0, 0, 0}};
  set_scale(&decimal2, 1);
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  // 0.499999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x0}};
  set_scale(&decimal2, 28);
  // 79228162514264337593543950335
  s21_decimal check = {{-1, -1, -1, 0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub6) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 0.500000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x0}};
  set_scale(&decimal2, 28);
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub7) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{-1, -1, -1, 0}};
  set_sign(&decimal1, 1);
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{-1, -1, -1, 0}};
  // -overflow
  int check = TEST_ARITHMETIC_SMALL;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub8) {
  // 157
  s21_decimal decimal1 = {{157, 0, 0, 0}};
  // 72
  s21_decimal decimal2 = {{72, 0, 0, 0}};
  // 85
  s21_decimal check = {{85, 0, 0, 0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub9) {
  // -15.7
  s21_decimal decimal1 = {{157, 0, 0, 0}};
  set_sign(&decimal1, 1);
  set_scale(&decimal1, 1);
  // 72
  s21_decimal decimal2 = {{72, 0, 0, 0}};
  // -87.7
  s21_decimal check = {{877, 0, 0, 0}};
  set_sign(&check, 1);
  set_scale(&check, 1);

  test_sub(decimal1, decimal2, check);
}

Suite *sub_suite1(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sub1");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sub1);
  tcase_add_test(tc_core, test_sub2);
  tcase_add_test(tc_core, test_sub3);
  tcase_add_test(tc_core, test_sub4);
  tcase_add_test(tc_core, test_sub5);
  tcase_add_test(tc_core, test_sub6);
  tcase_add_test(tc_core, test_sub7);
  tcase_add_test(tc_core, test_sub8);
  tcase_add_test(tc_core, test_sub9);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, check);
}