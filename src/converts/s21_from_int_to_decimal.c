#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  int sign = 0;

  if (!dst) {
    error = 1;
  } else {
    s21_set_zero_decimal(dst);

    if (src < 0) {
      src *= -1;
      sign = 1;
    }

    *dst = (s21_decimal){{src, 0, 0, 0}};
    s21_set_bit(dst, 127, sign);
  }

  return error;
}