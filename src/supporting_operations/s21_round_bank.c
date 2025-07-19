#include "../s21_decimal.h"

// parity - четность (1 нечетное, 0 четное)
// fract_num - первая цифра после запятой (напр. 3.5 == .5)
// sec_natural_num - есть ли число после fract_num, 1 - есть, 0 - нет.
// return 1 - огругляем в большую, 0 - не округляем.
int s21_rounding_bank(int parity, int fract_num, int sec_natural_num) {
  int result = 0;
  if (!parity && (fract_num == 5) && (sec_natural_num != 0)) {
    result = 1;
  } else if (!parity && (fract_num > 5)) {
    result = 1;
  } else if (parity && (fract_num >= 5)) {
    result = 1;
  }

  return result;
}