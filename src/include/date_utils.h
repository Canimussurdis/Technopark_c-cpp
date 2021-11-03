/*
* Copyright 2021 Canimussurdis
*/

#ifndef SRC_INCLUDE_DATE_UTILS_H_
#define SRC_INCLUDE_DATE_UTILS_H_

struct date {
    int day, month, year;
};

// convert to string format (for year)
int to_string(int value, char* str);

// get the current date
struct date get_current_date();

// convert month to quarter: 1 to 4
int month_to_quarter(int month);

// formatting date "year-month-day"
void format_date(char* str, const struct date date);

// convert to date format (for month and day)
void to_date_format(int value, char* str);

#endif  // SRC_INCLUDE_DATE_UTILS_H_

