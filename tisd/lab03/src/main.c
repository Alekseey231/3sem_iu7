/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/errors.h"
#include "../inc/matrix.h"
#include "../inc/linked_list.h"
#include "../inc/sparse_matrix.h"
#include "../inc/effective.h"

#define MAX_LEN_FILE_NAME 30 + 1
#define CONSOLE_INPUT 2
#define FILE_INPUT 1
#define FILE_INPUT_COORDINATE 3
#define CONSOLE_INPUT_COORDINATE 4



char read_str_to_buf(FILE *f, char *buf, size_t max_len);


int main()
{
	char rc = ERR_OK;
	int choice = -1;

	sparse_matrix_t *sparse_matrix = NULL, *sparse_vector = NULL, *sparse_result = NULL;

	sparse_matrix = init_sparse_matrix();
	sparse_vector = init_sparse_matrix();
	sparse_result = init_sparse_matrix();

	matrix_t matrix_result, matrix, vector;

	init_matrix(&matrix);
	init_matrix(&vector);
	init_matrix(&matrix_result);

	FILE *f;
	char file_name[MAX_LEN_FILE_NAME];

	char is_matrix_get = 0;

	char *menu = "0) Выйти из программы\n1) Считать вектор и матрицу из файла\n2) Ввести вектор и матрицу вручную\n3) Считать матрицу из файла координатно\n4) Ввести матрицу вручную координатно\n"
	"5) Сгенерировать случайный вектор и матрицу \n6) Сравнить время выполнения при различном проценте заполнения матриц\n";
	char *sub_menu = "0) Закончить работу с выбранным файлом\n1) Вывести считанные матрицы\n2) Выполнить умножение сжатых матриц\n3) Выполнить умножение матриц стандартным способом\n4) Вывод в сжатом формате\n";
	char *sep = "----------------------------------------------------------------------------------------------------------------------------------------------------------------";
	if(sparse_vector == NULL || sparse_matrix == NULL || sparse_result == NULL)
	{
		rc = ERR_ALLOCATE_MEM;
	}

	while(rc == ERR_OK)
	{
		if(is_matrix_get)
		{
			printf("%s", sub_menu);
		}
		else
		{
			printf("%s", menu);
		}
		
		printf("Выберите пункт меню: ");
		rc = scanf(" %d", &choice) == 1 ? ERR_OK : ERR_INPUT_CHOICE;
		if(rc == ERR_OK)
		{
			if(is_matrix_get == 0)
			{
				reinit_sparse_matrix(sparse_matrix);
				reinit_sparse_matrix(sparse_vector);
				reinit_sparse_matrix(sparse_result);
				free_matrix(&matrix);
				free_matrix(&vector);
				if(choice == 6)
				{
					rc = get_effective();
				}
				else
				{
					if(choice == FILE_INPUT || choice ==FILE_INPUT_COORDINATE)
					{
						printf("Введите путь к файлу (максимально 30 символов): ");
						clean_stdin();
						rc = read_str_to_buf(stdin, file_name, MAX_LEN_FILE_NAME);
						if(rc == ERR_OK)
						{
							f = fopen(file_name, "r");
							if(f == NULL)
								rc = ERR_OPEN_FILE;
						}
					}
					else if(choice == CONSOLE_INPUT || choice == CONSOLE_INPUT_COORDINATE || choice == 5)
					{
						f = stdin;
					}
					else if(choice == 0)
					{
						rc = ERR_EXIT;
					}
					else
					{
						rc = ERR_INPUT_CHOICE;
					}

					if(rc == ERR_OK && f != NULL)
					{
						if(choice == CONSOLE_INPUT || choice == FILE_INPUT)
							rc = get_matrix(f, choice, &matrix, &vector);
						else if(choice == CONSOLE_INPUT_COORDINATE || choice == FILE_INPUT_COORDINATE)
						{
							if(choice == CONSOLE_INPUT_COORDINATE)
								choice = CONSOLE_INPUT;
							rc = get_matrix_coordinate(f, choice, &matrix, &vector);
						}
						else if(choice == 5)
						{
							rc = generate_matrix_random(&matrix, &vector);
						}
						if(rc == ERR_OK)
						{
							rc = set_sparse_matrix(&matrix, &vector, sparse_matrix, sparse_vector);
						}
						if(choice == FILE_INPUT || choice == FILE_INPUT_COORDINATE)
						{
							fclose(f);
							f = NULL;
						}

					}

					if(rc == ERR_OK)
					{
						is_matrix_get = 1;
					}
				}
			}
			else
			{
				if(choice == 0)
				{
					is_matrix_get = 0;
				}
				else if(choice == 1)
				{
					printf("%.*s\n", (int)sparse_vector->columns_count * (WIDTH_NUM+2), sep);
					print_sparse_matrix(sparse_vector);
					printf("%.*s\n", (int)sparse_matrix->columns_count * (WIDTH_NUM+2), sep);
					print_sparse_matrix(sparse_matrix);
					printf("%.*s\n", (int)sparse_matrix->columns_count * (WIDTH_NUM+2), sep);

				}
				else if(choice == 2)
				{
					reinit_sparse_matrix(sparse_result);
					rc = matrix_sparse_mupltiplication(sparse_vector, sparse_matrix, sparse_result);
					if(rc == ERR_OK)
					{
						rc = print_sparse_matrix(sparse_result);
						printf("\n");
						print_sparse_format(sparse_result);
					}
				}
				else if(choice == 3)
				{
					free_matrix(&matrix_result);
					rc = matrix_multiplication(&vector, &matrix, &matrix_result);
					if(rc == ERR_OK)
					{
						print_matrix(&matrix_result);
					}
				}
				else if(choice == 4)
				{
					printf("Вектор в сжатом формате\n");
					print_sparse_format(sparse_vector);
					printf("Матрица в сжатом формате\n");
					print_sparse_format(sparse_matrix);
				}
				else
				{
					rc = ERR_INPUT_CHOICE;
				}
			}
		}
		process_error(rc);
		if(rc > 2 && (rc != ERR_EXIT_SUB && rc != ERR_EXIT))
		{
			rc = ERR_OK;
			
		}
	}
	//process_error(rc);
	free_matrix(&matrix);
	free_matrix(&vector);
	free_matrix(&matrix_result);
	free_sparse_matrix(sparse_matrix);
	free_sparse_matrix(sparse_vector);
	free_sparse_matrix(sparse_result);

	return rc;
}










char read_str_to_buf(FILE *f, char *buf, size_t max_len)
{
	char rc = ERR_OK;
    if (fgets(buf, max_len+1, f) == NULL)
    {
    	if (feof(f) == 0)
            rc = ERR_READ_FILE;
        else
            rc = ERR_EOF;
    }
    else
    {
    	if((buf)[strlen(buf) - 1] != '\n')
    	{
    		if(strlen(buf)==max_len)
    		{
    			rc = ERR_STR_TOO_LONG;
    		}
    	}
    	else if (!((buf)[strlen(buf) - 1] = 0) && strlen(buf) == 0)
    	{
    		rc = ERR_EMPTY_STR;
    	}

    }
    return rc;
}


