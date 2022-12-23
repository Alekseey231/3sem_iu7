#ifndef __EFFECTIVE_H__

#define __EFFECTIVE_H__

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../inc/errors.h"

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end);
double effective_find_not_balanced(char *file_name, int num);
double effective_find_balanced(char *file_name, int num);
double effective_find_hash(char *file_name, int num);
double effective_find_closed(char *file_name, int num);
void effective_find();
void effective_all_find(char *file_name, int num, int count, char *s);
void effective();
double effective_find_hash_not_restruct(char *file_name, int num);
double effective_find_closed_not_restruct(char *file_name, int num);
void effective_hash_find(char *file_name, int num, int count);
double effective_find_hash_restruct(char *file_name, int num);

#endif //#ifndef __EFFECTIVE_H__


