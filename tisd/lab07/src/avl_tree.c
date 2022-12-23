/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/tree.h"
#include "../inc/avl_tree.h"

unsigned char height(struct tree_node_t *node)
{
	unsigned char rc = 0;
	if(node != NULL)
	{
		rc = node->height;
	}
	return rc;
}

int balance_factor(struct tree_node_t *node)
{
	//printf("%p %p\n", (void *)node->right, (void *)node->left);
	return height(node->right) - height(node->left);
}

void fix_height(struct tree_node_t *node)
{
	unsigned char l = height(node->left);
	unsigned char r = height(node->right);
	node->height = (l > r ? l : r) + 1;
}

struct tree_node_t *rotate_right(struct tree_node_t *root)
{
	struct tree_node_t *new_root = root->left;
	root->left = new_root->right;
	new_root->right = root;
	fix_height(root);
	fix_height(new_root);
	return new_root;
}

struct tree_node_t *rotate_left(struct tree_node_t *root)
{
	struct tree_node_t *new_root = root->right;
	root->right = new_root->left;
	new_root->left = root;
	fix_height(root);
	fix_height(new_root);
	return new_root;
}

struct tree_node_t *balance(struct tree_node_t *node)
{
	fix_height(node);
	if(balance_factor(node) == -2)
	{
		if(balance_factor(node->left) > 0)
		{
			node->left = rotate_left(node->left);
		}
		return rotate_right(node);
	}

	if(balance_factor(node) == 2)
	{
		if(balance_factor(node->right) < 0)
		{
			node->right = rotate_right(node->right);
		}
		return rotate_left(node);
	}
	return node;
}

/*

struct tree_node_t *balance(struct tree_node_t *node)
{
	fix_height(node);
	if(balance_factor(node) == 2)
	{
		if(balance_factor(node->left) > 0)
		{
			node->left = rotate_left(node->left);
		}
		return rotate_right(node);
	}

	if(balance_factor(node) == -2)
	{
		if(balance_factor(node->right) < 0)
		{
			node->right = rotate_right(node->right);
		}
		return rotate_left(node);
	}
	return node;
}


*/