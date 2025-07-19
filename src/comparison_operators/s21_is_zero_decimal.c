#include "../s21_decimal.h"

/** @brief проверяет, равен ли мантисса s21_decimal == 0.
 * @param num s21_decimal, мантиссу которого мы проверяем.
 * @return 1 в случае, если мантисса не равна 0, иначе возвращает 0.
 */
int s21_is_zero_decimal_long(s21_decimal_long num) {
  return num.bits[5] || num.bits[4] || num.bits[3] || num.bits[2] ||
         num.bits[1] || num.bits[0] || 0;
}

int s21_is_zero_decimal(s21_decimal num) {
  return num.bits[2] || num.bits[1] || num.bits[0] || 0;
}