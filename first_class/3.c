#include <stdio.h>
#include <malloc.h>

void scan_arr(unsigned long long nelem, long long *arr);
void print_arr(unsigned long long nelem, long long *arr);
void modify_arr(unsigned long long nelem, long long *arr);

int main() {
    unsigned long long n = 0;
    scanf("%llu", &n);
    long long *arr = malloc(n * sizeof(*arr));
	assert(arr);
    scan_arr(n, arr);
	modify_arr(n, arr);
	print_arr(n, arr);
	free(arr);
	return 0;
}

void scan_arr(unsigned long long nelem, long long *arr) {
	for (unsigned long long i = 0; i < nelem; ++i) {
        scanf("%lld", arr + i);
    }
}

void print_arr(unsigned long long nelem, long long *arr) {
	for (unsigned long long i = 0; i < nelem; ++i) {
        printf("%lld\n", arr[i]);
    }
}

void modify_arr(unsigned long long nelem, long long *arr) {
	for (unsigned long long i = 0; i < nelem; ++i) {
        if (arr[i] % 2 == 0) {
			arr[i] *= 2;
		} else {
			arr[i] += 2;
		}
    }
}
