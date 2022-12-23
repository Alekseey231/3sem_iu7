#ifndef __ERRORS_H__

#define __ERRORS_H__

#define ERR_OK 0
#define ERR_READ_EMPTY_STR 1
#define ERR_EOF 2
#define ERR_ALLOCATE_MEM 3
#define ERR_GET_LINE 4
#define ERR_INCORRECT_QUEUE 5
#define ERR_EMPTY_QUEUE 6
#define ERR_READ_VOLUME 7
#define ERR_REALLOC_MEMORY 8

#define ERR_OPEN_FILE -1

void process_error(char rc);

#endif //#ifndef __ERRORS_H__
