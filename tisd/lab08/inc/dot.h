#ifndef __DOT_H__

#define __DOT_H__

#include <stddef.h>
#include <stdio.h>
#include "../inc/graph.h"

void graph_export_to_dot(FILE *f, char *graph_name, graph_t *graph);
void node_to_dot(node_t *node, void *param, size_t index);
void graph_export_to_dot_saved(FILE *f, char *graph_name, graph_t *graph, int edge);
void node_to_dot_saved(node_t *node, void *param, size_t index);

#endif	// #ifndef __EDGE_H__


