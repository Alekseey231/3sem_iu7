#include "long_float_process.h"
#include "input_long.h"

int process_long_float(long_float *num)
{
    int rc = ERR_OK;
    char str[MAX_LEN_FLOAT + 2] = { 0 };
    char buf[MAX_LEN_FLOAT + 1] = { 0 };
    rc = input_long(str, sizeof(str), MAX_LEN_FLOAT);
    if (rc == ERR_OK)
    {
        if (validate_float(str, buf))
        {
            rc = save_float(num, buf);
        }
        else
        {
            rc = ERR_INCORRECT_FLOAT;
        }
    }
    return rc;
}

int save_float(long_float *num, char *buf)
{
    int rc = ERR_OK;
    size_t index = 0, len_str = strlen(buf);
    char is_point = 0, is_exp = 0, is_start_zero = 0;
    int count_del_zero_digit = 0;
    short int count_digit_before_point = 0, sum_with_exp = 0;

    num->sign = check_sign(buf[0], &index);

    for (size_t i = index; i < len_str && is_exp == 0 && (num->count_digit) <= 30; ++i)
    {
        // если встретилась цифра до точки
        if (isdigit(buf[i]) && is_point == 0)
        {
            // если это не незначащий ноль
            if (i != 0 || buf[i] != '0')
            {
                (num->digits)[(num->count_digit)] = buf[i] - '0';
                ++count_digit_before_point;
                ++(num->count_digit);
            }
        }
        else if (buf[i] == '.')
        {
            // если встретилась точка, устанавливаем флаг точки и флаг для последующей проверки значащих нулей в начале числа (120.00005)
            is_point = 1;
            is_start_zero = 1;
            // если до точки была хотя бы одна цифра, не равная нулю - добавляем ее к переменной, которая в последствии будет прибавлена к экспоненте(при нормализации)
            if ((count_digit_before_point == 1 && buf[i - 1] != 0) || count_digit_before_point > 1)
            {
                sum_with_exp += count_digit_before_point;
            }
        }
        else if (isdigit(buf[i]) && is_point == 1)
        {
            if (is_start_zero == 1 && buf[i] == '0')
                count_del_zero_digit += 1;
            else
            {
                sum_with_exp -= count_del_zero_digit;
                count_del_zero_digit = 0;
                is_start_zero = 0;
                (num->digits)[(num->count_digit)] = buf[i] - '0';
                ++(num->count_digit);
            }
        }
        else if (tolower(buf[i]) == 'e')
        {
            if (is_point == 0)
            {
                sum_with_exp += count_digit_before_point;
            }
            is_exp = 1;
            ++i;
            num->exp += atoi(buf + i);
        }
    }

    if ((num->count_digit) > 30)
    {
        rc = ERR_MANTISSA_TOO_LONG;
    } else {

        if (num->exp > 99999 || num->exp < -99999)
            rc = ERR_DIGIT_TOO_LONG;
        else
        {
            num->exp += sum_with_exp;
            // удаление лишних нулей справа
            delete_zeros_right(num);

            // удаление возможно появившихся нулей слева

            delete_zeros_left(num);
        }
    }
    return rc;
}

int check_sign(char sym, size_t *index)
{
    int sign = 0;
    if (sym == '-')
    {
        *index = 1;
        sign = -1;
    }
    else if (sym == '+')
    {
        *index = 1;
        sign = 1;
    }
    else
    {
        *index = 0;
        sign = 1;
    }
    return sign;
}

void delete_zeros_left(long_float *num_float)
{
    for (size_t i = 0; i < (size_t)(num_float->count_digit) && (num_float->digits)[i] == 0;)
    {
        // удаление i-го элемента
        for (size_t j = i; j < (size_t)(num_float->count_digit) - 1; ++j)
            (num_float->digits)[j] = (num_float->digits)[j + 1];
        //уменьшение количества цифр числа и уменьшение порядка
        num_float->count_digit -= 1;
        num_float->exp -= 1;
    }
}

void delete_zeros_right(long_float *num)
{
    size_t i = (size_t)(num->count_digit) - 1;

    for (; (num->digits)[i] == 0; --i)
        num->count_digit -= 1;
}

void print_float(long_float *num)
{
    if (num->sign == -1)
        printf("-");
    else
        printf("+");

    printf("0.");

    for (size_t index = 0; index < (size_t)(num->count_digit); ++index)
    {
        printf("%d", (num->digits)[index]);
    }

    printf("e");
    if (num->exp >= 0)
        printf("+");
    printf("%d", num->exp);

    printf("\n");
}

int validate_float(char *str, char *buf)
{
    int is_exp = 0, is_digit = 0, is_point = 0;
    char exp = 'e', point = '.';
    char sign[COUNT_SIGN + 1] = "+-";
    char is_correct = 1;
    if (*str != 0)
    {
        for (size_t i = 0; *str && is_correct; ++i)
        {
            if (strchr(sign, *str) != 0)
            {
                check_sign_correct(buf, str, exp, &is_correct, i);
            }
            else if (*str == point)
            {
                check_point_correct(buf, str, &is_point, is_exp, &is_correct);
            }
            else if (isdigit(*str) != 0)
            {
                strncat(buf, str, 1);
                is_digit = 1;
            }
            else if (tolower(*(str)) == exp)
            {
                check_exp_correct(buf, str, point, is_digit, &is_exp, &is_correct, i);
            }
            else
                is_correct = 0;
            ++str;
        }
        size_t len = strlen(buf);
        if (is_all_param_incorrect(len, sign, buf, point, is_exp, is_point))
            is_correct = 0;
    }
    else
    {
        is_correct = 0;
    }
    return is_correct;
}

void check_sign_correct(char *buf, char *str, char exp, char *is_correct, size_t i)
{
    if (i == 0 || tolower(*(str - 1)) == exp)
    {
        strncat(buf, str, 1);
    }
    else
    {
        *is_correct = 0;
    }
}

void check_point_correct(char *buf, char *str, int *is_point, int is_exp, char *is_correct)
{
    if (*is_point || is_exp)
        *is_correct = 0;
    else
    {
        *is_point = 1;
        strncat(buf, str, 1);
    }
}

void check_exp_correct(char *buf, char *str, char point, int is_digit, int *is_exp, char *is_correct, size_t i)
{
    if (i != 0 && isdigit(*(str - 1)) != 0 && *is_exp == 0)
    // если до экспоненты есть мантиса и экспоненты еще не было
    {
        strncat(buf, str, 1);
        *is_exp = 1;
    }
    else if (i != 0 && is_digit && *(str - 1) == point && *is_exp == 0)
    // если перед экспонентой точка, но мантиса была введена
    {
        strncat(buf, str, 1);
        *is_exp = 1;
    }
    else
        *is_correct = 0;
}

char is_all_param_incorrect(size_t len, char *sign, char *buf, char point, int is_exp, int is_point)
{
    char exp = 'e';
    return (len == 0 || (strchr(sign, buf[0]) != 0 && len == 1) || (is_exp + is_point) == 0 ||
        (is_point == 0 && strchr(sign, buf[len - 1]) != 0) || (buf[len - 1] == point && len == 1) ||
        tolower(buf[len - 1]) == exp) ||
        (buf[len - 1] == '+' || (buf[len - 1] == '-'));
    // если длина равна 0 или знак не является единственным символом или число не вещественное(нет точки и экспоненты)
    // или нет точки и число окончивается знаком или или точка единственный символ или экспонента последний символ или
    // знак последний символ
}
