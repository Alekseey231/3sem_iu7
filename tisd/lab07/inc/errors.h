#ifndef __ERRORS_H__

#define __ERRORS_H__

#define ERR_OK 0
#define ERR_READ_VOLUME 3
#define ERR_INCORRECT_NUM 4
#define ERR_READ_EMPTY_STR 5
#define ERR_EOF 6
#define ERR_NOT_POSITIVE 7
#define ERR_NOT_DATA 8
#define ERR_INVALID_COUNT_ARG 9
#define ERR_TO_MACH_DATA 10
#define ERR_ALLOCATE_MEM 11
#define ERR_OK_EOF 12
#define ERR_EMPTY_FILE 13
#define ERR_INVALID_INPUT 14
#define ERR_NOT_DIV 15
#define ERR_OK_IS_ONE 16
#define ERR_GET_LINE 17

#define ERR_OPEN_FILE -1

void process_error(char rc);

#endif //#ifndef __ERRORS_H__
