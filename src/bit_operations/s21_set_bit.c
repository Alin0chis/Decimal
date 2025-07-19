#include "../s21_decimal.h"
/**
 * Функция получает и устанавливает бит {bit} по индексу {index} в числе
 * {dst} типа s21_decimal
 * @param num куда устанавливаем бит
 * @param index по какому индексу устанавливаем бит
 * @param bit какой бит необходимо установить (0 или 1)
 * @return возвращает изменную переменную dst типа s21_decimal
 */
void s21_set_bit(s21_decimal *num, int index, unsigned int bit) {
  if (bit) {
    num->bits[index / 32] |= (1u << (index % 32));
  } else {
    num->bits[index / 32] &= (~(1u << (index % 32)));
  }
}
/**
 * Функция получает и устанавливает бит {bit} по индексу {index}
 *  в числе {dst} типа s21_decimal_long
 * @param num куда устанавливаем бит
 * @param index по какому индексу устанавливаем бит
 * @param bit какой бит необходимо установить (0 или 1)
 * @return возвращает изменную переменную dst типа s21_decimal_long
 */
void s21_set_bit_long(s21_decimal_long *num, int index, unsigned int bit) {
  if (bit) {
    num->bits[index / 32] |= (1u << (index % 32));
  } else {
    num->bits[index / 32] &= (~(1u << (index % 32)));
  }
}
