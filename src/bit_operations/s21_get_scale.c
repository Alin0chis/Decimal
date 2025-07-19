#include "../s21_decimal.h"

/**
 * Функция получает и возвращает scale числа записанного в {dst}
 * @param dst где ищем scale
 * @return возвращает scale записанный в dst
 */
unsigned int s21_get_scale(s21_decimal num) { return (num.bits[3] & SC) >> 16; }

unsigned int s21_get_scale_long(s21_decimal_long num) {
  return (num.bits[6] & SC) >> 16;
}
