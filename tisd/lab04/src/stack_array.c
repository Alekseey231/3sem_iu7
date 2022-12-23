/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../inc/stack_array.h"
#include "../inc/errors.h"

char realloc_memory(void **dst, size_t size, size_t count_elements);
#define STEP_REALLOC 2

struct stack_type_array
{
	int *content;
	size_t top;
	size_t size;
};

size_t get_size_struct_stack_array()
{
    return sizeof(struct stack_type_array);
}

size_t get_struct_stack_array(stack_array_t stack)
{
    return stack->size;
}

stack_array_t create_ex_stack_array(size_t size)
{
    stack_array_t s = malloc(sizeof(struct stack_type_array));

    if (s)
    {
        s->content = malloc(size * sizeof(int));

        if (s->content)
        {
            s->size = size;

            make_empty_stack_array(s);
        }
        else
        {
            free(s);

            s = NULL;
        }
    }

    return s;
}


stack_array_t create_stack_array(void)
{
    return create_ex_stack_array(START_ALLOCATE);
}


void destroy_stack_array(stack_array_t s)
{
	assert(s);
	
    free(s->content);
    free(s);
}


void make_empty_stack_array(stack_array_t s)
{
	assert(s);
	
    s->top = 0;
}


bool is_empty_stack_array(const stack_array_t s)
{
	assert(s);
	
    return s->top == 0;
}


bool is_full_stack_array(const stack_array_t s)
{
	assert(s);
	
    return s->top == s->size;
}


int push_stack_array(stack_array_t s, int i)
{
    char rc = ERR_OK;
    if(s == NULL)
    {
        rc = ERR_INCORRECT_STACK;
    }
	else
    {
        if(is_full_stack_array(s))
        {
            s->size = s->size * STEP_REALLOC;
            rc = realloc_memory((void *)(&(s->content)), sizeof(int), s->size);
        }
        if(rc == ERR_OK)
        {
            s->content[(s->top)++] = i;
        }
        
    }

    return rc;
}


int pop_stack_array(stack_array_t s, int *i)
{
    char rc = ERR_OK;
    if(s == NULL)
	{
        rc = ERR_INCORRECT_STACK;
    }
    else if(is_empty_stack_array(s))
    {
        rc = ERR_EMPTY_STACK;
    }
    else
    {
        *i = s->content[--(s->top)];
    }
    return rc;
}

int print_stack_array(stack_array_t s)
{
    char rc = ERR_OK;
    if(is_empty_stack_array(s))
    {
        rc = ERR_EMPTY_STACK;
    }
    else
    {
        printf("Содержимое стека: \n");
        printf("------------------\n");

        for(size_t i = s->top-1; i > 0 ; --i)
        {
            printf("%d\n", s->content[i]);
        }

        printf("%d\n", s->content[0]);

        printf("------------------\n");       
    }

    return rc;
}

char calc_expression_array(stack_array_t a, int *sum)
{
    char rc = ERR_OK;
    if (is_empty_stack_array(a))
    {
        rc = ERR_EMPTY_STACK;
    }
    else
    {
        int i = 0;
        while(!is_empty_stack_array(a) && rc == ERR_OK)
        {
            rc = pop_stack_array(a, &i);
            (*sum)+=i;
        }
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
