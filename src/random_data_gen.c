#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "include/date_utils.h"
#include "include/comment_data.h"
#include "include/random_data_gen.h"

void random_data(struct comment_data* comment, int rand_years, unsigned* rseed) {
    struct date cur_date = get_current_date();

    comment->last_date.year = (cur_date.year - rand_years) + rand_r(rseed) % (rand_years + 1);
    comment->last_date.month = rand_r(rseed) % 12 + 1;
    comment->last_date.day = rand_r(rseed) % 28 + 1;
    comment->average_score = (rand_r(rseed) % 5001) / 1000.0;
    comment->score_amount = rand_r(rseed) % 10000;
    comment->last_score = rand_r(rseed) % 5 + 1;
}

int random_data_string(char* string, int s_len, unsigned* rseed) {
    struct comment_data comment;
    random_data(&comment, 2, rseed);

    if (comment.average_score <= 1.0000) {
        snprintf(string, s_len, "0 0 00-00-0000 0");
    }
    else {
        char buf[255];
        format_date(buf, comment.last_date);
        snprintf(string, s_len, "%0.2f %d %s %d",
            comment.average_score,
            comment.score_amount,
            buf,
            comment.last_score);
    }

    return 0;
}

int create_random_data_file(const char* fpath, int64_t amnt, unsigned* rseed) {
    FILE* file = fopen(fpath, "w");
    if (file == NULL) {
        return -1;
    }

    int s_len = 255;
    char* string = malloc(s_len * sizeof(string));
    if (string == NULL) {
        fclose(file);
        return -2;
    }
    for (int64_t i = 1; i <= amnt; i++) {
        string[0] = 0;
        if (random_data_string(string, s_len, rseed)) {
            free(string);
            fclose(file);
            return -2;
        }
        fprintf(file, "%" PRId64 " %s\n", i, string);
    }

    free(string);
    fclose(file);

    return 0;
}

