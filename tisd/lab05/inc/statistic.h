#ifndef _STATISTIC_H_

#define _STATISTIC_H_

#include <stddef.h>
#include <stdlib.h>

typedef struct stat_t
{
	size_t count_in;
	size_t count_out;
	size_t count_app_trigger;
} stat_t;

void delete_stat(stat_t *stat);
stat_t *create_stat();

#endif