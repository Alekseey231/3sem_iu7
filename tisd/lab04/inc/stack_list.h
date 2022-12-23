#ifndef _STACK_5_H_

#define _STACK_5_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct stack_type_list* stack_list_t;

stack_list_t create_stack_list(void);

void destroy_stack_list(stack_list_t s);

void make_empty_stack_list(stack_list_t s);

bool is_empty_stack_list(const stack_list_t s);

bool is_full_stack_list(const stack_list_t s);

int push_stack_list(stack_list_t s, int i);

int pop_stack_list(stack_list_t s, int *i);

int print_all_adress(stack_list_t s);

int print_stack_list(stack_list_t s);

//int back_stack_list(stack_list_t s);

int converse_rpn(char *s);

char calc_expression(stack_list_t s, int *sum);

int saved_pop_stack_list(stack_list_t s);

void is_adress_in(void *adress);

void *get_top(stack_list_t s);

char calc_expression_list(stack_list_t s, int *sum);

size_t get_node_size();

extern void **free_memory;
extern size_t count_ptrs;

#endif