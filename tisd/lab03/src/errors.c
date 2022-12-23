/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */


#include "../inc/errors.h"

void process_error(char rc)
{
	if(rc == ERR_ALLOCATE_MEM)
		printf("\nОшибка выделения памяти\n");
	else if(rc == ERR_INPUT_ROWS_COUNT)
		printf("\nНекорректный ввод количества строк\n");
	else if(rc == ERR_INPUT_COLUMNS_COUNT)
		printf("\nНекорректный ввод количества столбцов\n");
	else if(rc == ERR_INPUT_NUM)
		printf("\nНекорректный ввод элемента матрицы\n");
	else if(rc == ERR_INCORRECT_DIMENSION)
		printf("\nНекорректные размерности матрицы для их умножения\n");
	else if(rc == ERR_ALL_ELEMENTS_ZERO)
		printf("\nВсе элементы матрицы нулевые\n");
	else if(rc == ERR_ALL_ELEMENTS_ZERO_BY_MULT)
		printf("\nВ результате умножения матриц получилась матрица, состоящая полностью из нулей\n");
	else if(rc == ERR_IS_NOT_VECTOR)
		printf("\nКоличество строк вектора не может превышать 1\n");
	else if(rc == ERR_READ_FILE)
		printf("\nВ файле были указаны некорректные данные, произошла ошибка чтения файла\n");
	else if(rc == ERR_OPEN_FILE)
		printf("\nПроизошла ошибка при открытии файла, неверно указан путь до файла\n");
	else if(rc == ERR_EMPTY_FILE)
		printf("\nПроизошла ошибка: пустой файл");
	else if(rc == ERR_EOF)
		printf("\nПроизошла ошибка: при чтении записи преждевременно был достигнут конец файла\n");
	else if(rc == ERR_STR_TOO_LONG)
		printf("\nПроизошла ошибка: введенная строка превышает допустимые размеры\n");
	else if(rc == ERR_EMPTY_STR)
		printf("\nПроизошла ошибка: в записи присутствует пустая строка\n");
	else if(rc == ERR_INPUT_CHOICE)
		printf("\nНеверный выбор пункта меню\n");
	else if(rc == ERR_DIMENSION_NOT_EQUAL)
		printf("\nКоличество столбцов вектора не равно количеству строк матрицы\n");
	else if(rc == ERR_INPUT_DIMENSION_TOO_MUCH)
		printf("\nВведенные индексы превышает допустимые\n");
	else if(rc == ERR_INPUT_DIMENSION_TOO_SMALL)
		printf("\nВведенные индексы меньше допустимых\n");
	else if(rc == ERR_INCORRECT_PERCENT_DENSITY)
		printf("\nВведен некорректный процент заполненности\n");
}	