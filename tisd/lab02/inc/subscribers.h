#ifndef __SUBSCRIBERS_H__

#define __SUBSCRIBERS_H__

#define MAX_FIRSTNAME_LEN 20 + 1
#define MAX_LASTNAME_LEN 20 + 1
#define LEN_PHONE_NUMBER 11 + 1
#define LEN_PHONE_NUMBER_CORRECT 10
#define MAX_LEN_ADRESS 60 + 1
#define MAX_LEN_JOB_TITLE 20 + 1
#define MAX_LEN_ORGANIZATION 35 + 1

#include <stddef.h>

typedef enum
{
  	private = 0,
    offical = 1
} status_t;

typedef struct
{
    unsigned short int day;
    unsigned short int month;
    unsigned short int year;
} date_birth_t;

typedef struct
{
    date_birth_t date_birth;
} private_t;

typedef struct
{
    char job_title[MAX_LEN_JOB_TITLE + 1];
    char organization[MAX_LEN_ORGANIZATION + 1];
} offical_t;

// firstname - фамилия

typedef struct
{
    char firstname[MAX_FIRSTNAME_LEN + 1];
    char lastname[MAX_LASTNAME_LEN + 1];
    char phone_number[LEN_PHONE_NUMBER + 1];
    char adress[MAX_LEN_ADRESS + 1];
    status_t status;
    union {
        private_t private;
        offical_t offical;
    } variate_status;

} subscribers_t;

typedef struct
{
    size_t original_index;
    char firstname[MAX_FIRSTNAME_LEN + 1];
} keys_t;

#endif //#ifndef __SUBSCRIBERS_H__
