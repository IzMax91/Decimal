#include "test.h"

START_TEST(s21_from_int_to_decimal_test_1) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int num_1 = 12345678;

  s21_from_int_to_decimal(num_1, &dec);

  ck_assert_int_eq(dec.bits[0], num_1);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);

  int num_2 = 9632154;

  s21_from_int_to_decimal(num_2, &dec);

  ck_assert_int_eq(dec.bits[0], num_2);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);

  int num_3 = 75982;

  s21_from_int_to_decimal(num_3, &dec);

  ck_assert_int_eq(dec.bits[0], num_3);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_2) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int num_1 = -12345678;

  s21_from_int_to_decimal(num_1, &dec);

  ck_assert_int_eq(dec.bits[0], num_1 * -1);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], (int)0b10000000000000000000000000000000);

  int num_2 = -9632154;

  s21_from_int_to_decimal(num_2, &dec);

  ck_assert_int_eq(dec.bits[0], num_2 * -1);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], (int)0b10000000000000000000000000000000);

  int num_3 = -75982;

  s21_from_int_to_decimal(num_3, &dec);

  ck_assert_int_eq(dec.bits[0], num_3 * -1);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], (int)0b10000000000000000000000000000000);
}
END_TEST

Suite *s21_from_int_to_decimal_test() {
  Suite *s;
  TCase *tc_from_int_to_decimal_test_1, *tc_from_int_to_decimal_test_2;

  s = suite_create("s21_from_int_to_decimal");

  tc_from_int_to_decimal_test_1 =
      tcase_create("s21_from_int_to_decimal_test_1");
  tcase_add_test(tc_from_int_to_decimal_test_1, s21_from_int_to_decimal_test_1);
  suite_add_tcase(s, tc_from_int_to_decimal_test_1);

  tc_from_int_to_decimal_test_2 =
      tcase_create("s21_from_int_to_decimal_test_1");
  tcase_add_test(tc_from_int_to_decimal_test_2, s21_from_int_to_decimal_test_2);
  suite_add_tcase(s, tc_from_int_to_decimal_test_2);

  return s;
}
