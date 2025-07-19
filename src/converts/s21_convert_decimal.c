#include "../s21_decimal.h"

s21_decimal_long s21_move_to_long_decimal(s21_decimal num) {
  s21_decimal_long num_long = {0};
  num_long.bits[6] = num.bits[3];
  for (int i = 0; i < 3; i++) {
    num_long.bits[i] = num.bits[i];
  }
  return num_long;
}

s21_decimal s21_move_int_to_decimal(int n) {
  s21_decimal result = {{n, 0, 0, 0}};
  return result;
}

int s21_move_to_normal_decimal(s21_decimal *num, s21_decimal_long num_long) {
  int overflow = 0, i = 0;
  s21_decimal_long copy_num = num_long;
  s21_decimal_long del = {{10}};
  while (((num_long.bits[3] || num_long.bits[4] || num_long.bits[5]) &&
          (s21_get_scale_long(num_long) >= 1)) ||
         (s21_get_scale_long(num_long) > 28)) {
    s21_reduction_scale_decimal_long(&num_long, 1, 0);
    i++;
  }
  if (i != 0) {
    if (i > 1) {
      s21_addition_scale_decimal_long(&del, i - 1);
    }
    s21_set_zero_decimal_long(&num_long);
    s21_div_decimal_long(&copy_num, del, &num_long, 1);
    s21_set_scale_long(&num_long, s21_get_scale_long(copy_num) - i);
  }
  if (!(num_long.bits[3] || num_long.bits[4] || num_long.bits[5])) {
    s21_set_zero_decimal(num);
    num->bits[3] = num_long.bits[6];
    for (int i = 0; i <= 2; i++) {
      num->bits[i] = num_long.bits[i];
    }
  } else if (s21_get_sign_long(num_long)) {
    overflow = 2;
  } else {
    overflow = 1;
  }
  return overflow;
}
