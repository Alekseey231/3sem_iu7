/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/task.h"

task_t *create_task()
{
	task_t *task = malloc(sizeof(task_t));
	if(task != NULL)
	{
		task->time_until_end_process = 1;
		task->count_cycles_complete = 0;
	}
	return task;
}

void delete_task(task_t *task)
{
	free(task);
}

void print_task(task_t *task)
{
	printf("Цикл в очереди: %ld Время до конца обработки: %f\n", task->count_cycles_complete, task->time_until_end_process);
}