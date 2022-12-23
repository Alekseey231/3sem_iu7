#ifndef __EFFECTIVE_H__

#define __EFFECTIVE_H__

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../inc/errors.h"

char effective();
unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end);

#endif //#ifndef __EFFECTIVE_H__


