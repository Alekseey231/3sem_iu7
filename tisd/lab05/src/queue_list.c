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
#define _GNU_SOURCE_

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

void **free_memory;
size_t count_ptrs;

size_t get_length_queue_list(queue_list_t queue)
{
    return queue->length;
}

void *get_end(queue_list_t queue)
{
    return queue->end;
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


void destroy_queue_list_without_data(queue_list_t queue)
{
    assert(queue);
    
    task_t *task;
    //printf("%ld", queue->length);

    while (!is_empty_queue_list(queue))
    {
        (void) pop_queue_list(queue, &task);
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
            node->task = task;
            node->next = NULL;

            if(queue->length == 0)
            {

                queue->start = node;
                queue->end = node;
            }
            else
            {
                queue->end->next = node;
                queue->end = node;            
            }
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
            struct node *temp = queue->start;

            queue->start = (queue->start)->next;

            *task = temp->task;
            free(temp);

            if(queue->start == NULL)
                queue->end = NULL;

            --(queue->length);
        }
    }

    return rc;
}

int save_pop_queue_list(queue_list_t queue)
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
            free_memory[count_ptrs++] = queue->start;
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
        struct node *node = queue->start;

        printf("Очередь(от начала к концу): \n");
        printf("------------------\n");

        int i = 1;
        while(node != NULL)
        {
            printf("Номер: %d; Цикл в очереди: %ld Время до конца обработки: %f\n", i, node->task->count_cycles_complete, node->task->time_until_end_process);
            node = node->next;
            ++i;
        }

        printf("------------------\n");       
    }

    return rc;
}

int print_all_adress(queue_list_t queue)
{
    char rc = ERR_OK;
    if(is_empty_queue_list(queue))
    {
        rc = ERR_EMPTY_QUEUE;
    }
    else
    {
        struct node *node = queue->start;

        printf("Адреса элементов очереди: \n");
        printf("------------------\n");

        while(node != NULL)
        {
            printf("%p\n", (void *)node);
            node = node->next;
        }

        printf("------------------\n");       
    }

    return rc;
}

void is_adress_in(void *adress)
{
    char rc = 0;
    ssize_t index = -1;
    for(size_t i = 0; i < count_ptrs && index == -1; ++i)
    {
        if(adress == free_memory[i])
        {
            rc = 1;
            index = i;
        }
    }

    if(rc)
    {
        memmove(free_memory + index, free_memory + index + 1,
          (count_ptrs - index - 1) * sizeof(void *));
        --count_ptrs;
    }
}

size_t get_node_size()
{
    return sizeof(struct node);
}