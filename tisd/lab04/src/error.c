/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/errors.h"
#include <stdio.h>

void process_error(char rc)
{
	switch(rc)
	{
		case ERR_READ_EMPTY_STR:
		case ERR_EOF:
			printf("Некорректный ввод: пустая строка\n");
			break;
		case ERR_ALLOCATE_MEM:
			printf("Произошла ошибка выделения памяти\n");
			break;
		case ERR_GET_LINE:
			printf("Произошла ошибка при чтении строки\n");
			break;
		case ERR_INCORRECT_STACK:
			printf("Произошла ошибка - некорректный стек\n");
			break;
		case ERR_EMPTY_STACK:
			printf("Нельзя проводить операции удаления/чтения пустого стека\n");
			break;
		case ERR_READ_VOLUME:
			printf("Некорректный ввод: выражение не соответствует формату\n");
			break;
		default:
			printf("Произошла непредвиденная ошибка :(\n");
			break;	
	}	
}