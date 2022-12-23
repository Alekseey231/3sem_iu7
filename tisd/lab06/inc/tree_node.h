#ifndef __TREE_NODE_H__

#define __TREE_NODE_H__

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

struct tree_node_t
{
   	int num;

    // меньшие
    struct tree_node_t *left;
    // большие
    struct tree_node_t *right;
};


struct tree_node_t* node_create(int num);


void node_print(struct tree_node_t *node, void *param);


void node_free(struct tree_node_t *node, void *param);


void node_to_dot(struct tree_node_t *tree, void *param);


#endif	// #ifndef __TREE_NODE_H__