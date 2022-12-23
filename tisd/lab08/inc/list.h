#ifndef __LIST_H__

#define __LIST_H__


#include <stdio.h>
#include "../inc/edge.h"

typedef struct node_t
{
	char type;
	int dest;
	int weight;
	struct node_t *next;
} node_t;

node_t *create_node(edge_t *edge);
char list_add_front(node_t **head, edge_t *edge);
void free_list(node_t **head);
void print_node(node_t *node, void *arg, size_t index);
void list_apply(node_t *head, void (*f)(node_t*, void*, size_t), void* arg, size_t index);
void list_apply_dot(node_t *head, void (*f)(node_t*, void*, size_t), void* arg, size_t index, edge_t *arr, size_t *count_elements);
char is_edge_print(edge_t *arr, edge_t *edge, size_t *count_elements);
void print_edge(edge_t *edge);


#endif	// #ifndef __LIST_H__
