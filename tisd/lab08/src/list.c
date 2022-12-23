/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/list.h"
#include "../inc/errors.h"
#include <stdlib.h>

node_t *create_node(edge_t *edge)
{
	node_t *node = malloc(sizeof(node_t));
	if(node != NULL && edge != NULL)
	{
		node->type = edge->type;
		node->dest = edge->dest;
		node->weight = edge->weight;
		node->next = NULL;
	}
	return node;
}

char list_add_front(node_t **head, edge_t *edge)
{
	char rc = ERR_OK;
	node_t *tmp_node = create_node(edge);
	if(tmp_node != NULL)
	{
		tmp_node->next = (*head);
		(*head) = tmp_node;
	}
	else
	{
		rc = ERR_ALLOCATE_MEM;
	}
	return rc;
}

/*char list_find(node_t *head, int num, int *count_cmp)
{
	char is_find = 0;
	int count = 0;
	while(head != NULL && !is_find)
	{
		if(head->num == num)
		{
			is_find = 1;
		}
		else
		{
			head = head->next;
		}
		++count;
	}
	*count_cmp = count;
	return is_find;
}

char list_delete_num(node_t **head, int num)
{
	char is_deleted = 0;
	node_t *prev = NULL;
	node_t *cur = *head;

	while(cur != NULL && !is_deleted)
	{
		if(cur->num == num)
		{
			if(prev != NULL)
			{
				prev->next = cur->next;
			}
			else
			{
				*head = cur->next;
			}
			free(cur);
			is_deleted = 1;
		}
		if(!is_deleted)
		{
			prev = cur;
			cur = cur->next;		
		}
	}
	return is_deleted;
}*/

void free_list(node_t **head)
{
	if(head != NULL && *head != NULL)
	{
		node_t *cur = *head;
		node_t *tmp;
		for(; cur;)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
	}
}

void print_node(node_t *node, void *arg, size_t index)
{
	printf(arg, index, node->dest, node->weight, node->type);
}

void print_edge(edge_t *edge)
{
	printf("%d %d %d %d\n", edge->src, edge->dest, edge->weight, edge->type);
}

void list_apply(node_t *head, void (*f)(node_t*, void*, size_t), void* arg, size_t index)
{
	for(; head != NULL; head = head->next)
	{
		f(head, arg, index);
	}
}

void list_apply_dot(node_t *head, void (*f)(node_t*, void*, size_t), void* arg, size_t index, edge_t *arr, size_t *count_elements)
{
	for(; head != NULL; head = head->next)
	{
		edge_t tmp = {.src = head->dest, .dest = index, .weight = head->weight, .type = head->type};
		if(!is_edge_print(arr, &tmp, count_elements))
		{
			f(head, arg, index);
		}
	}
}

char is_edge_print(edge_t *arr, edge_t *edge, size_t *count_elements)
{
	char is_print = 0;
	for(size_t i = 0; i < *count_elements && !is_print; ++i)
	{
		//print_edge(arr+i);
		if((arr[i]).dest == edge->dest && (arr[i]).src == edge->src && (arr[i]).weight == edge->weight && (arr[i]).type == edge->type)
		{
			is_print = 1;
		}
	}
	if(!is_print)
	{
		(arr[*count_elements]).dest = edge->src;
		(arr[*count_elements]).src = edge->dest;
		(arr[*count_elements]).weight = edge->weight;
		(arr[*count_elements]).type = edge->type;
		++(*count_elements);
	}
	return is_print;
}
