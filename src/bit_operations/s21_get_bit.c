#include "../s21_decimal.h"
/**
 * Функция получает бит, находящийся по индексу {index}
 * из числа {dst} типа s21_decimal
 * @param dst - откуда получаем бит
 * @param index - по какому индексу хотим получить бит
 * @return возвращает 1 или 0 в зависимости от того
 * какой бит был по искомому индексу
 */
unsigned int s21_get_bit(s21_decimal num, int index) {
  return (num.bits[index / 32] & (1u << (index % 32))) >> (index % 32);
}
/**
 * Функция получает бит, находящийся по индексу {index}
 * из числа {dst} типа s21_long_decimal
 * @param dst - откуда получаем бит
 * @param index - по какому индексу хотим получить бит
 * @return возвращает 1 или 0 в зависимости от того
 * какой бит был по искомому индексу
 */
unsigned int s21_get_bit_long(s21_decimal_long num, int index) {
  return (num.bits[index / 32] & (1u << (index % 32))) >> (index % 32);
}