/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/sort_table.h"

void bubble_sort(void *base, size_t nmemd, size_t size, int (*compar)(const void *, const void *))
{
    if (nmemd != 0)
    {
        for (size_t i = 0; i < nmemd - 1; ++i)
        {
            for (size_t j = 0; j < nmemd - i - 1; ++j)
            {
                void *obj1 = (char *)base + j * size;
                void *obj2 = (char *)base + (j + 1) * size;
                if (compar(obj1, obj2) > 0)
                {
                    swap(obj1, obj2, size);
                }
            }
        }
    }
}


void insertion_sort(void *base, size_t nmemd, size_t size, int (*compar)(const void *, const void *))
{
    if (nmemd != 0)
    {
        void* buf = malloc(size);
        for (size_t i = 1; buf != NULL && i < nmemd; ++i)
        {
            void *key = (char *)base + i * size;
            memcpy(buf, key, size);
            int j = i-1;
            void *obj1 = (char *)base + j * size;
            void *obj2 = (char *)base + (j + 1) * size;
            while(j>=0 && compar(obj1, buf)>0)
            {
                memcpy(obj2, obj1, size);
                --j;
                obj1 = (char *)base + j * size;
                obj2 = (char *)base + (j + 1) * size;
            }
            memcpy(obj2, buf, size);
            free(buf);
        }
        free(buf);
        buf = NULL;
    }
}


void swap(void *obj1, void *obj2, size_t size)
{
    char *buffer = malloc(size);
    if (buffer != NULL)
    {
        memcpy(buffer, obj1, size);
        memcpy(obj1, obj2, size);
        memcpy(obj2, buffer, size);
    }
    // TODO проверка успеха выделения памяти
    free(buffer);
}

int comparator_subscribers(const void *a, const void *b)
{
    const subscribers_t *sub1 = a;
    const subscribers_t *sub2 = b;
    return strcmp(sub1->firstname, sub2->firstname);
}


int comparator_keys(const void *a, const void *b)
{
    const keys_t *sub1 = a;
    const keys_t *sub2 = b;
    return strcmp(sub1->firstname, sub2->firstname);
}

/*
int comparator(const void *a, const void *b)
{
    const char *lastname1 = a;
    const char *lastname2 = b;
    return strcmp(lastname1, lastname2);
}*/

