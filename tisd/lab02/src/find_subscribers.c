/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/find_subscribers.h"

void find_subscribers_by_birth_day(subscribers_t *subscribers, size_t count_structs, subscribers_t *finded_subscribers, size_t *count_finded_structs)
{
	for(size_t i = 0; i < count_structs; ++i)
	{
		if((subscribers+i)->status == private && check_is_birth(subscribers+i) == ERR_OK)
		{
			*(finded_subscribers+(*count_finded_structs)) = *(subscribers+i);
			++(*count_finded_structs);
		}
	}
}

char check_is_birth(const subscribers_t *subscribers)
{
	char rc = ERR_OK;
	time_t day_current = time(NULL);
	time_t day_week = time(NULL);
	time_t day_user = time(NULL);

	
	struct tm date_week = *localtime(&day_week);;
	struct tm date_current = *localtime(&day_current);
	struct tm date_user = *localtime(&day_user);
	

	
	date_user.tm_mday = (subscribers->variate_status).private.date_birth.day;
	date_user.tm_mon = (subscribers->variate_status).private.date_birth.month - 1;
	date_user.tm_year = date_week.tm_year;

	
	date_week.tm_mday = date_week.tm_mday + ADD_DAYS;
	
	day_current = mktime(&date_current);
	day_user = mktime(&date_user);
	day_week = mktime(&date_week);
	
		
	if (difftime(day_user, day_current) < 0.0)
	{
		rc = ERR_SMALL_DATE;
	}
	else if(difftime(day_week, day_user) < 0.0)
	{
		rc = ERR_TOO_MUCH_DATE;
	}
	return rc;
}