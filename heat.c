#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

double *heat_up(double *state_arr0, double *state_arr1,
                long nstep, long nseg_to_go);
static inline void step_state(const double *src_arr, double *dest_arr,
                              long nseg_to_go);

int main(int argc, char *argv[]) {
    long nseg = atol(argv[1]) + 2;
    double dur = atof(argv[2]);
    if (argc != 3 || dur < 0 || nseg <= 2) {
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

    double *state_arr_res = heat_up(state_arr0, state_arr1, nstep, nseg_to_go);
    for (long i = 1; i < nseg_to_go; ++i) {
        printf("%lf -- %lf\n", seg * i - seg / 2, state_arr_res[i]);
    }

    free(state_arr0);
    free(state_arr1);
    return 0;
}

double *heat_up(double *state_arr0, double *state_arr1,
                long nstep, long nseg_to_go) {
    long nstep_double = nstep / 2;
    for (long i = 0; i < nstep_double; ++i) {
        step_state(state_arr0, state_arr1, nseg_to_go);
        step_state(state_arr1, state_arr0, nseg_to_go);
    }
    if (nstep % 2 == 0) {
        return state_arr0;
    } else {
        step_state(state_arr0, state_arr1, nseg_to_go);
        return state_arr1;
    }
}

static inline void step_state(const double *src_arr, double *dest_arr,
                              long nseg_to_go) {
    for (long i = 1; i < nseg_to_go; ++i) {
        dest_arr[i] = src_arr[i] + (double)0.3 * (src_arr[i + 1] -
                                    2 * src_arr[i] + src_arr[i - 1]);
    }
}
