#include "big_decimal.h"
#include "s21_decimal.h"

char s21_main_def(s21_decimal num_1, s21_decimal num_2) {
  char res = '\0';
  int i = 0;
  int count = 0;
  int bit_num_1 = 0;
  int bit_num_2 = 0;
  int total_sign = 0;
  int scale_num_1 = get_scale(num_1);
  int scale_num_2 = get_scale(num_2);
  int sign_num_1 = get_sign(num_1);
  int sign_num_2 = get_sign(num_2);

  if (is_zero(num_1) && is_zero(num_2))
    res = '=';
  else if (sign_num_1 > sign_num_2)
    res = '<';
  else if (sign_num_1 < sign_num_2)
    res = '>';
  else if (sign_num_1 == sign_num_2) {
    total_sign = sign_num_1;
    if (scale_num_1 == scale_num_2) {
      for (i = 95; i > -1; i--) {
        bit_num_1 = get_bit(num_1, i);
        bit_num_2 = get_bit(num_2, i);

        if (bit_num_1 == bit_num_2)
          count++;
        else if (bit_num_1 < bit_num_2) {
          res = '<';
          break;
        } else if (bit_num_1 > bit_num_2) {
          res = '>';
          break;
        }
      }
    } else {
      s21_big_decimal num_01 = {{0, 0, 0, 0, 0, 0, 0, 0}};
      s21_big_decimal num_02 = {{0, 0, 0, 0, 0, 0, 0, 0}};
      int bit_num_01 = 0;
      int bit_num_02 = 0;
      int diff_scale = 0;
      int min_scale = 0;
      decimal_to_big(num_1, &num_01);
      decimal_to_big(num_2, &num_02);

      if (scale_num_2 < scale_num_1) {
        min_scale = 1;
        diff_scale = scale_num_1 - scale_num_2;
      } else
        diff_scale = scale_num_2 - scale_num_1;

      for (; diff_scale > 0; diff_scale--) {
        if (min_scale) {
          num_02 = big_multiply_by_10(num_02);
        } else {
          num_01 = big_multiply_by_10(num_01);
        }
      }
      for (i = 255; i > -1; i--) {
        bit_num_01 = big_get_bit(num_01, i);
        bit_num_02 = big_get_bit(num_02, i);

        if (bit_num_01 < bit_num_02) {
          res = '<';
          break;
        } else if (bit_num_01 > bit_num_02) {
          res = '>';
          break;
        }
      }
    }
  }

  if (count == 96)
    res = '=';
  else if (total_sign) {
    if (res == '<')
      res = '>';
    else
      res = '<';
  }

  return res;
}

int s21_is_less(s21_decimal num_1, s21_decimal num_2) {
  char result = s21_main_def(num_1, num_2);
  int answer = 0;
  if (result == '<') answer = 1;
  return answer;
}

int s21_is_less_or_equal(s21_decimal num_1, s21_decimal num_2) {
  char result = s21_main_def(num_1, num_2);
  int answer = 0;
  if (result == '<' || result == '=') answer = 1;
  return answer;
}

int s21_is_greater(s21_decimal num_1, s21_decimal num_2) {
  char result = s21_main_def(num_1, num_2);
  int answer = 0;
  if (result == '>') answer = 1;
  return answer;
}

int s21_is_greater_or_equal(s21_decimal num_1, s21_decimal num_2) {
  char result = s21_main_def(num_1, num_2);
  int answer = 0;
  if (result == '>' || result == '=') answer = 1;
  return answer;
}

int s21_is_equal(s21_decimal num_1, s21_decimal num_2) {
  char result = s21_main_def(num_1, num_2);
  int answer = 0;
  if (result == '=') answer = 1;
  return answer;
}

int s21_is_not_equal(s21_decimal num_1, s21_decimal num_2) {
  char result = s21_main_def(num_1, num_2);
  int answer = 0;
  if (result == '<' || result == '>') answer = 1;
  return answer;
}