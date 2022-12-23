#include "input_long.h"

int input_long(char *str, size_t len_str, size_t max_len)
{
    int rc = ERR_OK;
    if (fgets(str, len_str, stdin) == NULL)
    {
        rc = ERR_READ_STR;
    }
    else
    {
        if (isspace(str[strlen(str) - 1]))
            str[strlen(str) - 1] = 0;
        if (strlen(str) > max_len)
            rc = ERR_NUMBER_TOO_LONG;
        else if (strlen(str) == 0)
            rc = ERR_EMPTY_STR;
    }
    return rc;
}