#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <pthread.h>

struct thread_data_t {
    pthread_t thread;
    long double res;
    long double start, step;
    unsigned long nsteps;
};

static inline long double func(long double x) {
    return sqrt(4 - x * x);
}

static inline long double merge_subinteg(struct thread_data_t *thr_arr,
                                         unsigned long ncells) {
    long double integ = 0;
    for (unsigned long i = 0; i < ncells; ++i) {
        integ += thr_arr[i].res;
    }
    return integ;
}

void *thr_func(void *arg) {
    struct thread_data_t *data = (struct thread_data_t *)arg;
    long double path = data->start + data->step, prepath = data->start, subinteg = 0;
    for (unsigned long i = 0; i < data->nsteps; prepath = path, path += data->step, i += 1) {
        subinteg += (func(path) + func(prepath)) * data->step / (long double)2;
    }
    data->res = subinteg;
    pthread_exit(NULL);
}

void main_thr_func(struct thread_data_t *data) {
    /** Last chunk processed, data->nsteps cannot be zero */
    long double path = data->start + data->step, prepath = data->start, subinteg = 0;
    for (unsigned long i = 0, end = data->nsteps - 1; i < end; prepath = path, path += data->step, i += 1) {
        subinteg += (func(path) + func(prepath)) * data->step / (long double)2;
    }
    subinteg += func(prepath) * ((long double)2 - prepath) / (long double)2;
    data->res = subinteg;
}

int main() {
    unsigned long nsegs = 0, nthreads = 0;
    scanf("%lu%lu", &nsegs, &nthreads);
    if (nthreads > nsegs) {
        nthreads = nsegs;
    }

    if (nsegs == 0) {
        printf("doesn't look like a relevant number of segments, abort.\n");
        return 0;
    }
    if (nthreads == 0) {
        printf("doesn't look like a relevant number of threads, abort.\n");
        return 0;
    }

    // clock_t beg = clock();
    time_t beg = time(NULL);

    struct thread_data_t *thr_arr = malloc(nthreads * sizeof(struct thread_data_t));
    unsigned long chunksize = nsegs / nthreads;
    long double seglen = (long double)2 / nsegs, chunklen = seglen * chunksize, path = 0;
    for (unsigned long i = 1; i < nthreads; i += 1, path += chunklen) {
        thr_arr[i].nsteps = chunksize;
        thr_arr[i].start = path;
        thr_arr[i].step = seglen;
        pthread_create(&thr_arr[i].thread, NULL, thr_func, thr_arr + i);
    }
    thr_arr->nsteps = nsegs - chunksize * (nthreads - 1);
    thr_arr->start = path;
    thr_arr->step = seglen;
    main_thr_func(thr_arr);
    void *thr_st;
    for (unsigned long i = 0; i < nthreads; ++i) {
        pthread_join(thr_arr[i].thread, &thr_st);
    }
    long double integ = merge_subinteg(thr_arr, nthreads);
    free(thr_arr);

    // clock_t end = clock();
    time_t end = time(NULL);

    // printf("res == %.9Lf\nspent %lf sec to count\n", integ, (double)(end - beg) / CLOCKS_PER_SEC);
    printf("res == %.9Lf\nspent %.0lf sec to count\n", integ, difftime(end, beg));
    return 0;
}
