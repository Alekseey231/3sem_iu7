#ifndef __IO_H__

#define __IO_H__

#include "../inc/edge.h"
#include "../inc/graph.h"

char get_nums(FILE *f, edge_t *edge);
char get_count_all_nums(char *file_name, int *count);
char get_all_nums(char *file_name, graph_t **graph);
char get_count_edge(char *file_name, int *count);

#endif //#ifndef __IO_H__
