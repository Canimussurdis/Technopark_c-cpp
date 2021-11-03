#include <stdio.h>

#include "include/comment_data.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ./<bin> <path_to_data_file>\n");
        return -1;
    }

    int flt_amnt = count_actual_comments(argv[1], 4);
    if (flt_amnt < 0) {
        printf("Error: while reading %s!\n", argv[1]);
        return 1;
    }
    printf("%d comments are good and actual.\n", flt_amnt);

    return 0;
}





