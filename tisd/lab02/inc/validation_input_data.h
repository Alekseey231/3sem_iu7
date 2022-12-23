#ifndef __VALIDATION_INPUT_DATA_H__

#define __VALIDATION_INPUT_DATA_H__

#include "../inc/errors.h"
#include "../inc/subscribers.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define COUNT_PARTS_DATE 3

int is_name_correct(char *name);
char process_date(char *date, subscribers_t *subscribers);
char get_parts_date(char *date, char **part_date);
int is_num(char *num);
char is_day_correct(int day);
char is_month_correct(int month);
char is_year_correct(int year);
int getDays(int month, int year);

#endif //#ifndef __VALIDATION_INPUT_DATA_H__
