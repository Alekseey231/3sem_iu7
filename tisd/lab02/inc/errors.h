#ifndef __ERRORS_H__

#define __ERRORS_H__

#define ERR_OK 0
#define ERR_READ_FILE 1
#define ERR_OPEN_FILE 2
#define ERR_OPEN_NEW_FILE 9
#define ERR_ALLOCATE_MEM 3
#define ERR_EMPTY_FILE 5
#define ERR_EOF 9
#define ERR_INPUT_CHOICE 12
#define ERR_EXIT 13

#define ERR_STATUS 20
#define ERR_INCORRECT_NAME 21
#define ERR_TOO_MUCH_DAY 22
#define ERR_TOO_MUCH_MONTH 23
#define ERR_NEGATIVE_DAY 24
#define ERR_NEGATIVE_MONTH 25
#define ERR_NEGATIVE_YEAR 26
#define ERR_INCORRECT_DATE 27
#define ERR_NOT_DIGIT_IN_DATE 28
#define ERR_PHONE_NUMBER 29
#define ERR_EMPTY_STR 30
#define ERR_STR_TOO_LONG 31
#define ERR_TOO_MUCH_YEAR 32

#define ERR_OK_EOF 100

void process_error(char rc);

#endif //#ifndef __ERRORS_H__
