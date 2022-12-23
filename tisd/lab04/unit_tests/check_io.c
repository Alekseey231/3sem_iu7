#include "../inc/io.h"
#include "../inc/check_io.h"

START_TEST(test_correct_sum_two_nums)
{
	char *line = "1+2";
    int count = 2;
    int nums[3];
    int arr_res[] = { 1, 2 };

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(arr_res, nums, sizeof(arr_res)/ sizeof(int));
}
END_TEST

START_TEST(test_correct_delta_two_nums)
{
    char *line = "1-2";
    int count = 2;
    int nums[3];
    int arr_res[] = { 1, -2 };

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(arr_res, nums, sizeof(arr_res)/ sizeof(int));
}
END_TEST

START_TEST(test_correct_negative_two_nums)
{
    char *line = "-15-221";
    int count = 2;
    int nums[3];
    int arr_res[] = { -15, -221 };

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(arr_res, nums, sizeof(arr_res)/ sizeof(int));
}
END_TEST

START_TEST(test_correct_with_zero)
{
    char *line = "-1-0+0-5";
    int count = 4;
    int nums[5];
    int arr_res[] = { -1, 0, 0, -5 };

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(arr_res, nums, sizeof(arr_res)/ sizeof(int));
}
END_TEST

START_TEST(test_correct_with_seven_nums)
{
    char *line = "-795+2934-10000+5-234+1293312+123213";
    int count = 7;
    int nums[8];
    int arr_res[] = { -795, 2934, -10000, 5, 234, 1293312, 123213};

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(arr_res, nums, sizeof(arr_res)/ sizeof(int));
}
END_TEST

START_TEST(test_input_nums_more_that_need)
{
    char *line = "1+2+3";
    int count = 2;
    int nums[3];

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, ERR_READ_VOLUME);
}
END_TEST

START_TEST(test_input_nums_less_that_need)
{
    char *line = "1";
    int count = 2;
    int nums[3];

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, ERR_READ_VOLUME);
}
END_TEST

START_TEST(test_input_without_nums)
{
    char *line = "+";
    int count = 1;
    int nums[3];

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, ERR_READ_VOLUME);
}
END_TEST

START_TEST(test_input_without_nums_sign)
{
    char *line = "-";
    int count = 1;
    int nums[3];

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, ERR_READ_VOLUME);
}
END_TEST

START_TEST(test_input_start_letter)
{
    char *line = "a405";
    int count = 1;
    int nums[3];

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, ERR_READ_VOLUME);
}
END_TEST

START_TEST(test_input_end_letter)
{
    char *line = "4+6a6";
    int count = 2;
    int nums[3];

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, ERR_READ_VOLUME);
}
END_TEST

START_TEST(test_input_middle_letter)
{
    char *line = "4+a6";
    int count = 2;
    int nums[3];

    int rc = parse_nums_from_string(line, nums, count, NULL, NULL);

    ck_assert_int_eq(rc, ERR_READ_VOLUME);
}
END_TEST





Suite *input_correct_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    // Создадим тестовый набор для тестирования функции calc_avg
    s = suite_create("input_nums");

    // Создадим тестовый случай из функций-тестов, которые проверяют разного
    // рода ошибочные ситуации при вызове calc_avg
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_pos, test_correct_sum_two_nums);
    tcase_add_test(tc_pos, test_correct_delta_two_nums);
    tcase_add_test(tc_pos, test_correct_negative_two_nums);
    tcase_add_test(tc_pos, test_correct_with_zero);
    tcase_add_test(tc_pos, test_correct_with_seven_nums);

    tcase_add_test(tc_neg, test_input_nums_more_that_need);
    tcase_add_test(tc_neg, test_input_nums_less_that_need);
    tcase_add_test(tc_neg, test_input_without_nums);
    tcase_add_test(tc_neg, test_input_without_nums_sign);
    tcase_add_test(tc_neg, test_input_start_letter);
    tcase_add_test(tc_neg, test_input_end_letter);
    tcase_add_test(tc_neg, test_input_middle_letter);
    // Добавим сформированный тестовый случай в тестовый набор

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}


