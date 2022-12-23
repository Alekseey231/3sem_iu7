/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/tree.h"
#include "../inc/avl_tree.h"
#include <string.h>

void f(struct tree_node_t *node, void *arr, int *i);


struct tree_node_t* btree_insert(struct tree_node_t *tree, struct tree_node_t *node)
{
	int cmp;

	if(tree == NULL)
		return node;

	cmp = node->num-tree->num;
	if(cmp == 0)
	{
		printf("Данный узел уже есть в дереве\n");
		return tree;
	}
	else if(cmp < 0)
	{
		tree->left = btree_insert(tree->left, node);
	}
	else
	{
		tree->right = btree_insert(tree->right, node);
	}

	return balance(tree);
}

struct tree_node_t* btree_delete(struct tree_node_t *tree, int num)
{
	if(tree == NULL)
	{
		return tree;
	}

	if(num < tree->num)
	{
		tree->left = btree_delete(tree->left, num);
	}
	else if(num > tree->num)
	{
		tree->right = btree_delete(tree->right, num);
	}
	else
	{
		if(tree->left == NULL)
		{
			struct tree_node_t *temp = tree->right;
			free(tree);
			return temp;
		}
		else if(tree->right == NULL)
		{
			struct tree_node_t *temp = tree->left;
			free(tree);
			return temp;
		}
		else
		{
			struct tree_node_t *temp = min_value_right_tree(tree->right);

			tree->num = temp->num;
			tree->right = btree_delete(tree->right, temp->num);
		}
	}

	return balance(tree);
}

struct tree_node_t* min_value_right_tree(struct tree_node_t *node)
{
	while(node->left != NULL)
	{
		node = node->left;
	}
	return node;
}



struct tree_node_t* lookup1(struct tree_node_t *tree, int num)
{
	int cmp;

	while(tree != NULL)
	{
		cmp = num - tree->num;
		if(cmp == 0)
		{
			return tree;
		}
		else if(cmp < 0)
		{
			tree = tree->left;
		}
		else
		{
			tree = tree->right;
		}
	}
	return NULL;
}

struct tree_node_t* lookup2(struct tree_node_t *tree, int num, int *count_cmp)
{
	int cmp;

	if(tree == NULL)
	{
		return NULL;
	}
	++(*count_cmp);
	cmp = num - tree->num;
	if(cmp == 0)
		return tree;
	else if(cmp < 0)
		return lookup2(tree->left, num, count_cmp);
	else
		return lookup2(tree->right, num, count_cmp);
}

void post_order_apply(struct tree_node_t *tree, void (*f)(struct tree_node_t*, void*), void *arg)
{
	if(tree == NULL)
		return;
	post_order_apply(tree->left, f, arg);
	post_order_apply(tree->right, f, arg);
	f(tree, arg);
}

void pre_order_apply(struct tree_node_t *tree, void (*f)(struct tree_node_t*, void*), void *arg)
{
	if(tree == NULL)
		return;
	f(tree, arg);
	pre_order_apply(tree->left, f, arg);
	pre_order_apply(tree->right, f, arg);
	
}

void inf_order_apply(struct tree_node_t *tree, void (*f)(struct tree_node_t*, void*), void *arg)
{
	if(tree == NULL)
		return;
	inf_order_apply(tree->left, f, arg);
	f(tree, arg);
	inf_order_apply(tree->right, f, arg);
	
}


void inf_order_apply_sort(struct tree_node_t *tree, void (*f)(struct tree_node_t*, void*, int *i), void *arg, int *i)
{
	if(tree == NULL)
		return;
	inf_order_apply_sort(tree->left, f, arg, i);
	f(tree, arg, i);
	inf_order_apply_sort(tree->right, f, arg, i);
	
}

void f(struct tree_node_t *node, void *arr, int *i)
{
	int *a = arr;
	a[*i] = node->num;
	++(*i);
}

void btree_export_to_dot(FILE *f, const char *tree_name, struct tree_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    btree_apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}

void btree_apply_pre(struct tree_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    btree_apply_pre(tree->left, f, arg);
    btree_apply_pre(tree->right, f, arg);
}

void count_node(struct tree_node_t* tree, size_t level, size_t *arr)
{
	++arr[level];
	if(tree->left != NULL)
		count_node(tree->left, level+1, arr);
	if(tree->right != NULL)
		count_node(tree->right, level+1, arr);
}


struct tree_node_t* btree_insert_not_balanced(struct tree_node_t *tree, struct tree_node_t *node)
{
	int cmp;

	if(tree == NULL)
		return node;

	cmp = node->num-tree->num;
	if(cmp == 0)
	{
		printf("Данный узел уже есть в дереве\n");
		return tree;
	}
	else if(cmp < 0)
	{
		tree->left = btree_insert_not_balanced(tree->left, node);
	}
	else
	{
		tree->right = btree_insert_not_balanced(tree->right, node);
	}

	return tree;
}

struct tree_node_t* btree_delete_not_balanced(struct tree_node_t *tree, int num)
{
	if(tree == NULL)
	{
		printf("Данный узел отсутствует в дереве\n");
		return tree;
	}

	if(num < tree->num)
	{
		tree->left = btree_delete_not_balanced(tree->left, num);
	}
	else if(num > tree->num)
	{
		tree->right = btree_delete_not_balanced(tree->right, num);
	}
	else
	{
		if(tree->left == NULL)
		{
			struct tree_node_t *temp = tree->right;
			free(tree);
			return temp;
		}
		else if(tree->right == NULL)
		{
			struct tree_node_t *temp = tree->left;
			free(tree);
			return temp;
		}
		else
		{
			struct tree_node_t *temp = min_value_right_tree(tree->right);

			tree->num = temp->num;
			tree->right = btree_delete_not_balanced(tree->right, temp->num);
		}
	}

	return tree;
}

size_t get_size_tree_bin(struct tree_node_t *tree)
{
	size_t size = 0;
	size_t count = 0;
	count_node_all(tree, &count);
	size += count * sizeof(struct tree_node_t);
	size -= (count * sizeof(unsigned char));
	return size;
}

void count_node_all(struct tree_node_t* tree, size_t *count)
{
	++(*count);
	if(tree->left != NULL)
		count_node_all(tree->left, count);
	if(tree->right != NULL)
		count_node_all(tree->right, count);
}

size_t get_size_tree_balanced(struct tree_node_t *tree)
{
	size_t size = 0;
	size_t count = 0;
	count_node_all(tree, &count);
	size += count * sizeof(struct tree_node_t);
	return size;
}
