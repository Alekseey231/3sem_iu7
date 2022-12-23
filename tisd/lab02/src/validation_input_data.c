/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/validation_input_data.h"
#include <stdio.h>
int is_name_correct(char *name)
{
	int is_correct = 1;
	char count_defice = 0;
	for(size_t i = 0; name[i] != 0 && is_correct; ++i)
	{
		if(name[i] == '-' && count_defice < 1)
		{
			++count_defice;
		}
		else
		{
			is_correct = isalpha(name[i]);
		}
		
	}
	return (is_correct>0) ? 1 : 0;
}


char process_date(char *date, subscribers_t *subscribers)
{
	int rc = ERR_OK;
	char *part_date[COUNT_PARTS_DATE] = { 0 };
	rc = get_parts_date(date, part_date);
	if(rc == ERR_OK)
	{
		for(size_t i = 0; i < COUNT_PARTS_DATE && rc == ERR_OK; ++i)
		{
			if(is_num(part_date[i]) == 0)
			{
				rc = ERR_NOT_DIGIT_IN_DATE;
			}
		}
		if(rc == ERR_OK)
		{
			date_birth_t date_birth = { .day = atoi(part_date[0]), .month = atoi(part_date[1]), .year = atoi(part_date[2])};
			if((rc = is_day_correct(date_birth.day)) == ERR_OK && (rc = is_month_correct(date_birth.month)) == ERR_OK && (rc = is_year_correct(date_birth.year)) == ERR_OK)
			{
				int days = getDays(date_birth.month, date_birth.year);
				if(date_birth.day>days)
				{
					rc = ERR_TOO_MUCH_DAY;
				}
				else
				{
					(subscribers->variate_status).private.date_birth = date_birth;
				}	
			}
		}
	}
	return rc;
}

char get_parts_date(char *date, char **part_date)
{
    int rc = ERR_OK;
    size_t len_date = strlen(date);
	char *sep = ".";
	size_t count_parts = 1;
	part_date[0] = strtok(date, sep);
	while(count_parts < 3 && part_date[count_parts-1] != NULL)
	{
		part_date[count_parts] = strtok(NULL,sep);
		++count_parts;
	}
	if((count_parts < 3 || part_date[count_parts-1] == NULL) || len_date != (strlen(part_date[0])+strlen(part_date[1])+strlen(part_date[2])+2))
	{
		rc = ERR_INCORRECT_DATE;
	}
	return rc;
}

int is_num(char *num)
{
	int is_correct = 1;
	for(size_t i = 0; num[i] != 0 && is_correct; ++i)
	{
		is_correct = isdigit(num[i]);
	}
	return (is_correct>0) ? 1 : 0;
}

char is_day_correct(int day)
{
	char rc = ERR_OK;
	if(day < 1)
	{
		rc = ERR_NEGATIVE_DAY;
	}
	else if(day > 31)
	{
		rc = ERR_TOO_MUCH_DAY;
	}
	return rc;
}

char is_month_correct(int month)
{
	char rc = ERR_OK;
	if(month < 1)
	{
		rc = ERR_NEGATIVE_MONTH;
	}
	else if(month > 12)
	{
		rc = ERR_TOO_MUCH_MONTH;
	}
	return rc;
}

char is_year_correct(int year)
{
	char rc = ERR_OK;
	if(year < 1900)
	{
		rc = ERR_NEGATIVE_YEAR;
	}
	else if(year > 9999)
	{
		rc = ERR_TOO_MUCH_YEAR;
	}
	return rc;
}

int getDays(int month, int year)
{
	int days;
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		days = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		days = 30;
		break;
	case 2:
		days = 28;
	   	if((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0))
	   	{
	   		days = 29;
	   	}
	   	break;
	default:
	    days = -1;
	}
	return days;
}
