#include "../inc/effective.h"
#include "../inc/tree.h"
#include "../inc/tree_node.h"
#include "../inc/io.h"
#define _GNU_SOURCE_

#define MAX_COUNT 100000
#define N_REPS 1000

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)/1000); 
}

unsigned long long calc_elapsed_time_1(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)); 
}

char effective_right_tree(char *file_name, size_t count, int min, int middle, int max, int find_min, int find_mid, int find_max);
unsigned long long calc_elapsed_time_1(const struct timespec *beg, const struct timespec *end);
void copy_file(char *file_name);
char effective_add_to(int num);
char effective_find();
char sort_nums();

char effective()
{
	char rc = ERR_OK;
	srand(time(NULL));
	sort_nums();
	effective_add_to(1000);
	effective_find();
	//rc = effective_right_tree("test_right_tree_100.txt", 100, -195, 21, 200, -200, 22, 195);
	rc = effective_right_tree("test_right_tree_1000.txt", 1000, -1000, 4558, 10000, -997, 4557, 9989);
	rc = effective_right_tree("test_right_tree_10000.txt", 10000, -100000, -879, 100000, -99980, -880, 99984);	
		
		/*printf("Объем памяти\n");
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


char sort_nums()
{
	char rc = ERR_OK;
	{
		struct tree_node_t *root = NULL;
		printf("Время сортировки:\n");
		printf("| Количество элементов | Время sort-a  |\n");
		printf("+----------------------+--------------+\n");
		
		unsigned long long del, sum = 0;
		struct timespec t_beg, t_end;

		del = 0;
		sum = 0;
		int arr[100000];
		int  i = 0;

		

		for (int k = 0; rc == ERR_OK && k < N_REPS; k++)
		{
			i = 0;
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			rc = get_all_nums("any_tree_100.txt", &root);
			inf_order_apply_sort(root, f, arr, &i);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		    root = NULL;
		    post_order_apply(root, node_free, NULL);
		}

		

		printf("| %-20d | %-12f |\n", 100, (double) (sum)/ N_REPS);
		printf("+----------------------+--------------+\n");
	}
	{
		struct tree_node_t *root = NULL;
		
		unsigned long long del, sum = 0;
		struct timespec t_beg, t_end;

		del = 0;
		sum = 0;
		int arr[100000];
		int  i = 0;

		

		for (int k = 0; rc == ERR_OK && k < N_REPS; k++)
		{
			i = 0;
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			rc = get_all_nums("test_right_tree_100.txt", &root);
			inf_order_apply_sort(root, f, arr, &i);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		    root = NULL;
		    post_order_apply(root, node_free, NULL);
		}

		

		printf("| %-20d | %-12f |\n", 100, (double) (sum)/ N_REPS);
		printf("+----------------------+--------------+\n");
	}
	{
		struct tree_node_t *root = NULL;
		printf("+----------------------+--------------+\n");
		
		unsigned long long del, sum = 0;
		struct timespec t_beg, t_end;

		del = 0;
		sum = 0;
		int arr[100000];
		int  i = 0;

		

		for (int k = 0; rc == ERR_OK && k < N_REPS; k++)
		{
			i = 0;
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			rc = get_all_nums("any_tree_1000.txt", &root);
			inf_order_apply_sort(root, f, arr, &i);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		    root = NULL;
		    post_order_apply(root, node_free, NULL);
		}

		

		printf("| %-20d | %-12f |\n", 1000, (double) (sum)/ N_REPS);
		printf("+----------------------+--------------+\n");
	}
	{
		struct tree_node_t *root = NULL;
		
		unsigned long long del, sum = 0;
		struct timespec t_beg, t_end;

		del = 0;
		sum = 0;
		int arr[100000];
		int  i = 0;

		

		for (int k = 0; rc == ERR_OK && k < N_REPS; k++)
		{
			i = 0;
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			rc = get_all_nums("test_right_tree_1000.txt", &root);
			inf_order_apply_sort(root, f, arr, &i);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		    root = NULL;
		    post_order_apply(root, node_free, NULL);
		}

		

		printf("| %-20d | %-12f |\n", 1000, (double) (sum)/ N_REPS);
		printf("+----------------------+--------------+\n");
	}
	return rc;
}


char effective_find()
{
	char rc = ERR_OK;
	{
		char rc = ERR_OK;
		struct tree_node_t *root = NULL;
		printf("Время поиска элемента в правостороннем дереве:\n");
		printf("| Количество элементов | Время поиска |\n");
		printf("+----------------------+--------------+\n");
		
		int num = 9989;
		unsigned long long del, sum = 0;
		struct timespec t_beg, t_end;

		del = 0;
		sum = 0;
		rc = get_all_nums("test_right_tree_1000.txt", &root);
		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			lookup2(root, num);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		}

		post_order_apply(root, node_free, NULL);

		printf("| %-20d | %-12f |\n", 1000, (double) (sum)/ N_REPS);
		printf("+----------------------+--------------+\n");
	}
	{
		char rc = ERR_OK;
		struct tree_node_t *root = NULL;
		printf("Время поиска элемента в разветвленном дереве:\n");
		printf("| Количество элементов | Время поиска |\n");
		printf("+----------------------+--------------+\n");
		
		int num = -87841	;
		unsigned long long del, sum = 0;
		struct timespec t_beg, t_end;

		del = 0;
		sum = 0;
		rc = get_all_nums("any_tree_1000.txt", &root);
		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			lookup2(root, num);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		}

		post_order_apply(root, node_free, NULL);

		printf("| %-20d | %-12f |\n", 1000, (double) (sum)/ N_REPS);
		printf("+----------------------+--------------+\n");
	}
	return rc;
}


char effective_add_to(int num)
{
	char rc = ERR_OK;
	{
		char rc = ERR_OK;
		struct tree_node_t *root = NULL;
		printf("Время добавления элемента в правостороннее дерево и в файл:\n");
		printf("| Количество элементов | Время вставки в файл | Время вставки в дерево | Время вставки в дерево(без создания) |\n");
		printf("+----------------------+----------------------+------------------------+--------------------------------------+\n");
		

		unsigned long long del, sum = 0, sum_del = 0, sum_without_create = 0;
		struct timespec t_beg, t_end;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			struct tree_node_t *node = node_create(num);
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			rc = get_all_nums("test_right_tree_1000.txt", &root);
			root = btree_insert(root, node);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    root = btree_delete(root, num);
		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		    post_order_apply(root, node_free, NULL);
		    root = NULL;
		}

		del = 0;
		sum_del = 0;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			copy_file("./test_right_tree_1000.txt");
			struct tree_node_t *node = node_create(num);

			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			rc = add_node_to_file(node, "./tmp.txt");
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_del = sum_del + del;
		}

		del = 0;
		sum_without_create = 0;
		rc = get_all_nums("test_right_tree_1000.txt", &root);
		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			struct tree_node_t *node = node_create(num);
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			root = btree_insert(root, node);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    root = btree_delete(root, num);
		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_without_create = sum_without_create + del;
		}

		post_order_apply(root, node_free, NULL);

		printf("| %-20d | %-20f | %-22f | %-37f |\n", 100, (double) (sum_del)/ N_REPS, (double) (sum)/ N_REPS, (double) (sum_without_create)/ N_REPS);
		printf("+----------------------+----------------------+------------------------+--------------------------------------+\n");
	}
	{
		char rc = ERR_OK;
		struct tree_node_t *root = NULL;
		printf("Время добавления элемента в несбалансированное разветвленное дерево и в файл:\n");
		printf("| Количество элементов | Время вставки в файл | Время вставки в дерево | Время вставки в дерево(без создания) |\n");
		printf("+----------------------+----------------------+------------------------+--------------------------------------+\n");
		

		unsigned long long del, sum = 0, sum_del = 0, sum_without_create = 0;
		struct timespec t_beg, t_end;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			struct tree_node_t *node = node_create(num);
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			rc = get_all_nums("any_tree_100.txt", &root);
			root = btree_insert(root, node);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    root = btree_delete(root, num);
		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		    post_order_apply(root, node_free, NULL);
		    root = NULL;
		}

		del = 0;
		sum_del = 0;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			copy_file("./any_tree_100.txt");
			struct tree_node_t *node = node_create(num);

			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			rc = add_node_to_file(node, "./tmp.txt");
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_del = sum_del + del;
		}

		del = 0;
		sum_without_create = 0;
		rc = get_all_nums("any_tree_100.txt", &root);
		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			struct tree_node_t *node = node_create(num);
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			root = btree_insert(root, node);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    root = btree_delete(root, num);
		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_without_create = sum_without_create + del;
		}

		post_order_apply(root, node_free, NULL);

		printf("| %-20d | %-20f | %-22f | %-37f |\n", 100, (double) (sum_del)/ N_REPS, (double) (sum)/ N_REPS, (double) (sum_without_create)/ N_REPS);
		printf("+----------------------+----------------------+------------------------+--------------------------------------+\n");
	}
	return rc;
}


void copy_file(char *file_name)
{
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *new_file = fopen("tmp.txt", "w");

    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        fprintf(new_file, "%s", line);
    }

    fclose(fp);
    fclose(new_file);
    if (line)
        free(line);
}


char effective_right_tree(char *file_name, size_t count, int min, int middle, int max, int find_min, int find_mid, int find_max)
{
	char rc = ERR_OK;
	struct tree_node_t *root = NULL;
	rc = get_all_nums(file_name, &root);
	if(rc == ERR_OK)
	{
		printf("Время добавления элемента в правостороннее дерево:\n");
		printf("| Количество элементов | Место         | Время вставки | Время удаления | Время поиска |\n");
		printf("+----------------------+---------------+---------------+----------------+--------------+\n");
		srand(time(NULL));
		unsigned long long del, sum = 0, sum_del = 0, sum_find = 0;
		struct timespec t_beg, t_end;
		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			struct tree_node_t *node = node_create(min);
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			root = btree_insert(root, node);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    root = btree_delete(root, min);
		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		}
		del = 0;
		sum_del = 0;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
		    struct tree_node_t *node = node_create(min);
		    root = btree_insert(root, node);

			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			root = btree_delete(root, min);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_del = sum_del + del;
		}

		del = 0;
		sum_find = 0;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{

			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			lookup2(root, find_min);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_find = sum_find + del;
		}

		printf("| %-20ld | Начало        | %-13f | %-14f |%-14f|\n", count, (double) (sum)/ N_REPS, (double) (sum_del)/ N_REPS, (double) (sum_find)/ N_REPS);
		printf("+----------------------+---------------+---------------+----------------+--------------+\n");
		del = 0, sum = 0;
		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			struct tree_node_t *node = node_create(middle); //21
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			root = btree_insert(root, node);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    root = btree_delete(root, middle);
		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		}

		sum_del = 0;
		del = 0;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
		    struct tree_node_t *node = node_create(middle);
		    root = btree_insert(root, node);

			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			root = btree_delete(root, middle);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_del = sum_del + del;
		}

		del = 0;
		sum_find = 0;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{

			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			lookup2(root, find_mid);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_find = sum_find + del;
		}
		printf("| %-20ld | Середина      | %-13f | %-14f |%-14f|\n", count, (double) (sum)/ N_REPS, (double) (sum_del)/ N_REPS, (double) (sum_find)/ N_REPS);

		printf("+----------------------+---------------+---------------+----------------+--------------+\n");
		del = 0, sum = 0;
		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
			struct tree_node_t *node = node_create(max);
			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			root = btree_insert(root, node);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    root = btree_delete(root, max); //200
		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum = sum + del;
		}

		sum_del = 0;
		del = 0;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{
		    struct tree_node_t *node = node_create(max);
		    root = btree_insert(root, node);

			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			root = btree_delete(root, max);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_del = sum_del + del;
		}

		del = 0;
		sum_find = 0;

		for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
		{

			clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
			lookup2(root, find_max);
		    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		    del = calc_elapsed_time(&t_beg, &t_end);
		    sum_find = sum_find + del;
		}

		printf("| %-20ld | Конец         | %-13f | %-14f |%-14f|\n", count, (double) (sum)/ N_REPS, (double) (sum_del)/ N_REPS, (double) (sum_find)/ N_REPS);
		printf("+----------------------+---------------+---------------+----------------+--------------+\n");
		post_order_apply(root, node_free, NULL);
	}
	return rc;
}