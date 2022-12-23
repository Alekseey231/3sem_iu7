/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */


#include "../inc/linked_list.h"

node_t *init_node(size_t start)
{
	node_t *node = malloc(sizeof(node_t));
	if(node != NULL)
	{
		node->index_start_row = start;
		node->next = NULL;
	}
	return node != NULL ? node : NULL;
}

void print_list(node_t *list)
{
	node_t *tmp = list;
	while(tmp != NULL)
	{
		printf("%ld ", tmp->index_start_row);
		tmp = tmp->next;
	}
	printf("\n");
}

void push_back(node_t **list, size_t index_start_row)
{
	node_t *new_node = init_node(index_start_row);

	node_t *tmp = *list;
	while(tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = new_node;
}

size_t get_num_list(node_t *list, size_t desired_index)
{
	char rc = 1;
	node_t *tmp = list;
	size_t current_index = 0;
	while(tmp != NULL && rc)
	{
		if(current_index == desired_index)
			rc = 0;
		else
		{
			tmp = tmp->next;
			++current_index;		
		}
	}
	return rc == 0 ? tmp->index_start_row : 0;
}

size_t set_node_list(node_t *list, size_t desired_index, int new_value)
{
	char rc = 1;
	node_t *tmp = list;
	size_t current_index = 0;
	while(tmp != NULL && rc)
	{
		if(current_index == desired_index)
		{
			rc = 0;
			tmp->index_start_row = new_value;
		}
		else
		{
			tmp = tmp->next;
			++current_index;		
		}
	}
	return rc == 0 ? tmp->index_start_row : 0;
}

void free_list(node_t *list)
{
	node_t *node;
	while(list != NULL)
	{
		node = list;
		list = list->next;
		free(node);	
	}
}