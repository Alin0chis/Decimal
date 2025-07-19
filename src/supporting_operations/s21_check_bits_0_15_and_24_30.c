#include "../s21_decimal.h"

int s21_check_bits_0_15_and_24_30(s21_decimal src) {
  int error = 0;

  for (int i = 96; i <= 111; i++) {
    if (s21_get_bit(src, i) != 0) {
      error = 1;
      break;
    }
  }

  for (int i = 120; i <= 126; i++) {
    if (s21_get_bit(src, i) != 0) {
      error = 1;
      break;
    }
  }

  return error;
}