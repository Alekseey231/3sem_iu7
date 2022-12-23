#ifndef _STACK_5_H_

#define _STACK_5_H_

#include <stdbool.h>
#include <stddef.h>
#include "../inc/task.h"

typedef struct queue_type_list* queue_list_t;

queue_list_t create_queue_list(void);
void destroy_queue_list(queue_list_t queue);
bool is_empty_queue_list(const queue_list_t queue);
int push_queue_list(queue_list_t queue, task_t *task);
int pop_queue_list(queue_list_t queue, task_t **task);
int print_queue_list(queue_list_t queue);
size_t get_length_queue_list(queue_list_t queue);
int print_all_adress(queue_list_t queue);
void is_adress_in(void *adress);
size_t get_node_size();
void *get_end(queue_list_t queue);
int save_pop_queue_list(queue_list_t queue);
void destroy_queue_list_without_data(queue_list_t queue);

extern void **free_memory;
extern size_t count_ptrs;

#endif