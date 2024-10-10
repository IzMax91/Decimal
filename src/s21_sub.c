#include "big_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal big_value_1 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal big_value_2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal big_result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  null_decimal(result);

  decimal_to_big(value_1, &big_value_1);
  decimal_to_big(value_2, &big_value_2);

  int exp_1 = get_scale(value_1);
  int exp_2 = get_scale(value_2);
  int exp_diff = 0;
  int is_bigger = 0;
  int biggest_exp = 0;
  int sign_1 = -1;
  int sign_2 = -1;
  int sign_common = -1;
  int flag = 0;
  int new_flag = 0;

  sign_1 = get_sign(value_1);
  sign_2 = get_sign(value_2);

  if (exp_1 > exp_2) {
    exp_diff = exp_1 - exp_2;
    is_bigger = 1;
    biggest_exp = exp_1;
  } else if (exp_1 < exp_2) {
    exp_diff = exp_2 - exp_1;
    is_bigger = 2;
    biggest_exp = exp_2;
  } else if (exp_1 == exp_2) {
    exp_diff = 0;
    is_bigger = 0;
    biggest_exp = exp_1;
  }

  if (is_bigger == 1) {
    for (int i = 0; i < exp_diff; ++i) {
      big_value_2 = big_multiply_by_10(big_value_2);
    }
  } else if (is_bigger == 2) {
    for (int i = 0; i < exp_diff; ++i) {
      big_value_1 = big_multiply_by_10(big_value_1);
    }
  }

  if (sign_1 == 1 && sign_2 == 0) {
    sign_common = 1;
    big_result = big_sum_decimal(big_value_1, big_value_2);
  } else if (sign_1 == 0 && sign_2 == 1) {
    sign_common = 0;
    big_result = big_sum_decimal(big_value_1, big_value_2);
  } else if (sign_1 == 0 && sign_2 == 0) {
    if (s21_is_greater_or_equal(value_1, value_2)) {
      sign_common = 0;
      big_result = big_subtraction_decimal(big_value_2, big_value_1);
      inverse_bits(&big_result);
    } else {
      sign_common = 1;
      big_result = big_subtraction_decimal(big_value_1, big_value_2);
      inverse_bits(&big_result);
    }
  } else if (sign_1 == 1 && sign_2 == 1) {
    if (s21_is_greater_or_equal(value_1, value_2)) {
      sign_common = 0;
      big_result = big_subtraction_decimal(big_value_1, big_value_2);
      inverse_bits(&big_result);
    } else {
      sign_common = 1;
      big_result = big_subtraction_decimal(big_value_2, big_value_1);
      inverse_bits(&big_result);
    }
  }

  if (sign_common == 0) {
    for (int i = 3; i < 8; ++i) {
      if (big_result.bits[i] != 0) {
        flag = 1;
      }
    }
  }

  if (sign_common == 1) {
    for (int i = 3; i < 8; ++i) {
      if (big_result.bits[i] != 0) {
        flag = 2;
      }
    }
  }

  if (flag == 1 || flag == 2) {
    biggest_exp = banking_round(&big_result, biggest_exp);
  }

  if (sign_common == 0) {
    for (int i = 3; i < 8; ++i) {
      if (big_result.bits[i] != 0) {
        new_flag = 1;
      }
    }
  }

  if (sign_common == 1) {
    for (int i = 3; i < 8; ++i) {
      if (big_result.bits[i] != 0) {
        new_flag = 2;
      }
    }
  }

  if (new_flag == 0) {
    big_to_decimal(result, big_result);
    set_scale(result, biggest_exp);
    set_sign(result, sign_common);
  }

  return new_flag;
}