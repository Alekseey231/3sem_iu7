#ifndef __LONG_INT_PROCESS_H__

#define __LONG_INT_PROCESS_H__

#include "errors.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_INT 30

typedef struct long_int
{
    int sign;
    int digits[MAX_LEN_INT];
    int count_digit;
} long_int;

int process_long_int(long_int *num);
int validate_int(char *str);
void save_int(long_int *num, char *str, size_t len_str);
void print_int(long_int *num);
void delete_zeros_int(long_int *num_int);

#endif //#ifndef __LONG_INT_PROCESS_H__
