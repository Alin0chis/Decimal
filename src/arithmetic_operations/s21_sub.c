#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = s21_check_decimal(value_1, value_2, result);
  s21_decimal_long long_value_1 = s21_move_to_long_decimal(value_1);
  s21_decimal_long long_value_2 = s21_move_to_long_decimal(value_2);
  if (!error_code && !s21_normalize_long(&long_value_1, &long_value_2)) {
    s21_set_zero_decimal(result);
    error_code = s21_exeptions_sub(long_value_1, long_value_2, result);
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_exeptions_sub(s21_decimal_long num, s21_decimal_long num_2,
                      s21_decimal *result) {
  int error_code = 0;
  if (s21_get_bit_long(num, 223) && s21_get_bit_long(num_2, 223)) {
    if (!s21_is_greater_long_decimal(num_2, num)) {
      s21_sub_decimal_long(&num, num_2);
      error_code = s21_move_to_normal_decimal(result, num);
    } else {
      s21_negate_long(num_2, &num_2);
      s21_sub_decimal_long(&num_2, num);
      error_code = s21_move_to_normal_decimal(result, num_2);
    }
  } else if (s21_get_bit_long(num, 223) || s21_get_bit_long(num_2, 223)) {
    error_code = s21_sum_mantissas_long(&num, num_2);
    if (!error_code) {
      error_code = s21_move_to_normal_decimal(result, num);
    }
  } else if (s21_is_greater_long_decimal(num_2, num)) {
    s21_sub_decimal_long(&num_2, num);
    s21_negate_long(num_2, &num_2);
    error_code = s21_move_to_normal_decimal(result, num_2);
  } else {
    s21_sub_decimal_long(&num, num_2);
    error_code = s21_move_to_normal_decimal(result, num);
  }
  return error_code;
}

// LONG VERSION SUB:

void s21_set_senior_pomidor_bit_long(s21_decimal_long *num, int first_index,
                                     int final_index) {
  s21_set_bit_long(num, final_index--, 0);
  for (; final_index >= first_index; final_index--) {
    s21_set_bit_long(num, final_index, 1);
  }
}

int s21_get_senior_pomidor_bit_long(s21_decimal_long num, int current_index) {
  int index = 0;
  while (!s21_get_bit_long(num, (current_index + index))) {
    index++;
  }
  return (index + current_index);
}

void s21_sub_decimal_long(s21_decimal_long *num, s21_decimal_long num_2) {
  for (int i = 0; i < 191; i++) {
    if (!s21_get_bit_long(*num, i) && s21_get_bit_long(num_2, i)) {
      int final_index = s21_get_senior_pomidor_bit_long(*num, i);
      s21_set_senior_pomidor_bit_long(num, i, final_index);
    } else if (s21_get_bit_long(*num, i) && s21_get_bit_long(num_2, i)) {
      s21_set_bit_long(num, i, 0);
    }
  }
}