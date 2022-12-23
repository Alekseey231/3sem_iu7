#ifndef __LONG_FLOAT_PROCESS_H__

#define __LONG_FLOAT_PROCESS_H__

#include "errors.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_MANTISSA 30
#define MAX_EXP 5
#define MAX_E_POINT_SIGN 4
#define MAX_LEN_FLOAT (MAX_LEN_MANTISSA + MAX_EXP + MAX_E_POINT_SIGN)
#define COUNT_SIGN 2
#define MAX_NUM_LEN 60

typedef struct long_float
{
    int sign;
    int digits[MAX_NUM_LEN];
    int exp;
    int count_digit;
} long_float;


int process_long_float(long_float *num);

int validate_float(char *str, char *buf);
void check_sign_correct(char *buf, char *str, char exp, char *is_correct, size_t i);
void check_point_correct(char *buf, char *str, int *is_point, int is_exp, char *is_correct);
void check_exp_correct(char *buf, char *str, char point, int is_digit, int *is_exp, char *is_correct, size_t i);
char is_all_param_incorrect(size_t len, char *sign, char *buf, char point, int is_exp, int is_point);

int save_float(long_float *num, char *buf);

void delete_zeros_left(long_float *num_float);
void delete_zeros_right(long_float *num);
int check_sign(char sym, size_t *index);

void print_float(long_float *num);

#endif //#ifndef __LONG_FLOAT_PROCESS_H__
