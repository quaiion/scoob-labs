#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

pthread_barrier_t bar;

struct thread_data_t {
    pthread_t thr;
    double *arr0_start;
    double *arr1_start;
    long nseg_to_go;
    long nstep;
};

double *heat_up(double *state_arr0, double *state_arr1,
                long nstep, long nseg_to_go, long nthr);
static inline void step_state(const double *src_arr, double *dest_arr,
                              long nseg_to_go);
void *thread_go(void *arg);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("fuck you, fix the input\n");
        return 0;
    }
    long nseg = atol(argv[1]) + 2, nthr = atol(argv[3]);
    double dur = atof(argv[2]);
    if (dur < 0 || nseg <= 2 || nthr < 1) {
        printf("fuck you, fix the input\n");
        return 0;
    }
    
    double seg = (double)1 / (nseg - 2);
    double step = (double)0.3 * seg * seg;
    long nstep = (long)(dur / step);
    long nseg_to_go = nseg - 1;

    double *state_arr0 = calloc(nseg, sizeof(double));
    double *state_arr1 = malloc(nseg * sizeof(double));
    state_arr0[nseg - 1] = state_arr1[nseg - 1] = 1;
    state_arr1[0] = 0;

    time_t timbeg = time(NULL);
    pthread_barrier_init(&bar, NULL, nthr);
    double *state_arr_res = heat_up(state_arr0, state_arr1, nstep,
                                    nseg_to_go, nthr);
    time_t timend = time(NULL);

    printf("spent %.0lf secs\n", difftime(timend, timbeg));
    for (long i = 1; i < nseg_to_go; ++i) {
        printf("%.4lf -- %.9lf\n", seg * i - seg / 2, state_arr_res[i]);
    }

    free(state_arr0);
    free(state_arr1);
    return 0;
}

double *heat_up(double *state_arr0, double *state_arr1,
                long nstep, long nseg_to_go, long nthr) {
    struct thread_data_t *thr_arr = malloc(nthr * sizeof(struct thread_data_t));
    long thr_seg = (nseg_to_go - 1) / nthr, nthr_to_go = nthr - 1;

    double *arr0_ptr = state_arr0 + 1, *arr1_ptr = state_arr1 + 1;
    for(long i = 0; i < nthr_to_go; ++i, arr0_ptr += thr_seg, arr1_ptr += thr_seg) {
        thr_arr[i].nseg_to_go = thr_seg;
        thr_arr[i].nstep = nstep;
        thr_arr[i].arr0_start = arr0_ptr;
        thr_arr[i].arr1_start = arr1_ptr;
        pthread_create(&thr_arr[i].thr, NULL, thread_go, thr_arr + i);
    }
    thr_arr[nthr_to_go].nseg_to_go = thr_seg + (nseg_to_go - 1) % nthr;
    thr_arr[nthr_to_go].nstep = nstep;
    thr_arr[nthr_to_go].arr0_start = arr0_ptr;
    thr_arr[nthr_to_go].arr1_start = arr1_ptr;
    pthread_create(&thr_arr[nthr_to_go].thr, NULL, thread_go, thr_arr + nthr_to_go);

    void *thr_st;
    for (long i = 0; i < nthr; ++i) {
        pthread_join(thr_arr[i].thr, &thr_st);
    }

    free(thr_arr);
    if (nstep % 2 == 0) {
        return state_arr0;
    } else {
        return state_arr1;
    }
}

void *thread_go(void *arg) {
    struct thread_data_t *thr_arg = (struct thread_data_t *)arg;
    long nstep_double = thr_arg->nstep / 2;
    for (long i = 0; i < nstep_double; ++i) {
        step_state(thr_arg->arr0_start, thr_arg->arr1_start,
                   thr_arg->nseg_to_go);
        pthread_barrier_wait(&bar);
        step_state(thr_arg->arr1_start, thr_arg->arr0_start,
                   thr_arg->nseg_to_go);
        pthread_barrier_wait(&bar);
    }
    if (thr_arg->nstep % 2 != 0) {
        step_state(thr_arg->arr0_start, thr_arg->arr1_start,
                   thr_arg->nseg_to_go);
    }
    pthread_exit(NULL);
}

static inline void step_state(const double *src_arr, double *dest_arr,
                              long nseg_to_go) {
    for (long i = 0; i < nseg_to_go; ++i) {
        dest_arr[i] = src_arr[i] + (double)0.3 * (src_arr[i + 1] -
                                    2 * src_arr[i] + src_arr[i - 1]);
    }
}
