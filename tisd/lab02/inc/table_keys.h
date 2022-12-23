#ifndef __KEYS_H__

#define __KEYS_H__

#include "../inc/print_struct.h"
#include "../inc/subscribers.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_keys(keys_t *keys, size_t count_structs);
void create_keys(subscribers_t *subscribers, size_t count_structs, keys_t *keys);
void print_sturct_by_keys(subscribers_t *subscribers, size_t count_structs, keys_t *keys);
void save_key(keys_t *key, subscribers_t *subscribers, size_t index);
char realloc_mem_keys(keys_t **key, size_t *start_count_struct);

#endif //#ifndef __KEYS_H__
