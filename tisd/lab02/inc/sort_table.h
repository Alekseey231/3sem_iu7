#ifndef __SORT_TABLE_H__

#define __SORT_TABLE_H__

#include "subscribers.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(void *base, size_t nmemd, size_t size, int (*compar)(const void *, const void *));
void swap(void *obj1, void *obj2, size_t size);
int comparator_subscribers(const void *a, const void *b);
void insertion_sort(void *base, size_t nmemd, size_t size, int (*compar)(const void *, const void *));
int comparator_keys(const void *a, const void *b);

#endif //#ifndef __SORT_TABLE_H__
