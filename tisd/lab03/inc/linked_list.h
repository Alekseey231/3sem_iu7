#ifndef __LINKED_LIST_H__

#define __LINKED_LIST_H__

#include <stdlib.h>
#include <stdio.h>


typedef struct node
{
	size_t index_start_row;
	struct node *next;
} node_t;

node_t *init_node(size_t start);
void print_list(node_t *list);
void push_back(node_t **list, size_t index_start_row);
void free_list(node_t *list);
size_t get_num_list(node_t *list, size_t desired_index);
size_t set_node_list(node_t *list, size_t desired_index, int new_value);


#endif //#ifndef __LINKED_LIST_H__
