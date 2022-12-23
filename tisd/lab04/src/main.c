/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/errors.h"
#include "../inc/stack_array.h"
#include "../inc/stack_list.h"
#include "../inc/io.h"
#include "../inc/effective.h"

#define CHOICE_ARRAY 1
#define CHOICE_LIST 2
#define CHOICE_EFFECTIVE 3

#define CHOICE_EXIT 0
#define CHOICE_ADD_LIST 1
#define CHOICE_DELETE_LIST 2
#define CHOICE_ADD_ALL_EXPR_LIST 3
#define CHOICE_CALC_LIST 4
#define CHOICE_SHOW_LIST 5
#define CHOICE_CLEAR_LIST 6
#define CHOICE_SHOW_ADRESS 7

void clean_stdin(void);
char process_stack_list();
char process_show_adress(stack_list_t stack_list);
char delete_element_stack(stack_list_t stack_list);
char process_stack_array();

int main()
{
	char rc = ERR_OK;
	int choice = -1;
	char *mainmenu = "0) Выйти из программы\n1) Работа со стеком на основе массива\n2) Работа со стеком на основе списка\n3) Эффективность\n";

	free_memory = calloc(1000, sizeof(void *));
	count_ptrs = 0;

	while(choice != CHOICE_EXIT && rc == ERR_OK)
	{
		printf("%s", mainmenu);
		//rc = get_num(stdin, &choice);
		rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_READ_VOLUME;
		clean_stdin();

		if(choice == CHOICE_ARRAY)
		{
			rc = process_stack_array();
		}
		else if(choice == CHOICE_LIST)
		{
			rc = process_stack_list();
		}
		else if(choice == CHOICE_EFFECTIVE)
		{
			rc = effective();
		}
	}

	
	
	free(free_memory);
	return rc;
}

char process_stack_array()
{
	char rc = ERR_OK;

	char *menu = "0) Выйти в главное меню\n1) Добавить выражение в стек\n2) Удалить число с операцией из стека\n3) Записать выражение в стек\n"
				"4) Посчитать значение выражения\n5) Посмотреть содержимое стека\n6) Очистить стек\n";

	stack_array_t stack_array = create_stack_array();

	int choice = -1;

	while(choice != CHOICE_EXIT && rc == ERR_OK)
	{
		printf("%s", menu);
		//rc = get_num(stdin, &choice);
		rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_READ_VOLUME;
		clean_stdin();

		if(rc == ERR_OK)
		{	
			switch(choice)
			{
				case CHOICE_ADD_LIST:
					printf("Введите выражение(формат a+b или a-b, где а и b - числа): ");
					rc = set_expression_stack(NULL, stack_array, 2);
					break;
				case CHOICE_DELETE_LIST: ;
					int i = 0;
					rc = pop_stack_array(stack_array, &i);
					if(rc == ERR_OK)
					{
						printf("Значение удаленного элемента: %d\n", i);
					}
					break;
				case CHOICE_ADD_ALL_EXPR_LIST:
					printf("Введите выражение(формат a+b или a-b, где а и b - числа): ");
					rc = get_nums(0, NULL, NULL, stack_array);
					break;
				case CHOICE_SHOW_LIST:
					rc = print_stack_array(stack_array);
					break;
				case CHOICE_CALC_LIST: ;
					int sum = 0;
					rc = calc_expression_array(stack_array, &sum);
					if(rc == ERR_OK)
						printf("Значение выражения: %d\n", sum);
					break;
				case CHOICE_CLEAR_LIST:
					destroy_stack_array(stack_array);
					stack_array = create_stack_array();
					printf("Стек успешно очищен\n");
					break;
				case CHOICE_EXIT:
					break;
				default:
					printf("Некорректный выбор пункта меню\n");
					break;
			}	
		}
		if(rc != ERR_OK)
		{
			process_error(rc);
		}
		
		if(rc != ERR_ALLOCATE_MEM)
		{
			rc = ERR_OK;
		}
	}
	destroy_stack_array(stack_array);
	return rc;
}


char process_stack_list()
{
	char rc = ERR_OK;

	char *menu = "0) Выйти в главное меню\n1) Добавить выражение в стек\n2) Удалить число с операцией из стека\n3) Записать выражение в стек\n"
				"4) Посчитать значение выражения\n5) Посмотреть содержимое стека\n6) Очистить стек\n7) Просмотр адресов стека\n";

	stack_list_t stack_list = create_stack_list();

	int choice = -1;

	while(choice != CHOICE_EXIT && rc == ERR_OK)
	{
		printf("%s", menu);
		//rc = get_num(stdin, &choice);
		rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_READ_VOLUME;
		clean_stdin();

		if(rc == ERR_OK)
		{	
			switch(choice)
			{
				case CHOICE_ADD_LIST:
					printf("Введите выражение(формат a+b или a-b, где а и b - числа): ");
					rc = set_expression_stack(stack_list, NULL, 2);
					break;
				case CHOICE_DELETE_LIST: ;
					rc = delete_element_stack(stack_list);
					break;
				case CHOICE_ADD_ALL_EXPR_LIST:
					printf("Введите выражение(формат a+b или a-b, где а и b - числа): ");
					rc = get_nums(0, NULL, stack_list, NULL);
					break;
				case CHOICE_SHOW_LIST:
					rc = print_stack_list(stack_list);
					break;
				case CHOICE_CALC_LIST: ;
					int sum = 0;
					rc = calc_expression(stack_list, &sum);
					if(rc == ERR_OK)
						printf("Значение выражения: %d\n", sum);
					break;
				case CHOICE_CLEAR_LIST:
					destroy_stack_list(stack_list);
					memset(free_memory, 0, START_ALLOCATE * sizeof(void *));
					count_ptrs = 0;
					stack_list = create_stack_list();
					printf("Стек успешно очищен\n");
					break;
				case CHOICE_SHOW_ADRESS:
					rc = process_show_adress(stack_list);
					break;
				case CHOICE_EXIT:
					break;
				default:
					printf("Некорректный выбор пункта меню\n");
					break;
			}	
		}
		if(rc != ERR_OK)
		{
			process_error(rc);
		}
		
		if(rc != ERR_ALLOCATE_MEM)
		{
			rc = ERR_OK;
		}
	}
	destroy_stack_list(stack_list);
	return rc;
}

char delete_element_stack(stack_list_t stack_list)
{
	char rc = ERR_OK;
	int i = 0;
	rc = saved_pop_stack_list(stack_list);
	if(rc == ERR_OK)
	{
		rc = pop_stack_list(stack_list, &i);
	}
	if(rc == ERR_OK)
	{
		printf("Значение удаленного элемента: %d\n", i);
	}
	return rc;
}

char process_show_adress(stack_list_t stack_list)
{
	char rc = ERR_OK;
	if(!is_empty_stack_list(stack_list))
	{
		rc = print_all_adress(stack_list);
	}

	if(count_ptrs != 0)
	{
		printf("Освобожденные адреса: \n");
		printf("-----------------------\n");
		for(size_t i = 0; i < count_ptrs; ++i)
			printf("%p\n", (void*)free_memory[i]);
		printf("-----------------------\n");	
	}
	else if(is_empty_stack_list(stack_list))
	{
		rc = ERR_EMPTY_STACK;
	}
	return rc;
}


void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


/*
	stack_list_t s;

	s = create_stack_list();

	if(!s)
	{
		rc = ERR_ALLOCATE_MEM;
	}
	else
	{
		char *s = NULL;
		size_t n = 0;
		if(getline(&s, &n, stdin) != -1)
		{
			s[strlen(s)-1] = 0;
			converse_rpn(s);
		}
		free(s);
	}
*/