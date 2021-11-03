#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include <check.h>

#include "include/date_utils.h"
#include "include/comment_data.h"

const int TEST_BUF_SIZE = 1024;

bool create_file(const char* fname, char* data) {
    FILE* pf = fopen(fname, "wr");
    if (pf == NULL) {
        return false;
    }
    fputs(data, pf);
    fclose(pf);
    return true;
}

START_TEST(date_utils_test) {
    fail_unless(month_to_quarter(3) == 1, "month_to_quarter_test");
    fail_unless(month_to_quarter(4) == 2, "month_to_quarter_test");
    fail_unless(month_to_quarter(8) == 3, "month_to_quarter_test");
    fail_unless(month_to_quarter(12) == 4, "month_to_quarter_test");
    fail_unless(month_to_quarter(0) == -1, "month_to_quarter_test");
    fail_unless(month_to_quarter(13) == -1, "month_to_quarter_test");

    time_t t = time(NULL);
    struct tm buf;
    struct tm dt = *localtime_r(&t, &buf);
    struct date date = get_current_date();
    fail_unless(date.year == (dt.tm_year + 1900), "cur_date");
    fail_unless(date.month == (dt.tm_mon + 1), "cur_date");
    fail_unless(date.day == (dt.tm_mday), "cur_date");

    int a = 1, b = 12;
    char* string = malloc(3 * sizeof(*string));
    to_date_format(a, string);
    fail_unless(string[0] == '0' && string[1] == '1' && string[2] == 0, "to_d_form");
    to_date_format(b, string);
    fail_unless(string[0] == '1' && string[1] == '2' && string[2] == 0, "to_d_form");
} END_TEST

START_TEST(comment_data_test) {
    char* ok_comment_s = "9 2.56 9022 2020-06-21 1";
    char* bad_comment_s = "9 WOLF";
    struct comment_data* comment = malloc(sizeof(*comment));
    fail_unless(parse_comment(comment, ok_comment_s) == true, "parse_comment");
    fail_unless(comment->id == 9, "parse_comment");
    fail_unless(abs(comment->average_score - 2.56) < 0.01, "parse_comment");
    fail_unless(comment->score_amount == 9022, "parse_comment");
    fail_unless(comment->last_date.year == 2020 && comment->last_date.month == 6 && comment->last_date.day == 21,
        "parse_comment");
    fail_unless(comment->last_score == 1, "parse_comment");
    fail_unless(parse_comment(comment, bad_comment_s) == false, "parse_comment");

    struct date date = get_current_date();
    comment->last_date.year = date.year;
    comment->last_date.month = date.month;
    fail_unless(is_comment_in_last_quater(*comment) == false, "is_last_quater");
    comment->last_date.month -= 3;
    if (comment->last_date.month <= 0) {
        comment->last_date.month = 12;
    }
    fail_unless(is_comment_in_last_quater(*comment) == true, "is_last_quater");

    struct date date_last_quater, date_cur_quater = get_current_date();
    int last_quater_month = date_cur_quater.month - 3,
        last_quater_year = date_cur_quater.year;
    if (last_quater_month <= 0) {
        last_quater_month = 12;
        last_quater_year -= 1;
    }
    date_last_quater.year = last_quater_year;
    date_last_quater.month = last_quater_month;
    date_last_quater.day = 1;
    char last_q_sd[32], cur_q_sd[32];
    format_date(last_q_sd, date_last_quater);
    format_date(cur_q_sd, date_cur_quater);

    const char* fname = "temp_file.txt";
    char data[TEST_BUF_SIZE];

    snprintf(data, TEST_BUF_SIZE * sizeof(*data),
        "9 2.56 9022 %s 1\n"  // -
        "9 4.52 9022 %s 1\n"  // +
        "9 4.52 9022 %s 1\n",  // -
        last_q_sd, last_q_sd, cur_q_sd);
    create_file(fname, data);
    fail_unless(count_actual_comments(fname, 4) == 1, "count");

    snprintf(data, TEST_BUF_SIZE * sizeof(*data), "bad_data");
    create_file(fname, data);
    fail_unless(count_actual_comments(fname, 4) == -3, "count");

    snprintf(data, TEST_BUF_SIZE * sizeof(*data),
        "2 4.52 902212341234234213421342134123412331231412341212342123 %s 1\n",
        last_q_sd);
    create_file(fname, data);
    int res = count_actual_comments(fname, 4);
    fail_unless(res == -3 || res == 1, "count");

    snprintf(data, TEST_BUF_SIZE,
        "1 2.56 9022 %s 1\n"  // -
        "2 4.52 9022 %s 1\n"  // +
        "3 4.52 9022 %s 1\n"  // -
        "4 5 41234 2002-02-01 5\n"  // -
        "5 4.31 1233 %s 4\n"  // +
        "6 4.01 321 %s 2\n"   // +
        "7 3.99 321 %s 5\n",   // -
        last_q_sd, last_q_sd, cur_q_sd, last_q_sd, last_q_sd, last_q_sd);
    create_file(fname, data);
    fail_unless(count_actual_comments(fname, 4) == 3, "count");

    unlink(fname);
} END_TEST

int main() {
    Suite* s1 = suite_create("Core");
    TCase* tc1_1 = tcase_create("Core");
    SRunner* sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, date_utils_test);
    tcase_add_test(tc1_1, comment_data_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}

