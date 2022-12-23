/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */


#include "../inc/io.h"

char get_num(FILE *f, int *num)
{
    char rc = ERR_OK;
    char *line = NULL;
    size_t line_alloc = 0;

    rc = get_line(f, &line, &line_alloc);
    if (rc == ERR_OK)
    {
        char *endptr;
        *num = strtol(line, &endptr, 10);
        if (*endptr != 0)
            rc = ERR_READ_VOLUME;
    }

    free(line);
    return rc;
}

char set_expression_stack(stack_list_t s, stack_array_t a, int count_num)
{
    char rc = ERR_OK;
    int nums[3];
    rc = get_nums(count_num, nums, NULL, NULL);

    for(size_t i = 0; rc == ERR_OK && i < (size_t)count_num; ++i)
    {
        if(a == NULL)
        {
            rc = push_stack_list(s, nums[i]);
            is_adress_in(get_top(s));            
        }
        else
        {
            rc = push_stack_array(a, nums[i]);
        }

    }
    return rc;
}

char get_nums(int count, int *nums, stack_list_t stack_list, stack_array_t stack_array)
{
    char rc = ERR_OK;
    char *line = NULL;
    size_t line_alloc = 0;

    rc = get_line(stdin, &line, &line_alloc);
    if (rc == ERR_OK)
    {
        rc = parse_nums_from_string(line, nums, count, stack_list, stack_array);     
    }
   

    free(line);
    return rc;
}

char parse_nums_from_string(char *line, int *nums, int count, stack_list_t s, stack_array_t stack_array)
{
    char rc = ERR_OK;
    int count_parse = 0;
    char *endptr;
    char *lastptr = 0;
    errno = 0;

    long int num = strtol(line, &endptr, 10);

    if(nums == NULL)
    {
        count = INT_MAX-1;
    }

    if(endptr == line)
    {
        rc = ERR_READ_VOLUME;
    }

    while(!(CHECK_ERRNO(errno, num)) && endptr - lastptr && count_parse <= count && rc == ERR_OK)
    {
        if(nums == NULL)
        {
            if(stack_array == NULL)
            {
                rc = push_stack_list(s, num);
                is_adress_in(get_top(s));                
            }
            else
            {
                rc = push_stack_array(stack_array, num);
            }

        }
        else
        {
            nums[count_parse] = num;
        }
        
        ++count_parse;
        lastptr = endptr;
        num = strtol(endptr, &endptr, 10);
    }

    if(nums == NULL)
    {
        count = count_parse;
    }

    if(CHECK_ERRNO(errno, num) || endptr != line+strlen(line) || count_parse != count)
    {
        rc = ERR_READ_VOLUME;
    }

    return rc;
}



char get_line(FILE *f, char **line, size_t *line_alloc)
{
    char rc = ERR_OK;
    if (getline(line, line_alloc, f) != -1)
    {
        if ((*line)[strlen(*line) - 1] == '\n')
        {
            (*line)[strlen(*line) - 1] = 0;
        }
        if (strlen(*line) == 0)
        {
            rc = ERR_READ_EMPTY_STR;
        }
    }
    else if (feof(f))
    {
        rc = ERR_EOF;
    }
    else
    {
        rc = ERR_GET_LINE;
    }
    return rc;
}
