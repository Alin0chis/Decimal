#include "../s21_decimal.h"
/**
 * Функция зануляет структуру dst и возвращает ее
 * @param dst структура типа s21_decimal, которую будем занулять
 * return возвращает зануленную структуру
 */
void s21_set_zero_decimal(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

void s21_set_zero_decimal_long(s21_decimal_long *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = dst->bits[4] =
      dst->bits[5] = dst->bits[6] = 0;
}
