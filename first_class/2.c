#include <stdio.h>
#include <assert.h>
#include <malloc.h>

int main() {
    int nships = 0;
    scanf("%u", &nships);
    int *ships = malloc(nships * sizeof(*ships));
    assert(ships);
    int sum = 0, aver = 0;;
    for (int i = 0; i < nships; ++i) {
        scanf("%d", ships + i);
        sum += ships[i];
    }
    assert(sum % nships == 0);
    aver = sum / nships;
    for (int i = 0; i < nships; ++i) {
        printf("%d\n", aver - ships[i]);
    }
    free(ships);
    return 0;
}
