#include "big_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal big_value_1 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal big_value_2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal big_result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal inter_result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  null_decimal(result);

  decimal_to_big(value_1, &big_value_1);
  decimal_to_big(value_2, &big_value_2);

  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  int common_scale = scale_1 - scale_2;

  int flag = 0;

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int common_sign = -1;

  if (sign_1 == 1 && sign_2 == 1) {
    common_sign = 0;
  } else if ((sign_1 == 1 && sign_2 == 0) || (sign_1 == 0 && sign_2 == 1)) {
    common_sign = 1;
  } else {
    common_sign = 0;
  }

  if (is_zero(value_2)) {
    flag = 3;
  }
  if (flag != 3) {
    int i = 0;
    while (big_comparison(big_value_1,
                          (s21_big_decimal){{0, 0, 0, 0, 0, 0, 0, 0}}) == 1 &&
           i < 60) {
      common_scale += 1;
      inter_result = big_division(&big_value_1, big_value_2);
      if (big_comparison(big_value_1, big_value_2) == 0) {
        inter_result = big_sum_decimal(
            inter_result, (s21_big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}});
        big_value_1 = big_subtraction_decimal(big_value_2, big_value_1);
        inverse_bits(&big_value_1);
      }

      big_value_1 = big_multiply_by_10(big_value_1);
      ++i;
      big_result = big_multiply_by_10(big_result);
      big_result = big_sum_decimal(big_result, inter_result);
    }
    common_scale -= 1;
  }

  if (common_scale < 0) {
    while (common_scale < 0) {
      big_result = big_multiply_by_10(big_result);
      common_scale++;
    }
  }

  common_scale = banking_round(&big_result, common_scale);

  if (common_sign == 0) {
    for (int i = 3; i < 8; ++i) {
      if (big_result.bits[i] != 0) {
        flag = 1;
      }
    }
  }

  if (common_sign == 1) {
    for (int i = 3; i < 8; ++i) {
      if (big_result.bits[i] != 0) {
        flag = 2;
      }
    }
  }

  if (flag == 0) {
    big_to_decimal(result, big_result);
    set_scale(result, common_scale);
    set_sign(result, common_sign);
  }

  return flag;
}

s21_big_decimal big_division(s21_big_decimal *value_1,
                             s21_big_decimal value_2) {
  s21_big_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal shifted_bit = {{1, 0, 0, 0, 0, 0, 0, 0}};
  while (big_comparison(*value_1, value_2) == 1) {
    s21_big_decimal del = value_2;
    int i = 0;

    if (big_comparison(del, *value_1) == 2 ||
        big_comparison(del, *value_1) == 0) {
      while (big_comparison(del, *value_1) == 2 ||
             big_comparison(del, *value_1) == 0) {
        del = big_shift_bits(del, -1);
        ++i;
      }
      del = big_shift_bits(del, 1);
      i--;
    }

    res = big_sum_decimal(res, big_shift_bits(shifted_bit, -i));

    if (big_comparison(*value_1, del) == 1 ||
        big_comparison(*value_1, del) == 0) {
      *value_1 = big_subtraction_decimal(del, *value_1);
    }
    del = big_shift_bits(del, -i);
    inverse_bits(value_1);
  }

  return res;
}