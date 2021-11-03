#ifndef SRC_INCLUDE_COMMENT_DATA_H_
#define SRC_INCLUDE_COMMENT_DATA_H_

#include <stdbool.h>
#include <inttypes.h>

#include "date_utils.h"  // NOLINT

struct comment_data {
    int id;
    float average_score;
    int score_amount;
    struct date last_date;
    int last_score;
};

// parsing comment
bool parse_comment(struct comment_data* comment, char* string);

// check if comment is being sent in last quater 
bool is_comment_in_last_quater(const struct comment_data comment);

// count how many comments were in last quater
int count_actual_comments(const char* fpath, int avg_score);

#endif  // SRC_INCLUDE_COMMENT_DATA_H_
