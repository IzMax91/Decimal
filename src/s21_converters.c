#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  null_decimal(dst);
  if (src & (1 << 31)) {
    set_sign(dst, 1);
    src *= -1;
  }

  for (size_t i = 0; i < 31; i++) {
    if (src & (1 << i)) {
      set_bit(dst, i, 1);
    }
  }

  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code = 0;

  s21_truncate(src, &src);

  if (src.bits[0] >= 0 && !src.bits[1] && !src.bits[2]) {
    *dst = src.bits[0];
    if (get_sign(src)) *dst *= -1;
  } else
    error_code = 1;

  return error_code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error_code = 0;
  null_decimal(dst);

  char examination[13] = {0};
  sprintf(examination, "%e", src);
  int exa_len = strlen(examination);
  int exp = (int)(examination[exa_len - 2] - 48) * 10;
  exp += (int)(examination[exa_len - 1] - 48);

  if (exa_len > 4 && exp < 29) {
    int exhibitor = 0;
    char number[9] = {0};
    int final_number = 0;
    int bit_multiplication = 0;

    for (size_t i = 0, j = 0; examination[i] != 'e' && examination[i] != 'E';
         i++) {
      if (examination[i] != '-' && examination[i] != '.') {
        number[j++] = examination[i];
      }
      sscanf(number, "%d", &final_number);
    }

    if (examination[exa_len - 3] == '+') {
      if (exp > 6) {
        exhibitor = (exp + 1) - 7;
        bit_multiplication = 1;
      } else {
        exhibitor = 7 - (exp + 1);
      }

    } else if (examination[exa_len - 3] == '-') {
      exhibitor = 7 + (exp - 1);

      while (exhibitor > 0 && (final_number % 10 == 0 || exhibitor > 28)) {
        exhibitor--;
        final_number /= 10;
      }
    }

    s21_from_int_to_decimal(final_number, dst);

    if (bit_multiplication) {
      int ex = exhibitor;

      for (int i = 0; i < ex; i++) {
        *dst = multiply_by_10(*dst);
        exhibitor--;
      }
    }

    if (examination[0] == '-') {
      set_sign(dst, 1);
    }
    set_scale(dst, exhibitor);

  } else {
    error_code = 1;
  }

  return error_code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  char res[31] = {"0000000000000000000000000000000"};
  retu_decimal(src, res);
  char r_f[33] = {"00000000000000000000000000000000\0"};

  r_f[31 - get_scale(src)] = '.';

  for (size_t i = 0, j = 0; i < 31; i++, j++) {
    if (r_f[j] == '.') {
      j++;
    }

    r_f[j] = res[i];
  }

  sscanf(r_f, "%f", dst);

  return 0;
}