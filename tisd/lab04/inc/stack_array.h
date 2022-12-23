#ifndef _STACK_ARRAY_H_

#define _STACK_ARRAY_H_

#include <stdbool.h>

#define START_ALLOCATE 3

typedef struct stack_type_array* stack_array_t;

stack_array_t create_stack_array(void);

void destroy_stack_array(stack_array_t s);

void make_empty_stack_array(stack_array_t s);

bool is_empty_stack_array(const stack_array_t s);

bool is_full_stack_array(const stack_array_t s);

int push_stack_array(stack_array_t s, int i);

int pop_stack_array(stack_array_t s, int *i);

int print_stack_array(stack_array_t s);

char calc_expression_array(stack_array_t a, int *sum);

size_t get_size_struct_stack_array();

size_t get_struct_stack_array(stack_array_t stack);

#endif