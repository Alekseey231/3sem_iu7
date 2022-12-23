#ifndef __SPARSE_MATRIX_H__

#define __SPARSE_MATRIX_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../inc/errors.h"
#include "../inc/linked_list.h"
#include "../inc/matrix.h"

#define START_COUNT_ELEMENTS 10


typedef struct
{
	size_t rows_count;
	size_t columns_count;
	size_t count_elements;

	size_t count_memory;

	int *values;
	size_t *column_index;
	node_t *head;
	
} sparse_matrix_t;


//void init_sparse_matrix(sparse_matrix_t *sparse_matrix);
sparse_matrix_t* init_sparse_matrix();
char allocate_sparse_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix);
void free_sparse_matrix(sparse_matrix_t *sparse_matrix);
void print_sparse_format(sparse_matrix_t *sparse_matrix);
char matrix_transform_to_sparse(matrix_t *matrix, sparse_matrix_t *sparse_matrix);
char print_sparse_matrix(sparse_matrix_t *sparse_matrix);
char realloc_mem(sparse_matrix_t *sparse_matrix);
void transpose_sparse_matrix(sparse_matrix_t *sparse_matrix, sparse_matrix_t *t_sparse_matrix);
char matrix_sparse_mupltiplication(sparse_matrix_t *sparse_matrix_vector, sparse_matrix_t *sparse_matrix_right, sparse_matrix_t *sparse_matrix_result);
void clean_stdin(void);
void reinit_sparse_matrix(sparse_matrix_t *sparse_matrix);
void time_transpose_sparse_matrix(sparse_matrix_t *sparse_matrix, sparse_matrix_t *t_sparse_matrix);
unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end);
size_t calc_volume(sparse_matrix_t *sparse_matrix);
char set_sparse_matrix(matrix_t *matrix, matrix_t *vector, sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_vector);
char get_matrix(FILE *f, int choice, matrix_t *matrix, matrix_t *vector);
char get_matrix_coordinate(FILE *f, int choice, matrix_t *matrix, matrix_t *vector);
void check_transpose_sparse_matrix(sparse_matrix_t *sparse_matrix, sparse_matrix_t *t_sparse_matrix);

#endif //#ifndef __SPARSE_MATRIX_H__



