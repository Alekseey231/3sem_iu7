/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/queue_list.h"
#include "../inc/queue_array.h"
#include "../inc/errors.h"
#include "../inc/task.h"
#include "../inc/statistic.h"
#include "../inc/process_queue.h"
#include "../inc/effective.h"
#include <stdio.h>
#include <stddef.h>

#define CHOICE_EXIT 0
#define CHOICE_MODEL_LIST 1
#define CHOICE_MODEL_ARRAY 2
#define CHOICE_TEST_ARRAY 3
#define CHOICE_TEST_LIST 4
#define CHOICE_EFFECTIVE 5


#define T1_LOW_BOUND_C 0
#define T1_HIGH_BOUND_C 6

#define T2_LOW_BOUND_C 0
#define T2_HIGH_BOUND_C 1

char test_queue_array();
char test_queue_list();
void clean_stdin(void);
char process_show_adress(queue_list_t queue_list);

int main()
{
	char rc = ERR_OK;
	char *hello = "Заявка поступают в хвост по случайному закону с интервалом времени от 0 до 6 единиц времени.\n"
				"В аппарат они поступают из головы очереди по одной и осблуживаются за время от 0 до 1 е.в.\n"
				"Каждая заявка после аппарата поступает в хвост очереди, совершая всего 5 циклов обслуживания, после чего покидает систему\n";
	char *menu = "0) Выйти из программы\n1) Смоделировать процесс в очереди-списке\n"
					"2) Смоделировать процесс в очереди-массиве\n3) Работа с очередью-массивом\n4) Работа с очередью-списком\n5) Вывод эффективности\n";

	printf("%s\n", hello);
	int choice = -1;

	while(choice != CHOICE_EXIT && rc == ERR_OK)
	{
		printf("%s", menu);
		rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_READ_VOLUME;
		clean_stdin();

		if(rc == ERR_OK)
		{	
			switch(choice)
			{
				case CHOICE_MODEL_LIST: ;
					float t1_low, t1_high, t2_low, t2_high;
					printf("Введите x y z d, где\nx - нижняя граница T1, y - верхняя граница T1\nz - нижняя граница T2, d - верхняя граница T2\n \
						При некорректном вводе будет выполнено моделирование с данными по умолчанию\n");
					rc = (scanf("%f %f %f %f", &t1_low, &t1_high, &t2_low, &t2_high)==4 && t1_low>=0 && t1_high>=0 && t2_low>=0 && t2_high>=0
						&& t1_high>=t1_low && t2_high>=t2_low && (t1_high+t1_low) > 0 && (t2_high+t2_low) > 0) ? ERR_OK : ERR_READ_VOLUME;
					if(rc != ERR_OK)
					{
						t1_low = T1_LOW_BOUND_C;
						t1_high = T1_HIGH_BOUND_C;
						t2_low = T2_LOW_BOUND_C;
						t2_high = T2_HIGH_BOUND_C;
						rc = ERR_OK;
					}
					rc = process_queue_list(t1_low, t1_high, t2_low, t2_high);
					break;
				case CHOICE_MODEL_ARRAY: ;
					printf("Введите x y z d, где\nx - нижняя граница T1, y - верхняя граница T1\nz - нижняя граница T2, d - верхняя граница T2\n \
						При некорректном вводе будет выполнено моделирование с данными по умолчанию\n");
					rc = (scanf("%f %f %f %f", &t1_low, &t1_high, &t2_low, &t2_high)==4 && t1_low>=0 && t1_high>=0 && t2_low>=0 && t2_high>=0
						&& t1_high>=t1_low && t2_high>=t2_low && (t1_high+t1_low) > 0 && (t2_high+t2_low) > 0) ? ERR_OK : ERR_READ_VOLUME;
					if(rc != ERR_OK)
					{
						t1_low = T1_LOW_BOUND_C;
						t1_high = T1_HIGH_BOUND_C;
						t2_low = T2_LOW_BOUND_C;
						t2_high = T2_HIGH_BOUND_C;
						rc = ERR_OK;
					}
					rc = process_queue_array(t1_low, t1_high, t2_low, t2_high);
					break;
				case CHOICE_TEST_ARRAY: ;
					rc = test_queue_array();
					break;
				case CHOICE_TEST_LIST: ;
					rc = test_queue_list();
					break;
				case CHOICE_EFFECTIVE: ;
					rc = effective();
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
	return rc;
}

#define CHOICE_EXIT 0
#define CHOICE_ADD_ARRAY 1
#define CHOICE_DELETE_ARRAY 2
#define CHOICE_SHOW_ARRAY 3
#define CHOICE_CLEAR_ARRAY 4
#define CHOICE_SHOW_ADRESS 5

char test_queue_array()
{
	char rc = ERR_OK;
	queue_array_t queue_array = create_queue_array();
	//task_t *task = NULL;
	
	int choice = -1;

	char *menu = "0) Выйти в главное меню\n1) Добавить задачу в очередь\n2) Удалить задачу из очереди\n"
				"3) Посмотреть содержимое очереди\n4) Очистить очереди\n";

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
				case CHOICE_ADD_ARRAY:
					printf("Введите цикл в очереди и время до конца обработки: ");
					task_t *task = create_task();
					if(scanf("%zu %f", &(task->count_cycles_complete), &(task->time_until_end_process)) == 2 && task->time_until_end_process >= 0)
					{
						push_queue_array(queue_array, task);
					}
					else
					{
						rc = ERR_READ_VOLUME;
						delete_task(task);
					}
					break;
				case CHOICE_DELETE_ARRAY: ;
				{
					task_t *task;
					rc = pop_queue_array(queue_array, &task);
					if(rc == ERR_OK)
					{
						print_task(task);
						delete_task(task);
					}
					break;
				}
				case CHOICE_SHOW_ARRAY:
					rc = print_queue_array(queue_array);
					//printf("%d\n", get_length_queue_array(queue_array));
					break;
				case CHOICE_CLEAR_ARRAY:
					destroy_queue_array(queue_array);
					queue_array = create_queue_array();
					printf("Очередь успешно очищен\n");
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

	destroy_queue_array(queue_array); 

	return rc;
}

char test_queue_list()
{
	char rc = ERR_OK;
	queue_list_t queue_list = create_queue_list();
	//task_t *task = NULL;
	
	int choice = -1;
	free_memory = calloc(1000, sizeof(void *));
	count_ptrs = 0;

	char *menu = "0) Выйти в главное меню\n1) Добавить задачу в очередь\n2) Удалить задачу из очереди\n"
				"3) Посмотреть содержимое очереди\n4) Очистить очереди\n5) Посмотреть список адресов\n";

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
				case CHOICE_ADD_ARRAY:
					printf("Введите цикл в очереди и время до конца обработки: ");
					task_t *task = create_task();
					if(scanf("%zu %f", &(task->count_cycles_complete), &(task->time_until_end_process)) == 2 && task->time_until_end_process >= 0)
					{
						push_queue_list(queue_list, task);
						is_adress_in(get_end(queue_list));
					}
					else
					{
						rc = ERR_READ_VOLUME;
						delete_task(task);
					}
					break;
				case CHOICE_DELETE_ARRAY: ;
				{
					task_t *task;
					rc = save_pop_queue_list(queue_list);
					if(rc == ERR_OK)
					{
						rc = pop_queue_list(queue_list, &task);
					}
					if(rc == ERR_OK)
					{
						print_task(task);
						delete_task(task);
					}
					break;
				}
				case CHOICE_SHOW_ARRAY:
					rc = 	print_queue_list(queue_list);
					break;
				case CHOICE_CLEAR_ARRAY:
					destroy_queue_list(queue_list);
					queue_list = create_queue_list();
					printf("Очередь успешно очищен\n");
					break;
				case CHOICE_SHOW_ADRESS:
					rc = process_show_adress(queue_list);
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

	free(free_memory);
	destroy_queue_list(queue_list); 

	return rc;
}



void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

char process_show_adress(queue_list_t queue_list)
{
	char rc = ERR_OK;
	if(!is_empty_queue_list(queue_list))
	{
		rc = print_all_adress(queue_list);
	}

	if(count_ptrs != 0)
	{
		printf("Освобожденные адреса: \n");
		printf("-----------------------\n");
		for(size_t i = 0; i < count_ptrs; ++i)
			printf("%p\n", (void*)free_memory[i]);
		printf("-----------------------\n");	
	}
	else if(is_empty_queue_list(queue_list))
	{
		rc = ERR_EMPTY_QUEUE;
	}
	return rc;
}

