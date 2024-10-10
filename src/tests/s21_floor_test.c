#include "test.h"

START_TEST(s21_floor_test_1) {
  s21_decimal anwser = {{0, 0, 0, 0}};

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 5);
  s21_floor(dec_1, &anwser);

  ck_assert_int_eq(anwser.bits[0], 123);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);

  s21_decimal dec_2 = {{0, 1, 0, 0}};
  set_scale(&dec_2, 6);
  s21_floor(dec_2, &anwser);

  ck_assert_int_eq(anwser.bits[0], 4294);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);

  s21_decimal dec_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&dec_3, 28);
  s21_floor(dec_3, &anwser);

  ck_assert_int_eq(anwser.bits[0], 7);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(anwser.bits[3], 0);
}
END_TEST

START_TEST(s21_floor_test_2) {
  s21_decimal anwser = {{0, 0, 0, 0}};

  s21_decimal dec_1 = {{12345678, 0, 0, 0}};
  set_scale(&dec_1, 5);
  set_sign(&dec_1, 1);
  s21_floor(dec_1, &anwser);

  ck_assert_int_eq(anwser.bits[0], 124);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_1), 1);

  s21_decimal dec_2 = {{0, 1, 0, 0}};
  set_scale(&dec_2, 6);
  set_sign(&dec_2, 1);
  s21_floor(dec_2, &anwser);

  ck_assert_int_eq(anwser.bits[0], 4295);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_2), 1);

  s21_decimal dec_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&dec_3, 28);
  set_sign(&dec_3, 1);
  s21_floor(dec_3, &anwser);

  ck_assert_int_eq(anwser.bits[0], 8);
  ck_assert_int_eq(anwser.bits[1], 0);
  ck_assert_int_eq(anwser.bits[2], 0);
  ck_assert_int_eq(get_sign(dec_3), 1);
}
END_TEST

Suite *s21_floor_test() {
  Suite *s;
  TCase *tc_floor_test_1, *tc_floor_test_2;

  s = suite_create("s21_floor");

  tc_floor_test_1 = tcase_create("s21_floor_test_1");
  tcase_add_test(tc_floor_test_1, s21_floor_test_1);
  suite_add_tcase(s, tc_floor_test_1);

  tc_floor_test_2 = tcase_create("s21_floor_test_2");
  tcase_add_test(tc_floor_test_2, s21_floor_test_2);
  suite_add_tcase(s, tc_floor_test_2);

  return s;
}