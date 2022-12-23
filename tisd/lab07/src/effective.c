/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/effective.h"
#include "../inc/tree.h"
#include "../inc/tree_node.h"
#include "../inc/io.h"
#include "../inc/hash_table.h"
#include "../inc/closed_table.h"
#define _GNU_SOURCE_

#define MAX_COUNT 100000
#define N_REPS 100

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)); 
}

//поиск в правостороннем дереве
//поиск в обычном дереве
//в середине и в конце
//1000, 10000
void effective_collision(char *file_name, int num, int count);

size_t get_size_hash(char *file_name);
size_t get_size_closed(char *file_name);
size_t get_size_tree(char *file_name);
void get_size_all(char *file_name, int count);
size_t get_size_tree_bal(char *file_name);

void effective()
{
	effective_find();
}

void effective_find()
{
	printf("Время поиска элемента при отсортированной последовательности чисел:\n");
	printf("| Количество элементов | Место    | Дерево поиска | АВЛ дерево | Хеш-таблица(метод цепочек) | Хеш-таблица(открытая адресация) |\n");
	printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");
	effective_all_find("test_right_tree_1000.txt", 4557, 1000, "Середина");
	printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");
	effective_all_find("test_right_tree_1000.txt", 9989, 1000, "Конец   ");
	printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");
	effective_all_find("test_right_tree_10000.txt", -880, 10000, "Середина");
	printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");
	effective_all_find("test_right_tree_10000.txt", 99984, 10000, "Конец   ");
	printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");

	printf("\n");

	printf("Размеры структур данных: :\n");
	printf("| Количество элементов | Размер хеш таблцицы(метод цепочек) | Размер хеш таблицы(открытая адресация) | Размер ДДП | Размер АВЛ |\n");
	printf("+----------------------+------------------------------------+----------------------------------------+------------+------------+\n");
	get_size_all("test_right_tree_1000.txt", 1000);
	printf("+----------------------+------------------------------------+----------------------------------------+------------+------------+\n");
	get_size_all("test_right_tree_10000.txt", 10000);
	printf("+----------------------+------------------------------------+----------------------------------------+------------+------------+\n");

	printf("\n");

	printf("Время поиска элемента при произвольной последовательности чисел:\n");
	printf("| Количество элементов | Место    | Дерево поиска | АВЛ дерево | Хеш-таблица(метод цепочек) | Хеш-таблица(открытая адресация) |\n");
	printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");
	effective_all_find("any_tree_100.txt", -806, 100, "        ");
	printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");
	effective_all_find("any_tree_1000.txt", -22995, 1000, "        ");
	printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");

	printf("\n");

	printf("Размеры структур данных: :\n");
	printf("| Количество элементов | Размер хеш таблцицы(метод цепочек) | Размер хеш таблицы(открытая адресация) | Размер ДДП | Размер АВЛ |\n");
	printf("+----------------------+------------------------------------+----------------------------------------+------------+------------+\n");
	get_size_all("any_tree_100.txt", 100);
	printf("+----------------------+------------------------------------+----------------------------------------+------------+------------+\n");
	get_size_all("any_tree_1000.txt", 1000);
	printf("+----------------------+------------------------------------+----------------------------------------+------------+------------+\n");

	//effective_all_find("test_right_tree_100000.txt", -49, 100000, "Середина");
	//printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");
	//effective_all_find("test_right_tree_100000.txt", 99999, 100000, "Конец   ");
	//printf("+----------------------+----------+---------------+------------+----------------------------+---------------------------------+\n");

	printf("\n");

	printf("Время поиска в реструктуризированной таблице :\n");
	printf("| Количество элементов | Время в исходной | Время в реструктуризированной |\n");

	effective_hash_find("test_right_tree_100000.txt", -77079, 100000);
	effective_hash_find("test_right_tree_100000.txt", -63563, 100000);

	printf("Время поиска в таблице с коллизияими :\n");
	printf("| Количество элементов | Время(метод цепочек) | Время(открытая адресация) |\n");

	effective_collision("collision.txt", 35, 6);

	effective_collision("test_right_tree_100000.txt", 65178, 100000);

	effective_collision("test_right_tree_100000.txt", -99988, 100000);

	//get_size_all("test_right_tree_100000.txt", 10000);
	//effective_hash_find("test_right_tree_1000000.txt", -8561, 1000000);
}



void effective_all_find(char *file_name, int num, int count, char *s)
{
	// 1. В правостороннем 4557 - середина

	double sum1 = effective_find_not_balanced(file_name, num);
	double sum2 = effective_find_balanced(file_name, num);
	double sum3 = effective_find_hash(file_name, num);
	double sum4 = effective_find_closed(file_name, num);

	printf("| %-20d | %-8s | %-13f | %-10f | %-26f | %-31f |\n", count, s, sum1, sum2, sum3, sum4);
}

void effective_collision(char *file_name, int num, int count)
{
	
	double sum1 = effective_find_hash_not_restruct(file_name, num);
	double sum2 = effective_find_closed_not_restruct(file_name, num);
	printf("| %-20d | %-20f | %-25f |\n", count, sum1, sum2);
}

void effective_hash_find(char *file_name, int num, int count)
{
	
	double sum1 = effective_find_hash(file_name, num);
	double sum2 = effective_find_hash_not_restruct(file_name, num);
	printf("| %-20d | %-16f | %-29f |\n", count, sum2, sum1);
}

double effective_find_not_balanced(char *file_name, int num)
{
	struct tree_node_t *root = NULL;
	unsigned long long del, sum = 0;
	struct timespec t_beg, t_end;

	del = 0;
	sum = 0;
	get_all_nums_not_balanced(file_name, &root);
	for (int i = 0; i < N_REPS; i++)
	{
		int count_cmp = 0;
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
		lookup2(root, num, &count_cmp);
	    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

	    del = calc_elapsed_time(&t_beg, &t_end);
	    sum = sum + del;
	}

	post_order_apply(root, node_free, NULL);

	return (double) (sum)/ N_REPS;
}

double effective_find_balanced(char *file_name, int num)
{

	struct tree_node_t *root = NULL;
	unsigned long long del, sum = 0;
	struct timespec t_beg, t_end;

	del = 0;
	sum = 0;
	get_all_nums(file_name, &root);
	for (int i = 0; i < N_REPS; i++)
	{
		int count_cmp = 0;
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
		lookup2(root, num, &count_cmp);
	    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

	    del = calc_elapsed_time(&t_beg, &t_end);
	    sum = sum + del;
	}

	post_order_apply(root, node_free, NULL);

	return (double) (sum)/ N_REPS;
}

double effective_find_hash(char *file_name, int num)
{
	char is_restruct = 0;

	hash_table_t *table = create_hash_table(file_name);
	resturct_after_create(&table, &is_restruct);
	
	unsigned long long del, sum = 0;
	struct timespec t_beg, t_end;

	del = 0;
	sum = 0;

	for (int k = 0; k < N_REPS; k++)
	{
		int count_cmp = 0;
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
		find_hash_table(table, num, &count_cmp);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		del = calc_elapsed_time(&t_beg, &t_end);
		sum = sum + del;
	}
	free_hash_table(table);

	return (double) (sum)/ N_REPS;
}

double effective_find_closed(char *file_name, int num)
{
	char is_restruct = 0;

	closed_table_t *table = create_closed_table(file_name);
	resturct_after_create_closed(&table, &is_restruct);
	
	unsigned long long del, sum = 0;
	struct timespec t_beg, t_end;

	del = 0;
	sum = 0;

	for (int k = 0; k < N_REPS; k++)
	{
		int count_cmp = 0;
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
		closed_table_find(table, num, &count_cmp);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		del = calc_elapsed_time(&t_beg, &t_end);
		sum = sum + del;
	}
	free_closed_table(table);
	
	return (double) (sum)/ N_REPS;
}

double effective_find_hash_not_restruct(char *file_name, int num)
{

	hash_table_t *table = create_hash_table(file_name);
	unsigned long long del, sum = 0;
	struct timespec t_beg, t_end;
	//is_restruct_needed(table);
	//printf("hash - %ld %f\n", table->max_count_compare, table->avarage_count_compare);

	del = 0;
	sum = 0;

	for (int k = 0; k < N_REPS; k++)
	{
		int count_cmp = 0;
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
		find_hash_table(table, num, &count_cmp);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		del = calc_elapsed_time(&t_beg, &t_end);
		sum = sum + del;
	}
	free_hash_table(table);

	return (double) (sum)/ N_REPS;
}

double effective_find_closed_not_restruct(char *file_name, int num)
{

	closed_table_t *table = create_closed_table(file_name);

	unsigned long long del, sum = 0;
	struct timespec t_beg, t_end;
	//is_restruct_needed_closed(table);
	//printf("Closed - %ld %f\n", table->max_count_compare, table->avarage_count_compare);

	del = 0;
	sum = 0;

	for (int k = 0; k < N_REPS; k++)
	{
		int count_cmp = 0;
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
		closed_table_find(table, num, &count_cmp);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		del = calc_elapsed_time(&t_beg, &t_end);
		sum = sum + del;
	}
	free_closed_table(table);
	
	return (double) (sum)/ N_REPS;
}


double effective_find_hash_restruct(char *file_name, int num)
{	
	unsigned long long del, sum = 0;
	struct timespec t_beg, t_end;

	del = 0;
	sum = 0;

	for (int k = 0; k < N_REPS; k++)
	{
		char is_restruct = 0;

		hash_table_t *table = create_hash_table(file_name);

		int count_cmp = 0;
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

		resturct_after_create(&table, &is_restruct);
		find_hash_table(table, num, &count_cmp);

		clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

		del = calc_elapsed_time(&t_beg, &t_end);
		sum = sum + del;

		free_hash_table(table);
	}
	
	return (double) (sum)/ N_REPS;
}

// для замеров размеров

size_t get_size_hash(char *file_name)
{
	char is_restruct = 0;

	hash_table_t *table = create_hash_table(file_name);
	resturct_after_create(&table, &is_restruct);

	size_t size = get_size_hash_table(table);

	free_hash_table(table);

	return size;
}

size_t get_size_closed(char *file_name)
{
	char is_restruct = 0;

	closed_table_t *table = create_closed_table(file_name);
	resturct_after_create_closed(&table, &is_restruct);

	size_t size = get_size_closed_table(table);

	free_closed_table(table);

	return size;
}

size_t get_size_tree(char *file_name)
{
	struct tree_node_t *root = NULL;

	get_all_nums(file_name, &root);
	
	size_t size = get_size_tree_bin(root);

	post_order_apply(root, node_free, NULL);

	return size;
}

size_t get_size_tree_bal(char *file_name)
{
	struct tree_node_t *root = NULL;

	get_all_nums(file_name, &root);
	
	size_t size = get_size_tree_balanced(root);

	post_order_apply(root, node_free, NULL);

	return size;
}

void get_size_all(char *file_name, int count)
{
	size_t size1 = get_size_hash(file_name);
	size_t size2 = get_size_closed(file_name);
	size_t size3 = get_size_tree(file_name);
	size_t size4 = get_size_tree_bal(file_name);

	printf("| %-20d | %-34ld | %-38ld | %-10ld | %-10ld |\n", count, size1, size2, size3, size4);
}