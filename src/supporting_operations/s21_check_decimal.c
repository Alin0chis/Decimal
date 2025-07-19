#include "../s21_decimal.h"

int s21_check_decimal(s21_decimal num, s21_decimal num2, s21_decimal *result) {
  int error = 0;
  if (result != NULL) {
    for (int i = 96; i < 112; i++) {
      if (s21_get_bit(num, i)) {
        error = 1;
      }
    }
    for (int i = 120; i < 127; i++) {
      if (s21_get_bit(num, i)) {
        error = 1;
      }
    }
    if (error) {
      error = error + s21_get_sign(num);
    } else {
      for (int i = 96; i < 112; i++) {
        if (s21_get_bit(num2, i)) {
          error = 1;
        }
      }
      for (int i = 120; i < 127; i++) {
        if (s21_get_bit(num2, i)) {
          error = 1;
        }
      }
      if (error) {
        error = error + s21_get_sign(num);
      }
    }
  } else {
    error = 1;
  }
  return error;
}