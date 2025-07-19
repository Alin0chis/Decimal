#include "../s21_decimal.h"

/**
 * Функция устанавливает необходимое значение экспоненты (коэффициента
 * маcштабирования числа) в отведенное для него место в s21_decimal dst
 * (с 16 по 23 биты в dst.bits[3])
 * @param dst переменная типа s21_decimal, в которую записывается scale
 * @param scale коэффицент масштабирования, который необходимо записать
 */
void s21_set_scale(s21_decimal *dst, int scale) {
  int sign = s21_get_bit(*dst, 127);
  scale = scale << 16;
  dst->bits[3] = 0;
  dst->bits[3] |= scale;
  if (sign) {
    s21_set_bit(dst, 127, 1);
  }
}

void s21_set_scale_long(s21_decimal_long *dst, int scale) {
  int sign = s21_get_sign_long(*dst);
  scale = scale << 16;
  dst->bits[6] = 0;
  dst->bits[6] |= scale;
  if (sign) {
    s21_set_bit_long(dst, 223, 1);
  }
}