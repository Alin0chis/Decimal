#include "../s21_decimal.h"

/**
 * Функция сравнивает два числа типа s21_decimal_long {value_1} и {value_2}
 * @param value_1 первое число
 * @param value_2 второе число
 * @return возвращет 1, если {value_1} > {value_2}, 0 если {value_1} <=
 * {value_2}
 */
int s21_is_greater_long_decimal(s21_decimal_long value_1,
                                s21_decimal_long value_2) {
  int result = 0, out = 0;
  for (int i = 5; i >= 0; --i) {
    if (!result && !out && (value_1.bits[i] || value_2.bits[i])) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) {
        out = 1;
      }
    }
  }
  return result;
}

/**
 * Функция сравнивает два числа типа s21_decimal {value_1} и {value_2}
 * @param value_1 первое число
 * @param value_2 второе число
 * @return возвращет 1, если {value_1} > {value_2}, 0 если {value_1} <=
 * {value_2}
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_normalize(&value_1, &value_2);
  return s21_is_greater_or_not(value_1, value_2);
}

int s21_is_greater_or_not(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  if (s21_get_bit(value_1, 127) && !s21_get_bit(value_2, 127)) {
    result = 0;
  } else if (!s21_get_bit(value_1, 127) && s21_get_bit(value_2, 127)) {
    result = 1;
  } else if (s21_get_bit(value_1, 127) == s21_get_bit(value_2, 127)) {
    for (int i = 2; i >= 0; --i) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
        break;
      } else if (value_1.bits[i] < value_2.bits[i]) {
        result = 0;
        break;
      } else if (value_1.bits[i] == value_2.bits[i]) {
        result = 0;
      }
    }
    if (s21_get_bit(value_1, 127) && !s21_equal_or_not(value_1, value_2)) {
      if (result == 1) {
        result = 0;
      } else {
        result = 1;
      }
    }
  }
  return result;
}