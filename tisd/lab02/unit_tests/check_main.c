#include <check.h>
#include <stdlib.h>
#include "../inc/check_string_validation.h"
#include "../inc/validation_input_data.h"
#include "../inc/check_sort.h"
#include "../inc/sort_table.h"

int main(void)
{
    int no_failed = 0;
    Suite *name_s;
    Suite *date_s;
    Suite *sort_s;
    SRunner *runner;

    name_s = name_correct_suite();
    date_s = date_correct_suite();
    sort_s = sort_suite();
    // Для запуска тестов, всходящих в тестовый набор, нужно создать так называемый
    // "runner".
    runner = srunner_create(name_s);
    srunner_add_suite(runner, date_s);
    srunner_add_suite(runner, sort_s);
    // Вот таким образом запускаются все тесты. С помощью второго параметра (в данном случаев
    // CK_VERBOSE) можно детализировать вывод.
    srunner_run_all(runner, CK_VERBOSE);
    // После того, как все тесты будут выполнены, можно получить по ним дополнительную информацию,
    // например, вот так.
    no_failed = srunner_ntests_failed(runner);
    // Перед завершением main "runner" нужно обязательно освободить.
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
