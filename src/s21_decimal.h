#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdio.h>
#include <string.h>

typedef struct {
  int bits[4];
} s21_decimal;

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void retu_decimal(s21_decimal dec, char *result);
size_t degree(int x, int y);
void sum_bits(char *result, size_t num);
void text_multiplier(char *degree_ch, size_t deg);
void sum_test(char *result, char *degree_ch);

// функции для работы с битами
int is_zero(s21_decimal num);
int get_bit(s21_decimal num, int bit);
void set_bit(s21_decimal *num, int bit, unsigned value);
void null_decimal(s21_decimal *num);
int get_sign(s21_decimal num);
void set_sign(s21_decimal *num, int sign_value);
int get_scale(s21_decimal num);
void set_scale(s21_decimal *num, int scale_value);

// сложение/вычитание, а так же сдвиг и деление на 10
s21_decimal sum_decimal(s21_decimal d_1, s21_decimal d_2);
s21_decimal subtraction_decimal(s21_decimal d_1, s21_decimal d_2);
s21_decimal shift_bits(s21_decimal dec, int shif);
int division_by_10(s21_decimal *dec);
s21_decimal multiply_by_10(s21_decimal dec);

// сравнение
char s21_main_def(s21_decimal num_1, s21_decimal num_2);
int s21_is_less(s21_decimal num_1, s21_decimal num_2);
int s21_is_less_or_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_greater(s21_decimal num_1, s21_decimal num_2);
int s21_is_greater_or_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_not_equal(s21_decimal num_1, s21_decimal num_2);

// математика
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif
