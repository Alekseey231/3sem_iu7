#ifndef __PROCESS_DATE_H__

#define __PROCESS_DATE_H__

#define START_COUNT_STRUCT 2
#define LEN_BUF_STATUS 1+1
#define MAX_LEN_DATE 10 + 1
#define ADD_DAYS 7

#include <stdlib.h>
#include "../inc/errors.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../inc/subscribers.h"
#include "../inc/validation_input_data.h"
#include "../inc/find_subscribers.h"


char read_structs_from_file(char *file_name, subscribers_t *subscribers, size_t *count_structs);
char read_str_to_buf(FILE *f, char *buf, size_t max_len);
char read_all_structs_from_file(char *file_name, subscribers_t **subscribers, size_t *count_structs, size_t *start_count_struct);
char read_struct_from_file(FILE *f, subscribers_t *subscribers, size_t *count_structs, short int is_stdin_input);
char add_struct(subscribers_t **subscribers, size_t *count_structs, size_t *start_count_structs);
char realloc_mem(subscribers_t **subscribers, size_t *start_count_struct);
void clean_stdin(void);
char write_struct_to_file(char *filename, subscribers_t *subscribers);
char delete_struct_by_firstname(subscribers_t *subscribers, size_t *count_structs, char *name, char *filename, size_t *delete_structs);
void delete_subscribers_from_array(subscribers_t *subscribers, size_t *count_structs, size_t index);

#endif //#ifndef __PROCESS_DATE_H__	