/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../inc/stack_list.h"
#include "../inc/errors.h"


struct node
{
    int item;
    struct node *next;
};


struct stack_type_list
{
    struct node *top;

};

void **free_memory;
size_t count_ptrs;


stack_list_t create_stack_list(void)
{
    stack_list_t s = malloc(sizeof(struct stack_type_list));

    if (s)
        s->top = NULL;

    return s;
}

void *get_top(stack_list_t s)
{
    return s->top;
}


void destroy_stack_list(stack_list_t s)
{
	assert(s);
	
    int item;

    while (!is_empty_stack_list(s))
        (void) pop_stack_list(s, &item);

    free(s);
}


bool is_empty_stack_list(const stack_list_t s)
{
	assert(s);
	
    return s->top == NULL;
}


bool is_full_stack_list(const stack_list_t s)
{
	assert(s);
	
    return false;
}


int push_stack_list(stack_list_t s, int i)
{
	int rc = ERR_OK;

    if(s == NULL)
    {
        rc = ERR_INCORRECT_STACK;
    }
    else
    {
	
        struct node *node = malloc(sizeof(struct node));
        //printf("%ld\n", sizeof(struct node));

        if (!node)
        {
            rc = ERR_ALLOCATE_MEM;
        }
        else
        {
            node->next = s->top;
            node->item = i;

            s->top = node;   
        }
    }
    return rc;
}


int pop_stack_list(stack_list_t s, int *i)
{
    char rc = ERR_OK;

    if(s == NULL)
    {
        rc = ERR_INCORRECT_STACK;
    }
    else
    {
        struct node *node;

        if (is_empty_stack_list(s))
        {
            rc = ERR_EMPTY_STACK;
        }
        else
        {
            node = s->top;
            *i = node->item;
            s->top = node->next;     
            free(node);          
        }
    }

    return rc;
}

/*int back_stack_list(stack_list_t s)
{
    int i = 0;
    pop_stack_list(s, &i);
    push_stack_list(s, i);
    return i;
}*/

int print_all_adress(stack_list_t s)
{
    char rc = ERR_OK;
    if(is_empty_stack_list(s))
    {
        rc = ERR_EMPTY_STACK;
    }
    else
    {
        struct node *node = s->top;


        printf("Адреса элементов стека: \n");
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

int print_stack_list(stack_list_t s)
{
    char rc = ERR_OK;
    if(is_empty_stack_list(s))
    {
        rc = ERR_EMPTY_STACK;
    }
    else
    {
        struct node *node = s->top;


        printf("Содержимое стека: \n");
        printf("------------------\n");

        while(node != NULL)
        {
            printf("%d\n", node->item);
            node = node->next;
        }

        printf("------------------\n");       
    }

    return rc;
}

char calc_expression(stack_list_t s, int *sum)
{
    char rc = ERR_OK;
    if (is_empty_stack_list(s))
    {
        rc = ERR_EMPTY_STACK;
    }
    else
    {
        int i = 0;
        while(!is_empty_stack_list(s) && rc == ERR_OK)
        {
            rc = saved_pop_stack_list(s);
            if(rc == ERR_OK)
            {
                rc = pop_stack_list(s, &i);
            }
            if(rc == ERR_OK)
            {
                (*sum)+=i;
            }
        }
    }
    return rc;
}


char calc_expression_list(stack_list_t s, int *sum)
{
    char rc = ERR_OK;
    if (is_empty_stack_list(s))
    {
        rc = ERR_EMPTY_STACK;
    }
    else
    {
        int i = 0;
        while(!is_empty_stack_list(s) && rc == ERR_OK)
        {
            rc = pop_stack_list(s, &i);
            (*sum)+=i;
        }
    }
    return rc;
}

int saved_pop_stack_list(stack_list_t s)
{
    char rc = ERR_OK;

    if(s == NULL)
    {
        rc = ERR_INCORRECT_STACK;
    }
    else
    {

        if (is_empty_stack_list(s))
        {
            rc = ERR_EMPTY_STACK;
        }
        else
        {
            free_memory[count_ptrs++] = s->top;
        }
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