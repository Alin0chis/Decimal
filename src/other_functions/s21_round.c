#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);
  int error = 0;
  if (scale != 0) {
    s21_set_bit(&value, 127, 0);
    s21_decimal num_copy = value;
    s21_truncate(num_copy, &num_copy);
    s21_addition_scale_decimal(&num_copy, 1);
    while (s21_get_scale(value) != 1) {
      s21_reduction_scale_decimal(&value, 1, 0);
    }
    s21_sub(value, num_copy, &value);
    int i = value.bits[0];
    s21_reduction_scale_decimal(&value, 1, 0);
    s21_reduction_scale_decimal(&num_copy, 1, 0);
    if (i >= 5) {
      s21_add(num_copy, (s21_decimal){{1}}, &value);
    } else {
      value = num_copy;
    }
    s21_set_bit(&value, 127, sign);
  }
  *result = value;
  return error;
}