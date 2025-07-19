#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_set_zero_decimal(result);
  *result = value;
  int sign = s21_get_sign(value);
  s21_truncate(*result, result);
  if (sign && s21_get_scale(value) && s21_is_zero_decimal(value)) {
    s21_sub(*result, (s21_decimal){{1}}, result);
  } else if (!s21_is_zero_decimal(value)) {
    s21_set_scale(result, 0);
  }
  return 0;
}