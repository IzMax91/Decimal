#include "test.h"

START_TEST(s21_truncate_test_1) {
  s21_decimal anwser = {{0, 0, 0, 0}};

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 4);
  s21_truncate(dec_1, &anwser);

  ck_assert_int_eq(anwser.bits[0], 1234);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);

  s21_decimal dec_2 = {{0, 1, 0, 0}};
  set_scale(&dec_2, 2);
  s21_truncate(dec_2, &anwser);

  ck_assert_int_eq(anwser.bits[0], 42949672);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);

  s21_decimal dec_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&dec_3, 25);
  s21_truncate(dec_3, &anwser);

  ck_assert_int_eq(anwser.bits[0], 7922);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_2) {
  s21_decimal anwser = {{0, 0, 0, 0}};

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 7);
  set_sign(&dec_1, 1);
  s21_truncate(dec_1, &anwser);

  ck_assert_int_eq(anwser.bits[0], 1);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_1), 1);

  s21_decimal dec_2 = {{0, 1, 0, 0}};
  set_scale(&dec_2, 7);
  set_sign(&dec_2, 1);
  s21_truncate(dec_2, &anwser);

  ck_assert_int_eq(anwser.bits[0], 429);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_2), 1);

  s21_decimal dec_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&dec_3, 20);
  set_sign(&dec_3, 1);
  s21_truncate(dec_3, &anwser);

  ck_assert_int_eq(anwser.bits[0], 792281625);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_3), 1);
}
END_TEST

Suite *s21_truncate_test() {
  Suite *s;
  TCase *tc_round_test_1, *tc_round_test_2;

  s = suite_create("s21_truncate");

  tc_round_test_1 = tcase_create("s21_truncate_test_1");
  tcase_add_test(tc_round_test_1, s21_truncate_test_1);
  suite_add_tcase(s, tc_round_test_1);

  tc_round_test_2 = tcase_create("s21_truncate_test_2");
  tcase_add_test(tc_round_test_2, s21_truncate_test_2);
  suite_add_tcase(s, tc_round_test_2);

  return s;
}