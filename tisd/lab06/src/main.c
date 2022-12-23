/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <assert.h>
#include <stdio.h>
#include "../inc/tree.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/effective.h"

void clean_stdin();
char add_node_to_file(struct tree_node_t *node, char *file_name);

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

int main(int argc, char **argv)
{
	char rc = ERR_OK;
    struct tree_node_t *root = NULL;
    int choice = -1;
    char *menu = "0) Выйти из программы\n1) Добавить узел в дерево\n2) Найти узел в дерева\n3) Префиксный обход дерева\n"
    			"4) Инфиксный обход дерефа\n5) Постфиксный обход дерева\n6) Показать дерево\n7) Удалить узел из дерева\n"
    			"8) Вывести количество узлов на каждом уровне\n9) Замер эффективности\n";
    if(argc == 2)
    {
    	rc = get_all_nums(argv[1], &root);
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
					rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
					if(lookup2(root, num) != NULL)
					{
						printf("Такое число уже есть в дереве\n");
					}
					else
					{
						struct tree_node_t *node = node_create(num);

						unsigned long long sum = 0;
						struct timespec t_beg, t_end;

						if(node != NULL)
						{
							clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
							root = btree_insert(root, node);
							clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
							sum = calc_elapsed_time_1(&t_beg, &t_end);
							printf("Время вставки: %lld\n", sum);
						}
						else
						{
							rc = ERR_ALLOCATE_MEM;
						}
						if(rc == ERR_OK)
						{
							//unsigned long long sum = 0;
							//struct timespec t_beg, t_end;
							//clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
							rc = add_node_to_file(node, argv[1]);
							//clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
							//sum = calc_elapsed_time_1(&t_beg, &t_end);
							//printf("Время вставки в файл: %lld\n", sum);
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
							unsigned long long sum = 0;
							struct timespec t_beg, t_end;
							clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
							root = btree_delete(root, num);
							clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
							sum = calc_elapsed_time_1(&t_beg, &t_end);
							printf("Время удаления: %lld\n", sum);
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
						rc = scanf("%d", &num) == 1 ? ERR_OK : ERR_INVALID_INPUT;
						if(rc == ERR_OK && lookup2(root, num) != NULL)
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
				else if(choice == CHOICE_EFFECTIVE)
				{
					rc = effective();
				}
			}
			//post_order_apply(root, node_print, "%d ");
		    //printf("\n");

		    {
		        
		    }
			post_order_apply(root, node_free, NULL);
		}
    }
    else
    {
    	rc = ERR_INVALID_INPUT;
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