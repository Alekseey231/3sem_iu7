/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/queue_list.h"
#include "../inc/queue_array.h"
#include "../inc/errors.h"
#include "../inc/statistic.h"
#include "../inc/process_queue.h"
#include <math.h>
#include <time.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

char process_queue_list(float t1_low_bound, float t1_high_bound, float t2_low_bound, float t2_high_bound)
{
	char rc = ERR_OK;
	queue_list_t queue_list = create_queue_list();
	stat_t *stat = create_stat();
	task_t *current_task = NULL;
	task_t *new_task = NULL;


	srand(time(NULL));
	float t_waiting_get_task = generate_time(t1_low_bound, t1_high_bound); // время до прихода новой заявки
	float t_sum_app_downtime = 0; // время простоя аппарата
	float t_app_process_task = 0; // время обработки аппаратом текущей заявки
	float t_sum_process_queue = 0; // суммарное время обработки очереди
	float t_waiting_next_action = 0; // время до следующего тика
	//printf("%ld %ld %ld %ld", t1_low_bound, t1_high_bound, t2_low_bound, t2_high_bound);
	char is_show = 0;
	int count_iter = 0;
	int sum_queue_length = 0;
	printf("| Количество вышедних заявок | Текущая длина очереди | Средняя длина очереди |\n");
	printf("+----------------------------+-----------------------+-----------------------+\n");
	while(rc == ERR_OK && stat->count_out != 1000)
	{
		if(current_task != NULL && current_task->time_until_end_process <= 0)
		{
			++(current_task->count_cycles_complete);
			current_task->time_until_end_process = 0;
			if(current_task->count_cycles_complete == 5)
			{
				++(stat->count_out);
				delete_task(current_task);
			}
			else
			{	
				push_queue_list(queue_list, current_task);
			}
			current_task = NULL;
		}

		if(t_waiting_get_task <= 0)
		{
			new_task = create_task();
			rc = push_queue_list(queue_list, new_task);
			t_waiting_get_task = generate_time(t1_low_bound, t1_high_bound);
			++(stat->count_in);
			new_task = NULL;
		}
		sum_queue_length += get_length_queue_list(queue_list);
		++count_iter;
		if(t_app_process_task <= 0)
		{
			if(get_length_queue_list(queue_list) == 0)
			{
				t_sum_app_downtime+=t_waiting_get_task;
			}
			else
			{
				rc = pop_queue_list(queue_list, &current_task);
				t_app_process_task = generate_time(t2_low_bound, t2_high_bound);
				current_task->time_until_end_process = t_app_process_task;
				t_sum_process_queue += t_app_process_task;
				++(stat->count_app_trigger);
			}
		}
		if(current_task != NULL)
		{
			t_waiting_next_action = MIN(t_app_process_task, t_waiting_get_task);
		}
		else
		{
			t_waiting_next_action = t_waiting_get_task;
		}
		t_app_process_task -= t_waiting_next_action;
		t_waiting_get_task -= t_waiting_next_action;
		if(current_task != NULL)
		{
			current_task->time_until_end_process -= t_waiting_next_action;
		}
		if(stat->count_out % 100 == 1)
		{
			is_show = 1;
		}
		if(stat->count_out != 0 && stat->count_out % 100 == 0 && is_show == 1)
		{
			printf("| %26ld | %21ld | ", stat->count_out, get_length_queue_list(queue_list));
			if(count_iter != 0)
				printf("%21d |\n", sum_queue_length/count_iter);
			is_show = 0;
			count_iter = 0;
			sum_queue_length = 0;
		}
	}

	printf("Общее время моделирования:  %f\n", t_sum_process_queue+t_sum_app_downtime);
	printf("Общее время работы:  %f\n", t_sum_process_queue);
	printf("Время простоя машины:  %f\n", t_sum_app_downtime);
	printf("Количество вошедших заявок:  %ld\n", stat->count_in);
	printf("Количество вышедних заявок:  %ld\n", stat->count_out);
	printf("Аппарат сработал:  %ld\n", stat->count_app_trigger);

	float count_get_task = (t_sum_process_queue+t_sum_app_downtime)/((t1_high_bound - t1_low_bound)/2);
	//printf("%f\n", count_get_task);
	printf("Погрешность количества вошедших заявок: %f процентов\n", 100*fabs((stat->count_in-count_get_task))/count_get_task);
	float time_model = (stat->count_app_trigger*(t2_high_bound - t2_low_bound)/2) + t_sum_app_downtime;
	//printf("%f\n", time_model);
	printf("Погрешность работы системы по входу: %f процентов\n", 100*fabs((t_sum_process_queue+t_sum_app_downtime-time_model))/time_model);

	delete_stat(stat);	
	if(current_task != NULL)
		delete_task(current_task);

	destroy_queue_list(queue_list);
	return rc;
}

float generate_time(float t1, float t2)
{
	
	float t = (float) (float)rand() / (float)((unsigned)RAND_MAX + 1);
	return (t2 - t1)*t+t1;
}


char process_queue_array(float t1_low_bound, float t1_high_bound, float t2_low_bound, float t2_high_bound)
{
	char rc = ERR_OK;
	queue_array_t queue_array = create_queue_array();
	stat_t *stat = create_stat();
	task_t *current_task = NULL;
	task_t *new_task = NULL;


	srand(time(NULL));
	float t_waiting_get_task = generate_time(t1_low_bound, t1_high_bound); // время до прихода новой заявки
	float t_sum_app_downtime = 0; // время простоя аппарата
	float t_app_process_task = 0; // время обработки аппаратом текущей заявки
	float t_sum_process_queue = 0; // суммарное время обработки очереди
	float t_waiting_next_action = 0; // время до следующего тика
	//printf("%ld %ld %ld %ld", t1_low_bound, t1_high_bound, t2_low_bound, t2_high_bound);
	char is_show = 0;
	int count_iter = 0;
	int sum_queue_length = 0;
	printf("| Количество вышедних заявок | Текущая длина очереди | Средняя длина очереди |\n");
	printf("+----------------------------+-----------------------+-----------------------+\n");
	while(rc == ERR_OK && stat->count_out != 1000)
	{
		if(current_task != NULL && current_task->time_until_end_process <= 0)
		{
			++(current_task->count_cycles_complete);
			current_task->time_until_end_process = 0;
			if(current_task->count_cycles_complete == 5)
			{
				++(stat->count_out);
				delete_task(current_task);
			}
			else
			{	
				push_queue_array(queue_array, current_task);
			}
			current_task = NULL;
		}

		if(t_waiting_get_task <= 0)
		{
			new_task = create_task();
			rc = push_queue_array(queue_array, new_task);
			t_waiting_get_task = generate_time(t1_low_bound, t1_high_bound);
			++(stat->count_in);
			new_task = NULL;
		}
		sum_queue_length += get_length_queue_array(queue_array);
		++count_iter;
		if(t_app_process_task <= 0)
		{
			if(get_length_queue_array(queue_array) == 0)
			{
				t_sum_app_downtime+=t_waiting_get_task;
			}
			else
			{
				rc = pop_queue_array(queue_array, &current_task);
				t_app_process_task = generate_time(t2_low_bound, t2_high_bound);
				current_task->time_until_end_process = t_app_process_task;
				t_sum_process_queue += t_app_process_task;
				++(stat->count_app_trigger);
			}
		}
		if(current_task != NULL)
		{
			t_waiting_next_action = MIN(t_app_process_task, t_waiting_get_task);
		}
		else
		{
			t_waiting_next_action = t_waiting_get_task;
		}
		t_app_process_task -= t_waiting_next_action;
		t_waiting_get_task -= t_waiting_next_action;
		if(current_task != NULL)
		{
			current_task->time_until_end_process -= t_waiting_next_action;
		}
		if(stat->count_out % 100 == 1)
		{
			is_show = 1;
		}
		if(stat->count_out != 0 && stat->count_out % 100 == 0 && is_show == 1)
		{
			printf("| %26ld | %21d | ", stat->count_out, get_length_queue_array(queue_array));
			if(count_iter != 0)
				printf("%21d |\n", sum_queue_length/count_iter);
			is_show = 0;
			count_iter = 0;
			sum_queue_length = 0;
		}
	}

	printf("Общее время моделирования:  %f\n", t_sum_process_queue+t_sum_app_downtime);
	printf("Общее время работы:  %f\n", t_sum_process_queue);
	printf("Время простоя машины:  %f\n", t_sum_app_downtime);
	printf("Количество вошедших заявок:  %ld\n", stat->count_in);
	printf("Количество вышедних заявок:  %ld\n", stat->count_out);
	printf("Аппарат сработал:  %ld\n", stat->count_app_trigger);

	float count_get_task = (t_sum_process_queue+t_sum_app_downtime)/((t1_high_bound - t1_low_bound)/2);
	//printf("%f\n", count_get_task);
	printf("Погрешность количества вошедших заявок: %f процентов\n", 100*fabs((stat->count_in-count_get_task))/count_get_task);
	float time_model = (stat->count_app_trigger*(t2_high_bound - t2_low_bound)/2) + t_sum_app_downtime;
	//printf("%f\n", time_model);
	printf("Погрешность работы системы по входу: %f процентов\n", 100*fabs((t_sum_process_queue+t_sum_app_downtime-time_model))/time_model);

	delete_stat(stat);	
	if(current_task != NULL)
		delete_task(current_task);

	destroy_queue_array(queue_array);
	return rc;
}
/*

if(queue_list)
	{
		task_t *task = create_task(2);
		rc = push_queue_list(queue_list, task);
		task = create_task(5);
		rc = push_queue_list(queue_list, task);
		task = create_task(7);
		rc = push_queue_list(queue_list, task);
		if(rc == ERR_OK)
		{
			print_queue_list(queue_list);
			rc = pop_queue_list(queue_list, &task);
			delete_task(task);
			print_queue_list(queue_list);
		}
	}
*/