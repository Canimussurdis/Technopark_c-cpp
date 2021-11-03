/* 
* Copyright 2021 Canimussurdis
*/

#include <stdio.h>
#include <stdlib.h>

const int BASE_LINES_AMOUNT = 1000000;
const int MAX_LINE_LEN = 40;

void free_arr(void** ptr, int length) {
    for (int i = 0; i < length; i++) {
        if (ptr[i] != NULL) {
            free(ptr[i]);
        }
    }
}

int read_file(char*** p_str_arr, const char* fpath) {
    int current_size = BASE_LINES_AMOUNT;
    char** comment_data = *p_str_arr;
    comment_data = malloc(current_size * sizeof(*comment_data));

    FILE* fp = fopen(fpath, "r");

    int32_t ln_amount = 0;
    int string_len = MAX_LINE_LEN;
    char* res;
    do {
        if (ln_amount >= current_size) {
            current_size *= 2;
            char** new_ptr = realloc(comment_data, current_size *
                                     sizeof(*comment_data));
            if (new_ptr == NULL) {
                free_arr((void**)comment_data, ln_amount);
                free(comment_data);
                return -2;
            }
            comment_data = new_ptr;
        }
        comment_data[ln_amount] = malloc(string_len * sizeof(**comment_data));
        if (comment_data[ln_amount] == NULL) {
            free_arr((void**)comment_data, ln_amount);
            free(comment_data);
            return -2;
        }
        res = fgets(comment_data[ln_amount], string_len, fp);
        ln_amount++;
    } while (res != NULL);
    ln_amount--;
    free(comment_data[ln_amount]);
    fclose(fp);

    *p_str_arr = comment_data;

    return ln_amount;
}

