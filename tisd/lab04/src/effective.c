/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

 // В эффективности почти нигде не проверяется успешность аллокейта памяти,и в целом много дублирования - горели дедлайны

#include "../inc/effective.h"
#include "../inc/io.h"

#define MAX_GENERATE_NUM 2000
#define N_REPS 1000
#define MAX_COUNT 10000

char generate_nums(int **nums, size_t count_num)
{
	char rc = ERR_OK;
	*nums = calloc(count_num, sizeof(int));
	if(*nums == NULL)
	{
		rc = ERR_ALLOCATE_MEM;
	}
	else
	{
		srand(time(NULL));
		for(size_t i = 0; i < count_num; ++i)
		{
			(*nums)[i] = (int) (MAX_GENERATE_NUM * ((double) rand() / (RAND_MAX + 1.0)));
			(*nums)[i] -= MAX_GENERATE_NUM/2;
			//printf("%d\n", (*nums)[i]);
		}
	}
	return rc;
}

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)) / 1000; 
}

char effective()
{
	char rc = ERR_OK;
	stack_list_t stack_list = create_stack_list();
	stack_array_t stack_array = create_stack_array();
	if(stack_list && stack_array)
	{
		int *nums = NULL;
		size_t size1 = 0;
		size_t size2 = 0;
		size_t size3 = 0;

		printf("Время вычисления выражения:\n");
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

		//замер пушей и попов
		if(rc == ERR_OK)
		{
			printf("Время пушей\n");
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
					int sum_1 = 0;

					clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

					for(size_t i = 0; i<count; ++i)
					{
						push_stack_array(stack_array, nums[i]);
					}

				    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

				    rc = calc_expression_array(stack_array, &sum_1);
				    
				    del = calc_elapsed_time(&t_beg, &t_end);

				    sum = sum + del;
				}

				srand(time(NULL));
				del = 0;

				for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
				{
					int sum_1 = 0;

					clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

					for(size_t i = 0; i<count; ++i)
					{
						rc = push_stack_list(stack_list, nums[i]);
					}

				    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

					rc = calc_expression_list(stack_list, &sum_1);
				    
				    del = calc_elapsed_time(&t_beg, &t_end);

				    sum2 = sum2 + del;
				}

				printf("|%-22ld|%-13f|%-13f|\n", count, (double) (sum)/ N_REPS, (double) (sum2)/ N_REPS);
				free(nums);
			}
		}
		//замер pop-a
		if(rc == ERR_OK)
		{
			printf("Время pop-a\n");
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
						rc = push_stack_array(stack_array, nums[i]);
					}

					int elem = 0;
					clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

					for(size_t i = 0; i<count; ++i)
					{
						pop_stack_array(stack_array, &elem);
					}

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
					int elem = 0;
					clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

					for(size_t i = 0; i<count; ++i)
					{
						pop_stack_list(stack_list, &elem);
					}

				    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
				    
				    del = calc_elapsed_time(&t_beg, &t_end);

				    sum2 = sum2 + del;
				}

				printf("|%-22ld|%-13f|%-13f|\n", count, (double) (sum)/ N_REPS, (double) (sum2)/ N_REPS);
				free(nums);
			}
		}
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
	//	}
		
	}

	

	destroy_stack_list(stack_list);
	destroy_stack_array(stack_array);
	return rc;
}

