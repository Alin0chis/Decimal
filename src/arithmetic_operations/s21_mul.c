#include "../s21_decimal.h"

/** @brief Производит умножение двух decimal чисел.
 *  @param value_1 1-ый decimal множитель.
 *  @param value_2 2-ой decimal множитель.
 *  @param result decimal произведение, в который записывается результат.
 *  @return error, в случае ошибки будет равен не 0.
 * */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = s21_check_decimal(value_1, value_2, result);
  if (!(s21_get_scale(value_1) < 29 && s21_get_scale(value_2) < 29)) {
    error_code = 1;
  }
  s21_decimal_long long_value_1 = s21_move_to_long_decimal(value_1);
  s21_decimal_long long_value_2 = s21_move_to_long_decimal(value_2);
  if (!error_code) {
    error_code = s21_mul_decimal_long(&long_value_1, long_value_2);
    if (s21_is_zero_decimal_long(long_value_1)) {
      s21_set_scale_long(&long_value_1, s21_get_scale_long(long_value_1) +
                                            s21_get_scale_long(long_value_2));
    }
    if (s21_move_to_normal_decimal(result, long_value_1)) {
      if (s21_get_sign_long(long_value_1)) {
        error_code = 2;
      } else {
        error_code = 1;
      }
      s21_set_zero_decimal(result);
    }
  }
  return error_code;
}

/**
 * @brief Функция переменожает мантиссы двух decimal чисел.
 * @param num decimal, мантиссу которого нам нужно умножить
 *  и в которое записывается результат.
 * @param mul множитель, на которые умножается мантисса.
 * @return overflow, в случае перегрузки числа 1 или 0 в случае нормального
 * умножения.
 */
int s21_mul_decimal(s21_decimal *num, s21_decimal mul) {
  s21_decimal temp = {0};
  s21_decimal result = {0};
  result.bits[3] = num->bits[3];
  int overflow = 0;
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(mul, i)) {
      for (int n = 0; n < 96; n++) {
        if (s21_get_bit(*num, n)) {
          if ((i + n) < 96) {
            s21_set_bit(&temp, i + n, 1);
          } else {
            overflow = 1;
          }
        }
      }
    }
    s21_sum_mantissas(&result, temp);
    s21_set_zero_decimal(&temp);
  }
  *num = result;
  return overflow;
}

int s21_mul_decimal_long(s21_decimal_long *num, s21_decimal_long mul) {
  s21_decimal_long temp = {0};
  s21_decimal_long result = {0};
  result.bits[6] = num->bits[6];
  int overflow = 0;
  for (int i = 0; i < 192; i++) {
    if (s21_get_bit_long(mul, i)) {
      for (int n = 0; n < 192; n++) {
        if (s21_get_bit_long(*num, n)) {
          if ((i + n) < 192) {
            s21_set_bit_long(&temp, i + n, 1);
          } else {
            overflow = 1;
          }
        }
      }
    }
    overflow = s21_sum_mantissas_long(&result, temp);
    s21_set_zero_decimal_long(&temp);
  }
  if ((s21_get_bit_long(*num, 223) && s21_get_bit_long(mul, 223)) ||
      (!s21_get_bit_long(*num, 223) && s21_get_bit_long(mul, 223))) {
    s21_negate_long(result, &result);
  }
  if ((result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3] +
       result.bits[4] + result.bits[5]) == 0)
    result.bits[6] = 0;
  if (overflow == 0) {
    *num = result;
  }
  return overflow;
}