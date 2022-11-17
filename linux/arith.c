#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

double calculate(double val1, double val2, bool flag_a, bool flag_s, bool flag_m, bool glag_d);

int main(int argc, char **argv) {
    const struct option long_option[] = {
        {"add", no_argument, NULL, 'a'},
        {"sub", no_argument, NULL, 's'}, 
        {"mul", no_argument, NULL, 'm'},
        {"div", no_argument, NULL, 'd'},
        {NULL, no_argument, NULL, 0}
    };

    int long_index = 0, opt = 0;
    const char short_option[] = "asmd";
    bool flag_a = false, flag_s = false, flag_m = false, flag_d = false;

    while ((opt = getopt_long(argc, argv, short_option,
                              long_option, &long_index)) != -1) {
        switch (opt) {
            case 'a':
                flag_a = true;
                break;
            case 's':
                flag_s = true;
                break;
            case 'm':
                flag_m = true;
                break;
            case 'd':
                flag_d = true;
                break;
            default:
                /* system prints the 'switch unknown' message on its own */
                return 0;
        }
    }

    if (argc < 3 || optind != argc - 2) {
        printf("\nnot enough arguments\n\n");
        return 0;
    }

    double val1 = atof(argv[optind]), val = atof(argv[optind + 1]), res = 0;
    res = calculate(val1, val2, flag_a, flag_s, flag_m, flag_d);

    printf("\nget your number: %.3lf\n\n", res);
    return 0;
}

double calculate(double val1, double val2, bool flag_a, bool flag_s, bool flag_m, bool flag_d) {
    if (flag_a) {
        val1 += val2;
    }
    if (flag_s) {
        val1 -= val2;
    }
    if (flag_m) {
        val1 *= val2;
    }
    if (flag_d) {
        val1 /= val2;
    }
    return val1;
}
