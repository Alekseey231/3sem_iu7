#ifndef _PROCESS_QUEUE_H_

#define _PROCESS_QUEUE_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

float generate_time(float t1, float t2);
char process_queue_list(float t1_low_bound, float t1_high_bound, float t2_low_bound, float t2_high_bound);
char process_queue_array(float t1_low_bound, float t1_high_bound, float t2_low_bound, float t2_high_bound);

#endif

