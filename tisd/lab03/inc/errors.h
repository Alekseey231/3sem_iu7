#ifndef __ERRORS_H__

#define __ERRORS_H__

#include <stdio.h>

#define ERR_OK 0
#define ERR_ALLOCATE_MEM 1
#define ERR_INPUT_CHOICE 2

#define ERR_INPUT_COLUMNS_COUNT 9
#define ERR_INPUT_ROWS_COUNT 3
#define ERR_INPUT_NUM 4
#define ERR_INCORRECT_DIMENSION 5
#define ERR_IS_NOT_VECTOR 6
#define ERR_ALL_ELEMENTS_ZERO 7
#define ERR_ALL_ELEMENTS_ZERO_BY_MULT 8
#define ERR_READ_FILE 10
#define ERR_OPEN_FILE 11
#define ERR_EMPTY_FILE 12
#define ERR_EMPTY_STR 13
#define ERR_EOF 14
#define ERR_STR_TOO_LONG 15
#define ERR_INPUT_DIMENSION_TOO_SMALL 16
#define ERR_INPUT_DIMENSION_TOO_MUCH 17
#define ERR_INPUT_NUMBER_COUNT 18
#define ERR_DIMENSION_NOT_EQUAL 19
#define ERR_INCORRECT_PERCENT_DENSITY 20

#define ERR_EXIT 100
#define ERR_EXIT_SUB 120

void process_error(char rc);

#endif //#ifndef __ERRORS_H__