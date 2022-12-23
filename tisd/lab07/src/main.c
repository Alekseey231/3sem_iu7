/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <assert.h>
#include <stdio.h>
#include "../inc/tree.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/effective.h"
#include "../inc/hash_table.h"
#include "../inc/closed_table.h"

void clean_stdin();
char add_node_to_file(struct tree_node_t *node, char *file_name);
char hash_table(char *file_name);
char tree(char *file_name);
char not_balanced_tree(char *file_name);
char closed_table(char *file_name);

#define N_REPS 10000

#define CHOICE_EXIT 0
#define CHOICE_ADD_NODE 1
#define CHOICE_FIND_NODE 2
#define CHOICE_RAB 3
#define CHOICE_ARB 4
#define CHOICE_ABR 5
#define CHOICE_SHOW_TREE 6
#define CHOICE_DELETE_NODE 7
#define CHOICE_COUNT_NODE 8
#define CHOICE_EFFECTIVE 9

#define CHOICE_SHOW_TABLE 1
#define CHOICE_ADD_ELEMENT 2
#define CHOICE_DELETE_ELEMENT 3
#define CHOICE_FIND_ELEMENT 4



#define CHOICE_MAIN_AVL 1
#define CHOICE_MAIN_HESH 2
#define CHOICE_MAIN_CLOSED 3
#define CHOICE_MAIN_BIN 4
#define CHOICE_MAIN_EFFECTIVE 5

int main(int argc, char **argv)
{
	char rc = ERR_OK;
	int choice = -1;
    char *menu = "0) Выйти из программы\n1) Работа с авл-деревьями \n2) Работа с хеш-таблицей(метод цепочек)\n3) Работа с хеш-таблицей(закрытое хеширование)\n"
    "4) Работа с деревьями поиска\n5) Эффектиность\n";
	if(argc == 2)
	{	
		while(rc == ERR_OK && choice != CHOICE_EXIT)
		{
			printf("%s", menu);
			rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_INVALID_INPUT;
			if(rc == ERR_OK)
			{
				if(choice == CHOICE_MAIN_AVL)
				{
					rc = tree(argv[1]);
				}
				else if(choice == CHOICE_MAIN_HESH)
				{
					rc = hash_table(argv[1]);
				}
				else if(choice == CHOICE_MAIN_CLOSED)
				{
					rc = closed_table(argv[1]);
				}
				else if(choice == CHOICE_MAIN_BIN)
				{
					rc = not_balanced_tree(argv[1]);
				}
				else if(choice == CHOICE_MAIN_EFFECTIVE)
				{
					effective();
				}
			}
		}
	}
    return rc;
}


char tree(char *file_name)
{
	char rc = ERR_OK;
    struct tree_node_t *root = NULL;
    int choice = -1;
    char *menu = "0) Выйти из программы\n1) Добавить узел в дерево\n2) Найти узел в дерева\n3) Префиксный обход дерева\n"
    			"4) Инфиксный обход дерефа\n5) Постфиксный обход дерева\n6) Показать дерево\n7) Удалить узел из дерева\n"
    			"8) Вывести количество узлов на каждом уровне\n";
    rc = get_all_nums(file_name, &root);
	if(rc == ERR_OK)
	{
		while(rc == ERR_OK && choice != CHOICE_EXIT)
		{
			printf("%s", menu);
			rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_INVALID_INPUT;
			//clean_stdin();
			if(choice == CHOICE_SHOW_TREE)
			{
				if(root != NULL)
				{
					if(root->left == NULL && root->right == NULL)
					{
						node_print(root, "\nКорень дерева: %d\n\n");
					}
					else
					{
						FILE *f = fopen("test.gv", "w");

				        assert(f);

				        btree_export_to_dot(f, "test_tree", root);

				        fclose(f);
				        system("dot -Tpng test.gv -otest.png");
				        system("xdg-open test.png &");				
				    }	
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}

			}
			else if(choice == CHOICE_RAB)
			{
				if(root != NULL)
				{
					pre_order_apply(root, node_print, "%d ");
		    		printf("\n");					
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_ARB)
			{
				if(root != NULL)
				{
					inf_order_apply(root, node_print, "%d ");
		    		printf("\n");			
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_ABR)
			{
				if(root != NULL)
				{
					post_order_apply(root, node_print, "%d ");
		    		printf("\n");		
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_ADD_NODE)
			{
				int num;
				int count_cmp = 0;
				rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
				if(lookup2(root, num, &count_cmp) != NULL)
				{
					printf("Такое число уже есть в дереве\n");
				}
				else
				{
					struct tree_node_t *node = node_create(num);
					if(node != NULL)
					{
						root = btree_insert(root, node);
					}
					else
					{
						rc = ERR_ALLOCATE_MEM;
					}
					if(rc == ERR_OK)
					{
						rc = add_node_to_file(node, file_name);
					}
				}

			}
			else if(choice == CHOICE_DELETE_NODE)
			{
				if(root != NULL)
				{
					int num;
					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
					if(rc == ERR_OK)
					{
						root = btree_delete(root, num);
					}	
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_FIND_NODE)
			{
				if(root != NULL)
				{
					int num;
					int count_cmp = 0;
					struct tree_node_t *res = NULL;

					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
					
					unsigned long long sum = 0, del = 0;
					struct timespec t_beg, t_end;

					for (int k = 0; rc == ERR_OK && k < N_REPS; k++)
					{
						count_cmp = 0;
						clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
						res = lookup2(root, num, &count_cmp);
						clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

						del = calc_elapsed_time(&t_beg, &t_end);
						sum = sum + del;
					}
					sum = sum/N_REPS;


					printf("Время поиска: %lld\n", sum);
					printf("Количество сравнений: %d\n", count_cmp);
					if(rc == ERR_OK && res != NULL)
					{
						printf("Число найдено\n");
					}
					else
					{
						printf("Введеное число не найдено\n");
					}
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_COUNT_NODE)
			{
				if(root != NULL)
				{
					size_t *arr = calloc(100, sizeof(size_t));
					if(arr != NULL)
					{
						count_node(root, 0, arr);
						for(size_t i = 0; arr[i] != 0; ++i)
						{
							printf("Уровень: %ld | Количество вершин: %ld\n", i+1, arr[i]);
						}
					}
					free(arr);				
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
		}
		//post_order_apply(root, node_print, "%d ");
	    //printf("\n");

	    {
	        
	    }
		post_order_apply(root, node_free, NULL);
	}
    return rc;
}


char hash_table(char *file_name)
{
	char rc = ERR_OK;
    int choice = -1;
    char *menu = "0) Выйти из программы\n1) Вывести таблицу\n2) Добавить элемент в таблицу\n3) Удалить элемент из таблицы\n4) Найти элемент в таблице\n";
	hash_table_t *table = create_hash_table(file_name);
	if(table != NULL)
	{
		char is_restruct = 0;
		rc = resturct_after_create(&table, &is_restruct);
		if(is_restruct == 1)
		{
			printf("Таблица была реструктуризированна после создания\n");
		}
	}
	else
	{
		rc = ERR_ALLOCATE_MEM;
	}
	if(rc == ERR_OK)
	{
		while(rc == ERR_OK && choice != CHOICE_EXIT)
		{
			printf("%s", menu);
			rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_INVALID_INPUT;
			//clean_stdin();
			if(choice == CHOICE_SHOW_TABLE)
			{
				if(table->count_elements > 0)
				{
					print_hash_table(table);
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустой таблицы\n");
				}
			}
			else if(choice == CHOICE_ADD_ELEMENT)
			{
				int num;
				rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
				if(rc == ERR_OK)
				{
					char is_restruct = 0;
					unsigned long long sum = 0;
					struct timespec t_beg, t_end;
		    
		    		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
					rc = hash_table_insert(&table, num, 0, &is_restruct);
					clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

					sum = calc_elapsed_time(&t_beg, &t_end);
					if(rc == ERR_OK)
					{
						printf("Среднее количество сравнений: %f\n", table->avarage_count_compare);
						printf("Максимально количество сравнений: %ld\n", table->max_count_compare);
						printf("Время вставки: %lld\n", sum);
					}
					if(rc == ERR_OK && is_restruct == 1)
					{
						printf("Таблица была реструктуризированна\n");
					}
				}
			}
			else if(choice == CHOICE_DELETE_ELEMENT)
			{
				if(table->count_elements > 0)
				{
					int num;
					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
					if(rc == ERR_OK)
					{
						if(hash_table_delete(table, num))
						{
							printf("Элемент успешно удален из таблицы\n");
						}
						else
						{
							printf("Данный элемент отсутствует в таблице\n");
						}
					}	
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустой таблицы\n");
				}
			}
			else if(choice == CHOICE_FIND_ELEMENT)
			{
				if(table->count_elements > 0)
				{
					int num = 0;
					int res = 0;
					int count_cmp = 0;
					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;

					unsigned long long sum = 0, del = 0;
					struct timespec t_beg, t_end;

					for (int k = 0; rc == ERR_OK && k < N_REPS; k++)
					{
						count_cmp = 0;
						clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
						res = find_hash_table(table, num, &count_cmp);
						clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

						del = calc_elapsed_time(&t_beg, &t_end);
						sum = sum + del;
					}
					sum = sum/N_REPS;


					printf("Время поиска: %lld\n", sum);
					printf("Количество сравнений: %d\n", count_cmp);
					if(rc == ERR_OK && res == 1)
					{
						printf("Число найдено\n");
					}
					else
					{
						printf("Введеное число не найдено\n");
					}
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустой таблицы\n");
				}
			}
		}
		free_hash_table(table);
	}
	return rc;
}


void clean_stdin()
{
	int c;
	do {
		c = getchar();
	} while(c != '\n' && c != EOF);
}


char not_balanced_tree(char *file_name)
{
	char rc = ERR_OK;
    struct tree_node_t *root = NULL;
    int choice = -1;
    char *menu = "0) Выйти из программы\n1) Добавить узел в дерево\n2) Найти узел в дерева\n3) Префиксный обход дерева\n"
    			"4) Инфиксный обход дерефа\n5) Постфиксный обход дерева\n6) Показать дерево\n7) Удалить узел из дерева\n"
    			"8) Вывести количество узлов на каждом уровне\n";
    rc = get_all_nums_not_balanced(file_name, &root);
	if(rc == ERR_OK)
	{
		while(rc == ERR_OK && choice != CHOICE_EXIT)
		{
			printf("%s", menu);
			rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_INVALID_INPUT;
			//clean_stdin();
			if(choice == CHOICE_SHOW_TREE)
			{
				if(root != NULL)
				{
					if(root->left == NULL && root->right == NULL)
					{
						node_print(root, "\nКорень дерева: %d\n\n");
					}
					else
					{
						FILE *f = fopen("test.gv", "w");

				        assert(f);

				        btree_export_to_dot(f, "test_tree", root);

				        fclose(f);
				        system("dot -Tpng test.gv -otest.png");
				        system("xdg-open test.png &");				
				    }	
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}

			}
			else if(choice == CHOICE_RAB)
			{
				if(root != NULL)
				{
					pre_order_apply(root, node_print, "%d ");
		    		printf("\n");					
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_ARB)
			{
				if(root != NULL)
				{
					inf_order_apply(root, node_print, "%d ");
		    		printf("\n");			
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_ABR)
			{
				if(root != NULL)
				{
					post_order_apply(root, node_print, "%d ");
		    		printf("\n");		
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_ADD_NODE)
			{
				int num;
				int count_cmp = 0;
				rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
				if(lookup2(root, num, &count_cmp) != NULL)
				{
					printf("Такое число уже есть в дереве\n");
				}
				else
				{
					struct tree_node_t *node = node_create(num);
					if(node != NULL)
					{
						root = btree_insert_not_balanced(root, node);
					}
					else
					{
						rc = ERR_ALLOCATE_MEM;
					}
					if(rc == ERR_OK)
					{
						rc = add_node_to_file(node, file_name);
					}
				}

			}
			else if(choice == CHOICE_DELETE_NODE)
			{
				if(root != NULL)
				{
					int num;
					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
					if(rc == ERR_OK)
					{
						root = btree_delete_not_balanced(root, num);
					}	
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_FIND_NODE)
			{
				if(root != NULL)
				{
					int num;
					int count_cmp = 0;
					struct tree_node_t *res = NULL;

					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
					
					unsigned long long sum = 0, del = 0;
					struct timespec t_beg, t_end;

					for (int k = 0; rc == ERR_OK && k < N_REPS; k++)
					{
						count_cmp = 0;
						clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
						res = lookup2(root, num, &count_cmp);
						clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

						del = calc_elapsed_time(&t_beg, &t_end);
						sum = sum + del;
					}
					sum = sum/N_REPS;


					printf("Время поиска: %lld\n", sum);
					printf("Количество сравнений: %d\n", count_cmp);
					if(rc == ERR_OK && res != NULL)
					{
						printf("Число найдено\n");
					}
					else
					{
						printf("Введеное число не найдено\n");
					}
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
			else if(choice == CHOICE_COUNT_NODE)
			{
				if(root != NULL)
				{
					size_t *arr = calloc(1000, sizeof(size_t));
					if(arr != NULL)
					{
						count_node(root, 0, arr);
						for(size_t i = 0; arr[i] != 0; ++i)
						{
							printf("Уровень: %ld | Количество вершин: %ld\n", i+1, arr[i]);
						}
					}
					free(arr);				
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустого дерева\n");
				}
			}
		}
		//post_order_apply(root, node_print, "%d ");
	    //printf("\n");

	    {
	        
	    }
		post_order_apply(root, node_free, NULL);
	}
    return rc;
}


char closed_table(char *file_name)
{
	char rc = ERR_OK;
    int choice = -1;
    char *menu = "0) Выйти из программы\n1) Вывести таблицу\n2) Добавить элемент в таблицу\n3) Удалить элемент из таблицы\n4) Найти элемент в таблице\n";
	closed_table_t *table = create_closed_table(file_name);
	if(table != NULL)
	{
		char is_restruct = 0;
		rc = resturct_after_create_closed(&table, &is_restruct);
		if(is_restruct == 1)
		{
			printf("Таблица была реструктуризированна после создания\n");
		}
	}
	else
	{
		rc = ERR_ALLOCATE_MEM;
	}
	if(rc == ERR_OK)
	{
		while(rc == ERR_OK && choice != CHOICE_EXIT)
		{
			printf("%s", menu);
			rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_INVALID_INPUT;
			//clean_stdin();
			if(choice == CHOICE_SHOW_TABLE)
			{
				if(table->count_elements > 0)
				{
					print_closed_table(table);
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустой таблицы\n");
				}
			}
			else if(choice == CHOICE_ADD_ELEMENT)
			{
				int num;
				rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
				if(rc == ERR_OK)
				{
					char is_restruct = 0;
					unsigned long long sum = 0;
					struct timespec t_beg, t_end;
		    
		    		clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
					rc = closed_table_insert(&table, num, 0, &is_restruct);
					clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

					sum = calc_elapsed_time(&t_beg, &t_end);
					if(rc == ERR_OK)
					{
						printf("Среднее количество сравнений: %f\n", table->avarage_count_compare);
						printf("Максимально количество сравнений: %ld\n", table->max_count_compare);
						printf("Время вставки: %lld\n", sum);
					}
					if(rc == ERR_OK && is_restruct == 1)
					{
						printf("Таблица была реструктуризированна\n");
					}
				}
			}
			else if(choice == CHOICE_DELETE_ELEMENT)
			{
				if(table->count_elements > 0)
				{
					int num;
					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
					if(rc == ERR_OK)
					{
						if(closed_table_delete(table, num))
						{
							printf("Элемент успешно удален из таблицы\n");
						}
						else
						{
							printf("Данный элемент отсутствует в таблице\n");
						}
					}	
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустой таблицы\n");
				}
			}
			else if(choice == CHOICE_FIND_ELEMENT)
			{
				if(table->count_elements > 0)
				{
					int num = 0;
					int res = 0;
					int count_cmp = 0;
					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;

					unsigned long long sum = 0, del = 0;
					struct timespec t_beg, t_end;

					for (int k = 0; rc == ERR_OK && k < N_REPS; k++)
					{
						count_cmp = 0;
						clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
						res = closed_table_find(table, num, &count_cmp);
						clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

						del = calc_elapsed_time(&t_beg, &t_end);
						sum = sum + del;
					}
					sum = sum/N_REPS;


					printf("Время поиска: %lld\n", sum);
					printf("Количество сравнений: %d\n", count_cmp);
					if(rc == ERR_OK && res == 1)
					{
						printf("Число найдено\n");
					}
					else
					{
						printf("Введеное число не найдено\n");
					}
				}
				else
				{
					printf("Нельзя выполнить данную операцию для пустой таблицы\n");
				}
			}
		}
		free_closed_table(table);
	}
	return rc;
}