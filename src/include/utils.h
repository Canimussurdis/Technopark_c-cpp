#ifndef SRC_INCLUDE_UTILS_H_
#define SRC_INCLUDE_UTILS_H_

// free an array
void free_arr(void** ptr, int length);

// read file with data
int read_file(char*** p_str_arr, const char* fpath);

#endif  // SRC_INCLUDE_UTILS_H_

