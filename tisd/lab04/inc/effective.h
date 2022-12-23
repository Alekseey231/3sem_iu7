#ifndef __EFFECTIVE_H__

#define __EFFECTIVE_H__

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../inc/errors.h"

char generate_nums(int **nums, size_t count_num);
char generate_expression(int *nums, char **line, size_t count);
char effective();
unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end);

#endif //#ifndef __EFFECTIVE_H__


