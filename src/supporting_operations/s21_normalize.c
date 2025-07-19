#include "../s21_decimal.h"

int s21_normalize(s21_decimal *dec1, s21_decimal *dec2) {
  int scale_1 = s21_get_scale(*dec1);
  int scale_2 = s21_get_scale(*dec2);
  s21_decimal copy_dec_1;
  s21_decimal copy_dec_2;
  int error_1 = 0, error_2 = 0, error = 0;
  if (!((scale_1 < 29 && scale_2 < 29) && ((scale_1 >= 0 && scale_2 >= 0)))) {
    error = 1;
  }
  while ((scale_1 != scale_2) && !error_1 && !error_2 && !error) {
    copy_dec_1 = *dec1;
    copy_dec_2 = *dec2;
    if (scale_1 < scale_2) {
      error_1 = s21_addition_scale_decimal(dec1, 1);
      if (!error_1) {
        scale_1++;
      } else {
        *dec1 = copy_dec_1;
      }
    } else {
      error_2 = s21_addition_scale_decimal(dec2, 1);
      if (!error_2) {
        scale_2++;
      } else {
        *dec2 = copy_dec_2;
      }
    }
  }
  while ((scale_1 != scale_2 && !error)) {
    if (scale_1 < scale_2) {
      s21_reduction_scale_decimal(dec2, 1, 1);
      scale_2--;
    } else {
      s21_reduction_scale_decimal(dec1, 1, 1);
      scale_1--;
    }
  }
  if (scale_1 == scale_2) {
    s21_set_scale(dec1, scale_1);
    s21_set_scale(dec2, scale_2);
  } else {
    error = 1;
  }
  return error;
}

int s21_normalize_long(s21_decimal_long *dec1, s21_decimal_long *dec2) {
  int scale_1 = s21_get_scale_long(*dec1);
  int scale_2 = s21_get_scale_long(*dec2);
  int error = 0;
  if (!((scale_1 < 29 && scale_2 < 29) && ((scale_1 >= 0 && scale_2 >= 0)))) {
    error = 1;
  }
  while ((scale_1 != scale_2) && !error) {
    if (scale_1 < scale_2) {
      s21_addition_scale_decimal_long(dec1, 1);
      scale_1++;
    } else {
      s21_addition_scale_decimal_long(dec2, 1);
      scale_2++;
    }
  }
  if (scale_1 == scale_2) {
    s21_set_scale_long(dec1, scale_1);
    s21_set_scale_long(dec2, scale_2);
  } else {
    error = 1;
  }
  return error;
}

// Подумать над