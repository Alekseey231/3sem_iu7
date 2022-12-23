#include "long_int_process.h"
#include "input_long.h"
#include "long_float_process.h"

int process_long_int(long_int *num)
{
    int rc = ERR_OK;
    char str[MAX_LEN_INT + 2] = { 0 };
    rc = input_long(str, sizeof(str), MAX_LEN_INT);
    if (rc == ERR_OK)
    {
        rc = validate_int(str);
        if (rc == ERR_OK)
        {
            save_int(num, str, strlen(str));
            delete_zeros_int(num);
        }
    }
    return rc;
}

int validate_int(char *str)
{
    int rc = ERR_OK;
    char is_sign = (str[0] == '-') + (str[0] == '+');
    if (is_sign == 1 || isdigit(str[0]))
    {
        size_t i = 1;
        for (; i < strlen(str) && isdigit(str[i]); ++i);
        rc = (strlen(str) == i ? ERR_OK : ERR_INCORRECT_INT);
        if (rc == ERR_OK && is_sign == 1 && strlen(str) == 1)
            rc = ERR_INCORRECT_INT;
    }
    else
        rc = ERR_INCORRECT_INT;
    return rc;
}

void save_int(long_int *num, char *str, size_t len_str)
{
    size_t index = 0;

    num->sign = check_sign(str[0], &index);
    num->count_digit = len_str - index;

    for (size_t i = 0; index < len_str; ++index, ++i)
    {
         // '0' находится перед '1', таким образом разность дает нужное число
        (num->digits)[i] = (int)(str[index] - '0');
    }
}

void print_int(long_int *num)
{
    if (num->sign == -1)
        printf("-");

    for (size_t index = 0; index < (size_t)(num->count_digit); ++index)
    {
        printf("%d", (num->digits)[index]);
    }
    printf("\n");
}

void delete_zeros_int(long_int *num_int)
{
    for (size_t i = 0; i < (size_t)(num_int->count_digit) && (num_int->digits)[i] == 0;)
    {
        // удаление i-го элемента
        for (size_t j = i; j < (size_t)(num_int->count_digit) - 1; ++j)
            (num_int->digits)[j] = (num_int->digits)[j + 1];
        //уменьшение количества цифр числа и уменьшение порядка
        num_int->count_digit -= 1;
    }

    // если число состояло из одних нулей 

    if (num_int->count_digit == 0)
    {
        (num_int->digits)[0] = 0;
        num_int->count_digit += 1;
    }
}