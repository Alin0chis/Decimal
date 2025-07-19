#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;

  error = s21_check_bits_0_15_and_24_30(src);

  if (dst && s21_get_scale(src) <= 28) {
    s21_truncate(src, &src);
    if (src.bits[1] == 0 && src.bits[2] == 0 && s21_get_bit(src, 31) == 0 &&
        src.bits[0] != 0x80000000) {
      *dst = src.bits[0];
      if (s21_get_sign(src) == 1) {
        *dst *= -1;
      }
    } else if (src.bits[0] == 0x80000000 && src.bits[1] == 0 &&
               src.bits[2] == 0 && s21_get_sign(src) == 1) {
      *dst = -2147483648;
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }
  return error;
}