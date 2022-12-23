#include "errors.h"
#include "long_float_process.h"
#include "long_int_process.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_LEN 60

int multiplication(long_float *num_float, long_int *num_int, long_float *result);
void num_round(long_float *result);
void remove_overflow(long_float *result, size_t i);


int main()
{
    int rc = ERR_OK;
    long_int num_int = { .digits = { 0 } };
    long_float num_float = { .digits = { 0 }, .exp = 0 };
    long_float max_num_float = { .digits = { 0 }, .exp = 0 };
    printf("Введите целое число длиной до 30 десятичных цифр: \n");
    printf("------------------------------\n");
    rc = process_long_int(&num_int);
    if (rc == ERR_OK)
    {
        printf("Введенное целое число: ");
        print_int(&num_int);
        printf("Введите действительное число в формте +-m.nE+-K, где суммарная длина мантисы (m+n) \nдо 30 десятичных "
               "цифр, а величина порядка K - до 5 цифр: \n");
        printf("----|----|----|----|----|----|----|\n");
        rc = process_long_float(&num_float);
        if (rc == ERR_OK)
        {
            printf("Введенное действительное число: ");
            print_float(&num_float);
            rc = multiplication(&num_float, &num_int, &max_num_float);
            if(rc == ERR_OK)
            {
            printf("Результат умножения: ");
            print_float(&max_num_float);
            }
        }
    }
    if (rc != ERR_OK)
        process_error(rc);
    return rc;
}

int multiplication(long_float *num_float, long_int *num_int, long_float *result)
{
    int rc = ERR_OK;
    result->sign = num_float->sign * num_int->sign;
    result->exp = num_float->exp + num_int->count_digit;
    result->count_digit = num_int->count_digit + num_float->count_digit;
    for (size_t i = 0; i < (size_t)(num_float->count_digit); ++i)
        for (size_t j = 0; j < (size_t)(num_int->count_digit); ++j)
            (result->digits)[i + j + 1] += (num_float->digits)[i] * (num_int->digits)[j];

    // проверка переполнения

    for (size_t i = (size_t)(result->count_digit - 1); i > 0; --i)
    {
        remove_overflow(result, i);
    }

    // проверка, что число не 0

    char is_null = 0;
    for (size_t i = 0; i < (size_t)(result->count_digit) && is_null == 0; ++i)
        if ((result->digits)[i] != 0)
            is_null = 1;

    // удаляем лишние нули с правой и левой стороны

    delete_zeros_left(result);
    delete_zeros_right(result);

    // если получился 0

    if (is_null == 0)
    {
        result->exp = 0;
    }
    else
    {
        if (result->count_digit > 30)
        {
            num_round(result);

            delete_zeros_left(result);
            delete_zeros_right(result);
        }
        if (result->exp > 99999 || result->exp < -99999)
        {
            rc = ERR_OVERFLOW_DIGIT;
        }
    }
    return rc;
}

// удаление переполнения в разряде

void remove_overflow(long_float *result, size_t i)
{
    (result->digits)[i - 1] += (result->digits)[i] / 10;
    (result->digits)[i] %= 10;
}

void num_round(long_float *result)
{

    if ((result->digits)[MAX_LEN_MANTISSA] > 5)
        (result->digits)[MAX_LEN_MANTISSA - 1] += 1;

    (result->count_digit) = MAX_LEN_MANTISSA;

    for (size_t i = MAX_LEN_MANTISSA - 1; i > 0; --i)
    {
        if ((result->digits)[i] > 9)
        {
            remove_overflow(result, i);
        }
    }

    if ((result->digits)[1] > 9)
    {
        for (size_t i = MAX_LEN_MANTISSA; i > 0; --i)
        {
            (result->digits)[i + 1] = (result->digits)[i];
        }
        (result->digits)[1] = (result->digits)[0];
        // после сдвига заполняем старший разряд
        remove_overflow(result, 1);
    }
}

