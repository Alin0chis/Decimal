#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_set_zero_decimal(result);
  int sign = s21_get_sign(value);
  *result = value;
  int pow = s21_get_scale(value);
  for (int i = 0; i < pow; i++) {
    drop_last_digit(result);
  }
  set_pow(result, 0);
  if (sign) {
    s21_set_bit(result, 127, sign);
  }
  return 0;
}