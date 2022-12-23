/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../inc/queue_list.h"
#include "../inc/errors.h"
#include "../inc/task.h"

struct node
{
    task_t *task;
    struct node *next;
};


struct queue_type_list
{
    struct node *start;
    struct node *end;

    size_t length;
    //size_t max_length;

};

size_t get_length_queue_list(queue_list_t queue)
{
    return queue->length;
}

queue_list_t create_queue_list(void)
{
    queue_list_t queue = malloc(sizeof(struct queue_type_list));

    if (queue)
    {
        queue->start = NULL;
        queue->end = NULL;
        queue->length = 0;
        //size_t max_length = 0;
    }

    return queue;
}

void destroy_queue_list(queue_list_t queue)
{
    assert(queue);
    
    task_t *task;
    //printf("%ld", queue->length);

    while (!is_empty_queue_list(queue))
    {
        (void) pop_queue_list(queue, &task);
        delete_task(task);
    }

    free(queue);
}


bool is_empty_queue_list(const queue_list_t queue)
{
    assert(queue);
    
    return queue->start == NULL;
}


int push_queue_list(queue_list_t queue, task_t *task)
{
    int rc = ERR_OK;

    if(queue == NULL)
    {
        rc = ERR_INCORRECT_QUEUE;
    }
    else
    {
    
        struct node *node = malloc(sizeof(struct node));

        if (!node)
        {
            rc = ERR_ALLOCATE_MEM;
        }
        else
        {
            node->next = queue->end;
            node->task = task;

            queue->end = node;
            if(queue->length == 0)
                queue->start = node;
            ++(queue->length);
        }
    }
    return rc;
}


int pop_queue_list(queue_list_t queue, task_t **task)
{
    char rc = ERR_OK;

    if(queue == NULL)
    {
        rc = ERR_INCORRECT_QUEUE;
    }
    else
    {
       

        if (is_empty_queue_list(queue))
        {
            rc = ERR_EMPTY_QUEUE;
        }
        else
        {
            //printf("%p\n", (void*)queue->start);
            struct node *tmp = queue->start;
            struct node *node = queue->end;
            while(node->next != NULL)
            {
                tmp = node;
                node = node->next;
            }

            *task = node->task;
            tmp->next = NULL;
            --(queue->length);
            if(queue->length == 0)
            {
                queue->start = NULL;
                queue->end = NULL;
            }
            else
            {
                queue->start = tmp;
            }
            free(node);         
        }
    }

    return rc;
}


int print_queue_list(queue_list_t queue)
{
    char rc = ERR_OK;
    if(is_empty_queue_list(queue))
    {
        rc = ERR_EMPTY_QUEUE;
    }
    else
    {
        struct node *node = queue->end;

        printf("Очередь(от конца к началу): \n");
        printf("------------------\n");

        int i = queue->length;
        while(node != NULL)
        {
            printf("Номер: %d; Цикл в очереди: %ld Время до конца обработки: %f\n", i, node->task->count_cycles_complete, node->task->time_until_end_process);
            node = node->next;
            --i;
        }

        printf("------------------\n");       
    }

    return rc;
}
