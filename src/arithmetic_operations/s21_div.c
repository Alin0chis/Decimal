#include "../s21_decimal.h"

/** @brief Производит деление двух decimal чисел.
 *  @param value_1 1-ый decimal, делимое.
 *  @param value_2 2-ой decimal, делитель.
 *  @param result decimal частное, в который записывается результат.
 *  @return error, в случае ошибки будет равен не 0.
 * */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = s21_check_decimal(value_1, value_2, result);
  s21_decimal checking = value_2;
  if ((s21_get_scale(value_1) > 28) || (s21_get_scale(value_2) > 28)) {
    error_code = 1;
  }
  if (!s21_is_zero_decimal(value_2)) {
    error_code = 3;
    s21_set_zero_decimal(result);
  } else if (!error_code) {
    s21_set_zero_decimal(result);
    s21_decimal_long lres = {0};
    s21_decimal_long temp = {0};
    int i = 32;
    int scale_pa_pb = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (s21_get_scale(value_1) == 0 && s21_get_scale(value_2) != 0) {
      s21_reduction_scale_decimal(&checking, s21_get_scale(value_2), 0);
      if (!s21_is_zero_decimal(checking)) {
        error_code =
            s21_addition_scale_decimal(&value_1, s21_get_scale(value_2));
        s21_addition_scale_decimal(&value_2, s21_get_scale(value_2));
        s21_set_scale(&value_2, 0);
        s21_set_scale(&value_1, 0);
        if ((s21_get_bit(value_1, 127) && !s21_get_bit(value_2, 127)) ||
            (!s21_get_bit(value_1, 127) && s21_get_bit(value_2, 127))) {
          if (error_code) {
            error_code = 2;
          }
        }
      }
    }
    s21_decimal_long lvalue_1 = s21_move_to_long_decimal(value_1);
    s21_decimal_long lvalue_2 = s21_move_to_long_decimal(value_2);
    while (s21_is_zero_decimal_long(lvalue_1) && (scale_pa_pb < i) &&
           error_code == 0) {
      s21_div_decimal_long(&lvalue_1, lvalue_2, &temp, 0);
      error_code = s21_sum_mantissas_long(&lres, temp);
      if (s21_is_zero_decimal_long(lvalue_1)) {
        scale_pa_pb++;
        s21_addition_scale_decimal_long(&lvalue_1, 1);
        s21_addition_scale_decimal_long(&lres, 1);
      }
      s21_set_zero_decimal_long(&temp);
    }
    if (scale_pa_pb >= 0 && !error_code) {
      s21_set_scale_long(&lres, scale_pa_pb);
      s21_move_to_normal_decimal(result, lres);
      if ((s21_get_bit(value_1, 127) && !s21_get_bit(value_2, 127)) ||
          (!s21_get_bit(value_1, 127) && s21_get_bit(value_2, 127))) {
        if (error_code) {
          error_code = 1;
        }
        s21_negate(*result, result);
      }
    } else if (scale_pa_pb < 0 && !error_code) {
      s21_move_to_normal_decimal(result, lres);
      error_code = s21_addition_scale_decimal(result, scale_pa_pb * -1);
      s21_set_scale(result, 0);
      if ((s21_get_bit(value_1, 127) && !s21_get_bit(value_2, 127)) ||
          (!s21_get_bit(value_1, 127) && s21_get_bit(value_2, 127))) {
        if (error_code) {
          error_code = 2;
        }
        s21_negate(*result, result);
      }
    }
  }
  return error_code;
}

/** @brief Вспомогательная функция для расчета деления мантис (без учета знака и
 * степени).
 *  @param num 1-ый decimal, делимое.
 *  @param n 2-ой decimal, делитель.
 *  @param res decimal частное, в который записывается результат.
 *  @param option переключатель для деления с округлением или без.
 *  @return error, в случае ошибки будет равен не 0.
 * */
int s21_div_decimal_long(s21_decimal_long *num, s21_decimal_long n,
                         s21_decimal_long *res, int option) {
  s21_decimal_long n_copy = n;
  int i, error = 0;
  if (s21_is_zero_decimal_long(*num)) {
    while (!s21_is_greater_long_decimal(n, *num) && !error) {
      i = 0;
      while (!s21_is_greater_long_decimal(n, *num) && !error) {
        if (s21_shift_left_decimal_long(&n, 1, 6)) {
          error = 1;
          break;
        } else {
          i++;
        }
      }
      s21_div_add_result(num, &n, res, n_copy, i);
    }
    if (!error) {
      if (option && s21_is_zero_decimal_long(*num)) {
        s21_sum_mantissas_long(
            res,
            (s21_decimal_long){{s21_check_fractional(*num, n, *res, &error)}});
      }
      res->bits[6] = num->bits[6];
    }
  } else {
    error = 3;
  }
  return error;
}

/** @brief Вспомогательная функция для s21_div_decimal_long.
 * Используется для записи подсчетов в результирующую переменную.
 *  @param num 1-ый decimal, делимое.
 *  @param n_d 2-ой decimal, делитель.
 *  @param result decimal частное, в который записывается результат.
 *  @param i Переменная, которая хранит часть результата.
 * */
void s21_div_add_result(s21_decimal_long *num, s21_decimal_long *n_d,
                        s21_decimal_long *result, s21_decimal_long n, int i) {
  s21_shift_right_decimal_long(n_d, 1);
  s21_sub_decimal_long(num, *n_d);
  s21_set_zero_decimal_long(n_d);
  n_d->bits[0] = 1;
  s21_shift_left_decimal_long(n_d, i - 1, 6);
  s21_sum_mantissas_long(result, *n_d);
  *n_d = n;
}

/** @brief Функция, которая подсчитывает остаток от деления.
 *  @param integral 1-ый decimal, делимое.
 *  @param divider 2-ой decimal, делитель.
 *  @param error код ошибки, в случае ошибки не равен 0.
 *  @param num получившийся результат, который будет использован для округления.
 *  @return result округление числа, если округление в большую – вернет 1, в
 * ином случае – 0.
 * */
int s21_check_fractional(s21_decimal_long integral, s21_decimal_long divider,
                         s21_decimal_long num, int *error) {
  s21_decimal_long fractional = {0};
  s21_decimal_long n = divider;
  int index_num = 0, firts_num = 0, second_natural_num = 0;
  while (s21_is_zero_decimal_long(integral) && (fractional.bits[5] == 0)) {
    if (s21_is_greater_long_decimal(divider, integral)) {
      if (index_num == 1) {
        firts_num = fractional.bits[0];
      }
      s21_mul_decimal_long(&integral, (s21_decimal_long){{10}});
      s21_mul_decimal_long(&fractional, (s21_decimal_long){{10}});
      index_num++;
    }
    int i = 0;
    while (!s21_is_greater_long_decimal(divider, integral)) {
      *error = s21_shift_left_decimal_long(&divider, 1, 5);
      i++;
    }
    if (i != 0) {
      s21_div_add_result(&integral, &divider, &fractional, n, i);
      if (index_num > 1) {
        second_natural_num = 1;
      }
    }
  }
  if (index_num == 1) {
    firts_num = fractional.bits[0];
  }
  int result = s21_rounding_bank(s21_get_bit_long(num, 0), firts_num,
                                 second_natural_num);
  return result;
}

int s21_div_decimal(s21_decimal num, s21_decimal n, s21_decimal *res,
                    int option) {
  s21_decimal_long long_number = s21_move_to_long_decimal(num);
  s21_decimal_long long_n = s21_move_to_long_decimal(n);
  s21_decimal_long result = {0};
  result.bits[6] = num.bits[3];
  int i, error = 0;
  if (s21_is_zero_decimal_long(long_number)) {
    while (!s21_is_greater_long_decimal(long_n, long_number) && !error) {
      i = 0;
      while (!s21_is_greater_long_decimal(long_n, long_number) && !error) {
        error = s21_shift_left_decimal_long(&long_n, 1, 6);
        i++;
      }
      s21_div_add_result(&long_number, &long_n, &result,
                         s21_move_to_long_decimal(n), i);
    }
    if (!error) {
      if (option && !s21_is_zero_decimal_long(long_number)) {
        s21_sum_mantissas_long(&result,
                               (s21_decimal_long){{s21_check_fractional(
                                   long_number, long_n, result, &error)}});
      }
      error = s21_move_to_normal_decimal(res, result);
    }
  } else {
    error = 3;
  }
  return error;
}