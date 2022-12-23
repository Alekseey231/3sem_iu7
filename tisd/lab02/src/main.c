/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/errors.h"
#include <string.h>
#include <ctype.h>
#include "../inc/subscribers.h"
#include "../inc/validation_input_data.h"
#include "../inc/sort_table.h"
#include "../inc/effective.h"
#include "../inc/process_date_file_struct.h"
#include "../inc/table_keys.h"
#include "../inc/print_struct.h"
#include "../inc/find_subscribers.h"

int main(void)
{
	char rc = ERR_OK;
	size_t start_count_struct = START_COUNT_STRUCT;
	subscribers_t *subscribers = NULL;
	size_t count_structs = 0;
	keys_t *keys = NULL;
	char *menu = "Выберите пункт меню:\n0 - выход из программы\n1 - считать данные из файла\n2 - добавить запись\n3 - вывод на экран\n4 - сортировка исходной таблицы(пузырьком)\n"
				 "5 - сортировка исходной таблицы(быстрая)\n6 - вывод таблицы ключей\n7 - сортировка таблицы ключей(пузырьком)\n8 - сортировка таблицы ключей(быстрая)\n"
				 "9 - вывод упорядоченной исходной таблицы по упорядоченной таблице ключей\n10 - вывод эффективности\n"
				 "11 - поиск друзей, которых надо поздравить с днем рождения в ближайшую неделю\n12 - удалить записи по фамилии\n";
	char filename[40] = {0};

	int choice = 0;
	while(rc == ERR_OK)
	{
		printf("%s", menu);
		rc = scanf("%d", &choice) == 1 ? ERR_OK : ERR_INPUT_CHOICE;
		if(rc == ERR_OK)
		{
			if(choice == 0)
			{
				//TODO уменьшение числа выделенной памяти при удалении 
				rc = ERR_EXIT;
			}
			else if(choice == 1)
			{
				printf("\nВведите путь до файла: ");
				
				if(scanf("%39s", filename) == 1)
				{
					free(subscribers);
					free(keys);
					subscribers = NULL;
					keys = NULL;
					start_count_struct = START_COUNT_STRUCT;
					subscribers = malloc(start_count_struct * sizeof(subscribers_t));
					count_structs = 0;
					rc = read_all_structs_from_file(filename, &subscribers, &count_structs, &start_count_struct);
					if(rc == ERR_OK)
					{
						printf("\nФайл успешно считан!\n\n");
						keys = malloc(start_count_struct * sizeof(keys_t));
						create_keys(subscribers, count_structs, keys);
					}
					else
					{
						process_error(rc);
					}
				}
				else
				{
					printf("\nНекорректный ввод\n");
				}
				
			}
			else if(choice == 2)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					rc = add_struct(&subscribers, &count_structs, &start_count_struct);
					if(rc == ERR_OK)
					{
						if(start_count_struct == count_structs)
						{
							size_t tmp = start_count_struct;
							rc = realloc_mem(&subscribers, &tmp);
							if(rc == ERR_OK)
								rc = realloc_mem_keys(&keys, &start_count_struct);
						}
						if(rc == ERR_OK)
						{
							save_key(keys+(count_structs-1), subscribers+(count_structs-1), count_structs-1);
							rc = write_struct_to_file(filename, subscribers+(count_structs-1));
						}
						else
						{
							process_error(rc);
						}
					}
					else if(rc >= 20)
					{
						process_error(rc);
						rc = ERR_OK;
					}
					else
					{
						process_error(rc);
					}
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			}
			else if(choice == 3)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					print_sturcts(subscribers, count_structs);
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			}
			else if(choice == 4)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					bubble_sort(subscribers, count_structs, sizeof(subscribers_t), comparator_subscribers);
					create_keys(subscribers, count_structs, keys);
				}
				else
				{
					printf("\nНе выбран файл\n");
				}

			}
			else if(choice == 5)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					qsort(subscribers, count_structs, sizeof(subscribers_t), comparator_subscribers);
					create_keys(subscribers, count_structs, keys);
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
				//insertion_sort(subscribers, count_structs, sizeof(subscribers_t), comparator_subscribers);
			}
			else if(choice == 6)
			{	
				if(count_structs != 0 && subscribers != NULL)
				{
					if(keys != NULL)
						print_keys(keys, count_structs);
					else
						printf("\nТаблица ключей отсутствует\n");
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			} 
			else if(choice == 7)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					if(keys != NULL)
						bubble_sort(keys, count_structs, sizeof(keys_t), comparator_keys);
					else
						printf("\nТаблица ключей отсутствует\n");
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			}
			else if(choice == 8)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					if(keys != NULL)
						//insertion_sort(keys, count_structs, sizeof(keys_t), comparator_keys);
						qsort(keys, count_structs, sizeof(keys_t), comparator_keys);
					else
						printf("\nТаблица ключей отсутствует\n");	
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			}
			else if(choice == 9)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					if(keys != NULL)
						print_sturct_by_keys(subscribers, count_structs, keys);
					else
						printf("\nТаблица ключей отсутствует\n");
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			}
			else if(choice == 10)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					rc = effective(subscribers, count_structs);
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			}
			else if(choice == 11)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					subscribers_t *finded_subscribers = malloc(count_structs * sizeof(subscribers_t));
					size_t count_finded_structs = 0;
					if(finded_subscribers != NULL)
					{
						find_subscribers_by_birth_day(subscribers, count_structs, finded_subscribers, &count_finded_structs);
						if(count_finded_structs != 0)
						{
							printf("\nСписок друзей, которых необходимо поздравить с днем рождения в ближайшую неделю\n");
							print_sturcts(finded_subscribers, count_finded_structs);
						}
						else
						{
							printf("\nНе найдены друзья, которых необходимо поздравить с днем рождения в ближайшую неделю\n");
						}

					}
					else
					{
						rc = ERR_ALLOCATE_MEM;
					}
					free(finded_subscribers);
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			}
			else if(choice == 12)
			{
				if(count_structs != 0 && subscribers != NULL)
				{
					char buf[MAX_FIRSTNAME_LEN] = {0};
					printf("Введите фамилию(макс. 20 символов): ");
					clean_stdin();
					rc = read_str_to_buf(stdin, buf, MAX_FIRSTNAME_LEN);
					if(rc == ERR_OK)
					{
						size_t count_deletes = 0;
						rc = delete_struct_by_firstname(subscribers, &count_structs, buf, filename, &count_deletes);
						if(rc == ERR_OK)
						{
							if(count_deletes == 0)
							{
								printf("\nЛюди с данной фамилией отсутствуют\n");
							}
							else
							{
								printf("\nЗаписи успешно удалены\n");
								create_keys(subscribers, count_structs, keys);
							}
						}
					}
					else if(rc >= 20)
					{
						process_error(rc);
						rc = ERR_OK;
					}
					else
					{
						process_error(rc);
					}
				}
				else
				{
					printf("\nНе выбран файл\n");
				}
			}
			else
			{
				printf("\nIncorrect input\n");
			}
		}
		process_error(rc);
	}
	free(subscribers);
	free(keys);
	return rc;
}



