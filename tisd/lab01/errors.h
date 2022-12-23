#ifndef __ERRORS_H__

#define __ERRORS_H__

#define ERR_OK 0
#define ERR_READ_STR 1
#define ERR_INCORRECT_INT 2
#define ERR_NUMBER_TOO_LONG 3
#define ERR_EMPTY_STR 4
#define ERR_INCORRECT_FLOAT 5
#define ERR_DIGIT_TOO_LONG 6
#define ERR_OVERFLOW_DIGIT 7
#define ERR_MANTISSA_TOO_LONG 8

#include <stdio.h>

void process_error(int rc);

#endif //#ifndef __ERRORS_H__
