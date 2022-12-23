#ifndef __BIN_TREE_H__

#define __BIN_TREE_H__


#include <stdio.h>
#include "tree_node.h"


typedef void (*ptr_action_t)(struct tree_node_t*, void*);


struct tree_node_t* btree_insert(struct tree_node_t *tree, struct tree_node_t *node);
void post_order_apply(struct tree_node_t *tree, void (*f)(struct tree_node_t*, void*), void *arg);
struct tree_node_t* lookup2(struct tree_node_t *tree, int num, int *count_cmp);
void btree_export_to_dot(FILE *f, const char *tree_name, struct tree_node_t *tree);
void btree_apply_pre(struct tree_node_t *tree, ptr_action_t f, void *arg);
void pre_order_apply(struct tree_node_t *tree, void (*f)(struct tree_node_t*, void*), void *arg);
void inf_order_apply(struct tree_node_t *tree, void (*f)(struct tree_node_t*, void*), void *arg);
struct tree_node_t* min_value_right_tree(struct tree_node_t *node);
struct tree_node_t* btree_delete(struct tree_node_t *tree, int num);
void count_node(struct tree_node_t* tree, size_t level, size_t *arr);
struct tree_node_t* lookup1(struct tree_node_t *tree, int num);
void inf_order_apply_sort(struct tree_node_t *tree, void (*f)(struct tree_node_t*, void*, int *i), void *arg, int *i);
void f(struct tree_node_t *node, void *arr, int *i);

void count_node_all(struct tree_node_t* tree, size_t *count);
size_t get_size_tree_bin(struct tree_node_t *tree);
size_t get_size_tree_balanced(struct tree_node_t *tree);

struct tree_node_t* btree_insert_not_balanced(struct tree_node_t *tree, struct tree_node_t *node);
struct tree_node_t* btree_delete_not_balanced(struct tree_node_t *tree, int num);

#endif	// #ifndef __BIN_TREE_H__
