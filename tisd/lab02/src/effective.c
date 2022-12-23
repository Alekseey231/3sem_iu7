/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/effective.h"

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)) / 1000; 
}


char effective(subscribers_t *subscribers, size_t count_structs)
{
	char rc = ERR_OK;
	subscribers_t *test_subscribers = malloc(count_structs * sizeof(subscribers_t));


	struct timespec t_beg, t_end;

	unsigned long long del, sum = 0, max = 0, min = (unsigned long long) -1;

	srand(time(NULL));

    int volume = count_structs * sizeof(subscribers_t);
    printf("| Type sort      |  All time  |  Volume  |\n");
	memcpy(test_subscribers, subscribers, count_structs * sizeof(subscribers_t));

	for (int i = 0; i < N_REPS; i++)
    {
        memcpy(test_subscribers, subscribers, count_structs * sizeof(subscribers_t));

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        qsort(test_subscribers, count_structs, sizeof(subscribers_t), comparator_subscribers);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
        
        del = calc_elapsed_time(&t_beg, &t_end);
    
        sum = sum + del;
        
        if (del > max)
            max = del;
        
        if (del < min)
            min = del;
    }
    
    printf("| qsort          |  %-8g  |  %-6d  |\n", (double) (sum)/ N_REPS, volume);


    del = 0;
    sum = 0;
    max = 0;
    min = (unsigned long long) -1;

    srand(time(NULL));

    keys_t *keys = malloc(count_structs * sizeof(keys_t));
    int volume1 = count_structs * sizeof(subscribers_t) + count_structs * sizeof(keys_t);
    create_keys(subscribers, count_structs, keys);


    for (int i = 0; i < N_REPS; i++)
    {

        create_keys(subscribers, count_structs, keys);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        qsort(keys, count_structs, sizeof(keys_t), comparator_keys);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
        
        del = calc_elapsed_time(&t_beg, &t_end);
    
        sum = sum + del;
        
        if (del > max)
            max = del;
        
        if (del < min)
            min = del;
    }
    
    printf("| qsort keys     |  %-8g  |  %-6d  |\n", (double) (sum)/ N_REPS, volume1);
    del = 0;
    sum = 0;
    max = 0;
    min = (unsigned long long) -1;

    srand(time(NULL));

    memcpy(test_subscribers, subscribers, count_structs * sizeof(subscribers_t));

    for (int i = 0; i < N_REPS; i++)
    {
        memcpy(test_subscribers, subscribers, count_structs * sizeof(subscribers_t));

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        bubble_sort(test_subscribers, count_structs, sizeof(subscribers_t), comparator_subscribers);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
        
        del = calc_elapsed_time(&t_beg, &t_end);
    
        sum = sum + del;
        
        if (del > max)
            max = del;
        
        if (del < min)
            min = del;
    }

    printf("| bubble         |  %-8g  |  %-6d  |\n", (double) (sum)/ N_REPS, volume);

    del = 0;
    sum = 0;
    max = 0;
    min = (unsigned long long) -1;

    srand(time(NULL));

    create_keys(subscribers, count_structs, keys);


    for (int i = 0; i < N_REPS; i++)
    {
        create_keys(subscribers, count_structs, keys);

        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        bubble_sort(keys, count_structs, sizeof(keys_t), comparator_keys);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
        
        del = calc_elapsed_time(&t_beg, &t_end);
    
        sum = sum + del;
        
        if (del > max)
            max = del;
        
        if (del < min)
            min = del;
    }
    
    printf("| bubble keys    |  %-8g  |  %-6d  |\n", (double) (sum)/ N_REPS, volume1);



	free(test_subscribers);
    free(keys);
	return rc;
}

