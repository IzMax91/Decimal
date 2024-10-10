#include "test.h"

START_TEST(s21_negate_test_1) {
  s21_decimal anwser = {{0, 0, 0, 0}};

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 4);
  s21_negate(dec_1, &anwser);

  ck_assert_int_eq(anwser.bits[0], dec_1.bits[0]);
  ck_assert_int_eq(anwser.bits[1], dec_1.bits[1]);
  ck_assert_int_eq(anwser.bits[2], dec_1.bits[2]);
  ck_assert_int_eq(get_scale(anwser), get_scale(dec_1));
  ck_assert_int_eq(get_sign(anwser), get_sign(dec_1) ^ 1);

  s21_decimal dec_2 = {{0, 1, 0, 0}};
  set_scale(&dec_2, 2);
  s21_negate(dec_2, &anwser);

  ck_assert_int_eq(anwser.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(anwser.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(anwser.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(get_scale(anwser), get_scale(dec_2));
  ck_assert_int_eq(get_sign(anwser), get_sign(dec_2) ^ 1);

  s21_decimal dec_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&dec_3, 25);
  s21_negate(dec_3, &anwser);

  ck_assert_int_eq(anwser.bits[0], dec_3.bits[0]);
  ck_assert_int_eq(anwser.bits[1], dec_3.bits[1]);
  ck_assert_int_eq(anwser.bits[2], dec_3.bits[2]);
  ck_assert_int_eq(get_scale(anwser), get_scale(dec_3));
  ck_assert_int_eq(get_sign(anwser), get_sign(dec_3) ^ 1);
}
END_TEST

START_TEST(s21_negate_test_2) {
  s21_decimal anwser = {{0, 0, 0, 0}};

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 7);
  set_sign(&dec_1, 1);
  s21_negate(dec_1, &anwser);

  ck_assert_int_eq(anwser.bits[0], dec_1.bits[0]);
  ck_assert_int_eq(anwser.bits[1], dec_1.bits[1]);
  ck_assert_int_eq(anwser.bits[2], dec_1.bits[2]);
  ck_assert_int_eq(get_scale(anwser), get_scale(dec_1));
  ck_assert_int_eq(get_sign(anwser), get_sign(dec_1) ^ 1);

  s21_decimal dec_2 = {{0, 1, 0, 0}};
  set_scale(&dec_2, 7);
  set_sign(&dec_2, 1);
  s21_negate(dec_2, &anwser);

  ck_assert_int_eq(anwser.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(anwser.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(anwser.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(get_scale(anwser), get_scale(dec_2));
  ck_assert_int_eq(get_sign(anwser), get_sign(dec_2) ^ 1);

  s21_decimal dec_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&dec_3, 20);
  set_sign(&dec_3, 1);
  s21_negate(dec_3, &anwser);

  ck_assert_int_eq(anwser.bits[0], dec_3.bits[0]);
  ck_assert_int_eq(anwser.bits[1], dec_3.bits[1]);
  ck_assert_int_eq(anwser.bits[2], dec_3.bits[2]);
  ck_assert_int_eq(get_scale(anwser), get_scale(dec_3));
  ck_assert_int_eq(get_sign(anwser), get_sign(dec_3) ^ 1);
}
END_TEST

Suite *s21_negate_test() {
  Suite *s;
  TCase *tc_round_test_1, *tc_round_test_2;

  s = suite_create("s21_negate");

  tc_round_test_1 = tcase_create("s21_negate_test_1");
  tcase_add_test(tc_round_test_1, s21_negate_test_1);
  suite_add_tcase(s, tc_round_test_1);

  tc_round_test_2 = tcase_create("s21_negate_test_2");
  tcase_add_test(tc_round_test_2, s21_negate_test_2);
  suite_add_tcase(s, tc_round_test_2);

  return s;
}