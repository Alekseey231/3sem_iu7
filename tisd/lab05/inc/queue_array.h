#ifndef _QUEUE_ARRAY_H_

#define _QUEUE_ARRAY_H_

#include <stdbool.h>
#include "../inc/task.h"

#define START_ALLOCATE 1000

typedef struct queue_type_array* queue_array_t;

queue_array_t create_queue_array(void);

void destroy_queue_array(queue_array_t s);

void make_empty_queue_array(queue_array_t s);

bool is_empty_queue_array(const queue_array_t s);

bool is_full_queue_array(const queue_array_t s);

int push_queue_array(queue_array_t s, task_t *task);

int pop_queue_array(queue_array_t s, task_t **task);

int print_queue_array(queue_array_t s);

size_t get_size_struct_queue_array();

int get_length_queue_array(queue_array_t queue);

void destroy_queue_array_without_data(queue_array_t queue);

#endif