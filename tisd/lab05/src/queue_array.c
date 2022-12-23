/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../inc/queue_array.h"
#include "../inc/errors.h"
#include "../inc/task.h"

char realloc_memory(void **dst, size_t size, size_t count_elements);
#define STEP_REALLOC 2

struct queue_type_array
{
	task_t **content;
	size_t start;
    size_t end;

	size_t size;
};

size_t get_size_struct_queue_array()
{
    return sizeof(struct queue_type_array);
}

queue_array_t create_ex_queue_array(size_t size)
{
    queue_array_t s = malloc(sizeof(struct queue_type_array));

    if (s)
    {
        s->content = malloc(size * sizeof(task_t));

        if (s->content)
        {
            s->size = size;

            make_empty_queue_array(s);
        }
        else
        {
            free(s);

            s = NULL;
        }
    }

    return s;
}

int get_length_queue_array(queue_array_t queue)
{
    return (queue->end - queue->start);
}


queue_array_t create_queue_array(void)
{
    return create_ex_queue_array(START_ALLOCATE);
}


void destroy_queue_array(queue_array_t queue)
{
    task_t *task;
    //printf("%ld", queue->length);

    while (!is_empty_queue_array(queue))
    {
        (void) pop_queue_array(queue, &task);
        delete_task(task);
    }

    free(queue->content);
    free(queue);
}


void make_empty_queue_array(queue_array_t s)
{
	assert(s);
	
    s->start = 0;
    s->end = 0;
}


bool is_empty_queue_array(const queue_array_t s)
{
	assert(s);
	
    return s->start == s->end;
}


bool is_full_queue_array(const queue_array_t s)
{
	assert(s);
	
    return s->end == s->size;
}


int push_queue_array(queue_array_t s, task_t *task)
{
    char rc = ERR_OK;
    if(s == NULL)
    {
        rc = ERR_INCORRECT_QUEUE;
    }
	else
    {
        if(is_full_queue_array(s))
        {
            if(s->start != 0)
            {
                //printf("memove\n");
                 memmove(s->content, s->content + s->start,
                  (s->size - 1) * sizeof(task_t*));
                 s->end -= s->start;
                 s->start = 0;
            }
            else
            {
                s->size = s->size * STEP_REALLOC;
                rc = realloc_memory((void *)(&(s->content)), sizeof(task_t*), s->size);                
            }

        }
        if(rc == ERR_OK)
        {
            s->content[(s->end)++] = task;
        }
        
    }

    return rc;
}


int pop_queue_array(queue_array_t queue, task_t **task)
{
    char rc = ERR_OK;
    if(queue == NULL)
	{
        rc = ERR_INCORRECT_QUEUE;
    }
    else if(is_empty_queue_array(queue))
    {
        rc = ERR_EMPTY_QUEUE;
    }
    else
    {
        *task = queue->content[(queue->start)++];
    }
    return rc;
}

int print_queue_array(queue_array_t q)
{
    char rc = ERR_OK;
    if(is_empty_queue_array(q))
    {
        rc = ERR_EMPTY_QUEUE;
    }
    else
    {
        printf("Содержимое очереди: \n");
        printf("------------------\n");

        for(size_t i = q->start; i != q->end ; ++i)
        {
            print_task(q->content[i]);
        }

        printf("------------------\n");       
    }

    return rc;
}

char realloc_memory(void **dst, size_t size, size_t count_elements)
{
    char rc = ERR_OK;
    void *pbuf = realloc(*dst, size * count_elements);
    if (pbuf == NULL)
    {
        rc = ERR_REALLOC_MEMORY;
    }
    else
    {
        *dst = pbuf;
    }
    return rc;
}

void destroy_queue_array_without_data(queue_array_t queue)
{
    task_t *task;
    //printf("%ld", queue->length);

    while (!is_empty_queue_array(queue))
    {
        (void) pop_queue_array(queue, &task);
    }

    free(queue->content);
    free(queue);
}