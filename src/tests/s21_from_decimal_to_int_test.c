#include "test.h"

START_TEST(s21_from_decimal_to_int_test_1) {
  int num = 0;

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  s21_from_decimal_to_int(dec_1, &num);

  ck_assert_int_eq(num, dec_1.bits[0]);
  ck_assert_int_eq(0, dec_1.bits[1]);
  ck_assert_int_eq(0, dec_1.bits[2]);
  ck_assert_int_eq(0, dec_1.bits[3]);

  s21_decimal dec_2 = {{9632154, 0, 0, 0}};
  s21_from_decimal_to_int(dec_2, &num);

  ck_assert_int_eq(num, dec_2.bits[0]);
  ck_assert_int_eq(0, dec_2.bits[1]);
  ck_assert_int_eq(0, dec_2.bits[2]);
  ck_assert_int_eq(0, dec_2.bits[3]);

  s21_decimal dec_3 = {{75982, 0, 0, 0}};
  s21_from_decimal_to_int(dec_3, &num);

  ck_assert_int_eq(num, dec_3.bits[0]);
  ck_assert_int_eq(0, dec_3.bits[1]);
  ck_assert_int_eq(0, dec_3.bits[2]);
  ck_assert_int_eq(0, dec_3.bits[3]);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_2) {
  int num = 0;

  s21_decimal dec_1 = {{12345678, 0, 0, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(s21_from_decimal_to_int(dec_1, &num), 0);

  ck_assert_int_eq(num * -1, dec_1.bits[0]);
  ck_assert_int_eq(0, dec_1.bits[1]);
  ck_assert_int_eq(0, dec_1.bits[2]);
  ck_assert_int_eq((int)0b10000000000000000000000000000000, dec_1.bits[3]);

  s21_decimal dec_2 = {{9632154, 0, 0, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(s21_from_decimal_to_int(dec_2, &num), 0);

  ck_assert_int_eq(num * -1, dec_2.bits[0]);
  ck_assert_int_eq(0, dec_2.bits[1]);
  ck_assert_int_eq(0, dec_2.bits[2]);
  ck_assert_int_eq((int)0b10000000000000000000000000000000, dec_2.bits[3]);

  s21_decimal dec_3 = {{75982, 0, 0, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(s21_from_decimal_to_int(dec_3, &num), 0);

  ck_assert_int_eq(num * -1, dec_3.bits[0]);
  ck_assert_int_eq(0, dec_3.bits[1]);
  ck_assert_int_eq(0, dec_3.bits[2]);
  ck_assert_int_eq((int)0b10000000000000000000000000000000, dec_3.bits[3]);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_3) {
  int num = 777;

  s21_decimal dec_1 = {{12345678, 9, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(dec_1, &num), 1);

  ck_assert_int_eq(num, 777);

  s21_decimal dec_2 = {{0, 0, 9, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(s21_from_decimal_to_int(dec_2, &num), 1);

  ck_assert_int_eq(num, 777);

  s21_decimal dec_3 = {{0b11111111111111111111111111111111, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(dec_3, &num), 1);

  ck_assert_int_eq(num, 777);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_4) {
  int num = 0;

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 5);
  ck_assert_int_eq(s21_from_decimal_to_int(dec_1, &num), 0);

  ck_assert_int_eq(num, 123);

  s21_decimal dec_2 = {{9632154, 0, 0, 0b10000000000000000000000000000000}};
  set_scale(&dec_2, 2);
  ck_assert_int_eq(s21_from_decimal_to_int(dec_2, &num), 0);

  ck_assert_int_eq(num, -96321);

  s21_decimal dec_3 = {{75982, 0, 0, 0}};
  set_scale(&dec_3, 5);
  ck_assert_int_eq(s21_from_decimal_to_int(dec_3, &num), 0);

  ck_assert_int_eq(num, 0);
}
END_TEST

Suite *s21_from_decimal_to_int_test() {
  Suite *s;
  TCase *tc_from_decimal_to_int_test_1, *tc_from_decimal_to_int_test_2,
      *tc_from_decimal_to_int_test_3, *tc_from_decimal_to_int_test_4;

  s = suite_create("s21_from_decimal_to_int");

  tc_from_decimal_to_int_test_1 =
      tcase_create("s21_from_decimal_to_int_test_1");
  tcase_add_test(tc_from_decimal_to_int_test_1, s21_from_decimal_to_int_test_1);
  suite_add_tcase(s, tc_from_decimal_to_int_test_1);

  tc_from_decimal_to_int_test_2 =
      tcase_create("s21_from_decimal_to_int_test_2");
  tcase_add_test(tc_from_decimal_to_int_test_2, s21_from_decimal_to_int_test_2);
  suite_add_tcase(s, tc_from_decimal_to_int_test_2);

  tc_from_decimal_to_int_test_3 =
      tcase_create("s21_from_decimal_to_int_test_3");
  tcase_add_test(tc_from_decimal_to_int_test_3, s21_from_decimal_to_int_test_3);
  suite_add_tcase(s, tc_from_decimal_to_int_test_3);

  tc_from_decimal_to_int_test_4 =
      tcase_create("s21_from_decimal_to_int_test_4");
  tcase_add_test(tc_from_decimal_to_int_test_4, s21_from_decimal_to_int_test_4);
  suite_add_tcase(s, tc_from_decimal_to_int_test_4);

  return s;
}
