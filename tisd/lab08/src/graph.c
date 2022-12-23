/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/graph.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/dot.h"
#include <limits.h>
#include <string.h>
#include <assert.h>

void visualization_found_path(size_t count_path_elements, graph_t *graph, edge_t *path);
void print_path_to_stdout(edge_t *path, size_t count_path_elements);
void prepare_found_path(size_t *count_path_elements, edge_t *path, edge_t *p, size_t start_index, size_t last_index);
void init_array_distance(long int *d, size_t start_index, graph_t *graph);

#define INF INT_MAX+1L

graph_t *init(size_t size_list)
{
	graph_t *graph = malloc(sizeof(graph_t));
	if(graph != NULL)
	{
		graph->adjacency_list = calloc(size_list, sizeof(node_t*));
		graph->count_edge = size_list;
		graph->visited = calloc(graph->count_edge, sizeof(char));
		if(graph->adjacency_list == NULL || graph->visited == NULL)
		{
			free(graph->visited);
			free(graph->adjacency_list);
			free(graph);
			graph = NULL;
		}
	}
	return graph;
}

char create_graph(char *file_name, graph_t **graph)
{
	int count = 0;
	char rc = ERR_OK;
	rc = get_count_edge(file_name, &count);
	if(rc == ERR_OK)
	{
		*graph = init(count+1);
		if(*graph != NULL)
		{
			rc = get_all_nums(file_name, graph);
		}
		else
		{
			rc = ERR_ALLOCATE_MEM;
		}
	}
	return rc;
}

char insert_graph(graph_t *graph, edge_t *edge)
{
	char rc = ERR_OK;
	rc = list_add_front(graph->adjacency_list + edge->src, edge);
	if(rc == ERR_OK)
	{
		int tmp = edge->src;
		edge->src = edge->dest;
		edge->dest = tmp;
		rc = list_add_front(graph->adjacency_list + edge->src, edge);
	}
	return rc;
}

void print_graph(graph_t *graph)
{
	for(size_t i = 0; i < graph->count_edge; ++i)
	{
		list_apply((graph->adjacency_list)[i], print_node, "(%ld %d) %d | %d\n", i);
	}
}

void free_graph(graph_t **graph)
{
	if(graph != NULL && *graph != NULL)
	{
		for(size_t i = 0; i < (*graph)->count_edge; ++i)
		{
			free_list((*graph)->adjacency_list + i);
		}
		free((*graph)->adjacency_list);
		free((*graph)->visited);
		free(*graph);
		(*graph) = NULL;
	}
}

char find_deykstra(graph_t *graph, size_t start_index, size_t last_index)
{
	char is_finded = 0;
	long int *d = calloc(graph->count_edge, sizeof(long int));
	memset(graph->visited, 0, sizeof(char) * graph->count_edge);
	edge_t *p = calloc(graph->count_edge, sizeof(edge_t));

	if(d != NULL && p != NULL)
	{
		init_array_distance(d, start_index, graph);
		for(size_t i = 0; i < graph->count_edge; ++i)
		{
			int v = -1;
			for(size_t j = 0; j<graph->count_edge; ++j)
			{
				if(!graph->visited[j] && (v == -1 || d[j] < d[v]))
				{
					v = j;
				}
			}
			if(d[v] == INF)
				break;

			graph->visited[v] = 1;
			node_t *node = (graph->adjacency_list)[v];
			while(node)
			{
				if(node->weight + d[v] < d[node->dest])
				{
					d[node->dest] = node->weight + d[v];
					p[node->dest].src = v;
					p[node->dest].type = node->type;
				}
				node = node->next;
			}
		}

		if(d[last_index] != INF)
		{
			is_finded = 1;
			printf("Минимальная длина пути:%ld\n", d[last_index]);

			edge_t *path = calloc(graph->count_edge, sizeof(edge_t));
			size_t count_path_elements = 0;

			if(path != NULL)
			{
				prepare_found_path(&count_path_elements,path, p, start_index, last_index);
				visualization_found_path(count_path_elements, graph, path);
				print_path_to_stdout(path, count_path_elements);		
			}

			free(path);
		}
	}
	else
	{
		is_finded = -1;
	}
	free(d);
	free(p);
	return is_finded;
}

void init_array_distance(long int *d, size_t start_index, graph_t *graph)
{
	for(size_t i = 0; i < graph->count_edge; ++i)
	{
		d[i] = INF;
	}
	d[start_index] = 0;
}

void prepare_found_path(size_t *count_path_elements, edge_t *path, edge_t *p, size_t start_index, size_t last_index)
{
	path[*count_path_elements].src = last_index;
	path[*count_path_elements].type = -1;
	++(*count_path_elements);

	for(size_t i = last_index; i != start_index;)
	{
		path[*count_path_elements] = p[i];
		i = p[i].src;
		++(*count_path_elements);
	}
	
	for(size_t i = 0; i < (*count_path_elements)/2; ++i)
	{
		edge_t tmp = path[i];
		path[i] = path[*count_path_elements - i -1];
		path[*count_path_elements - i -1] = tmp;
	}
}


void visualization_found_path(size_t count_path_elements, graph_t *graph, edge_t *path)
{
	for(size_t i = 0; i < count_path_elements; ++i)
	{
		char buf[16] = {0};
		char buf2[50] = {0};
		snprintf(buf, 16, "./dot/res%ld.gv", i);
		snprintf(buf2, 50, "dot -Tpng %s -o./dot/res%ld.png", buf, i);
		FILE *f = fopen(buf, "w");

	    assert(f);

	    graph_export_to_dot_saved(f, "test_graph", graph, path[i].src);

	    fclose(f);

	    system(buf2);
	}
}

void print_path_to_stdout(edge_t *path, size_t count_path_elements)
{
	int prev = path[0].type;
	printf("%d\n", path[0].src);
	printf("|\n");
	printf("V\n");
	for(size_t i = 1; i < count_path_elements; ++i)
	{
		printf("%d", path[i].src);
		if(path[i].type != prev && i != count_path_elements-1)
		{
			printf(" | Пересадка с %s на %s", prev == 0 ? "машины" : "поезда", path[i].type == 0 ? "машинy" : "поезд");
		}
		prev = path[i].type;
		if(i != count_path_elements-1)
		{
			printf("\n");
			printf("|\n");
			printf("V\n");
		}
	}
	printf("\n");
}
