/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <math.h>
#include "../inc/hash_table.h"
#include "../inc/io.h"
#include "../inc/errors.h"
#include "../inc/closed_table.h"

#define STATUS_EMPTY 0
#define STATUS_DELETED -1
#define STATUS_BUSY 1

#define MAX_COUNT_COMPARE 5

closed_table_t *init_closed_table(size_t size, size_t prime_num)
{
	closed_table_t *table = malloc(sizeof(closed_table_t));
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


closed_table_t *create_closed_table(char *file_name)
{
	char rc = ERR_OK;
	closed_table_t *table = NULL;
	size_t count_nums = 0;
	rc = get_count_nums(file_name, &count_nums);
	if(rc == ERR_OK)
	{
		count_nums = ceil(count_nums*1.2);
		size_t prime_num = get_min_prime_large_num(count_nums);
		if(prime_num != 0)
		{
			table = init_closed_table(count_nums, prime_num);
		}

		if(table != NULL)
		{
			rc = fill_closed_table(file_name, table);
			if(rc != ERR_OK)
			{
				table = NULL;
			}
		}
	}
	return table;
}

char fill_closed_table(char *file_name, closed_table_t *table)
{
	char rc = ERR_OK;
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        rc = ERR_OPEN_FILE;
    }
    else
    {
    	char is_restruct = 0;
        int num = 0;
        int count_num = 0;
        rc = get_num(f, &num);
        while (rc == ERR_OK)
        {
            ++count_num;
            rc = closed_table_insert(&table, num, 1, &is_restruct);
            
            if (rc == ERR_OK)
            {
                rc = get_num(f, &num);
            }

        }
        if (rc == ERR_OK_EOF)
            rc = ERR_OK;
        else if(rc != ERR_OK)
        {
           free_closed_table(table);
        }

        fclose(f);
    }
    return rc;
}

void free_closed_table(closed_table_t *table)
{
	free(table->content);
	free(table);
}

char resturct_after_create_closed(closed_table_t **table, char *is_restruct)
{
	char rc = ERR_OK;
	if(is_restruct_needed_closed(*table))
	{
		//printf("Выполняется реструктуризация\n");
		printf("%f\n", (*table)->avarage_count_compare);
		*is_restruct = 1;
		closed_table_t *tmp = NULL;
		rc = restruct_closed_table(*table, &tmp);
		if(rc == ERR_OK)
		{
			*table = tmp;
		}
		rc = resturct_after_create_closed(table, is_restruct);
	}
	return rc;
}


char closed_table_insert(closed_table_t **table, int num, char is_creating, char *is_restruct)
{
	char rc = ERR_OK;
	size_t index = closed_func((*table), num);

	//printf("%d\n", (((*table)->content)[index]).status == STATUS_EMPTY);
	while(!((((*table)->content)[index]).status == STATUS_EMPTY || (((*table)->content)[index]).status == STATUS_DELETED))
	{
		++index;
		index %= (*table)->capacity;
	}
	//printf("2");
	if(((*table)->content)[index].status == STATUS_EMPTY || ((*table)->content)[index].status == STATUS_DELETED)
	{
		((*table)->content)[index].status = STATUS_BUSY;
		((*table)->content)[index].num = num;
		++((*table)->count_elements);
	}

	if(!is_creating)
	{
		int cur_count_compare = 0;

		cls_cell_t tmp = ((*table)->content)[index];

		closed_table_find(*table, tmp.num, &cur_count_compare);

		if(cur_count_compare >= 1)
		{
			(*table)->all_count_compare += cur_count_compare;
		}

		if((size_t)cur_count_compare > (*table)->max_count_compare)
		{
			(*table)->max_count_compare = cur_count_compare;
		}

		(*table)->avarage_count_compare = (float)((*table)->all_count_compare)/((*table)->count_elements);

		if((*table)->count_elements == (*table)->capacity || (*table)->avarage_count_compare > MAX_COUNT_COMPARE)
		{
			// можно сразу вызывать подфункцию, что бы лишний раз не проврять
			rc = resturct_after_create_closed(table, is_restruct);
		}


	}

	return rc;
}


char restruct_closed_table(closed_table_t *table, closed_table_t **new_table)
{
	char rc = ERR_OK;
	printf("%ld\n", table->capacity);
	size_t prime_num = get_min_prime_large_num(table->capacity * 2);
	*new_table = init_closed_table(table->capacity * 2, prime_num);
	if(*new_table != NULL)
	{
		for(size_t i = 0; i < table->capacity; ++i)
		{
			char is_restruct = 0;
			rc = closed_table_insert(new_table, ((table->content)[i]).num, 1, &is_restruct);

		}
		free_closed_table(table);
	}
	else
	{
		rc = ERR_ALLOCATE_MEM;
	}
	return rc;
}


char is_restruct_needed_closed(closed_table_t *table)
{
	if(table->count_elements == table->capacity)
		return 1;
	
	char is_needed = 0;

	int cur_count_compare = 0;
	int sum = 0;
	int max_count_compare = 0;

	for(size_t i = 0; i < table->capacity; ++i)
	{
		cur_count_compare = 0;

		cls_cell_t tmp = (table->content)[i];
		if(tmp.status == STATUS_BUSY)
		{
			closed_table_find(table, tmp.num, &cur_count_compare);
			if(cur_count_compare >= 1)
			{
				sum+=cur_count_compare;
			}
			if(cur_count_compare > max_count_compare)
			{
				max_count_compare = cur_count_compare;
			}
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


char closed_table_delete(closed_table_t *table, int num)
{
	size_t index = closed_func(table, num);

	char is_deleted = 0;
	char is_stop = 0;

	int all_count_compare = 0;

	size_t saved_index = index;

	while((table->content)[index].status != STATUS_EMPTY && !is_deleted && !is_stop)
	{
		++all_count_compare;
		if((table->content)[index].num == num)
		{
			(table->content)[index].status = STATUS_DELETED;
			
			is_deleted = 1;

			--(table->count_elements);
			(table->all_count_compare) -= all_count_compare;

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
		else
		{
			++index;
			index %= table->capacity;
		}
		if(saved_index == index)
		{
			is_stop = 1;
		}
	}

	return is_deleted;
}


char closed_table_find(closed_table_t *table, int num, int *count_cmp)
{
	size_t index = closed_func(table, num);

	char is_find = 0;
	char is_stop = 0;

	int count = 0;

	size_t saved_index = index;

	while((table->content)[index].status != STATUS_EMPTY && !is_find && !is_stop)
	{
		if((table->content)[index].num == num)
		{
			is_find = 1;
		}
		else
		{
			++index;
			index %= table->capacity;
		}
		if(saved_index == index)
		{
			is_stop = 1;
		}
		++count;
	}
	*count_cmp = count;

	return is_find;
}


size_t closed_func(closed_table_t *table, int num)
{
	return (num % table->mod) % table->capacity;
}

void print_closed_table(closed_table_t *table)
{
	for(size_t i = 0; i < table->capacity; ++i)
	{
		printf("%ld : ", i);
		if(((table->content)[i]).status == STATUS_EMPTY || ((table->content)[i]).status == STATUS_DELETED)
		{
			printf(" \n");
		}
		else
		{
			printf("%d\n", ((table->content)[i]).num);
		}
	}
	printf("Размер таблицы: %ld\n", table->capacity);
	printf("Модуль хеш-функции: %ld\n", table->mod);
	printf("Среднее количество сравнений: %f\n", table->avarage_count_compare);
	printf("Максимальноe количество сравнений: %ld\n", table->max_count_compare);
}

size_t get_size_closed_table(closed_table_t *table)
{
	size_t size = 0;
	size += sizeof(closed_table_t);
	size += sizeof(closed_table_t *);
	size += sizeof(cls_cell_t) * table->capacity;
	return size;
}