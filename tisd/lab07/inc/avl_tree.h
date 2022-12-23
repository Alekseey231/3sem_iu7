#ifndef __AVL_TREE_H__

#define __AVL_TREE_H__

#include <stdio.h>
#include "tree_node.h"

unsigned char height(struct tree_node_t *node);
int balance_factor(struct tree_node_t *node);
void fix_height(struct tree_node_t *node);
struct tree_node_t *rotate_right(struct tree_node_t *root);
struct tree_node_t *rotate_left(struct tree_node_t *root);
struct tree_node_t *balance(struct tree_node_t *node);


#endif	// #ifndef __AVL_TREE_H__
