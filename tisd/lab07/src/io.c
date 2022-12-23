/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/errors.h"
#include "../inc/tree_node.h"
#include "../inc/tree.h"
#include "../inc/io.h"
#define _GNU_SOURCE_


char get_all_nums(char *file_name, struct tree_node_t **root)
{
    char rc = ERR_OK;
    FILE *f = fopen(file_name, "r");
    struct tree_node_t *node;
    if (f == NULL)
    {
        rc = ERR_OPEN_FILE;
    }
    else
    {
        int num = 0;
        int count_num = 0;
        rc = get_num(f, &num);
        while (rc == ERR_OK)
        {
            ++count_num;
            node = node_create(num);
            if(node == NULL)
            {
                rc = ERR_ALLOCATE_MEM;
            }
            else
            {
                *root = btree_insert(*root, node);
            }
            
            if (rc == ERR_OK)
            {
                rc = get_num(f, &num);
            }

        }
        if (rc == ERR_OK_EOF)
            rc = ERR_OK;
        if(rc != ERR_OK)
        {
            post_order_apply(*root, node_free, NULL);
        }

        fclose(f);
    }
    return rc;
}

char get_line(FILE *f, char **line, size_t *line_alloc)
{
    char rc = ERR_OK;
    if (getline(line, line_alloc, f) != -1)
    {
        if ((*line)[strlen(*line) - 1] == '\n')
        {
            (*line)[strlen(*line) - 1] = 0;
        }
        if (strlen(*line) == 0)
        {
            rc = ERR_READ_EMPTY_STR;
        }
    }
    else if (feof(f))
    {
        rc = ERR_EOF;
    }
    else
    {
        rc = ERR_GET_LINE;
    }
    return rc;
}

char get_num(FILE *f, int *num)
{
    char rc = ERR_OK;

    char *line = NULL;
    size_t line_alloc = 0;

    rc = get_line(f, &line, &line_alloc);
    if (rc == ERR_OK)
    {
        char *endptr;
        *num = strtoll(line, &endptr, 10);
        if (*endptr != 0)
            rc = ERR_READ_VOLUME;
    }
    if (rc == ERR_EOF)
        rc = ERR_OK_EOF;
    free(line);
    return rc;
}

char add_node_to_file(struct tree_node_t *node, char *file_name)
{
    char rc = ERR_OK;
    FILE *f = fopen(file_name, "a");
    if(f != NULL)
    {
        fprintf(f, "%d\n", node->num);
        fclose(f);
    }
    return rc;
}

char get_count_nums(char *file_name, size_t *count_nums)
{
    char rc = ERR_OK;
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        rc = ERR_OPEN_FILE;
    }
    else
    {
        int num = 0;
        int count_num = 0;
        rc = get_num(f, &num);
        while (rc == ERR_OK)
        {
            ++count_num;
            rc = get_num(f, &num);
        }

        fclose(f);
        *count_nums = count_num;
    }
    return rc;
}


char get_all_nums_not_balanced(char *file_name, struct tree_node_t **root)
{
    char rc = ERR_OK;
    FILE *f = fopen(file_name, "r");
    struct tree_node_t *node;
    if (f == NULL)
    {
        rc = ERR_OPEN_FILE;
    }
    else
    {
        int num = 0;
        int count_num = 0;
        rc = get_num(f, &num);
        while (rc == ERR_OK)
        {
            ++count_num;
            node = node_create(num);
            if(node == NULL)
            {
                rc = ERR_ALLOCATE_MEM;
            }
            else
            {
                *root = btree_insert_not_balanced(*root, node);
            }
            
            if (rc == ERR_OK)
            {
                rc = get_num(f, &num);
            }

        }
        //if (rc == ERR_OK_EOF && count_num == 0)
            //rc = ERR_EMPTY_FILE;
        if (rc == ERR_OK_EOF)
            rc = ERR_OK;
        if(rc != ERR_OK)
        {
            post_order_apply(*root, node_free, NULL);
        }

        fclose(f);
    }
    return rc;
}