#include "test.h"

START_TEST(s21_from_float_to_decimal_test_1) {
  s21_decimal dec = {{0, 0, 0, 0}};
  float num_1 = 1234567.89;

  s21_from_float_to_decimal(num_1, &dec);

  ck_assert_int_eq(dec.bits[0], 1234568);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);

  float num_2 = 963.2154999;

  s21_from_float_to_decimal(num_2, &dec);

  ck_assert_int_eq(dec.bits[0], 9632155);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(get_scale(dec), 4);
  ck_assert_int_eq(get_sign(dec), 0);

  float num_3 = 0.7598228957;

  s21_from_float_to_decimal(num_3, &dec);

  ck_assert_int_eq(dec.bits[0], 7598229);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(get_scale(dec), 7);
  ck_assert_int_eq(get_sign(dec), 0);

  float num_4 = 1234567890123456789012345678.0;

  s21_from_float_to_decimal(num_4, &dec);

  ck_assert_int_eq(dec.bits[0], 0b00000101000000000000000000000000);
  ck_assert_int_eq(dec.bits[1], 0b01100010010100010110000001111000);
  ck_assert_int_eq(dec.bits[2], 0b00000011111111010011010111110001);
  ck_assert_int_eq(get_scale(dec), 0);
  ck_assert_int_eq(get_sign(dec), 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_2) {
  s21_decimal dec = {{0, 0, 0, 0}};
  float num_1 = -1234567.89;

  s21_from_float_to_decimal(num_1, &dec);

  ck_assert_int_eq(dec.bits[0], 1234568);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(get_scale(dec), 0);
  ck_assert_int_eq(get_sign(dec), 1);

  float num_2 = -963.2154999;

  s21_from_float_to_decimal(num_2, &dec);

  ck_assert_int_eq(dec.bits[0], 9632155);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(get_scale(dec), 4);
  ck_assert_int_eq(get_sign(dec), 1);

  float num_3 = -0.7598228957;

  s21_from_float_to_decimal(num_3, &dec);

  ck_assert_int_eq(dec.bits[0], 7598229);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(get_scale(dec), 7);
  ck_assert_int_eq(get_sign(dec), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_3) {
  s21_decimal dec = {{0, 0, 0, 0}};
  float num_1 = 0.0000000000000000000000000001;

  s21_from_float_to_decimal(num_1, &dec);

  ck_assert_int_eq(dec.bits[0], 1);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(get_scale(dec), 28);
  ck_assert_int_eq(get_sign(dec), 0);

  float num_2 = 0.00000000000000000000000000009;

  ck_assert_int_eq(s21_from_float_to_decimal(num_2, &dec), 1);

  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);

  float num_3 = 0;
  int *p_num_3 = (int *)&num_3;
  *p_num_3 = 0b01111111100000000000000000000000;

  ck_assert_int_eq(s21_from_float_to_decimal(num_3, &dec), 1);

  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);

  float num_4 = 0;
  int *p_num_4 = (int *)&num_4;
  *p_num_4 = 0b11111111100000000000000000000000;

  ck_assert_int_eq(s21_from_float_to_decimal(num_4, &dec), 1);

  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

Suite *s21_from_float_to_decimal_test() {
  Suite *s;
  TCase *tc_from_float_to_decimal_test_1, *tc_from_float_to_decimal_test_2,
      *tc_from_float_to_decimal_test_3;

  s = suite_create("s21_from_float_to_decimal");

  tc_from_float_to_decimal_test_1 =
      tcase_create("s21_from_float_to_decimal_test_1");
  tcase_add_test(tc_from_float_to_decimal_test_1,
                 s21_from_float_to_decimal_test_1);
  suite_add_tcase(s, tc_from_float_to_decimal_test_1);

  tc_from_float_to_decimal_test_2 =
      tcase_create("s21_from_float_to_decimal_test_2");
  tcase_add_test(tc_from_float_to_decimal_test_2,
                 s21_from_float_to_decimal_test_2);
  suite_add_tcase(s, tc_from_float_to_decimal_test_2);

  tc_from_float_to_decimal_test_3 =
      tcase_create("s21_from_float_to_decimal_test_3");
  tcase_add_test(tc_from_float_to_decimal_test_3,
                 s21_from_float_to_decimal_test_3);
  suite_add_tcase(s, tc_from_float_to_decimal_test_3);

  return s;
}