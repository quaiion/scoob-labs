#include <iostream>

static inline long eucl_gcd(long val1, long val2) {
    val1 = abs(val1); val2 = abs(val2);
    long rem = val1 % val2;
    while (rem != 0) {
        val1 = val2;
        val2 = rem;
        rem = val1 % val2;
    }
    return val2;
}

class rational {
public:
    rational(long numer_, long denom_) {
        if (denom_ == 0) {
            throw std::exception();
        }
        numer = numer_;
        denom = denom_;
        ensign();
        shrink();
    }
    rational() {
        numer = 0;
        denom = 1;
    }

    long get_numer() {
        return numer;
    }
    long get_denom() {
        return denom;
    }
    void set_numer(long numer_) {
        numer = numer_;
        shrink();
    }
    void set_denom(long denom_) {
        if (denom_ == 0) {
            throw std::exception();
        }
        denom = denom_;
        ensign();
        shrink();
    }

    rational operator+(rational smnd) {
        rational sum{};
        sum.numer = numer * smnd.denom +
                        smnd.numer * denom;
        sum.denom = denom * smnd.denom;
        sum.shrink();
        return sum;
    }
    rational operator-(rational sbtd) {
        rational dif{};
        dif.numer = numer * sbtd.denom -
                        sbtd.numer * denom;
        dif.denom = denom * sbtd.denom;
        dif.shrink();
        return dif;
    }
    rational operator*(rational mtpr) {
        rational prod{};
        prod.numer = numer * mtpr.numer;
        prod.denom = denom * mtpr.denom;
        prod.shrink();
        return prod;
    }
    rational operator/(rational div) {
        rational quot{};
        quot.numer = numer * div.denom;
        quot.denom = denom * div.numer;
        quot.ensign();
        quot.shrink();
        return quot;
    }
    rational operator=(rational val) {
        numer = val.numer;
        denom = val.denom;
        return val;
    }

    bool operator==(rational val) {
        if (val.numer == numer && val.denom == denom) {
            return true;
        }
        return false;
    }
    bool operator>(rational val) {
        if (numer * val.denom > val.numer * denom) {
            return true;
        }
        return false;
    }
    bool operator<(rational val) {
        if (numer * val.denom < val.numer * denom) {
            return true;
        }
        return false;
    }
    bool operator>=(rational val) {
        if (numer * val.denom >= val.numer * denom) {
            return true;
        }
        return false;
    }
    bool operator<=(rational val) {
        if (numer * val.denom <= val.numer * denom) {
            return true;
        }
        return false;
    }
    
    rational& operator++() {
        numer += denom;
        return *this;
    }
    rational operator++(int) {
        rational oldval = *this;
        numer += denom;
        return oldval;
    }
    rational& operator--() {
        numer -= denom;
        return *this;
    }
    rational operator--(int) {
        rational oldval = *this;
        numer -= denom;
        return oldval;
    }

    friend std::istream& operator>>(std::istream& os, rational& val);
    friend std::ostream& operator<<(std::ostream& os, const rational& val);

private:
    long numer, denom;
    void shrink() {
        long gcd = eucl_gcd(numer, denom);
        numer /= gcd;
        denom /= gcd;
    }
    void ensign() {
        if (denom < 0) {
            numer *= -1;
            denom *= -1;
        }
    }
};

std::istream& operator>>(std::istream& is, rational& val) {
    long num = 0, den = 0;
    is >> num >> den;
    val.numer = num;
    val.set_denom(den);
    return is;
}
std::ostream& operator<<(std::ostream& os, const rational& val) {
    return os << val.numer << '/' << val.denom;
}

int main() {
    rational a(1, 2), b(5, 8), c;
    std::cout << a << ' ' << b << ' ' << c << std::endl;
    std::cin >> c;
    std::cout << c << std::endl;
    std::cout << a + b << ' ' << a - b << ' ' << a * b << ' ' << a / b << ' ' << std::endl;
    if (a > b) {
        std::cout << "a" << std::endl;
    }
    if (b == c) {
        std::cout << "c" << std::endl;
    }
    if (a <= b) {
        std::cout << "b" << std::endl;
    }
    rational d = b;
    std::cout << d << std::endl;
    std::cout << --a << ' ' << b++ << ' ';
    std::cout << b << std::endl;
    return 0;
}
