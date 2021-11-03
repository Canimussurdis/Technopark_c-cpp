/*
* Copyright 2021 Canimussurdis
*/

#ifndef SRC_INCLUDE_RANDOM_DATA_GEN_H_
#define SRC_INCLUDE_RANDOM_DATA_GEN_H_

#include <stdint.h>

// field structure with random data
void random_data(struct comment_data* comment, int rand_years, unsigned* rseed);

// print comment string filled with random data
int random_data_string(char* str, int s_len, unsigned* rseed);

// create file with random data
int create_random_data_file(const char* fpath, int64_t amnt, unsigned* rseed);

#endif  // SRC_INCLUDE_RANDOM_DATA_GEN_H_

