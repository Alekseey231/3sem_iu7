#include "../inc/check_string_validation.h"
#include "../inc/validation_input_data.h"

START_TEST(test_name_without_hyphen)
{
	char *name = "Aleksey";

    int rc = is_name_correct(name);

    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(test_name_with_one_hyphen)
{
	char *name = "Petrov-Tverdov";

    int rc = is_name_correct(name);

    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(test_name_with_two_hyphen)
{
	char *name = "Marian-Stanislav-Uriev";

    int rc = is_name_correct(name);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_name_have_num)
{
	char *name = "Ivanov123";

    int rc = is_name_correct(name);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_name_have_space)
{
	char *name = "Petr Petrov";

    int rc = is_name_correct(name);

    ck_assert_int_eq(rc, 0);
}
END_TEST


Suite *name_correct_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    // Создадим тестовый набор для тестирования функции calc_avg
    s = suite_create("name_correct_suite");

    // Создадим тестовый случай из функций-тестов, которые проверяют разного
    // рода ошибочные ситуации при вызове calc_avg
    tc_pos = tcase_create("positives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_pos, test_name_without_hyphen);
    tcase_add_test(tc_pos, test_name_with_one_hyphen);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_name_with_two_hyphen);
    tcase_add_test(tc_neg, test_name_have_num);
    tcase_add_test(tc_neg, test_name_have_space);
    

    // Добавим сформированный тестовый случай в тестовый набор

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}


START_TEST(test_correct_date)
{
    subscribers_t subscribers;
    char date[] = "10.11.2021";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 10, .month = 11, .year = 2021}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

START_TEST(test_date_min_day)
{
    subscribers_t subscribers;
    char date[] = "1.11.2021";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 1, .month = 11, .year = 2021}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

START_TEST(test_date_day_start_zero)
{
    subscribers_t subscribers;
    char date[] = "01.11.2021";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 1, .month = 11, .year = 2021}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

START_TEST(test_date_max_day)
{
    subscribers_t subscribers;
    char date[] = "31.11.2021";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 31, .month = 11, .year = 2021}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

START_TEST(test_date_min_month)
{
    subscribers_t subscribers;
    char date[] = "20.01.2021";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 20, .month = 1, .year = 2021}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

START_TEST(test_date_max_month)
{
    subscribers_t subscribers;
    char date[] = "20.12.2021";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 20, .month = 12, .year = 2021}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

START_TEST(test_date_min_year)
{
    subscribers_t subscribers;
    char date[] = "20.06.1";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 20, .month = 06, .year = 1}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

START_TEST(test_date_min)
{
    subscribers_t subscribers;
    char date[] = "1.1.1";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 1, .month = 1, .year = 1}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

START_TEST(test_date_max)
{
    subscribers_t subscribers;
    char date[] = "31.12.9999";

    subscribers_t res_subscribers = {.variate_status = {.private = {.date_birth = {.day = 31, .month = 12, .year = 9999}}}};

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.day, subscribers.variate_status.private.date_birth.day);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.month, subscribers.variate_status.private.date_birth.month);
    ck_assert_int_eq(res_subscribers.variate_status.private.date_birth.year, subscribers.variate_status.private.date_birth.year);
}
END_TEST

//negatives

START_TEST(test_date_not_positive_day)
{
    subscribers_t subscribers;
    char date[] = "0.6.2015";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_NEGATIVE_DAY);
}
END_TEST

START_TEST(test_date_too_much_day)
{
    subscribers_t subscribers;
    char date[] = "32.6.2015";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_TOO_MUCH_DAY);
}
END_TEST

START_TEST(test_date_not_positive_month)
{
    subscribers_t subscribers;
    char date[] = "3.0.2015";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_NEGATIVE_MONTH);
}
END_TEST

START_TEST(test_date_too_much_month)
{
    subscribers_t subscribers;
    char date[] = "3.13.2015";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_TOO_MUCH_MONTH);
}
END_TEST

START_TEST(test_date_not_positive_year)
{
    subscribers_t subscribers;
    char date[] = "3.3.0";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_NEGATIVE_YEAR);
}
END_TEST

START_TEST(test_date_world)
{
    subscribers_t subscribers;
    char date[] = "hello";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_INCORRECT_DATE);
}
END_TEST

START_TEST(test_date_with_sign)
{
    subscribers_t subscribers;
    char date[] = "+12.3.2005";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_NOT_DIGIT_IN_DATE);
}
END_TEST

START_TEST(test_date_with_end_dot)
{
    subscribers_t subscribers;
    char date[] = "12.3.2005.";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_INCORRECT_DATE);
}
END_TEST

START_TEST(test_date_with_only_dot)
{
    subscribers_t subscribers;
    char date[] = "..";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_INCORRECT_DATE);
}
END_TEST

START_TEST(test_date_with_incorrect_char_at_end)
{
    subscribers_t subscribers;
    char date[] = "12.12.2022 gh";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_NOT_DIGIT_IN_DATE);
}
END_TEST

START_TEST(test_date_with_incorrect_char)
{
    subscribers_t subscribers;
    char date[] = "aa.bb.cc";

    int rc = process_date(date, &subscribers);

    ck_assert_int_eq(rc, ERR_NOT_DIGIT_IN_DATE);
}
END_TEST

Suite *date_correct_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    // Создадим тестовый набор для тестирования функции calc_avg
    s = suite_create("date_correct_suite");

    // Создадим тестовый случай из функций-тестов, которые проверяют разного
    // рода ошибочные ситуации при вызове calc_avg
    tc_pos = tcase_create("positives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_pos, test_correct_date);
    tcase_add_test(tc_pos, test_date_min_day);
    tcase_add_test(tc_pos, test_date_day_start_zero);

    tcase_add_test(tc_pos, test_date_max_day);
    tcase_add_test(tc_pos, test_date_min_month);
    tcase_add_test(tc_pos, test_date_max_month);
    tcase_add_test(tc_pos, test_date_min_year);
    tcase_add_test(tc_pos, test_date_min);
    tcase_add_test(tc_pos, test_date_max);
    // Добавим сформированный тестовый случай в тестовый набор

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_date_not_positive_day);
    tcase_add_test(tc_neg, test_date_too_much_day);
    tcase_add_test(tc_neg, test_date_not_positive_month);
    tcase_add_test(tc_neg, test_date_too_much_month);
    tcase_add_test(tc_neg, test_date_not_positive_year);

    tcase_add_test(tc_neg, test_date_world);
    tcase_add_test(tc_neg, test_date_with_sign);
    tcase_add_test(tc_neg, test_date_with_end_dot);
    tcase_add_test(tc_neg, test_date_with_only_dot);
    tcase_add_test(tc_neg, test_date_with_incorrect_char_at_end);
    tcase_add_test(tc_neg, test_date_with_incorrect_char);

    suite_add_tcase(s, tc_neg);
    
    return s;
}
