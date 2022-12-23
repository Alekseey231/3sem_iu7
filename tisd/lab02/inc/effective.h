#ifndef __EFFECTIVE_H__

#define __EFFECTIVE_H__

#include "../inc/sort_table.h"
#include "../inc/subscribers.h"
#include "../inc/table_keys.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_REPS 100

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end);
char effective(subscribers_t *subscribers, size_t count_structs);

#endif //#ifndef __EFFECTIVE_H__
