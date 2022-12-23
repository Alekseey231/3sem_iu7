#ifndef _TASK_H_

#define _TASK_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct task_t
{
	size_t count_cycles_complete;
	float time_until_end_process;
} task_t;

void delete_task(task_t *task);
task_t *create_task();
void print_task(task_t *task);

#endif