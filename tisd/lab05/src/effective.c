/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/effective.h"
#include "../inc/queue_list.h"
#include "../inc/queue_array.h"
#include "../inc/task.h"

#define MAX_COUNT 100000
#define N_REPS 10000

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)) / 1000; 
}

char effective()
{
	char rc = ERR_OK;
	queue_list_t queue_list = NULL;
	queue_array_t queue_array = NULL;
		/*int *nums = NULL;
		size_t size1 = 0;
		size_t size2 = 0;
		size_t size3 = 0;
		if(rc == ERR_OK)
		{
			printf("Время моделирования выражения:\n");
			printf("| Количество элементов | Стек-массив | Стек-список |\n");
			printf("+----------------------+---------------------------+\n");
			for(size_t count = 100; count <= MAX_COUNT; count*=10)
			{
				rc = generate_nums(&nums, count);
				if(rc != ERR_OK)
					return -1;
				unsigned long long del, sum, sum2 = 0;
				struct timespec t_beg, t_end;

				srand(time(NULL));

				sum = 0;

				for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
				{
					for(size_t i = 0; i<count; ++i)
					{
						push_stack_array(stack_array, nums[i]);
					}
					int sum_1 = 0;

					clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

					rc = calc_expression_array(stack_array, &sum_1);

				    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
				    
				    del = calc_elapsed_time(&t_beg, &t_end);

				    sum = sum + del;
				}

				srand(time(NULL));
				del = 0;

				for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
				{
					for(size_t i = 0; i<count; ++i)
					{
						rc = push_stack_list(stack_list, nums[i]);
					}
					int sum_1 = 0;

					clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

					rc = calc_expression_list(stack_list, &sum_1);

				    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
				    
				    del = calc_elapsed_time(&t_beg, &t_end);

				    sum2 = sum2 + del;
				}

				if(count == 100)
				{
					size1 = get_struct_stack_array(stack_array);
				}
				else if(count == 1000)
				{
					size2 = get_struct_stack_array(stack_array);
				}
				else if(count == 10000)
				{
					size3 = get_struct_stack_array(stack_array);
				}

				printf("|%-22ld|%-13f|%-13f|\n", count, (double) (sum)/ N_REPS, (double) (sum2)/ N_REPS);
				free(nums);
			}
		}*/
	
	
		//замер пушей и попов
			printf("Время добавления элементов в конец очереди\n");
			printf("| Количество элементов | Очередь-массив | Очередь-список |\n");
			printf("+----------------------+----------------+----------------+\n");
			for(size_t count = 100; count <= MAX_COUNT; count*=10)
			{

				task_t *task= NULL;

				if(rc != ERR_OK)
					return -1;
				unsigned long long del, sum, sum2 = 0;
				struct timespec t_beg, t_end;

				srand(time(NULL));

				sum = 0;

				for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
				{
					queue_array = create_queue_array();
					task= create_task();
					clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

					for(size_t i = 0; i<count; ++i)
					{
						rc = push_queue_array(queue_array, task);
					}

				    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

				    
				    destroy_queue_array_without_data(queue_array);
				    delete_task(task);
				   // queue_array = create_queue_array();
				    
				    del = calc_elapsed_time(&t_beg, &t_end);

				    sum = sum + del;
				}

				srand(time(NULL));
				del = 0;

				for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
				{
					queue_list = create_queue_list();
					task_t *task= create_task();

					clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

					for(size_t i = 0; i<count; ++i)
					{
						rc = push_queue_list(queue_list, task);
					}

				    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

				    destroy_queue_list_without_data(queue_list);
				    delete_task(task);
				    //queue_list = create_queue_list();
				    
				    del = calc_elapsed_time(&t_beg, &t_end);

				    sum2 = sum2 + del;
				}
				//destroy_queue_list(queue_list);
				//destroy_queue_array(queue_array);

				printf("|%-22ld| %-14f | %-14f |\n", count, (double) (sum)/ N_REPS, (double) (sum2)/ N_REPS);
		}
		//замер pop-a
		printf("+----------------------+----------------+----------------+\n\n");
		printf("Время извлечения элементов из начала очереди\n");
		printf("| Количество элементов | Очередь-массив | Очередь-список |\n");
		printf("+----------------------+----------------+----------------+\n");
		for(size_t count = 100; count <= MAX_COUNT; count*=10)
		{

			task_t *task= NULL;

			if(rc != ERR_OK)
				return -1;
			unsigned long long del, sum, sum2 = 0;
			struct timespec t_beg, t_end;

			srand(time(NULL));

			sum = 0;

			for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
			{
				queue_array = create_queue_array();
				task= create_task();
				task_t *tmp = NULL;
				for(size_t i = 0; i<count; ++i)
				{
					rc = push_queue_array(queue_array, task);
				}
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

				for(size_t i = 0; i<count; ++i)
				{
					rc = pop_queue_array(queue_array, &tmp);
				}

			    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

			    
			    destroy_queue_array_without_data(queue_array);
			    delete_task(task);
			   // queue_array = create_queue_array();
			    
			    del = calc_elapsed_time(&t_beg, &t_end);

			    sum = sum + del;
			}

			srand(time(NULL));
			del = 0;

			for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
			{
				queue_list = create_queue_list();
				task_t *task= create_task();
				task_t *tmp = NULL;
				for(size_t i = 0; i<count; ++i)
				{
					rc = push_queue_list(queue_list, task);
				}

				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

				for(size_t i = 0; i<count; ++i)
				{
					rc = pop_queue_list(queue_list, &tmp);
				}

			    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

			    destroy_queue_list_without_data(queue_list);
			    delete_task(task);
			    //queue_list = create_queue_list();
			    
			    del = calc_elapsed_time(&t_beg, &t_end);

			    sum2 = sum2 + del;
			}
			//destroy_queue_list(queue_list);
			//destroy_queue_array(queue_array);

			printf("|%-22ld| %-14f | %-14f |\n", count, (double) (sum)/ N_REPS, (double) (sum2)/ N_REPS);
		}
		printf("+----------------------+----------------+----------------+\n");
		/*
		printf("Объем памяти\n");
		printf("| Количество элементов | Стек-массив | Стек-список |\n");
		printf("+----------------------+---------------------------+\n");
	//	for(size_t count = 100; count <= MAX_COUNT; count*=10)
	//	{
		size_t count = 100;
		printf("|%-22ld|%-13ld|%-13ld|\n", count, size1*sizeof(int)+get_size_struct_stack_array(), count*get_node_size()+sizeof(stack_list_t));
		count*=10;
		printf("|%-22ld|%-13ld|%-13ld|\n", count, size2*sizeof(int)+get_size_struct_stack_array(), count*get_node_size()+sizeof(stack_list_t));
		count*=10;
		printf("|%-22ld|%-13ld|%-13ld|\n", count, size3*sizeof(int)+get_size_struct_stack_array(), count*get_node_size()+sizeof(stack_list_t));
		*/
	//	}



	return rc;
}
