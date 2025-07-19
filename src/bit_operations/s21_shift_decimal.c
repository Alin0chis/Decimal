#include "../s21_decimal.h"

/**
 * @brief Делает сдвиг всего long_decimal в левую сторону на n количество
 * раз.
 * @param n количество бит, на которое нужно сдвинуть decimal_long.
 * @param num decimal_long, которому нужно передвинуть биты.
 * @param i_max Сколько интов нужно задействовать в сдвиге
 * @return overflow, в случае невозможности дальнейшего сдвига и переполнения
 * возвращает 1.
 */
int s21_shift_left_decimal_long(s21_decimal_long *num, int n, int i_max) {
  int overflow = 0;
  while (n != 0) {
    if (s21_get_bit_long(*num, (i_max * 32) - 1) != 1) {
      num->bits[i_max] = num->bits[i_max] << 1;
      for (int i = i_max - 1; i >= 0; i--) {
        if (s21_get_bit_long(*num, ((i + 1) * 32 - 1)) != 1) {
          num->bits[i] = num->bits[i] << 1;
        } else {
          s21_set_bit_long(num, (i + 1) * 32, 1);
          num->bits[i] = num->bits[i] << 1;
        }
      }
      n--;
    } else {
      overflow = 1;
      break;
    }
  }
  return overflow;
}

void s21_shift_right_decimal_long(s21_decimal_long *num, int n) {
  while (n != 0) {
    for (int i = 0; i <= 5; i++) {
      if (s21_get_bit_long(*num, i * 32) != 1) {
        num->bits[i] = num->bits[i] >> 1;
      } else {
        num->bits[i] = num->bits[i] >> 1;
        s21_set_bit_long(num, i * 32 - 1, 1);
      }
    }
    n--;
  }
}