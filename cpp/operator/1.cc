#include <iostream>

static inline int eucl_gcd(int val1, int val2) {
    val1 = abs(val1); val2 = abs(val2);
    int rem = val1 % val2;
    while (rem != 0) {
        val1 = val2;
        val2 = rem;
        rem = val1 % val2;
    }
    return val2;
}

class rational {
public:
    rational(int numerator_, int denominator_) {
        if (denominator_ == 0) {
            throw exception();
        }
        numerator = numerator_;
        denominator = denominator_;
        ensign();
        shrink();
    }
    rational() {
        numerator = 0;
        denominator = 1;
    }
    int get_numerator() {
        return numerator;
    }
    int get_denominator() {
        return denominator;
    }
    void set_numerator(int numerator_) {
        numerator = numerator_;
        shrink();
    }
    void set_denominator(int denominator_) {
        if (denominator_ == 0) {
            throw exception();
        }
        denominator = denominator_;
        ensign();
        shrink();
    }
private:
    int numerator, denominator;
    void shrink() {
        int gcd = eucl_gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }
    void ensign() {
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }
};
