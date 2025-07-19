#include "../s21_decimal.h"

/**
 * Функция сравнивает два числа типа s21_decimal {value_1} и {value_2}
 * @param value_1 первое число
 * @param value_2 второе число
 * @return возвращет 1, если {value_1} != {value_2}, 0 если {value_1} ==
 * {value_2}
 */
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return (!s21_is_equal(value_1, value_2));
}