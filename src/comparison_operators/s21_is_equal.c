#include "../s21_decimal.h"

/**
 * Функция сравнивает два числа типа s21_decimal {value_1} и {value_2}
 * @param value_1 первое число
 * @param value_2 второе число
 * @return возвращает 1, если {value_1} == {value_2}, 0 если {value_1} !=
 * {value_2}
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_normalize(&value_1, &value_2);
  return s21_equal_or_not(value_1, value_2);
}

int s21_equal_or_not(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  int is_zero_1 = 0, is_zero_2 = 0;
  if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
    is_zero_1 = 1;
  }
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    is_zero_2 = 1;
  }
  if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
    result = 0;
  }
  if (s21_get_sign(value_1) != s21_get_sign(value_2) && is_zero_1 &&
      is_zero_2) {
    result = 1;
  } else if (value_1.bits[0] == value_2.bits[0] &&
             value_1.bits[1] == value_2.bits[1] &&
             value_1.bits[2] == value_2.bits[2] && result) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}