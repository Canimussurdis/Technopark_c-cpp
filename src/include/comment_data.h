#ifndef SRC_INCLUDE_COMMENT_DATA_H_
#define SRC_INCLUDE_COMMENT_DATA_H_

#include <stdbool.h>
#include <inttypes.h>

#include "date_utils.h"  // NOLINT

struct comment_data {
    int id;
    float average_score;
    int score_amount;
    struct date ld;
    int last_score;
};

bool parse_comment(struct comment_data* c, char* s);

bool is_comment_in_last_q(const struct comment_data c);

int count_actual_comments(const char* fpath, int avg_score);

#endif  // SRC_INCLUDE_COMMENT_DATA_H_
