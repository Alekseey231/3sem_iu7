/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/tree_node.h"

struct tree_node_t* node_create(int num)
{
    struct tree_node_t *node;

    node = malloc(sizeof(struct tree_node_t));
    
    if (node)
    {
        node->num = num;

        node->left = NULL;
        node->right = NULL;
    }

    return node;
}


void node_print(struct tree_node_t *node, void *param)
{
    const char *fmt = param;

    printf(fmt, node->num);
}


void node_free(struct tree_node_t *node, void *param)
{
    free(param);
    free(node);
}


void node_to_dot(struct tree_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%d -> %d;\n", tree->num, tree->left->num);

    if (tree->right)
        fprintf(f, "%d -> %d;\n", tree->num, tree->right->num);
}
