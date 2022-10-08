#include <stdio.h>
#include <assert.h>

unsigned gcd(unsigned a, unsigned b);

int main() {
    unsigned a = 0, b = 0;
    scanf("%u%u", &a, &b);
    assert(a > 0);
    assert(b > 0);
    printf("\n\n%u\n", gcd(a, b));
    return 0;
}

unsigned gcd(unsigned a, unsigned b) {
    unsigned remainder = a % b;
    while (remainder != 0) {
        a = b;
        b = remainder;
        remainder = a % b;
    }
    return b;
}
