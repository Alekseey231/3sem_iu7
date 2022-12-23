/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/print_struct.h"

void print_sturcts(subscribers_t *subscribers, size_t count_structs)
{
	printf("| Фамилия              | Имя                  | Номер тел. | Адрес                                                        | Статус | Дата рождения/служебная информация\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for(size_t i = 0; i < count_structs; ++i)
	{
		print_entry(subscribers+i);
	}
}


void print_entry(subscribers_t *subscribers)
{
	printf("| %-20s | %-20s | %-10s | %-60s |", subscribers->firstname, subscribers->lastname, subscribers->phone_number, subscribers->adress);
	if(subscribers->status == 0)
	{
		printf("private ");
		printf("| %49d.%d.%d  |\n", (subscribers->variate_status).private.date_birth.day, (subscribers->variate_status).private.date_birth.month,
		 (subscribers->variate_status).private.date_birth.year);
	}
	else
	{
		printf("offical ");
		printf("| %-20s | %-35s |\n", (subscribers->variate_status).offical.job_title, (subscribers->variate_status).offical.organization);
	}
}



/*void print_entry(subscribers_t *subscribers)
{
	printf("%s %s %s %s ", subscribers->firstname, subscribers->lastname, subscribers->phone_number, subscribers->adress);
	if(subscribers->status == 0)
	{
		printf("private ");
		printf("%d.%d.%d\n", (subscribers->variate_status).private.date_birth.day, (subscribers->variate_status).private.date_birth.month,
		 (subscribers->variate_status).private.date_birth.year);
	}
	else
	{
		printf("offical ");
		printf("%s  %s\n", (subscribers->variate_status).offical.job_title, (subscribers->variate_status).offical.organization);
	}
}
*/