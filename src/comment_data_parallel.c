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

#include "include/utils.h"
#include "include/date_utils.h"
#include "include/comment_data.h"

struct args {
    char** c_data;
    int avg_score;
    int32_t ln_offset, ln_amount;
};

void* thread_count_comments(void* arg) {
    struct args* args = arg;

    int flt_amount = 0;
    int i = args->ln_offset;
    struct comment_data* comment = malloc(sizeof(*comment));
    if (comment == NULL) {
        pthread_exit((void*)(uintptr_t)-2);
    }
    while (i < args->ln_offset + args->ln_amount) {
        if (!parse_comment(comment, args->c_data[i])) {
            free(comment);
            pthread_exit((void*)(uintptr_t)-3);
        }

        if (is_comment_in_last_quater(*comment) && 
            comment->average_score > args->avg_score) {
            flt_amount++;
        }
        free(args->c_data[i]);  // to free memory as soon as possible
        args->c_data[i] = NULL;  // to prevent free() of freed memory
        i++;
    }
    free(comment);

    pthread_exit((void*)(uintptr_t)flt_amount);
}

int count_actual_comments(const char* fpath, int avg_score) {
    char** c_data;
    int ln_amount = read_file(&c_data, fpath);
    if (ln_amount <= 0) {
        return -3;
    }

    int nthreads = get_nprocs();
    int32_t ln_per_thread = ln_amount / nthreads,
        ln_remains = ln_amount % nthreads,
        flt_amount = 0;

    int errflag;
    pthread_t* threads = malloc(nthreads * sizeof(*threads));
    struct args* arg[nthreads];

    for (int i = 0; i < nthreads; i++) {
        arg[i] = malloc(sizeof(*arg[i]));
        arg[i]->c_data = c_data;
        arg[i]->avg_score = avg_score;
        arg[i]->ln_offset = ln_per_thread * i;
        arg[i]->ln_amount = ln_per_thread;
        if (i + 1 == nthreads) {
            arg[i]->ln_amount += ln_remains;
        }

        errflag = pthread_create(
            &threads[i], NULL, thread_count_comments, arg[i]);
        if (errflag != 0) {
            free(threads);
            free_arr((void**)c_data, ln_amount);
            free(c_data);
            free_arr((void**)arg, nthreads);
            return -4;
        }
    }

    for (int i = 0; i < nthreads; i++) {
        void* res = NULL;
        int ret = pthread_join(threads[i], &res);
        int32_t ln_amnt = (uintptr_t)res;
        if (ret || ln_amnt < 0) {
            free(threads);
            free_arr((void**)c_data, ln_amount);
            free(c_data);
            free_arr((void**)arg, nthreads);
            return -3;
        }
        flt_amount += ln_amnt;
        free(arg[i]);
        arg[i] = NULL;
    }
    free(threads);
    free(c_data);
    
    return flt_amount;
}

