/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/list.h"
#include "../inc/io.h"
#include "../inc/hash_table.h"
#include "../inc/errors.h"
#include <math.h>
#define MAX_COUNT_COMPARE 3

void count_compare(node_t *node, void *num);

hash_table_t *init_hash_table(size_t size, size_t prime_num)
{
	hash_table_t *table = malloc(sizeof(hash_table_t));
	if(table != NULL)
	{
		table->content = calloc(size, sizeof(node_t*));
		if(table->content != NULL)
		{
			table->count_elements = 0;
			table->capacity = size;
			table->mod = prime_num;
			table->avarage_count_compare = 0;
			table->max_count_compare = 0;
			table->all_count_compare = 0;
		}
		else
		{
			free(table);
			table = NULL;
		}
	}
	return table;
}


//возможно лучше не пересоздавать ноды
char restruct_hash_table(hash_table_t *table, hash_table_t **new_table)
{
	char rc = ERR_OK;

	size_t prime_num = get_min_prime_large_num(table->capacity * 2);
	*new_table = init_hash_table(table->capacity * 2, prime_num);
	if(*new_table != NULL)
	{
		for(size_t i = 0; i < table->capacity; ++i)
		{
			node_t *head = (table->content)[i];
			while(head != NULL)
			{
				char is_restruct = 0;
				rc = hash_table_insert(new_table, head->num, 1, &is_restruct);
				head = head->next;
			}
		}
		free_hash_table(table);
	}
	else
	{
		rc = ERR_ALLOCATE_MEM;
	}
	return rc;
}

char find_hash_table(hash_table_t *table, int num, int *count_cmp)
{
	size_t index = hash_func(table, num);
	char is_find = list_find((table->content)[index], num, count_cmp);
	return is_find;
}

char resturct_after_create(hash_table_t **table, char *is_restruct)
{
	char rc = ERR_OK;
	if(is_restruct_needed(*table))
	{
		//printf("Выполняется реструктуризация\n");
		*is_restruct = 1;
		hash_table_t *tmp = NULL;
		rc = restruct_hash_table(*table, &tmp);
		if(rc == ERR_OK)
		{
			*table = tmp;
		}
		rc = resturct_after_create(table, is_restruct);
	}
	return rc;
}

char is_restruct_needed(hash_table_t *table)
{
	char is_needed = 0;

	int cur_count_compare = 0;
	unsigned int sum = 0;
	int max_count_compare = 0;

	for(size_t i = 0; i < table->capacity; ++i)
	{
		cur_count_compare = 0;
		list_apply((table->content)[i], count_compare, &cur_count_compare);
		if(cur_count_compare >= 1)
		{
			sum+=(1+cur_count_compare)*cur_count_compare/2;
		}
		if(cur_count_compare > max_count_compare)
		{
			max_count_compare = cur_count_compare;
		}
	}
	table->max_count_compare = max_count_compare;
	table->all_count_compare = sum;
	if(table->count_elements != 0)
	{
		table->avarage_count_compare = (float)sum/table->count_elements;
	}

	if(table->avarage_count_compare > MAX_COUNT_COMPARE)
	{
		is_needed = 1;
	}
	return is_needed;
}


char hash_table_insert(hash_table_t **table, int num, char is_creating, char *is_restruct)
{
	char rc = ERR_OK;
	size_t index = hash_func((*table), num);
	rc = list_add_front(((*table)->content)+index, num);
	if(rc == ERR_OK)
	{
		++((*table)->count_elements);
	}
	if(rc == ERR_OK && !is_creating)
	{
		int len_list = 0;
		list_apply(((*table)->content)[index], count_compare, &len_list);
		(*table)->all_count_compare += len_list;
		(*table)->avarage_count_compare = (float)((*table)->all_count_compare)/((*table)->count_elements);
		if((size_t)len_list > (*table)->max_count_compare)
		{
			(*table)->max_count_compare = len_list;
		}

		if((*table)->avarage_count_compare > MAX_COUNT_COMPARE)
		{
			rc = resturct_after_create(table, is_restruct);
			/*hash_table_t *tmp = NULL;
			*is_restruct = 1;
			rc = restruct_hash_table(*table, &tmp);
			if(rc == ERR_OK)
			{
				*table = tmp;
			}*/
		}
	}
	return rc;
}

char hash_table_delete(hash_table_t *table, int num)
{
	char rc = ERR_OK;
	size_t index = hash_func(table, num);


	//возможно есть способ оптимальнее...
	int len_old = 0;
	list_apply((table->content)[index], count_compare, &len_old);

	rc = list_delete_num((table->content)+index, num);
	if(rc == 1)
	{
		--(table->count_elements);
		(table->all_count_compare) = (table->all_count_compare) - len_old;

		if(table->count_elements != 0)
		{
			table->avarage_count_compare = (float)table->all_count_compare/table->count_elements;
		}
		else
		{
			table->all_count_compare = 0;
			table->avarage_count_compare = 0;
			table->max_count_compare = 0;
		}
	}
	return rc;
}

void count_compare(node_t *node, void *num)
{
	if(node != NULL)
	{
		int *n = num;
		++(*n);
	}
}


void print_hash_table(hash_table_t *table)
{
	for(size_t i = 0; i < table->capacity; ++i)
	{
		if(table->content + i != NULL)
		{
			printf("%ld:", i);
			list_apply(table->content[i], print_node, "%d ");
			printf("\n");
		}
	}
	printf("Размер таблицы: %ld\n", table->capacity);
	printf("Модуль хеш-функции: %ld\n", table->mod);
	printf("Среднее количество сравнений: %f\n", table->avarage_count_compare);
	printf("Максимальноe количество сравнений: %ld\n", table->max_count_compare);
	//printf("Общее количество сравнений: %ld\n", table->all_count_compare);
}

hash_table_t *create_hash_table(char *file_name)
{
	char rc = ERR_OK;
	hash_table_t *table = NULL;
	size_t count_nums = 0;
	rc = get_count_nums(file_name, &count_nums);
	if(rc == ERR_OK)
	{
		count_nums = ceil(count_nums*0.72/2.);
		size_t prime_num = get_min_prime_large_num(count_nums);
		if(prime_num != 0)
		{
			table = init_hash_table(count_nums, prime_num);
		}

		if(table != NULL)
		{
			rc = fill_hash_table(file_name, table);
			if(rc != ERR_OK)
			{
				table = NULL;
			}
		}
	}
	return table;
}

char fill_hash_table(char *file_name, hash_table_t *table)
{
	char rc = ERR_OK;
    FILE *f = fopen(file_name, "r");
    char is_restruct = 0;
    if (f == NULL)
    {
        rc = ERR_OPEN_FILE;
    }
    else
    {
        int num = 0;
        int count_num = 0;
        rc = get_num(f, &num);
        while (rc == ERR_OK)
        {
            ++count_num;
            rc = hash_table_insert(&table, num, 1, &is_restruct);
            
            if (rc == ERR_OK)
            {
                rc = get_num(f, &num);
            }

        }
        if (rc == ERR_OK_EOF)
            rc = ERR_OK;
        else if(rc != ERR_OK)
        {
           free_hash_table(table);
        }

        fclose(f);
    }
    return rc;
}

void free_hash_table(hash_table_t *table)
{
	for(size_t i = 0; i < table->capacity; ++i)
	{
		free_list(table->content + i);
	}
	free(table->content);
	free(table);
}



size_t hash_func(hash_table_t *table, int num)
{
	return (num % table->mod) % table->capacity;
}


size_t get_min_prime_large_num(size_t n)
{
	char is_prime = 0;
	while(!is_prime)
	{
		++n;
		is_prime = prime_factor(n);
	}
	return n;
}

char prime_factor(size_t n)
{
	char is_prime = 0;
	if(n == 2 || n == 3)
	{
		is_prime = 1;
	}	
	else if(n <= 1 || n%2==0 || n%3==0)
	{
		is_prime = 0;
	}
	else
	{
		for(size_t i = 5; i*i <= n && is_prime; i+=6)
		{
			if(n%i == 0 || n % (i+2) == 0)
			{
				is_prime = 0;
			}
		}
	}
	return is_prime;
}

size_t get_size_hash_table(hash_table_t *table)
{
	size_t size = 0;
	size += sizeof(hash_table_t);
	size += sizeof(node_t*)*table->capacity;
	for(size_t i = 0; i < table->capacity; ++i)
	{
		if((table->content)[i] != NULL)
		{
			int cur_count_compare = 0;
			list_apply((table->content)[i], count_compare, &cur_count_compare);
			size += cur_count_compare * sizeof(node_t);
		}
	}
	size += sizeof(hash_table_t *);
	return size;
}

/*char is_restruct_needed(hash_table_t *table)
{
	char is_needed = 0;

	int cur_count_compare = 0;
	int max_count_compare = 0;

	for(size_t i = 0; i < table->capacity; ++i)
	{
		cur_count_compare = 0;
		list_apply((table->content)[i], count_compare, &cur_count_compare);
		if(cur_count_compare > max_count_compare)
		{
			max_count_compare = cur_count_compare;
		}
	}
	if(max_count_compare > MAX_COUNT_COMPARE)
	{
		is_needed = 1;
	}
	return is_needed;
}*/