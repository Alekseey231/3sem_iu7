/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/errors.h"
#include "stdio.h"

void process_error(char rc)
{
	if(rc == ERR_READ_FILE)
		printf("В файле были указаны некорректные данные, произошла ошибка чтения файла\n");
	else if(rc == ERR_OPEN_FILE)
		printf("Произошла ошибка при открытии файла, неверно указан путь до файла\n");
	else if(rc == ERR_ALLOCATE_MEM)
		printf("Произошла ошибка при выделении памяти\n");
	else if(rc == ERR_EMPTY_FILE)
		printf("Произошла ошибка: пустой файл");
	else if(rc == ERR_EOF)
		printf("Произошла ошибка: при чтении записи преждевременно был достигнут конец файла\n");
	else if(rc == ERR_STR_TOO_LONG)
		printf("Произошла ошибка: введенная строка превышает допустимые размеры\n");
	else if(rc == ERR_EMPTY_STR)
		printf("Произошла ошибка: в записи присутствует пустая строка\n");
	else if(rc == ERR_INPUT_CHOICE)
		printf("Неверный выбор пункта меню\n");
	else if(rc == ERR_STATUS)
		printf("некорректный ввод: неверно указан статус\n");
	else if(rc == ERR_INCORRECT_NAME)
		printf("некорректный ввод: некорректное имя\n");
	else if(rc == ERR_TOO_MUCH_DAY)
		printf("количество дней превышает допустимое\n");
	else if(rc == ERR_TOO_MUCH_MONTH)
		printf("некорректный ввод: максимальное значение месяца - 12\n");
	else if(rc == ERR_NEGATIVE_DAY)
		printf("некорректный ввод: минимальное значение дня - 1\n");
	else if(rc == ERR_NEGATIVE_MONTH)
		printf("некорректный ввод: минимальное значение месяца - 1\n");
	else if(rc == ERR_NEGATIVE_YEAR)
		printf("некорректный ввод: год не может быть меньше 1900\n");
	else if(rc == ERR_TOO_MUCH_YEAR)
		printf("некорректный ввод: год не может быть больше 9999\n");
	else if(rc == ERR_INCORRECT_DATE)
		printf("некорректная дата\n");
	else if(rc == ERR_NOT_DIGIT_IN_DATE)
		printf("в дате присутствуют не только цифры\n");
	else if(rc == ERR_PHONE_NUMBER)
		printf("указан некорректный номер телефона\n");
}
