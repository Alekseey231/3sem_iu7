#ifndef __FIND_SUBSCRIBERS_H__

#define __FIND_SUBSCRIBERS_H__

#include <time.h>
#include "../inc/subscribers.h"
#define ADD_DAYS 7
#define ERR_SMALL_DATE 34
#define ERR_TOO_MUCH_DATE 35
#define ERR_OK 0

void find_subscribers_by_birth_day(subscribers_t *subscribers, size_t count_structs, subscribers_t *finded_subscribers, size_t *count_finded_structs);
char check_is_birth(const subscribers_t *subscribers);

#endif //#ifndef __FIND_SUBSCRIBERS_H__
