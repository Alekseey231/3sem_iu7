#ifndef __IO_H__

#define __IO_H__

char get_all_nums(char *file_name, struct tree_node_t **root);
char get_line(FILE *f, char **line, size_t *line_alloc);
char get_num(FILE *f, int *num);
char add_node_to_file(struct tree_node_t *node, char *file_name);

#endif //#ifndef __IO_H__
