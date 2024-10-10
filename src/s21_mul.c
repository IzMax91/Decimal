#include "big_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal big_value_1 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal big_value_2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal big_result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  null_decimal(result);

  decimal_to_big(value_1, &big_value_1);
  decimal_to_big(value_2, &big_value_2);

  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  int common_scale = scale_1 + scale_2;
  int new_scale = common_scale;

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int common_sign = -1;

  int flag = 0;

  if (sign_1 == 1 && sign_2 == 1) {
    common_sign = 0;
  } else if ((sign_1 == 1 && sign_2 == 0) || (sign_1 == 0 && sign_2 == 1)) {
    common_sign = 1;
  } else {
    common_sign = 0;
  }

  for (int i = 0; i < 256; ++i) {
    if (big_get_bit(big_value_1, i) == 1) {
      s21_big_decimal big_shifted_2 = big_shift_bits(big_value_2, -i);
      big_result = big_sum_decimal(big_result, big_shifted_2);
    }
  }
  new_scale = banking_round(&big_result, common_scale);

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
    set_scale(result, new_scale);
    set_sign(result, common_sign);
  }

  return flag;
}
