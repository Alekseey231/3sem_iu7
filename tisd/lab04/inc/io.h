#ifndef __IO_H__

#define __IO_H__

#include "../inc/errors.h"
#include "../inc/stack_list.h"
#include "../inc/stack_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#define CHECK_ERRNO(errno, num) (errno == ERANGE && (num == LONG_MAX || num == LONG_MIN)) || (errno != 0 && num == 0)
#define _GNU_SOURCE

char get_line(FILE *f, char **line, size_t *line_alloc);
char get_num(FILE *f, int *num);
char get_nums(int count, int *nums, stack_list_t stack_list, stack_array_t stack_array);
char parse_nums_from_string(char *line, int *nums, int count, stack_list_t s, stack_array_t stack_array);
char set_expression_stack(stack_list_t s, stack_array_t a, int count_num);

#endif //#ifndef __IO_H__
