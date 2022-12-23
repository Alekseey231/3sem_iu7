/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/table_keys.h"

void print_sturct_by_keys(subscribers_t *subscribers, size_t count_structs, keys_t *keys)
{
	for(size_t i = 0; i < count_structs; ++i)
	{
		print_entry(subscribers + ((keys+i)->original_index));
	}
}

void create_keys(subscribers_t *subscribers, size_t count_structs, keys_t *keys)
{
	for(size_t i = 0; i < count_structs; ++i)
		save_key((keys+i), (subscribers+i), i);
}

void save_key(keys_t *key, subscribers_t *subscribers, size_t index)
{
	key->original_index = index;
	memcpy(key->firstname, subscribers->firstname, sizeof(subscribers->firstname));
}


void print_keys(keys_t *keys, size_t count_structs)
{
	for(size_t i = 0; i < count_structs; ++i)
	{
		printf("%ld %s\n", (keys+i)->original_index, (keys+i)->firstname);
	}
}

char realloc_mem_keys(keys_t **key, size_t *start_count_struct)
{
	char rc = ERR_OK;
	*start_count_struct = (*start_count_struct) * 2;
	keys_t *pbuf = realloc(*key, *start_count_struct * sizeof(keys_t));
	if(pbuf != NULL)
	{
		(*key) = pbuf;
	}
	else
	{
		rc = ERR_ALLOCATE_MEM;
	}
	return rc;
}