#include "big_decimal.h"

void big_set_bit(s21_big_decimal *num, int bit, unsigned value) {
  int i = 0;
  if (bit >= 0 && bit <= 31) {
    i = 0;
  } else if (bit >= 32 && bit <= 63) {
    i = 1;
  } else if (bit >= 64 && bit <= 95) {
    i = 2;
  } else if (bit >= 96 && bit <= 127) {
    i = 3;
  } else if (bit >= 128 && bit <= 159) {
    i = 4;
  } else if (bit >= 160 && bit <= 191) {
    i = 5;
  } else if (bit >= 192 && bit <= 223) {
    i = 6;
  } else if (bit >= 224 && bit <= 255) {
    i = 7;
  }
  if (value) {
    num->bits[i] |= value << (bit % 32);
  } else {
    num->bits[i] &= ~(1 << (bit % 32));
  }
}

int big_get_bit(s21_big_decimal num, int bit) {
  int i = 0;
  int ret = 0;
  if (bit >= 0 && bit <= 31) {
    i = 0;
  } else if (bit >= 32 && bit <= 63) {
    i = 1;
  } else if (bit >= 64 && bit <= 95) {
    i = 2;
  } else if (bit >= 96 && bit <= 127) {
    i = 3;
  } else if (bit >= 128 && bit <= 159) {
    i = 4;
  } else if (bit >= 160 && bit <= 191) {
    i = 5;
  } else if (bit >= 192 && bit <= 223) {
    i = 6;
  } else if (bit >= 224 && bit <= 255) {
    i = 7;
  }
  if ((num.bits[i] >> bit % 32) & 1) {
    ret = 1;
  } else {
    ret = 0;
  }
  return ret;
}

void big_null_decimal(s21_big_decimal *value) {
  for (int i = 0; i < 8; ++i) {
    value->bits[i] = 0;
  }
}

void decimal_to_big(s21_decimal value_dec, s21_big_decimal *value_big) {
  big_null_decimal(value_big);
  for (int i = 0; i < 3; ++i) {
    value_big->bits[i] = value_dec.bits[i];
  }
}

void big_to_decimal(s21_decimal *value_dec, s21_big_decimal value_big) {
  null_decimal(value_dec);
  for (int i = 0; i < 3; ++i) {
    value_dec->bits[i] = value_big.bits[i];
  }
}

s21_big_decimal big_shift_bits(s21_big_decimal dec, int shif) {
  s21_big_decimal answer = {{0, 0, 0, 0, 0, 0, 0, 0}};

  if (shif > 0) {
    for (int i = 0; i < 256 - shif; i++) {
      if (big_get_bit(dec, i + shif)) {
        big_set_bit(&answer, i, 1);
      }
    }
  } else {
    for (int i = 255; i > -1 + (shif * -1); i--) {
      if (big_get_bit(dec, i + shif)) {
        big_set_bit(&answer, i, 1);
      }
    }
  }

  return answer;
}

int big_division_by_10(s21_big_decimal *dec) {
  s21_big_decimal q =
      big_sum_decimal(big_shift_bits(*dec, 1), big_shift_bits(*dec, 2));
  q = big_sum_decimal(q, big_shift_bits(q, 4));
  q = big_sum_decimal(q, big_shift_bits(q, 8));
  q = big_sum_decimal(q, big_shift_bits(q, 16));
  q = big_sum_decimal(q, big_shift_bits(q, 32));
  q = big_sum_decimal(q, big_shift_bits(q, 64));
  q = big_sum_decimal(q, big_shift_bits(q, 128));

  q = big_shift_bits(q, 3);
  s21_big_decimal r = big_subtraction_decimal(
      *dec, big_shift_bits(big_sum_decimal(big_shift_bits(q, -2), q), -1));

  s21_big_decimal res = {{1, 0, 0, 0, 0, 0, 0, 0}};
  if (r.bits[0] > 9) {
    res = big_sum_decimal(q, res);
  } else {
    res = q;
  }

  *dec = res;

  return r.bits[0];
}

s21_big_decimal big_multiply_by_10(s21_big_decimal dec) {
  s21_big_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  res = big_sum_decimal(big_shift_bits(dec, -3), big_shift_bits(dec, -1));
  return res;
}

s21_big_decimal big_sum_decimal(s21_big_decimal d_1, s21_big_decimal d_2) {
  s21_big_decimal answer = {{0, 0, 0, 0, 0, 0, 0, 0}};

  int dop = 0;
  for (size_t i = 0; i < 256; i++) {
    int n_1 = big_get_bit(d_1, i);
    int n_2 = big_get_bit(d_2, i);

    int finl_bit = n_1 + n_2 + dop;
    if (finl_bit > 1) {
      if (finl_bit == 3) {
        big_set_bit(&answer, i, 1);
      }
      dop = 1;
    } else {
      if (finl_bit == 1) {
        big_set_bit(&answer, i, 1);
      }
      dop = 0;
    }
  }
  return answer;
}

s21_big_decimal big_subtraction_decimal(s21_big_decimal d_1,
                                        s21_big_decimal d_2) {
  s21_big_decimal answer = {{1, 0, 0, 0, 0, 0, 0, 0}};

  for (int i = 0; i < 256; i++) {
    big_set_bit(&d_2, i, (big_get_bit(d_2, i) - 1) * -1);
  }

  d_2 = big_sum_decimal(d_2, answer);
  answer = big_sum_decimal(d_1, d_2);

  return answer;
}

void inverse_bits(s21_big_decimal *value) {
  for (int i = 0; i < 256; i++) {
    big_set_bit(value, i, (big_get_bit(*value, i) - 1) * -1);
  }
  *value = big_sum_decimal(*value, (s21_big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}});
}

int big_comparison(s21_big_decimal value_1, s21_big_decimal value_2) {
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  char res = 0;
  for (int i = 255; i > -1; i--) {
    bit_value_1 = big_get_bit(value_1, i);
    bit_value_2 = big_get_bit(value_2, i);

    if (bit_value_1 < bit_value_2) {
      res = 2;
      break;
    } else if (bit_value_1 > bit_value_2) {
      res = 1;
      break;
    } else if (i == 0 && bit_value_1 == bit_value_2) {
      res = 0;
    }
  }
  return res;
}

int banking_round(s21_big_decimal *value, int scale) {
  s21_big_decimal temp = {{0}};

  int over_division_remainder = 0;
  int bank_rounding = 0;

  if (scale > 28) {
    while (scale > 28) {
      over_division_remainder = big_division_by_10(value);
      scale--;

      if (!bank_rounding && over_division_remainder != 10 && scale > 29) {
        bank_rounding = 1;
      }
    }
  }

  temp = *value;
  int temp_scale = scale;
  int count_numbers = 0;
  int flag = 0;

  for (int i = 3; i < 8; ++i) {
    if (temp.bits[i] != 0) {
      flag = 1;
      break;
    }
  }

  while (flag == 1 || scale > 28) {
    flag = 0;
    big_division_by_10(&temp);
    count_numbers++;
    for (int i = 3; i < 8; ++i) {
      if (temp.bits[i] != 0) {
        flag = 1;
        break;
      }
    }
  }

  if (count_numbers > scale) {
    temp_scale = -1;
  } else {
    temp_scale = scale - count_numbers;
  }

  if ((temp_scale != -1 && count_numbers != 0) ||
      over_division_remainder != 0) {
    int new_division_remainder = 0;
    int division_remainder = 0;

    if (count_numbers != 0) {
      for (int i = 0; i < count_numbers; ++i) {
        division_remainder = big_division_by_10(value);

        if (!bank_rounding && division_remainder != 10 &&
            i + 1 != count_numbers) {
          bank_rounding = 1;
        }
      }
    } else {
      division_remainder = over_division_remainder;
    }

    if (division_remainder == 5 || division_remainder == 15) {
      s21_big_decimal intet_dec = *value;
      new_division_remainder = big_division_by_10(&intet_dec);

      if (new_division_remainder % 2 == 1 || bank_rounding) {
        *value = big_sum_decimal(*value,
                                 (s21_big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}});
      }

    } else if ((division_remainder >= 6 && division_remainder <= 9) ||
               (division_remainder >= 16 && division_remainder <= 19)) {
      *value =
          big_sum_decimal(*value, (s21_big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}});
    }
  }

  return temp_scale;
}