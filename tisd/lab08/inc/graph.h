#ifndef __GRAPH_H__

#define __GRAPH_H__


#include <stdio.h>
#include <stdlib.h>
#include "../inc/list.h"
#include "../inc/edge.h"

typedef struct graph_t
{
	struct node_t **adjacency_list;
	size_t count_edge;
	char *visited;
} graph_t;



graph_t *init(size_t size_list);
char insert_graph(graph_t *graph, edge_t *edge);
void print_graph(graph_t *graph);
void free_graph(graph_t **graph);
char create_graph(char *file_name, graph_t **graph);
char insert_graph_ort(graph_t *graph, edge_t *edge);
char find_deykstra(graph_t *graph, size_t start_index, size_t last_index);
#endif	// #ifndef __GRAPH_H__


