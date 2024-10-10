#ifndef BIG_DECIMAL_H
#define BIG_DECIMAL_H

#include "s21_decimal.h"

typedef struct {
  int bits[8];
} s21_big_decimal;

void decimal_to_big(s21_decimal value_dec, s21_big_decimal *value_big);
void big_to_decimal(s21_decimal *value_dec, s21_big_decimal value_big);

int big_get_bit(s21_big_decimal num, int bit);
void big_set_bit(s21_big_decimal *num, int bit, unsigned value);
void big_null_decimal(s21_big_decimal *value);

s21_big_decimal big_shift_bits(s21_big_decimal dec, int shif);
int big_division_by_10(s21_big_decimal *dec);
s21_big_decimal big_multiply_by_10(s21_big_decimal dec);
s21_big_decimal big_sum_decimal(s21_big_decimal d_1, s21_big_decimal d_2);
s21_big_decimal big_subtraction_decimal(s21_big_decimal d_1,
                                        s21_big_decimal d_2);
int banking_round(s21_big_decimal *value, int exp);
void inverse_bits(s21_big_decimal *value);
int big_comparison(s21_big_decimal value_1, s21_big_decimal value_2);

s21_big_decimal big_division(s21_big_decimal *value_1, s21_big_decimal value_2);

#endif