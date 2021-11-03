/*
* Copyright 2021 Canimussurdis
*/

#include <time.h>

#include "include/date_utils.h"

int to_string(int value, char* string) {
    int len = 0;
    int a[32];
    while (value > 0) {
        a[len++] = value % 10;
        value /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        string[len - i - 1] = a[i] + 48;
    }
    string[len] = 0;

    return --len;
}

struct date get_current_date() {
    time_t t = time(NULL);
    struct tm buf;
    struct tm dt = *localtime_r(&t, &buf);
    struct date date;
    date.day = dt.tm_mday;
    date.month = dt.tm_mon + 1;  // tm_month is in range [0; 11]
    date.year = dt.tm_year + 1900;  // 0 = year 1900
    return date;
}

int month_to_quarter(int month) {
    // quarters: q1: 1, 2, 3; q2: 4, 5, 6; q3: 7, 8, 9; q4: 10, 11, 12
    if (month <= 0) {
        return -1;
    } else if (month <= 3) {
        return 1;
    } else if (month <= 6) {
        return 2;
    } else if (month <= 9) {
        return 3;
    } else if (month <= 12) {
        return 4;
    } else {
        return -1;
    }
}

void format_date(char* string, const struct date date) {
    char buf[3];
    int len = to_string(date.year, string);
    string[len + 1] = '-';
    to_date_format(date.month, buf);
    string[len + 2] = buf[0];
    string[len + 3] = buf[1];
    string[len + 4] = '-';
    to_date_format(date.day, buf);
    string[len + 5] = buf[0];
    string[len + 6] = buf[1];
    string[len + 7] = 0;
}

void to_date_format(int value, char* string) {
    // 1 <= v <= 99
    // prepends zero if needed and converts to string
    string[1] = value % 10 + 48;
    value /= 10;
    string[0] = value % 10 + 48;
    string[2] = 0;
}

