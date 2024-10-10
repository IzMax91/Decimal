#include "s21_decimal.h"

int is_zero(s21_decimal num) {
  int is_zero = 1;
  for (int i = 0; i < 3; ++i) {
    if (num.bits[i] != 0) {
      is_zero = 0;
      break;
    }
  }
  return is_zero;
}

void set_bit(s21_decimal *num, int bit, unsigned value) {
  int i = 0;
  if (bit >= 0 && bit <= 31) {
    i = 0;
  } else if (bit >= 32 && bit <= 63) {
    i = 1;
  } else if (bit >= 64 && bit <= 95) {
    i = 2;
  }

  if (value) {
    num->bits[i] |= value << (bit % 32);
  } else
    num->bits[i] &= ~(1 << (bit % 32));
}

int get_bit(s21_decimal num, int bit) {
  int i = 0;
  int ret = 0;
  if (bit >= 0 && bit <= 31) {
    i = 0;
  } else if (bit >= 32 && bit <= 63) {
    i = 1;
  } else if (bit >= 64 && bit <= 95) {
    i = 2;
  }
  if ((num.bits[i] >> bit % 32) & 1) {
    ret = 1;
  } else {
    ret = 0;
  }
  return ret;
}

void null_decimal(s21_decimal *num) {
  num->bits[0] = 0;
  num->bits[1] = 0;
  num->bits[2] = 0;
  num->bits[3] = 0;
}

int get_sign(s21_decimal num) { return num.bits[3] >> 31 & 1; }

void set_sign(s21_decimal *num, int sign_value) {
  if (sign_value == 1) {
    num->bits[3] |= sign_value << 31;
  } else
    num->bits[3] &= ~(1 << 31);
}

int get_scale(s21_decimal num) {
  int ret = 0;
  ret = num.bits[3] >> 16 & 255;
  return ret;
}

void set_scale(s21_decimal *num, int scale_value) {
  num->bits[3] |= scale_value << 16;
}
