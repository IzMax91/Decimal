#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_truncate(value, result);

  if (get_sign(value) && get_scale(value)) {
    int ex = get_scale(value);

    s21_decimal intet_dec = *result;
    for (; ex > 0; ex--) {
      intet_dec = multiply_by_10(intet_dec);
    }

    intet_dec = subtraction_decimal(value, intet_dec);
    if (intet_dec.bits[0] != 0 || intet_dec.bits[1] != 0 ||
        intet_dec.bits[2] != 0) {
      *result = sum_decimal(*result, (s21_decimal){{1, 0, 0, 0}});
    }

    set_sign(result, get_sign(value));
  }

  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int scale = get_scale(value);
  int division_remainder = 0;
  int bank_rounding = 0;

  for (int i = 0; i < scale; i++) {
    division_remainder = division_by_10(&value);

    if (!bank_rounding && division_remainder != 10 && i + 1 != scale) {
      bank_rounding = 1;
    }
  }

  if (division_remainder == 5) {
    s21_decimal intet_dec = value;
    division_remainder = division_by_10(&intet_dec);

    if (division_remainder % 2 == 1 || bank_rounding) {
      *result = sum_decimal(value, (s21_decimal){{1, 0, 0, 0}});
    }

    else {
      *result = value;
    }

  } else if (division_remainder >= 6 && division_remainder <= 9) {
    *result = sum_decimal(value, (s21_decimal){{1, 0, 0, 0}});

  } else {
    *result = value;
  }

  set_sign(result, get_sign(value));

  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = value;
  int scale = get_scale(value);

  for (int i = 0; i < scale; i++) {
    division_by_10(&value);
  }

  *result = value;

  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;

  set_sign(result, (get_sign(*result) - 1) * -1);

  return 0;
}