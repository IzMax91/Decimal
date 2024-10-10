#include "test.h"

START_TEST(s21_round_test_1) {
  s21_decimal anwser = {{0, 0, 0, 0}};

  s21_decimal dec_1 = {{12345, 0, 0, 0}};
  set_scale(&dec_1, 2);
  s21_round(dec_1, &anwser);

  ck_assert_int_eq(anwser.bits[0], 123);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);

  s21_decimal dec_2 = {{12355, 0, 0, 0}};
  set_scale(&dec_2, 2);
  s21_round(dec_2, &anwser);

  ck_assert_int_eq(anwser.bits[0], 124);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);

  s21_decimal dec_3 = {{12388, 0, 0, 0}};
  set_scale(&dec_3, 2);
  s21_round(dec_3, &anwser);

  ck_assert_int_eq(anwser.bits[0], 124);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_2) {
  s21_decimal anwser = {{0, 0, 0, 0}};

  s21_decimal dec_1 = {{2323, 0, 0, 0}};
  set_scale(&dec_1, 1);
  set_sign(&dec_1, 1);
  s21_round(dec_1, &anwser);

  ck_assert_int_eq(anwser.bits[0], 232);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_1), 1);

  s21_decimal dec_2 = {{2325, 0, 0, 0}};
  set_scale(&dec_2, 1);
  set_sign(&dec_2, 1);
  s21_round(dec_2, &anwser);

  ck_assert_int_eq(anwser.bits[0], 232);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_2), 1);

  s21_decimal dec_3 = {{2327, 0, 0, 0}};
  set_scale(&dec_3, 1);
  set_sign(&dec_3, 1);
  s21_round(dec_3, &anwser);

  ck_assert_int_eq(anwser.bits[0], 233);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_3), 1);
}
END_TEST

Suite *s21_round_test() {
  Suite *s;
  TCase *tc_round_test_1, *tc_round_test_2;

  s = suite_create("s21_round");

  tc_round_test_1 = tcase_create("s21_round_test_1");
  tcase_add_test(tc_round_test_1, s21_round_test_1);
  suite_add_tcase(s, tc_round_test_1);

  tc_round_test_2 = tcase_create("s21_round_test_2");
  tcase_add_test(tc_round_test_2, s21_round_test_2);
  suite_add_tcase(s, tc_round_test_2);

  return s;
}