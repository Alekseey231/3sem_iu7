/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

//В замерах эффективности пренебрегал принципами декомпозиции и проверками успешности выделения памяти :/
#include "../inc/effective.h"

char get_effective(void)
{
	char rc = ERR_OK;
	
	matrix_t vector; 	
	init_matrix(&vector);
	vector.rows_count = 1;
	vector.columns_count = 50000;

	rc = allocate_matrix(&vector);

	matrix_t matrix;
	init_matrix(&matrix);
	matrix.rows_count = 50000;
	matrix.columns_count = 50000;	

	if(rc == ERR_OK)
		rc = allocate_matrix(&matrix);

	matrix_t matrix_result;
	init_matrix(&matrix_result);
	matrix_result.rows_count = vector.rows_count;
	matrix_result.columns_count = matrix.columns_count;

	sparse_matrix_t *sparse_matrix = NULL, *sparse_vector = NULL, *sparse_result = NULL;

	sparse_matrix = init_sparse_matrix();
	sparse_vector = init_sparse_matrix();
	sparse_result = init_sparse_matrix();

	if(rc == ERR_OK)
	{
		double percent_density = 0;
		for(size_t j = 10; rc == ERR_OK && j <= 15; j=j+5)
		{
			struct timespec t_beg, t_end;

			unsigned long long del, sum = 0;

			percent_density = (double)j / 100;

			reinit_sparse_matrix(sparse_matrix);
			reinit_sparse_matrix(sparse_vector);
			reinit_sparse_matrix(sparse_result);
			free_matrix(&matrix);
			free_matrix(&vector);
			free_matrix(&matrix_result);

			rc = allocate_matrix(&vector);
			rc = allocate_matrix(&matrix);

			generate_matrix(&vector, percent_density);
			generate_matrix(&matrix, percent_density);

			rc = set_sparse_matrix(&matrix, &vector, sparse_matrix, sparse_vector);

			srand(time(NULL));

			for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
			{
				reinit_sparse_matrix(sparse_result);

				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

			    rc = matrix_sparse_mupltiplication(sparse_vector, sparse_matrix, sparse_result);

			    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
			    
			    del = calc_elapsed_time(&t_beg, &t_end);

			    sum = sum + del;
			}

			printf("Заполненость: %ld; Время(умножние разреженных) %f ", j*1, (double) (sum)/ N_REPS);

			del = 0, sum = 0;

			sparse_matrix_t *t_sparse_matrix = NULL;

			srand(time(NULL));

			for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
			{
				t_sparse_matrix = init_sparse_matrix();

				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

				transpose_sparse_matrix(sparse_matrix, t_sparse_matrix);

			    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
			    
			    del = calc_elapsed_time(&t_beg, &t_end);

			    sum = sum + del;

			    free_sparse_matrix(t_sparse_matrix);
			}

			printf("Время транспонирования %f ", (double) (sum)/ N_REPS);

			del = 0, sum = 0;

			srand(time(NULL));

			for (int i = 0; rc == ERR_OK && i < N_REPS; i++)
			{
				free_matrix(&matrix_result);

				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

				rc = clear_matrix_multiplication(&vector, &matrix, &matrix_result);

			    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
			    
			    del = calc_elapsed_time(&t_beg, &t_end);

			    sum = sum + del;
			}

			printf("Время(умножение стандартных) %f\n", (double) (sum)/ N_REPS);


			del = 0, sum = 0;

			srand(time(NULL));

			printf("Объем памяти(стандартный): %ld |", matrix.rows_count * matrix.columns_count * sizeof(int));
			printf("Объем памяти(сжатый): %ld \n\n", calc_volume(sparse_matrix));
		
			
		}

	}

	
	free_sparse_matrix(sparse_matrix);
	free_sparse_matrix(sparse_vector);
	free_sparse_matrix(sparse_result);

	free_matrix(&matrix);
	free_matrix(&vector);
	free_matrix(&matrix_result);
	return rc;
}


char t_matrix_sparse_mupltiplication(sparse_matrix_t *sparse_matrix_vector, sparse_matrix_t *t_sparse_matrix, sparse_matrix_t *sparse_matrix_result)
{
	char rc = ERR_OK;
	matrix_t tmp;
	tmp.rows_count = sparse_matrix_vector->rows_count;
	tmp.columns_count = t_sparse_matrix->columns_count;
	sparse_matrix_result->count_memory = t_sparse_matrix->columns_count;
	allocate_sparse_matrix(&tmp, sparse_matrix_result);
//TODO count memory поменять
	//sparse_matrix_result->count_elements = sparse_matrix_vector->rows_count * sparse_matrix_right->columns_count;
	sparse_matrix_result->count_elements = 0;
	sparse_matrix_result->head = init_node(0);

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
		for(size_t i = 0; i < t_sparse_matrix->rows_count; ++i)
		{
			int sum = 0;
			for(size_t j = get_num_list(t_sparse_matrix->head, i) ; j < get_num_list(t_sparse_matrix->head, i+1); ++j)
			{
				if(buf[(t_sparse_matrix->column_index)[j]] != -1)
				{
					//printf("%d ", buf[(t_sparse_matrix->column_index)[j]]);
					//printf("%d\n", (t_sparse_matrix->values)[j]);
					//printf("%d ", (sparse_matrix_vector->values)[buf[(t_sparse_matrix->column_index)[j]]]);
					sum += (t_sparse_matrix->values)[j] * (sparse_matrix_vector->values)[buf[(t_sparse_matrix->column_index)[j]]];
				}
			}

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
	return rc;
}