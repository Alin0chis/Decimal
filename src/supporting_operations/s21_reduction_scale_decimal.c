#include "../s21_decimal.h"
/**
 * Функция уменьшения scale числа {dst} типа s21_decimal_long на {n}
 * @param dst переменная типа s21_decimal, scale которой уменьшаем
 * @param n на сколько необходимо уменьшить коеффицент масштабирование числа
 */
int s21_reduction_scale_decimal(s21_decimal *dst, int n, int option) {
  s21_decimal result = {0};
  int overflow = 0;
  s21_set_scale(dst, s21_get_scale(*dst) - n);
  for (int i = 0; i < n; i++) {
    overflow =
        s21_div_decimal(*dst, s21_move_int_to_decimal(10), &result, option);
    *dst = result;
  }
  return overflow;
}

int s21_reduction_scale_decimal_long(s21_decimal_long *dst, int n, int option) {
  s21_decimal_long result = {0};
  int overflow = 0;
  s21_set_scale_long(dst, s21_get_scale_long(*dst) - n);
  for (int i = 0; i < n; i++) {
    overflow =
        s21_div_decimal_long(dst, (s21_decimal_long){{10}}, &result, option);
    *dst = result;
  }
  return overflow;
}