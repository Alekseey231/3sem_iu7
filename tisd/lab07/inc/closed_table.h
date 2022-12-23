#ifndef __CLOSED_TABLE_H__

#define __CLOSED_TABLE_H__



typedef struct cls_cell_t
{
	int num;
	char status;
} cls_cell_t;

typedef struct closed_table_t
{
	cls_cell_t *content;
	size_t capacity;
	size_t count_elements;
	size_t mod;
	float avarage_count_compare;
	size_t max_count_compare;
	size_t all_count_compare;
} closed_table_t;


closed_table_t *init_closed_table(size_t size, size_t prime_num);
closed_table_t *create_closed_table(char *file_name);
char fill_closed_table(char *file_name, closed_table_t *table);
void free_closed_table(closed_table_t *table);
char closed_table_insert(closed_table_t **table, int num, char is_creating, char *is_restruct);
size_t closed_func(closed_table_t *table, int num);
char closed_table_delete(closed_table_t *table, int num);
void print_closed_table(closed_table_t *table);
char closed_table_find(closed_table_t *table, int num, int *count_cmp);
char is_restruct_needed_closed(closed_table_t *table);
char restruct_closed_table(closed_table_t *table, closed_table_t **new_table);
char is_restruct_needed_closed(closed_table_t *table);
char resturct_after_create_closed(closed_table_t **table, char *is_restruct);
size_t get_size_closed_table(closed_table_t *table);

#endif	// #ifndef __CLOSED_TABLE_H__




