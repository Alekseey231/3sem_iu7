#include "../inc/check_sort.h"
#include "../inc/sort_table.h"
#include <check.h>

START_TEST(test_sort_already_sorted_array)
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    int arr_res[] = {1, 2, 3, 4, 5, 6};

    insertion_sort(&arr, sizeof(arr) / sizeof(int), sizeof(int), comparator);
    ck_assert_mem_eq(arr_res, arr, sizeof(int) * 6);
}
END_TEST

START_TEST(test_sort_reverse_sorted_array)
{
    int arr[] = {6, 5, 4, 3, 2, 1};
    int arr_res[] = {1, 2, 3, 4, 5, 6};

    insertion_sort(&arr, sizeof(arr) / sizeof(int), sizeof(int), comparator);
    ck_assert_mem_eq(arr_res, arr, sizeof(arr));
}
END_TEST

START_TEST(test_sort_partially_ordered_array)
{
    int arr[] = {5, 6, 15, 7, 8, 14};
    int arr_res[] = {5, 6, 7, 8, 14, 15};

    insertion_sort(&arr, sizeof(arr) / sizeof(int), sizeof(int), comparator);
    ck_assert_mem_eq(arr_res, arr, sizeof(arr));
}
END_TEST

START_TEST(test_sort_array_with_duplicate_elements)
{
    int arr[] = {1, 4, 1, 2, 4, 2, 5, 6};
    int arr_res[] = {1, 1, 2, 2, 4, 4, 5, 6};

    insertion_sort(&arr, sizeof(arr) / sizeof(int), sizeof(int), comparator);
    ck_assert_mem_eq(arr_res, arr, sizeof(arr));
}
END_TEST

START_TEST(test_sort_array_with_equal_elements)
{
    int arr[] = {1, 1, 1, 1, 1, 1};
    int arr_res[] = {1, 1, 1, 1, 1, 1};

    insertion_sort(&arr, sizeof(arr) / sizeof(int), sizeof(int), comparator);
    ck_assert_mem_eq(arr_res, arr, sizeof(arr));
}
END_TEST

START_TEST(test_sort_array_with_negative_elements)
{
    int arr[] = {1, -5, -10, 15, 6, 0};
    int arr_res[] = {-10, -5, 0, 1, 6, 15};

    insertion_sort(&arr, sizeof(arr) / sizeof(int), sizeof(int), comparator);
    ck_assert_mem_eq(arr_res, arr, sizeof(arr));
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции calc_avg
    s = suite_create("sort_suite");

    // Создадим тестовый случай из функций-тестов, которые проверяют разного
    // рода ошибочные ситуации при вызове calc_avg
    tc_pos = tcase_create("positives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_pos, test_sort_already_sorted_array);
    tcase_add_test(tc_pos, test_sort_reverse_sorted_array);
    tcase_add_test(tc_pos, test_sort_partially_ordered_array);
    tcase_add_test(tc_pos, test_sort_array_with_duplicate_elements);
    tcase_add_test(tc_pos, test_sort_array_with_equal_elements);
    tcase_add_test(tc_pos, test_sort_array_with_negative_elements);

    // Добавим сформированный тестовый случай в тестовый набор

    suite_add_tcase(s, tc_pos);

    return s;
}
