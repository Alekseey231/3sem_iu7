/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */


#include "../inc/matrix.h"

#define MAX_GENERATE_NUM 10

char get_matrix(FILE *f, int choice, matrix_t *matrix, matrix_t *vector)
{
	char rc = ERR_OK;
	if(choice == 2)
	{
		choice = CONSOLE_INPUT;
	}
	if(choice == CONSOLE_INPUT)
		printf("Ввод вектора:\n");
	rc = input_matrix(f, choice, vector);
	if(rc == ERR_OK)
	{
		if(vector->rows_count != 1)
		{
			rc = ERR_IS_NOT_VECTOR;
		}
		if(rc == ERR_OK)
		{
			if(choice == CONSOLE_INPUT)
				printf("Ввод матрицы:\n");
			rc = input_matrix(f, choice, matrix);
			if(rc == ERR_OK && matrix->rows_count != vector->columns_count)
			{
				rc = ERR_DIMENSION_NOT_EQUAL;
			}
		}

	}
	return rc;
}


char get_matrix_coordinate(FILE *f, int choice, matrix_t *matrix, matrix_t *vector)
{
	char rc = ERR_OK;
	if(choice == 2)
	{
		choice = CONSOLE_INPUT;
	}
	if(choice == CONSOLE_INPUT)
		printf("Ввод вектора:\n");
	rc = input_matrix_coordinate(f, choice, vector);
	if(rc == ERR_OK)
	{
		if(vector->rows_count != 1)
		{
			rc = ERR_IS_NOT_VECTOR;
		}
		if(rc == ERR_OK)
		{
			if(choice == CONSOLE_INPUT)
				printf("Ввод матрицы:\n");
			rc = input_matrix_coordinate(f, choice, matrix);
			if(rc == ERR_OK && matrix->rows_count != vector->columns_count)
			{
				rc = ERR_DIMENSION_NOT_EQUAL;
			}
		}

	}
	return rc;
	
}

char generate_matrix_random(matrix_t *matrix, matrix_t *vector)
{
	char rc = ERR_OK;
	printf("Ввод вектора:\n");
	rc = input_matrix_dimension(stdin, CONSOLE_INPUT, vector);
	clean_stdin();
	if(rc == ERR_OK && vector->rows_count != 1)
	{
		rc = ERR_IS_NOT_VECTOR;
	}
	
	if(rc == ERR_OK)
	{
		printf("Ввод матрицы:\n");
		rc = input_matrix_dimension(stdin, CONSOLE_INPUT, matrix);
		clean_stdin();
	}
	if(rc == ERR_OK && vector->columns_count != matrix->rows_count)
	{
		rc = ERR_DIMENSION_NOT_EQUAL;
	}
	if(rc == ERR_OK)
	{
		rc = allocate_matrix(matrix);
		if(rc == ERR_OK)
		{
			rc = allocate_matrix(vector);
		}
	}
	if(rc == ERR_OK)
	{
		srand(time(NULL));
		double percent_density = 0;
		printf("Введите процент заполненности матрицы\n");
		if(scanf("%lf", &percent_density) == 1 && percent_density > 0 && percent_density <= 1)
		{
			generate_matrix(vector, percent_density);
			generate_matrix(matrix, percent_density);	
		}
		else
		{
			rc = ERR_INCORRECT_PERCENT_DENSITY;
		}


	}

	return rc;
}


void generate_matrix(matrix_t *matrix, double percent_density)
{
	if(percent_density <= 1)
	{
		size_t count_num = 0;
		size_t dimension = (matrix->rows_count) * (matrix->columns_count);
		int num = 0;
		srand(time(NULL));
		size_t i = 0, j = 0;
		while((double)(count_num)/dimension < percent_density)
		{
			i = (size_t) ((matrix->rows_count) * ((double) rand() / (RAND_MAX + 1.0))); 
			j = (size_t) ((matrix->columns_count) * ((double) rand() / (RAND_MAX + 1.0))); 
			if((matrix->data)[i][j] == 0)
			{
				num = (int) (MAX_GENERATE_NUM * ((double) rand() / (RAND_MAX + 1.0)));
				if(num != 0)
				{
					++count_num;
					(matrix->data)[i][j] = num;
				}
			}
		}
		//printf("%f %ld ", (double)count_num, dimension);
		//2printf("%f\n", (double)(count_num)/dimension);
	}
}

char clear_matrix_multiplication(matrix_t *matrix_left, matrix_t *matrix_right, matrix_t *matrix_result)
{
	char rc = ERR_OK;
	if(matrix_left->columns_count != matrix_right->rows_count)
		rc = ERR_INCORRECT_DIMENSION;
	else
	{
		matrix_result->rows_count = matrix_left->rows_count;
		matrix_result->columns_count = matrix_right->columns_count;
		//printf("%ld %ld \n", matrix_result->rows_count,matrix_result->columns_count);
		rc = allocate_matrix(matrix_result);
		if(rc == ERR_OK)
		{
			for(size_t i = 0; i < matrix_result->rows_count; ++i)
			{
				for(size_t j = 0; j < matrix_result->columns_count; ++j)
				{
					int buf = 0;
					for(size_t k = 0; k < matrix_left->columns_count; ++k)
					{
						buf += (matrix_left->data)[i][k] * (matrix_right->data)[k][j];
					}
					(matrix_result->data)[i][j] = buf;
				}
			}
		}
	}

	return rc;
}


char matrix_multiplication(matrix_t *matrix_left, matrix_t *matrix_right, matrix_t *matrix_result)
{
	char rc = ERR_OK;
	if(matrix_left->columns_count != matrix_right->rows_count)
	{
		rc = ERR_INCORRECT_DIMENSION;
	}
	else
	{
		matrix_result->rows_count = matrix_left->rows_count;
		matrix_result->columns_count = matrix_right->columns_count;
		//printf("%ld %ld \n", matrix_result->rows_count,matrix_result->columns_count);
		rc = allocate_matrix(matrix_result);
		if(rc == ERR_OK)
		{

			rc = transponse_matrix(matrix_right);

			for(size_t i = 0; rc == ERR_OK && i < matrix_result->rows_count; ++i)
			{
				for(size_t j = 0; j < matrix_result->columns_count; ++j)
				{
					(matrix_result->data)[i][j] = 0;
					for(size_t k = 0; k < matrix_left->columns_count; ++k)
					{
						(matrix_result->data)[i][j] += (matrix_left->data)[i][k] * (matrix_right->data)[j][k];
					}
				}
			}
			if(rc == ERR_OK)
				rc = transponse_matrix(matrix_right);
		}
	}

	return rc;
}


void transponse(matrix_t *matrix, matrix_t *tmp_matrix)
{
	for(size_t i = 0; i < matrix->rows_count; ++i)
	{
		for(size_t j = 0; j < matrix->columns_count; ++j)
		{
			(tmp_matrix->data)[j][i] = (matrix->data)[i][j];
		}
	}

}

char transponse_matrix(matrix_t *matrix)
{
	char rc = ERR_OK;

	matrix_t tmp_matrix;

	tmp_matrix.columns_count = matrix->rows_count;
	tmp_matrix.rows_count = matrix->columns_count;
	rc = allocate_matrix(&tmp_matrix);
	if(rc == ERR_OK)
	{
		transponse(matrix, &tmp_matrix);
	}

	free_matrix(matrix);
	*matrix = tmp_matrix;

	return rc;
}


void init_matrix(matrix_t *matrix)
{
	matrix->rows_count = 0;
	matrix->columns_count = 0;	
	matrix->data = NULL;
}

void print_matrix(matrix_t *matrix)
{
	for(size_t i = 0; i < matrix->rows_count; ++i)
	{
		for(size_t j = 0; j < matrix->columns_count; ++j)
			printf("%*d ", WIDTH_NUM, ((matrix->data)[i][j]));
		printf("\n");
	}
}

char input_matrix_coordinate(FILE *f, int choice, matrix_t *matrix)
{
	char rc = ERR_OK;
	rc = input_matrix_dimension(f, choice, matrix);
	if(rc == ERR_OK && (rc = allocate_matrix(matrix)) == ERR_OK)
	{
		rc = input_matrix_content_coordinate(f, choice, matrix);
	}
	return rc;	
}

char input_matrix_content_coordinate(FILE *f, int choice, matrix_t *matrix)
{
	char rc = ERR_OK;
	if(choice == CONSOLE_INPUT)
	{
		printf("Введите количество элементов: ");
	}
	int count_num = 0;
	rc = input_num(f, &count_num, ERR_INPUT_NUMBER_COUNT);
	if(rc == ERR_OK)
	{
		int row_number = 0, column_number = 0;
		int num = 0;
		for(size_t i = 0; rc == ERR_OK && i < (size_t)count_num; ++i)
		{
			if(choice == CONSOLE_INPUT)
			{
				printf("Введите координаты элемента(с 1): ");
			}
			if(fscanf(f, "%d %d", &row_number, &column_number) != 2)
			{
				rc = ERR_INPUT_NUM;
			}
			else if((row_number-1)<0 || (column_number-1)<0)
			{
				rc = ERR_INPUT_DIMENSION_TOO_SMALL;
			}
			else if((size_t)(row_number-1) >= matrix->rows_count || (size_t)(column_number-1) >= matrix->columns_count)
			{
				rc = ERR_INPUT_DIMENSION_TOO_MUCH;
			}
			else
			{
				if(choice == CONSOLE_INPUT)
				{
					printf("Введите элемент: ");
				}
				if(fscanf(f, "%d", &num) == 1)
					(matrix->data)[row_number-1][column_number-1] = num;
			}
		}
	}
	return rc;
}


char input_matrix(FILE *f, int choice, matrix_t *matrix)
{
	char rc = ERR_OK;
	rc = input_matrix_dimension(f, choice, matrix);
	if(rc == ERR_OK && (rc = allocate_matrix(matrix)) == ERR_OK)
	{
		rc = input_matrix_content(f, choice, matrix);
	}
	return rc;
}

char input_matrix_content(FILE *f, int choice, matrix_t *matrix)
{
	char rc = ERR_OK;
	if(choice == CONSOLE_INPUT)
	{
		printf("Введите элементы: \n");
	}
	for(size_t i = 0; i < matrix->rows_count && rc == ERR_OK; ++i)
	{
		for(size_t j = 0; j < matrix->columns_count && rc == ERR_OK; ++j)
		{
			rc = fscanf(f, "%d", (matrix->data)[i]+j) == 1 ? ERR_OK : ERR_INPUT_NUM;
		}
	}
	return rc;
}

char input_matrix_dimension(FILE *f, int choice, matrix_t *matrix)
{
	char rc = ERR_OK;
	int columns_count = 0, rows_count = 0;
	if(choice == CONSOLE_INPUT)
	{
		printf("Введите размерность (количество строк и столбцов, через пробел): ");
	}
	rc = input_num(f, &rows_count, ERR_INPUT_ROWS_COUNT);
		
	if(rc == ERR_OK)
	{
		matrix->rows_count = rows_count;
		rc = input_num(f, &columns_count, ERR_INPUT_COLUMNS_COUNT);
		if(rc == ERR_OK)
			matrix->columns_count = columns_count;
	}

	return rc;
}

char input_num(FILE *f, int *num, char rc)
{
	if(fscanf(f, "%d", num) == 1 && *num > 0)
		rc = ERR_OK;
	return rc;
}


char allocate_matrix(matrix_t *matrix)
{
	char rc = ERR_OK;
	rc = allocate_mem((void *)(&(matrix->data)), sizeof(int **), matrix->rows_count);
	for(size_t i = 0; rc == ERR_OK && i < matrix->rows_count; ++i)
	{
		rc = allocate_mem((void *)((matrix->data)+i), sizeof(int), matrix->columns_count);
		if(rc != ERR_OK)
		{
			free_matrix(matrix);
			rc = ERR_ALLOCATE_MEM;
		}
	}
	return rc;
}

char allocate_mem(void **dst, size_t size, size_t elements_count)
{
	char rc = ERR_OK;
	*dst = calloc(elements_count, size);
	if(*dst == NULL)
	{
		rc = ERR_ALLOCATE_MEM;
	}
	return rc;
}

//идти не до н, а до i, ведь остальное и так не маллочили...?
void free_matrix(matrix_t *matrix)
{
	if(matrix->data != NULL)
	{
		for(size_t i = 0; i < matrix->rows_count; ++i)
		{
			free((matrix->data)[i]);
		}
	}

	free(matrix->data);
	matrix->data = NULL;
}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
