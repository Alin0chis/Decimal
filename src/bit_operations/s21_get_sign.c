#include "../s21_decimal.h"
/**
 * Функция возвращает знак числа
 * @param dst где ищем знак
 * @return возвращает 0 если число положительное, 1 если число отрицательное
 */
int s21_get_sign(s21_decimal dst) {
  int sign = (dst.bits[3] & (1u << 31)) ? 1 : 0;
  return sign;
}

int s21_get_sign_long(s21_decimal_long dst) {
  int sign = (dst.bits[6] & (1u << 31)) ? 1 : 0;
  return sign;
}