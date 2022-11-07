#include <stdio.h>
#include <math.h>
#include <time.h>

static inline long double func(long double x) {
    return sqrt(4 - x * x);
}

int main() {
    unsigned long nsegs = 0;
    scanf("%lu", &nsegs);

    if (nsegs == 0) {
        printf("doesn't look like a relevant number of segments, abort.\n");
        return 0;
    }

    long double seglen = (long double)2 / nsegs, integ = 0;
    clock_t beg = clock();
    
    long double path, prepath;
    for (path = seglen, prepath = 0; nsegs > 1; prepath = path, path += seglen, nsegs -= 1) {
        integ += (func(path) + func(prepath)) * seglen / (long double)2;
    }
    integ += func(prepath) * ((long double)2 - prepath) / (long double)2;

    clock_t end = clock();

    printf("res == %.9Lf\nspent %lf sec to count\n", integ, (double)(end - beg) / CLOCKS_PER_SEC);
    return 0;
}
