#ifndef __HASH_TABLE_H__

#define __HASH_TABLE_H__

#include <stdlib.h>
#include "../inc/list.h"

typedef struct hash_table_t
{
	node_t **content;
	size_t count_elements;
	size_t capacity;
	size_t mod;
	float avarage_count_compare;
	size_t all_count_compare;
	size_t max_count_compare;
} hash_table_t;



hash_table_t *init_hash_table(size_t size, size_t prime_num);
size_t get_min_prime_large_num(size_t n);
char prime_factor(size_t n);
char hash_table_insert(hash_table_t **table, int num, char is_creating, char *is_restruct);
char fill_hash_table(char *file_name, hash_table_t *table);
hash_table_t *create_hash_table(char *file_name);
size_t hash_func(hash_table_t *table, int num);
void free_hash_table(hash_table_t *table);
void print_hash_table(hash_table_t *table);
char find_hash_table(hash_table_t *table, int num, int *count_cmp);
char restruct_hash_table(hash_table_t *table, hash_table_t **new_table);
char is_restruct_needed(hash_table_t *table);
char resturct_after_create(hash_table_t **table, char *is_restruct);
char hash_table_delete(hash_table_t *table, int num);
size_t get_size_hash_table(hash_table_t *table);

#endif //#ifndef __HASH_TABLE_H__
