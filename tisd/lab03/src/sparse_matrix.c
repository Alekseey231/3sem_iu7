/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */


#include "../inc/sparse_matrix.h"

char set_sparse_matrix(matrix_t *matrix, matrix_t *vector, sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_vector)
{
	char rc = ERR_OK;
	rc = matrix_transform_to_sparse(vector, sparse_vector);
	if(rc == ERR_OK)
	{
		rc = matrix_transform_to_sparse(matrix, sparse_matrix);
	}
	return rc;
}

size_t calc_volume(sparse_matrix_t *sparse_matrix)
{
	size_t volume_values = sizeof(int) * sparse_matrix->count_elements;
	size_t volume_columns_index = sizeof(size_t) * sparse_matrix->count_elements;
	size_t volume_node = (sparse_matrix->rows_count+1) * sizeof(node_t);
	return volume_node + volume_values + volume_columns_index;
}

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)) / 1000; 
}


void check_transpose_sparse_matrix(sparse_matrix_t *sparse_matrix, sparse_matrix_t *t_sparse_matrix)
{
	matrix_t tmp;
	tmp.rows_count = sparse_matrix->columns_count;
	tmp.columns_count = sparse_matrix->rows_count;
	t_sparse_matrix->count_memory = sparse_matrix->count_memory;
	allocate_sparse_matrix(&tmp, t_sparse_matrix);

	//t_sparse_matrix->rows_count = sparse_matrix->columns_count;
	//t_sparse_matrix->columns_count = sparse_matrix->rows_count;
	t_sparse_matrix->count_elements = sparse_matrix->count_elements;
	t_sparse_matrix->head = init_node(0);

	//инициализуем связанный список нулями
	for(size_t i = 0; i < t_sparse_matrix->rows_count; ++i)
	{
		push_back(&(t_sparse_matrix->head), 0);
	}

	//считываем количество элеметов в каждом столбце и сохраняем 
	//printf("---- %ld\n", t_sparse_matrix->count_elements);
	for(size_t i = 0; i < t_sparse_matrix->count_elements; ++i)
	{
		size_t value = get_num_list(t_sparse_matrix->head, (sparse_matrix->column_index)[i]+1);
		set_node_list(t_sparse_matrix->head, (sparse_matrix->column_index)[i]+1, value+1);
	}


	size_t sum = 0;
	for(size_t i = 1; i < t_sparse_matrix->rows_count + 1; ++i)
	{
		size_t index = get_num_list(t_sparse_matrix->head, i);
		set_node_list(t_sparse_matrix->head, i, sum);
		sum+=index;
	}

	node_t *start_node = sparse_matrix->head;
	node_t *end_node = start_node->next;
	
	for(size_t i = 0; i < t_sparse_matrix->rows_count; ++i)
	{
		for(size_t j = start_node->index_start_row; end_node != NULL && j < end_node->index_start_row; ++j)
		{
			size_t index = get_num_list(t_sparse_matrix->head, (sparse_matrix->column_index)[j]+1);
			(t_sparse_matrix->values)[index] = (sparse_matrix->values)[j];
			(t_sparse_matrix->column_index)[index] = i;
			size_t val = get_num_list(t_sparse_matrix->head, sparse_matrix->column_index[j]+1);
			set_node_list(t_sparse_matrix->head, sparse_matrix->column_index[j]+1, val+1);
		}
		end_node = start_node;
		start_node = start_node -> next;
	}


}







void transpose_sparse_matrix(sparse_matrix_t *sparse_matrix, sparse_matrix_t *t_sparse_matrix)
{
	matrix_t tmp;
	tmp.rows_count = sparse_matrix->columns_count;
	tmp.columns_count = sparse_matrix->rows_count;
	t_sparse_matrix->count_memory = sparse_matrix->count_memory;
	allocate_sparse_matrix(&tmp, t_sparse_matrix);

	//t_sparse_matrix->rows_count = sparse_matrix->columns_count;
	//t_sparse_matrix->columns_count = sparse_matrix->rows_count;
	t_sparse_matrix->count_elements = sparse_matrix->count_elements;
	t_sparse_matrix->head = init_node(0);
	//print_sparse_format(sparse_matrix);
	//инициализуем связанный список нулями

	for(size_t i = 0; i < t_sparse_matrix->rows_count; ++i)
	{
		push_back(&(t_sparse_matrix->head), 0);

	}

	size_t *buf;
	allocate_mem((void *)(&buf), sizeof(size_t), t_sparse_matrix->rows_count + 1);
	//считываем количество элеметов в каждом столбце и сохраняем 
	//printf("---- %ld\n", t_sparse_matrix->count_elements);

	for(size_t i = 0; i < t_sparse_matrix->count_elements; ++i)
	{
		++buf[(sparse_matrix->column_index)[i]+1];
	}


	//print_sparse_format(t_sparse_matrix);


	/*node_t *sum_node = (t_sparse_matrix->head)->next;
	
	for(size_t i = 1; i < t_sparse_matrix->rows_count + 1; ++i)
	{
		size_t index = sum_node->index_start_row;
		sum_node->index_start_row = sum;
		sum+=index;
		sum_node = sum_node->next;
	}*/
	size_t sum = 0;
	for(size_t i = 1; i < t_sparse_matrix->rows_count + 1; ++i)
	{
		size_t index = buf[i];
		buf[i] = sum;
		sum+=index;
	}



	//print_sparse_format(t_sparse_matrix);

	node_t *start_node = sparse_matrix->head;
	node_t *end_node = start_node->next;

	//print_sparse_format(sparse_matrix);
	
	for(size_t i = 0; i < sparse_matrix->rows_count; ++i)
	{
		
		for(size_t j = start_node->index_start_row; end_node != NULL && j < end_node->index_start_row; ++j)
		{
			size_t index = buf[(sparse_matrix->column_index)[j]+1];
			(t_sparse_matrix->values)[index] = (sparse_matrix->values)[j];
			(t_sparse_matrix->column_index)[index] = i;
			++buf[(sparse_matrix->column_index)[j]+1];
			//printf("о ----- %ld\n", j);
			//size_t index = get_num_list(t_sparse_matrix->head, (sparse_matrix->column_index)[j]+1);
			/*node_t *ind = get_node_list(t_sparse_matrix->head, (sparse_matrix->column_index)[j]+1);
			(t_sparse_matrix->values)[ind->index_start_row] = (sparse_matrix->values)[j];
			(t_sparse_matrix->column_index)[ind->index_start_row] = i;
			ind->index_start_row += 1;*/
			//ind = ind -> next;
			//set_node_list(t_sparse_matrix->head, sparse_matrix->column_index[j]+1, index+1);
		}

		start_node = start_node -> next;
		end_node = end_node -> next;	
	}

	node_t *node_rows = t_sparse_matrix->head;
	for(size_t i = 0; node_rows != NULL && i < t_sparse_matrix->count_elements; ++i)
	{
		node_rows->index_start_row = buf[i];
		node_rows = node_rows->next;
	}

	free(buf);
	//print_sparse_format(t_sparse_matrix);


}



char matrix_sparse_mupltiplication(sparse_matrix_t *sparse_matrix_vector, sparse_matrix_t *sparse_matrix_right, sparse_matrix_t *sparse_matrix_result)
{
	char rc = ERR_OK;
	if(sparse_matrix_vector->columns_count != sparse_matrix_right->rows_count)
	{
		rc = ERR_INCORRECT_DIMENSION;
	}
	else
	{
		matrix_t tmp;
		tmp.rows_count = sparse_matrix_vector->rows_count;
		tmp.columns_count = sparse_matrix_right->columns_count;
		sparse_matrix_result->count_memory = sparse_matrix_right->columns_count;
		allocate_sparse_matrix(&tmp, sparse_matrix_result);
	//TODO count memory поменять
		//sparse_matrix_result->count_elements = sparse_matrix_vector->rows_count * sparse_matrix_right->columns_count;
		sparse_matrix_result->count_elements = 0;
		sparse_matrix_result->head = init_node(0);

		sparse_matrix_t *t_sparse_matrix = NULL;
		t_sparse_matrix = init_sparse_matrix();

		transpose_sparse_matrix(sparse_matrix_right, t_sparse_matrix);
		//print_sparse_matrix(t_sparse_matrix);
		//print_sparse_matrix(t_sparse_matrix);

		int *buf = NULL;
		rc = allocate_mem((void *)(&buf), sizeof(int), sparse_matrix_vector->columns_count);
		if(rc == ERR_OK)
		{
			// init -1
			for(size_t i = 0; i < sparse_matrix_vector->columns_count; ++i)
				buf[i] = -1;

			// IP
			//printf("%ld\n", sparse_matrix_vector->columns_count);
			for(size_t i = 0; i < sparse_matrix_vector->count_elements; ++i)
			{
				buf[(sparse_matrix_vector->column_index)[i]] = i;
				//printf("%d ", buf[(sparse_matrix_vector->column_index)[i]]);
			}

			//printf("Count %ld \n", t_sparse_matrix->rows_count);
			node_t *start_node = t_sparse_matrix->head;
			node_t *end_node = start_node->next;
			for(size_t i = 0; i < t_sparse_matrix->rows_count; ++i)
			{
				int sum = 0;
				for(size_t j = start_node->index_start_row; end_node != NULL && j < end_node->index_start_row; ++j)
				{
					if(buf[(t_sparse_matrix->column_index)[j]] != -1)
					{
						//printf("%d ", buf[(t_sparse_matrix->column_index)[j]]);
						//printf("%d\n", (t_sparse_matrix->values)[j]);
						//printf("%d ", (sparse_matrix_vector->values)[buf[(t_sparse_matrix->column_index)[j]]]);
						sum += (t_sparse_matrix->values)[j] * (sparse_matrix_vector->values)[buf[(t_sparse_matrix->column_index)[j]]];
					}
				}

				start_node = start_node -> next;
				end_node = end_node -> next;

				if(sum != 0)
				{
					(sparse_matrix_result->values)[(sparse_matrix_result->count_elements)] = sum;
					(sparse_matrix_result->column_index)[(sparse_matrix_result->count_elements)] = i;	
					++(sparse_matrix_result->count_elements);			
				}

				//printf("%d ", sum);
				//printf("%d\n", (sparse_matrix_result->values)[i]);
			}
			push_back(&(sparse_matrix_result->head), sparse_matrix_result->count_elements);
		}
		free(buf);
		
		free_sparse_matrix(t_sparse_matrix);
		if(sparse_matrix_result->count_elements == 0)
		{
			rc = ERR_ALL_ELEMENTS_ZERO_BY_MULT;
		}
	}
	return rc;
}


/*char matrix_sparse_multiplication(sparse_matrijx_t *sparse_matrix_vector, sparse_matrix_t *sparse_matrix_right, sparse_matrix_t *sparse_matrix_result)
{
	char rc = ERR_OK;

	init_sparse_matrix(sparse_matrix_result);
	//TODO не совпадение размерностей
	sparse_matrix_result->rows_count = sparse_matrix_vector->rows_count;
	sparse_matrix_result->columns_count = sparse_matrix_right->columns_count;
	
	int *buf = NULL;
	rc = allocate_mem((void *)(&buf), sizeof(int), sparse_matrix->columns_count);
	if(rc == ERR_OK)
	{
		// IP
		for(size_t j = get_num_list(sparse_matrix->head, i) ; j < get_num_list(sparse_matrix->head, i+1); ++j)
			buf[(sparse_matrix->column_index)[j]] = j+1;


		for(size_t column = 0; column < sparse_matrix->columns_count; ++column)
		{
			size_t *new_buf = NULL;
			rc = allocate_mem((void *)(&buf), sizeof(size_t), sparse_matrix->rows_count);
			size_t count_elements = 0;
			for(size_t i = 0; rc == ERR_OK && i < sparse_matrix->rows_count; ++i)
			{

				for(size_t j = get_num_list(sparse_matrix->head, i) ; j < get_num_list(sparse_matrix->head, i+1); ++j)
				{
					if((sparse_matrix->column_index)[j] == column)
					{
						new_buf[count_elements] = i;
						++count_elements;
					}
				}

			}


			}
		}






		}





	}

	free(buf);
	return rc;
}*/


char matrix_transform_to_sparse(matrix_t *matrix, sparse_matrix_t *sparse_matrix)
{
	char rc = ERR_OK;
	rc = allocate_sparse_matrix(matrix, sparse_matrix);

	sparse_matrix->head = init_node(0);
	//(sparse_matrix->index_start_row_values)[0] = 0;

	for(size_t i = 0; rc == ERR_OK && i < matrix->rows_count; ++i)
	{
		for(size_t j = 0; rc == ERR_OK && j < matrix->columns_count; ++j)
		{

			if(sparse_matrix->count_elements == sparse_matrix->count_memory)
			{
				rc = realloc_mem(sparse_matrix);
			}


			if(rc == ERR_OK && (matrix->data)[i][j] != 0)
			{
				(sparse_matrix->values)[sparse_matrix->count_elements] = (matrix->data)[i][j];
				(sparse_matrix->column_index)[sparse_matrix->count_elements] = j;
				++(sparse_matrix->count_elements);
			}
		}

		push_back(&(sparse_matrix->head), sparse_matrix->count_elements);
		//(sparse_matrix->index_start_row_values)
		//(sparse_matrix->index_start_row_values)[i+1] = sparse_matrix->count_elements;
	}

	if(sparse_matrix->count_elements == 0)
		rc = ERR_ALL_ELEMENTS_ZERO;
	return rc;
}

char realloc_mem(sparse_matrix_t *sparse_matrix)
{
	char rc = ERR_OK;
	sparse_matrix->count_memory = sparse_matrix->count_memory * 2;
	int* pbuf_values = realloc(sparse_matrix->values, sparse_matrix->count_memory * sizeof(int));
	size_t* pbuf_column_index = realloc(sparse_matrix->column_index, sparse_matrix->count_memory * sizeof(size_t));
	if(pbuf_values != NULL && pbuf_column_index != NULL)
	{
		sparse_matrix->values = pbuf_values;
		sparse_matrix->column_index = pbuf_column_index;
	}
	else
	{
		rc = ERR_ALLOCATE_MEM;
	}
	return rc;
}

sparse_matrix_t* init_sparse_matrix()
{
	char rc = ERR_OK;
	sparse_matrix_t *sparse_matrix;
	rc = allocate_mem((void *)(&sparse_matrix), sizeof(sparse_matrix_t), 1);
	if(rc == ERR_OK)
	{
		sparse_matrix->count_elements = 0;
		sparse_matrix->values = NULL;
		sparse_matrix->column_index = NULL;
		sparse_matrix->head = NULL;
		sparse_matrix->count_memory = START_COUNT_ELEMENTS;
	}
	return sparse_matrix;
}

/*void init_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
	sparse_matrix->count_elements = 0;
	sparse_matrix->values = NULL;
	sparse_matrix->column_index = NULL;
	sparse_matrix->head = NULL;
	sparse_matrix->count_memory = START_COUNT_ELEMENTS;
}*/


char allocate_sparse_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix)
{
	char rc = ERR_OK;

	//init_sparse_matrix(sparse_matrix);
	sparse_matrix->columns_count = matrix->columns_count;
	sparse_matrix->rows_count = matrix->rows_count;


	rc = allocate_mem((void *)(&sparse_matrix->values), sizeof(int), sparse_matrix->count_memory);
	if(rc == ERR_OK)
	{
		rc = allocate_mem((void *)(&sparse_matrix->column_index), sizeof(size_t), sparse_matrix->count_memory);
	}
	if(rc != ERR_OK)
	{
		free_sparse_matrix(sparse_matrix);
	}
	return rc;
}

void free_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
	if(sparse_matrix != NULL)
	{
		free(sparse_matrix->values);
		free(sparse_matrix->column_index);
		free_list(sparse_matrix->head);
		sparse_matrix->values = NULL;
		sparse_matrix->column_index = NULL;
		sparse_matrix->head = NULL;

		free(sparse_matrix);
		sparse_matrix = NULL;
	}
}

void reinit_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
	if(sparse_matrix != NULL)
	{
		free(sparse_matrix->values);
		free(sparse_matrix->column_index);
		free_list(sparse_matrix->head);
		sparse_matrix->count_elements = 0;
		sparse_matrix->values = NULL;
		sparse_matrix->column_index = NULL;
		sparse_matrix->head = NULL;
		sparse_matrix->count_memory = START_COUNT_ELEMENTS;
	}
}

void print_sparse_format(sparse_matrix_t *sparse_matrix)
{
	if(sparse_matrix->count_elements != 0)
	{
		printf("Матрица в разреженном формате\n");
		printf("Ненулевые значения: ");
		for(size_t i = 0; i < sparse_matrix->count_elements; ++i)
		{
			printf("%d ", (sparse_matrix->values)[i]);
		}
		printf("\n");
		printf("Индексы столбцов: ");
		for(size_t i = 0; i < sparse_matrix->count_elements; ++i)
		{
			printf("%ld ", (sparse_matrix->column_index)[i]);
		}
		printf("\n");

		printf("Индексы начала строк: ");
		/*for(size_t i = 0; i < sparse_matrix->rows_count + 1; ++i)
		{
			printf("%ld ", (sparse_matrix->index_start_row_values)[i]);
		}*/

		print_list(sparse_matrix->head);
		printf("Разреженная матрица стандартном формате:\n");
		for(size_t i = 0; i < sparse_matrix->rows_count; ++i)
		{
			for(size_t j = get_num_list(sparse_matrix->head, i) ; j < get_num_list(sparse_matrix->head, i+1); ++j)
			{
				printf("(%ld, %ld) - %d\n", i, (sparse_matrix->column_index)[j], sparse_matrix->values[j]);
			}
			//if((sparse_matrix->index_start_row_values)[i+1] != (sparse_matrix->index_start_row_values)[i])
			//	printf("%d ", (sparse_matrix->values)[i]);
		}
		printf("\n");
	}
	else
	{
		printf("Отсутствуют ненулевые элементы\n");
	}
}

char print_sparse_matrix(sparse_matrix_t *sparse_matrix)
{
	char rc = ERR_OK;
	if(sparse_matrix->count_elements == 0)
	{
		rc = ERR_ALL_ELEMENTS_ZERO;
	}
	for(size_t i = 0; rc == ERR_OK && i < sparse_matrix->rows_count; ++i)
	{
		int *buf = NULL;
		rc = allocate_mem((void *)(&buf), sizeof(int), sparse_matrix->rows_count + sparse_matrix->columns_count);

		for(size_t j = get_num_list(sparse_matrix->head, i) ; j < get_num_list(sparse_matrix->head, i+1); ++j)
			buf[(sparse_matrix->column_index)[j]] = j+1;

		for(size_t j = 0; rc == ERR_OK && j < sparse_matrix->columns_count; ++j)
		{
			if(buf[j] != 0)
				printf("%5d ", (sparse_matrix->values)[buf[j]-1]);
			else
				printf("%5d ", buf[j]);
		}
		free(buf);
		printf("\n");
	}
	return rc;
}