/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/statistic.h"

stat_t *create_stat()
{
	stat_t *stat = malloc(sizeof(stat_t));
	if(stat != NULL)
	{
		stat->count_in = 0;
		stat->count_out = 0;
		stat->count_app_trigger = 0;
	}
	return stat;
}

void delete_stat(stat_t *stat)
{
	free(stat);
}