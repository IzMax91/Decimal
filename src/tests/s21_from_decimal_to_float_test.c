#include "test.h"

START_TEST(s21_from_decimal_to_float_1) {
  float num = 0;

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 4);
  s21_from_decimal_to_float(dec_1, &num);

  ck_assert_float_eq(num, 1234.5678);

  s21_decimal dec_2 = {{0, 1, 0, 0}};
  set_scale(&dec_2, 8);
  s21_from_decimal_to_float(dec_2, &num);

  ck_assert_float_eq(num, 42.94967296);

  s21_decimal dec_3 = {{75982, 0, 0, 0}};
  set_scale(&dec_3, 5);
  s21_from_decimal_to_float(dec_3, &num);

  ck_assert_float_eq(num, 0.75982);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  float num = 0;

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 4);
  set_sign(&dec_1, 1);
  s21_from_decimal_to_float(dec_1, &num);

  ck_assert_float_eq(num, -1234.5678);

  s21_decimal dec_2 = {{0, 1, 0, 0}};
  set_scale(&dec_2, 8);
  set_sign(&dec_2, 1);
  s21_from_decimal_to_float(dec_2, &num);

  ck_assert_float_eq(num, -42.94967296);

  s21_decimal dec_3 = {{75982, 0, 0, 0}};
  set_scale(&dec_3, 5);
  set_sign(&dec_3, 1);
  s21_from_decimal_to_float(dec_3, &num);

  ck_assert_float_eq(num, -0.75982);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  float num = 0;

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 10);
  s21_from_decimal_to_float(dec_1, &num);

  ck_assert_float_eq(num, 0.0012345678);

  s21_decimal dec_2 = {{0b00000101000000000000000000000000,
                        0b01100010010100010110000001111000,
                        0b00000011111111010011010111110001, 0}};
  set_scale(&dec_2, 21);
  set_sign(&dec_2, 1);
  s21_from_decimal_to_float(dec_2, &num);

  ck_assert_float_eq(num, -1234568.0);

  //   -1.23457e+27 - 1.23457e+27
}
END_TEST

Suite *s21_from_decimal_to_float_test() {
  Suite *s;
  TCase *tc_from_decimal_to_float_1, *tc_from_decimal_to_float_2,
      *tc_from_decimal_to_float_3;

  s = suite_create("s21_from_decimal_to_float");

  tc_from_decimal_to_float_1 = tcase_create("s21_from_decimal_to_float_1");
  tcase_add_test(tc_from_decimal_to_float_1, s21_from_decimal_to_float_1);
  suite_add_tcase(s, tc_from_decimal_to_float_1);

  tc_from_decimal_to_float_2 = tcase_create("s21_from_decimal_to_float_2");
  tcase_add_test(tc_from_decimal_to_float_2, s21_from_decimal_to_float_2);
  suite_add_tcase(s, tc_from_decimal_to_float_2);

  tc_from_decimal_to_float_3 = tcase_create("s21_from_decimal_to_float_3");
  tcase_add_test(tc_from_decimal_to_float_3, s21_from_decimal_to_float_3);
  suite_add_tcase(s, tc_from_decimal_to_float_3);

  return s;
}