#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SC 0x00ff0000
#define S21_2IN32 4294967296

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_decimal_long;

// BIT OPERATIONS:

void s21_set_scale(s21_decimal *dst, int scale);
void s21_set_scale_long(s21_decimal_long *dst, int scale);
int s21_get_sign(s21_decimal dst);
int s21_get_sign_long(s21_decimal_long dst);
void s21_set_bit(s21_decimal *num, int index, unsigned int bit);
unsigned int s21_get_bit(s21_decimal num, int index);
unsigned int s21_get_scale(s21_decimal num);
unsigned int s21_get_scale_long(s21_decimal_long num);
void s21_set_bit_long(s21_decimal_long *num, int index, unsigned int bit);
unsigned int s21_get_bit_long(s21_decimal_long num, int index);
void s21_set_zero_decimal(s21_decimal *dst);
void s21_set_zero_decimal_long(s21_decimal_long *dst);

// ARITHMETIC OPERATIONS:

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_decimal(s21_decimal *num, s21_decimal mul);
int s21_mul_decimal_long(s21_decimal_long *num, s21_decimal_long mul);
int s21_sum_mantissas(s21_decimal *bits, s21_decimal addendum);
int s21_exeptions_sub(s21_decimal_long num, s21_decimal_long num_2,
                      s21_decimal *result);
void s21_sub_decimal_long(s21_decimal_long *num, s21_decimal_long num_2);
void s21_div_add_result(s21_decimal_long *num, s21_decimal_long *n_d,
                        s21_decimal_long *result, s21_decimal_long n, int i);
int s21_sum_mantissas_long(s21_decimal_long *bits, s21_decimal_long addendum);
int s21_div_decimal(s21_decimal num, s21_decimal n, s21_decimal *res,
                    int option);
int s21_div_decimal_long(s21_decimal_long *num, s21_decimal_long n,
                         s21_decimal_long *res, int option);

// CONVERSION:

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int get_num(int *i, int *float_pow, char str_float[20]);
int get_pow(int *i, int *pow_sign, int *float_pow, char str_float[20]);
int converter(int num, int float_pow, int pow_sign, s21_decimal *dst,
              float src);
s21_decimal s21_move_int_to_decimal(int n);
s21_decimal_long s21_move_to_long_decimal(s21_decimal num);
int set_pow(s21_decimal *dst, int value);
int drop_last_digit(s21_decimal *src);
int s21_move_to_normal_decimal(s21_decimal *num, s21_decimal_long num_long);

// COMPARISON ORERATIONS:

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_not(s21_decimal value_1, s21_decimal value_2);
int s21_equal_or_not(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_long_decimal(s21_decimal_long value_1,
                                s21_decimal_long value_2);
int s21_is_zero_decimal_long(s21_decimal_long num);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
void s21_negate_long(s21_decimal_long num, s21_decimal_long *result);
int s21_is_zero_decimal(s21_decimal num);

// OTHER OPERATIONS:

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// SUPPORTING OPERATIONS:

int s21_check_decimal(s21_decimal num, s21_decimal num2, s21_decimal *result);
int s21_addition_scale_decimal(s21_decimal *dst, int n);
int s21_addition_scale_decimal_long(s21_decimal_long *dst, int n);
int s21_normalize(s21_decimal *dec1, s21_decimal *dec2);
int s21_normalize_long(s21_decimal_long *dec1, s21_decimal_long *dec2);
int s21_rounding_bank(int parity, int fract_num, int second_natural_num);
int s21_get_senior_pomidor_bit_long(s21_decimal_long num, int current_index);
void s21_set_senior_pomidor_bit_long(s21_decimal_long *num, int first_index,
                                     int final_index);
int s21_shift_left_decimal_long(s21_decimal_long *num, int n, int i_max);
void s21_shift_right_decimal_long(s21_decimal_long *num, int n);
void s21_shift_right_decimal(s21_decimal *num, int n);
int s21_check_fractional(s21_decimal_long integral, s21_decimal_long divider,
                         s21_decimal_long num, int *error);
int s21_reduction_scale_decimal(s21_decimal *dst, int n, int option);
int s21_reduction_scale_decimal_long(s21_decimal_long *dst, int n, int option);
int s21_check_bits_0_15_and_24_30(s21_decimal src);
int s21_round(s21_decimal value, s21_decimal *result);

#endif