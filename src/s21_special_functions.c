#include "s21_decimal.h"

int division_by_10(s21_decimal *dec) {
  s21_decimal q = sum_decimal(shift_bits(*dec, 1), shift_bits(*dec, 2));
  q = sum_decimal(q, shift_bits(q, 4));
  q = sum_decimal(q, shift_bits(q, 8));
  q = sum_decimal(q, shift_bits(q, 16));
  q = sum_decimal(q, shift_bits(q, 32));
  q = sum_decimal(q, shift_bits(q, 64));
  q = shift_bits(q, 3);
  s21_decimal r = subtraction_decimal(
      *dec, shift_bits(sum_decimal(shift_bits(q, -2), q), -1));

  s21_decimal res = {{1, 0, 0, 0}};
  if (r.bits[0] > 9) {
    res = sum_decimal(q, res);
  } else {
    res = q;
  }

  if (get_sign(*dec)) {
    set_sign(&res, 1);
  }

  *dec = res;

  return r.bits[0];
}

s21_decimal multiply_by_10(s21_decimal dec) {
  s21_decimal pr_dst = shift_bits(dec, -2);
  dec = sum_decimal(pr_dst, dec);
  dec = shift_bits(dec, -1);

  return dec;
}

s21_decimal subtraction_decimal(s21_decimal d_1, s21_decimal d_2) {
  s21_decimal answer = {{1, 0, 0, 0}};

  for (int i = 0; i < 96; i++) {
    set_bit(&d_2, i, (get_bit(d_2, i) - 1) * -1);
  }

  d_2 = sum_decimal(d_2, answer);
  answer = sum_decimal(d_1, d_2);

  return answer;
}

s21_decimal sum_decimal(s21_decimal d_1, s21_decimal d_2) {
  s21_decimal answer = {{0, 0, 0, 0}};

  int dop = 0;
  for (size_t i = 0; i < 96; i++) {
    int n_1 = get_bit(d_1, i);
    int n_2 = get_bit(d_2, i);

    int finl_bit = n_1 + n_2 + dop;
    if (finl_bit > 1) {
      if (finl_bit == 3) {
        set_bit(&answer, i, 1);
      }
      dop = 1;

    } else {
      if (finl_bit == 1) {
        set_bit(&answer, i, 1);
      }
      dop = 0;
    }
  }
  return answer;
}

s21_decimal shift_bits(s21_decimal dec, int shif) {
  s21_decimal answer = {{0, 0, 0, 0}};

  if (shif > 0) {
    for (int i = 0; i < 96 - shif; i++) {
      if (get_bit(dec, i + shif)) {
        set_bit(&answer, i, 1);
      }
    }
  } else {
    for (int i = 95; i > -1 + (shif * -1); i--) {
      if (get_bit(dec, i + shif)) {
        set_bit(&answer, i, 1);
      }
    }
  }

  return answer;
}

void retu_decimal(s21_decimal dec, char *result) {
  char degree_ch[30] = {"000000000009223372036854775808"};
  size_t num = 0;
  size_t queue = 63;

  for (int bit = 0; bit < 96; bit++) {
    if (get_bit(dec, bit)) {
      if (bit < 64) {
        num = degree(2, bit);
        sum_bits(result, num);

      } else {
        num = degree(2, bit - queue);
        queue = bit;
        text_multiplier(degree_ch, num);
        sum_test(result, degree_ch);
      }
    }
  }

  if (get_sign(dec)) {
    result[0] = '-';
  }
}

size_t degree(int x, int y) {
  size_t result = 1;
  for (int i = 0; i < y; i++) {
    result *= x;
  }

  return result;
}

void sum_bits(char *result, size_t num) {
  int plus_one = 0;
  for (int i = 30; i > 0 && (num > 0 || plus_one); i--) {
    int n = ((int)result[i] - 48) + (num % 10) + plus_one;
    if (n < 10) {
      result[i] = n + 48;
      plus_one = 0;
    } else {
      result[i] = (n % 10) + 48;
      plus_one = 1;
    }
    num /= 10;
  }
}

void text_multiplier(char *degree_ch, size_t deg) {
  size_t plus_num = 0;
  for (size_t i = 29; i > 0; i--) {
    size_t n = (((size_t)degree_ch[i] - 48) * deg) + plus_num;
    if (n < 10) {
      degree_ch[i] = n + 48;
      plus_num = 0;
    } else {
      degree_ch[i] = (n % 10) + 48;
      plus_num = n / 10;
    }
  }
}

void sum_test(char *result, char *degree_ch) {
  size_t plus_one = 0;
  for (int i = 30; i > 0; i--) {
    size_t n =
        ((size_t)result[i] - 48) + ((size_t)degree_ch[i - 1] - 48) + plus_one;
    if (n < 10) {
      result[i] = n + 48;
      plus_one = 0;
    } else {
      result[i] = (n % 10) + 48;
      plus_one = 1;
    }
  }
}