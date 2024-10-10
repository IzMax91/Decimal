#include "test.h"

START_TEST(s21_is_equal_test_1) {
  s21_decimal dec1 = {{123, 0, 0, 0}};  // 123
  s21_decimal dec2 = {{57, 0, 0, 0}};   // -57
  set_sign(&dec2, 1);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_2) {
  s21_decimal dec1 = {
      {943631353, 926581834, 823645299, 0}};  // -15193574042146620.354957585401
  s21_decimal dec2 = {
      {693417853, 974334754, 823698313, 0}};  // 15194551.978042041222565246845
  set_sign(&dec1, 1);
  set_scale(&dec1, 12);
  set_scale(&dec2, 21);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_3) {
  s21_decimal dec1 = {{854914291, 0, 0, 0}};  // 8549142.91
  s21_decimal dec2 = {{595306241, 0, 0, 0}};  // -5953062.41
  set_sign(&dec2, 1);
  set_scale(&dec1, 2);
  set_scale(&dec2, 2);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_4) {
  s21_decimal dec1 = {{4365, 0, 0, 0}};    // -4365
  s21_decimal dec2 = {{934602, 0, 0, 0}};  // -934602
  set_sign(&dec1, 1);
  set_sign(&dec2, 1);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_5) {
  s21_decimal dec1 = {{857231, 0, 0, 0}};  // -857.231
  s21_decimal dec2 = {{857444, 0, 0, 0}};  // -857.444
  set_sign(&dec1, 1);
  set_sign(&dec2, 1);
  set_scale(&dec1, 3);
  set_scale(&dec2, 3);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_6) {
  s21_decimal dec1 = {
      {857231, 231235, 2131245, 0}};  // -39314531.074366260097389711
  s21_decimal dec2 = {
      {857444, 451231, 2123653, 0}};  // -3917448339430.3532806772068
  set_sign(&dec1, 1);
  set_sign(&dec2, 1);
  set_scale(&dec1, 18);
  set_scale(&dec2, 13);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_7) {
  s21_decimal dec1 = {{111, 111, 111, 0}};  // 20475885926.58501599343
  s21_decimal dec2 = {{131, 112, 111, 0}};  // 20475885926.62796566659
  set_scale(&dec1, 11);
  set_scale(&dec2, 11);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_8) {
  s21_decimal dec1 = {
      {992512350, 964884127, 999993470, 0}};  // 1844662362.0614896063514970462
  s21_decimal dec2 = {
      {868679658, 997548823, 999992365, 0}};  // 184466.03237102988415390384106
  set_scale(&dec1, 19);
  set_scale(&dec2, 23);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_9) {
  s21_decimal dec1 = {{4, 4, 4, 0}};  // 73786976312018075652
  s21_decimal dec2 = {{4, 4, 4, 0}};  // 73786976312018075652

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(s21_is_equal_test_10) {
  s21_decimal dec1 = {{0, 0, 0, 0}};  // -0
  s21_decimal dec2 = {{0, 0, 0, 0}};  // 0.0000000000000000000000000
  set_sign(&dec1, 1);
  set_scale(&dec2, 25);

  ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
}
END_TEST

Suite *s21_is_equal_test() {
  Suite *s;
  TCase *tc_is_equal_test_1, *tc_is_equal_test_2, *tc_is_equal_test_3,
      *tc_is_equal_test_4, *tc_is_equal_test_5, *tc_is_equal_test_6,
      *tc_is_equal_test_7, *tc_is_equal_test_8, *tc_is_equal_test_9,
      *tc_is_equal_test_10;

  s = suite_create("s21_is_equal");

  tc_is_equal_test_1 = tcase_create("s21_is_equal_test_1");
  tcase_add_test(tc_is_equal_test_1, s21_is_equal_test_1);
  suite_add_tcase(s, tc_is_equal_test_1);

  tc_is_equal_test_2 = tcase_create("s21_is_equal_test_2");
  tcase_add_test(tc_is_equal_test_2, s21_is_equal_test_2);
  suite_add_tcase(s, tc_is_equal_test_2);

  tc_is_equal_test_3 = tcase_create("s21_is_equal_test_3");
  tcase_add_test(tc_is_equal_test_3, s21_is_equal_test_3);
  suite_add_tcase(s, tc_is_equal_test_3);

  tc_is_equal_test_4 = tcase_create("s21_is_equal_test_4");
  tcase_add_test(tc_is_equal_test_4, s21_is_equal_test_4);
  suite_add_tcase(s, tc_is_equal_test_4);

  tc_is_equal_test_5 = tcase_create("s21_is_equal_test_5");
  tcase_add_test(tc_is_equal_test_5, s21_is_equal_test_5);
  suite_add_tcase(s, tc_is_equal_test_5);

  tc_is_equal_test_6 = tcase_create("s21_is_equal_test_6");
  tcase_add_test(tc_is_equal_test_6, s21_is_equal_test_6);
  suite_add_tcase(s, tc_is_equal_test_6);

  tc_is_equal_test_7 = tcase_create("s21_is_equal_test_7");
  tcase_add_test(tc_is_equal_test_7, s21_is_equal_test_7);
  suite_add_tcase(s, tc_is_equal_test_7);

  tc_is_equal_test_8 = tcase_create("s21_is_equal_test_8");
  tcase_add_test(tc_is_equal_test_8, s21_is_equal_test_8);
  suite_add_tcase(s, tc_is_equal_test_8);

  tc_is_equal_test_9 = tcase_create("s21_is_equal_test_9");
  tcase_add_test(tc_is_equal_test_9, s21_is_equal_test_9);
  suite_add_tcase(s, tc_is_equal_test_9);

  tc_is_equal_test_10 = tcase_create("s21_is_equal_test_10");
  tcase_add_test(tc_is_equal_test_10, s21_is_equal_test_10);
  suite_add_tcase(s, tc_is_equal_test_10);

  return s;
}