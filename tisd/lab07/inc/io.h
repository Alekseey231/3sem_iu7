#ifndef __IO_H__

#define __IO_H__

#include "../inc/tree_node.h"
#include "../inc/tree.h"
#include "../inc/io.h"
#define _GNU_SOURCE_

char get_all_nums(char *file_name, struct tree_node_t **root);
char get_line(FILE *f, char **line, size_t *line_alloc);
char get_num(FILE *f, int *num);
char add_node_to_file(struct tree_node_t *node, char *file_name);

char get_count_nums(char *file_name, size_t *count_nums);
char get_all_nums_not_balanced(char *file_name, struct tree_node_t **root);

#endif //#ifndef __IO_H__
