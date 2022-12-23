/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/edge.h"
#include "../inc/graph.h"
#include "../inc/list.h"


char get_all_nums(char *file_name, graph_t **graph)
{
    char rc = ERR_OK;
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        rc = ERR_OPEN_FILE;
    }
    else
    {
        edge_t edge;
        int count_num = 0;
        int count = 0;
        fscanf(f, "%d", &count);
        rc = get_nums(f, &edge);
        while (rc == ERR_OK)
        {
            ++count_num;
            rc = insert_graph(*graph, &edge);
            
            if (rc == ERR_OK)
            {
                rc = get_nums(f, &edge);
            }
        }
        if (rc == ERR_OK_EOF && count_num == 0)
            rc = ERR_EMPTY_FILE;
        if (rc == ERR_OK_EOF && count_num > 0)
            rc = ERR_OK;
        else if(rc != ERR_OK)
        {
            free_graph(graph);
        }
        fclose(f);
    }
    return rc;
}

char get_nums(FILE *f, edge_t *edge)
{
    char rc = fscanf(f, "%d %d %d %d", &(edge->src), &(edge->dest), &(edge->weight), &(edge->type));
    if(rc == 4)
    {
        rc = ERR_OK;
    }
    else if(feof(f))
    {
        rc = ERR_OK_EOF;
    }
    else
    {
        rc = ERR_READ_VOLUME;
    }
    return rc;
}


char get_count_edge(char *file_name, int *count)
{
    char rc = ERR_OK;
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        rc = ERR_OPEN_FILE;
    }
    else
    {
        if(fscanf(f, "%d", count) == 1)
        {
            if(*count <= 0)
            {
                *count = 0;
                rc = ERR_INCORRECT_NUM;
            }
        }
        else
        {
            rc = ERR_READ_VOLUME;
        }
        fclose(f);
    }
    return rc;
}
/*char get_count_all_nums(char *file_name, int *count)
{
    char rc = ERR_OK;
    FILE *f = fopen(file_name, "r");
    edge_t edge;
    if (f == NULL)
    {
        rc = ERR_OPEN_FILE;
    }
    else
    {
        int count_num = 0;
        rc = get_nums(f, &edge);
        while (rc == ERR_OK)
        {
            ++count_num;
            
            if (rc == ERR_OK)
            {
                rc = get_nums(f, &edge);
            }

        }
        //if (rc == ERR_OK_EOF && count_num == 0)
            //rc = ERR_EMPTY_FILE;
        if (rc == ERR_OK_EOF && count_num >= 0)
            rc = ERR_OK;
        fclose(f);
        *count = count_num;
    }
    return rc;
}*/
