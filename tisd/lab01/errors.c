#include "errors.h"

void process_error(int rc)
{
    if (rc == ERR_READ_STR)
        printf("Ошибка при чтении строки\n");
    else if (rc == ERR_INCORRECT_INT)
        printf("Введено некорректное целое число\n");
    else if (rc == ERR_NUMBER_TOO_LONG)
        printf("Введено слишком длинное число");
    else if (rc == ERR_EMPTY_STR)
        printf("Введена пустая строка");
    else if (rc == ERR_INCORRECT_FLOAT)
        printf("Введено некорректное вещественное число\n");
    else if (rc == ERR_DIGIT_TOO_LONG)
        printf("Превышено допустимое число разрядов порядка\n");
    else if (rc == ERR_OVERFLOW_DIGIT)
        printf("Превышено допустимое число разрядов порядка в процессе вычисления\n");
    else if (rc == ERR_MANTISSA_TOO_LONG)
        printf("Превышена допустимая длина мантиссы\n");
}
