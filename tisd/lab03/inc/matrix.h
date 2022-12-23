#ifndef __MATRIX_H__

#define __MATRIX_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../inc/errors.h"

#define CONSOLE_INPUT 2
#define FILE_INPUT 1
#define WIDTH_NUM 5

typedef struct
{
	size_t rows_count;
	size_t columns_count;
	int **data;
} matrix_t;


void init_matrix(matrix_t *matrix);

char allocate_mem(void **dst, size_t size, size_t elements_count);
char allocate_matrix(matrix_t *matrix);
void free_matrix(matrix_t *matrix);

char input_matrix_coordinate(FILE *f, int choice, matrix_t *matrix);
char input_matrix_content_coordinate(FILE *f, int choice, matrix_t *matrix);
char input_matrix_dimension(FILE *f, int choice, matrix_t *matrix);
char input_matrix_content(FILE *f, int choice, matrix_t *matrix);
char input_num(FILE *f, int *num, char rc);
char input_matrix(FILE *f, int choice, matrix_t *matrix);
void print_matrix(matrix_t *matrix);
void generate_matrix(matrix_t *matrix, double percent_density);
char generate_matrix_random(matrix_t *matrix, matrix_t *vector);
void clean_stdin(void);


char clear_matrix_multiplication(matrix_t *matrix_left, matrix_t *matrix_right, matrix_t *matrix_result);
char matrix_multiplication(matrix_t *matrix_left, matrix_t *matrix_right, matrix_t *matrix_result);
char transponse_matrix(matrix_t *matrix);
void transponse(matrix_t *matrix, matrix_t *tmp_matrix);

#endif //#ifndef __MATRIX_H__
