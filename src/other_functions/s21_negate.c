#include "../s21_decimal.h"

/** @brief Функция меняет знак decimal числа на противоположный
 *  @param num decimal, знак которого нужно поменять.
 */
int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = s21_check_bits_0_15_and_24_30(value);
  s21_set_zero_decimal(result);
  *result = value;

  s21_set_bit(result, 127, !s21_get_bit(value, 127));
  return error;
}

void s21_negate_long(s21_decimal_long num, s21_decimal_long *result) {
  s21_get_bit_long(num, 223) ? s21_set_bit_long(&num, 223, 0)
                             : s21_set_bit_long(&num, 223, 1);
  *result = num;
}