#include "../s21_decimal.h"

/** @brief Производит сложение двух decimal чисел.
 *  @param value_1 1-ый decimal, слагаемое.
 *  @param value_2 2-ой decimal, слагаемое.
 *  @param result decimal, в который записывается результат
 *  @return error, в случае ошибки будет равен не 0
 * */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = s21_check_decimal(value_1, value_2, result);
  s21_decimal_long long_value_1 = s21_move_to_long_decimal(value_1);
  s21_decimal_long long_value_2 = s21_move_to_long_decimal(value_2);
  if (!error_code && !s21_normalize_long(&long_value_1, &long_value_2)) {
    if (s21_get_sign_long(long_value_1) != s21_get_sign_long(long_value_2)) {
      if (!s21_is_greater_long_decimal(long_value_1, long_value_2)) {
        s21_sub_decimal_long(&long_value_2, long_value_1);
        error_code = s21_move_to_normal_decimal(result, long_value_2);
      } else {
        s21_sub_decimal_long(&long_value_1, long_value_2);
        error_code = s21_move_to_normal_decimal(result, long_value_1);
      }
    } else if (!s21_sum_mantissas_long(&long_value_1, long_value_2)) {
      error_code = s21_move_to_normal_decimal(result, long_value_1);
    } else {
      error_code = 1;
    }
  } else {
    error_code = 1;
  }
  if (error_code && result != NULL) {
    s21_set_zero_decimal(result);
  }
  return error_code;
}

/** @brief Складывает мантиссы двух децималов без учета степеней и знаков.
 * @param bits 1-ое слагаемое decimal типа, в нем же и будет результат,
 * возвращенный по указателю.
 * @param addendum 2-ое слагаемое decimal типа.
 * @return overflow, True в случае если переполнения или False.
 */
int s21_sum_mantissas(s21_decimal *bits, s21_decimal addendum) {
  int temp = 0;
  int overflow = 0;
  for (int n = 0; n < 97; n++) {
    temp = s21_get_bit(*bits, n) + s21_get_bit(addendum, n) + overflow;
    if (temp == 3) {
      s21_set_bit(bits, n, 1);
    } else if (temp == 2) {
      s21_set_bit(bits, n, 0);
      overflow = 1;
    } else if (temp) {
      s21_set_bit(bits, n, 1);
      overflow = 0;
    }
  }
  return overflow;
}

int s21_sum_mantissas_long(s21_decimal_long *bits, s21_decimal_long addendum) {
  int temp = 0;
  int overflow = 0;
  for (int n = 0; n < 192; n++) {
    temp =
        s21_get_bit_long(*bits, n) + s21_get_bit_long(addendum, n) + overflow;
    if (temp == 3) {
      s21_set_bit_long(bits, n, 1);
    } else if (temp == 2) {
      s21_set_bit_long(bits, n, 0);
      overflow = 1;
    } else if (temp) {
      s21_set_bit_long(bits, n, 1);
      overflow = 0;
    }
  }
  return overflow;
}