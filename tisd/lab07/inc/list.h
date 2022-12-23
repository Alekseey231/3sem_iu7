#ifndef __LIST_TREE_H__

#define __LIST_TREE_H__


#include <stdio.h>

typedef struct node_t
{
	int num;
	struct node_t *next;
} node_t;

node_t *create_node(int num);
char list_add_front(node_t **head, int num);
char list_find(node_t *head, int num, int *count_cmp);
char list_delete_num(node_t **head, int num);
void free_list(node_t **head);
void print_node(node_t *node, void *arg);
void list_apply(node_t *head, void (*f)(node_t*, void*), void* arg);

#endif	// #ifndef __LIST_TREE_H__
