#include "../s21_decimal.h"

/**
  float_pow – степень экспоненты
  pow_sign – знак экспоненты
  num – само число
  true_pow – настоящая степень
  i – длина строки
*/
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  char str_float[20] = {0};
  int error = 0;
  int sign = 0;
  int float_pow = 1;
  int pow_sign = 0;
  int num = 0;
  int true_pow = 0;
  int i = 0;

  sprintf(str_float, "%e", src);
  s21_set_zero_decimal(dst);

  if (isnan(src) || isinf(src)) {
    error = 1;
  } else {
    if (str_float[i] == '-') {
      sign = 1;
      i++;
    }
    num = get_num(&i, &float_pow, str_float);
    true_pow = get_pow(&i, &pow_sign, &float_pow, str_float);
    float_pow += true_pow;
    if (i) {
      i = 0;
    }
    if (true_pow <= 28 && true_pow >= -28) {
      error = converter(num, float_pow, pow_sign, dst, src);
    } else {
      error = 1;
    }
    s21_set_bit(dst, 127, sign);
    if (error) {
      error = 1;
      s21_set_zero_decimal(dst);
    }
  }
  return error;
}

int get_num(int *i, int *float_pow, char str_float[20]) {
  int num = 0;
  for (; str_float[*i] != 'e'; (*i)++) {
    if (str_float[*i] == '.') {
      continue;
    }
    num *= 10;
    num += str_float[*i] - '0';
    (*float_pow)--;
  }
  (*i)++;
  return num;
}

int get_pow(int *i, int *pow_sign, int *float_pow, char str_float[20]) {
  int tmp = 0;
  if (str_float[*i] == '-') {
    *pow_sign = 1;
    (*i)++;
  } else if (str_float[*i] == '+') {
    (*i)++;
  }
  for (; str_float[*i]; (*i)++) {
    tmp *= 10;
    tmp += str_float[*i] - '0';
  }
  if (*pow_sign) {
    *float_pow *= -1;
  }
  return tmp;
}

int converter(int num, int float_pow, int pow_sign, s21_decimal *dst,
              float src) {
  int error = 0;
  while (num % 10 == 0 && float_pow != 0) {
    num /= 10;
    float_pow += pow_sign ? -1 : 1;
  }
  s21_set_zero_decimal(dst);
  dst->bits[0] = num;
  if ((!pow_sign && float_pow > 0)) {
    while (float_pow) {
      s21_decimal dec = {{10, 0, 0, 0}};
      error = s21_mul(*dst, dec, dst);
      float_pow--;
      if (error) {
        break;
      }
    }
    set_pow(dst, abs(float_pow));
  } else {
    int last = 0;
    if (float_pow > 28) {
      char float_tmp[20] = {'\0'};
      sprintf(float_tmp, "%.7e", src);
      if (float_tmp[2] == '.') {
        last = float_tmp[3] - '0';
      } else {
        last = float_tmp[2] - '0';
      }
    }
    while (float_pow > 28) {
      drop_last_digit(dst);
      float_pow--;
    }
    if (last > 4) {
      dst->bits[0]++;
    }
    set_pow(dst, abs(float_pow));
  }
  return error;
}

int set_pow(s21_decimal *dst, int value) {
  int sign = s21_get_sign(*dst);
  int result = 0;
  if (value < 0 || value > 28) {
    result = 1;
  }
  (dst->bits)[3] = 0;
  int id = 0;
  while (value > 0) {
    s21_set_bit(dst, 112 + id, value % 2);
    value /= 2;
    id++;
  }
  s21_set_bit(dst, 127, sign);
  return result;
}

// опускаем последнюю цифру
int drop_last_digit(s21_decimal *src) {
  unsigned long long last, div;

  last = *((unsigned int *)&src->bits[2]);
  div = last % 10;
  src->bits[2] = last / 10;

  last = *((unsigned int *)&src->bits[1]) + div * S21_2IN32;
  div = last % 10;
  src->bits[1] = last / 10;

  last = *((unsigned int *)&src->bits[0]) + div * S21_2IN32;
  div = last % 10;
  src->bits[0] = last / 10;
  return (int)div;
}