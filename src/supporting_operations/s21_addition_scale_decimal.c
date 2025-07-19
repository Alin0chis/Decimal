#include "../s21_decimal.h"
/**
 * Функция повышает scale и возводит число в степень {dst} типа s21_decimal_long
 * на {n}.
 * @param dst переменная типа s21_decimal_long, scale которой увеличиваем и
 * мантиссу которой будем возводить в степень.
 * @param n на сколько необходимо увеличить коеффицент масштабирование числа
 */
int s21_addition_scale_decimal(s21_decimal *dst, int n) {
  int overflow = 0;
  int sum_scale = s21_get_scale(*dst) + n;
  // 16 17 18 19 20 21 22 23
  for (int i = 0; (i < n) && !overflow; i++) {
    overflow = s21_mul_decimal(dst, (s21_decimal){{10}});
  }
  if (overflow == 0) {
    s21_set_scale(dst, sum_scale);
  }
  return overflow;
}

int s21_addition_scale_decimal_long(s21_decimal_long *dst, int n) {
  int overflow = 0;
  int sum_scale = s21_get_scale_long(*dst) + n;
  // 16 17 18 19 20 21 22 23
  for (int i = 0; (i < n) && !overflow; i++) {
    overflow = s21_mul_decimal_long(dst, (s21_decimal_long){{10}});
  }
  if (overflow == 0) {
    s21_set_scale_long(dst, sum_scale);
  }
  return overflow;
}