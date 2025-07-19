#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  int sign = s21_get_sign(src);
  int scale = s21_get_scale(src);
  if (!dst) {
    error = 1;
  } else {
    *dst = 0.0;
    double number = 0;

    for (int i = 0; i < 96; i++) {
      number += s21_get_bit(src, i) * pow(2.0, i);
    }
    double ten = pow(10.0, -scale);
    number *= ten;
    *dst = (float)number;
  }

  if (!error && sign) {
    *dst *= -1;
  }

  return error;
}