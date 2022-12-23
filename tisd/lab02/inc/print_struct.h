#ifndef __PRINT_STRUCT_H__

#define __PRINT_STRUCT_H__

#include "../inc/subscribers.h"
#include "errors.h"
#include <stdio.h>

void print_entry(subscribers_t *subscribers);
void print_sturcts(subscribers_t *subscribers, size_t count_structs);

#endif //#ifndef __PRINT_STRUCT_H__