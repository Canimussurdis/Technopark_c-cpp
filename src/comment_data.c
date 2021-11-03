/*
* Copyright 2021 Canimussurdis
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <pthread.h>

#ifdef __APPLE__
#define get_nprocs() 4
#else
#include <sys/sysinfo.h>
#endif

#include "include/date_utils.h"
#include "include/comment_data.h"

bool parse_comment(struct comment_data* comment, char* string) {
    int var_amount = sscanf(string, "%d %f %d %d-%d-%d %d\n",
                            &comment->id, &comment->average_score,
                            &comment->score_amount, &comment->last_date.year,
                            &comment->last_date.month, &comment->last_date.day,
                            &comment->last_score);

    return var_amount == 7;
}

bool is_comment_in_last_quater(const struct comment_data comment) {
    int upd_quater = month_to_quarter(comment.last_date.month);
    struct date current_date = get_current_date();
    int last_quater = month_to_quarter(current_date.month) - 1;
    int quater_year = current_date.year;
    if (last_quater == 0) {
        last_quater = 4;
        quater_year--;
    }
    return last_quater == upd_quater && quater_year == comment.last_date.year;
}

