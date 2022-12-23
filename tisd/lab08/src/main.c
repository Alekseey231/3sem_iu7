/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include <stdio.h>
#include <assert.h>
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/graph.h"
#include "../inc/dot.h"

#define CHOICE_EXIT 0
#define CHOICE_SHOW_GRAPH 1
#define CHOICE_FIND_PATH 2

int main(int argc, char **argv)
{
	char rc = ERR_OK;
	if(argc == 2)
	{
		graph_t *graph = NULL;
		rc = create_graph(argv[1], &graph);

		int choice = -1;
		char *menu = "0) Выйти из программы\n1) Показать граф\n2) Найти путь\n";
		while(rc == ERR_OK && choice != CHOICE_EXIT)
		{
			printf("%s", menu);
			rc = scanf("%d", &choice)==1 ? ERR_OK : ERR_INVALID_INPUT;
			if(choice == CHOICE_SHOW_GRAPH)
			{
				FILE *f = fopen("test.gv", "w");

		        assert(f);

		        graph_export_to_dot_saved(f, "test_graph", graph, -1);

		        fclose(f);
		        system("dot -Tpng test.gv -otest.png");
		        system("xdg-open test.png &");	
			}
			else if(choice == CHOICE_FIND_PATH)
			{
				size_t start_index = 0, last_index = 0;
				printf("Введите начальную и конечную вершины: ");
				if(scanf("%zu %zu", &start_index, &last_index) == 2)
				{
					if(start_index == last_index)
					{
						printf("Стартовая вершина совпадает с конечной\n");
					}
					else if(start_index > graph->count_edge || last_index > graph->count_edge || last_index <= 0 || start_index <= 0)
					{
						printf("Некорректный ввод вершин\n");
					}
					else
					{
						if(find_deykstra(graph, start_index, last_index))
						{
							system("convert -delay 100 -loop 0 ./dot/*.png ./dot/myimage.gif");	
							system("xdg-open ./dot/myimage.gif &");
							system("rm ./dot/*.png ./dot/*.gv");	
						}
						else
						{
							printf("Путь не найден\n");
						}

					}
				}	
			}
			//TODO проверка что путь найден
		}
		free_graph(&graph);
	}
	else
	{
		rc = ERR_INVALID_COUNT_ARG;
	}
	return rc;
}
