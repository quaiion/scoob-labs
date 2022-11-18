#include <iostream>
#include <vector>

int main() {
    unsigned nppl {};
    std::cin >> nppl;
    double sum {0};
    std::vector<double> vec(nppl);
    for (unsigned i = 0; i < nppl; ++i) {
        std::cin >> vec[i];
        sum += vec[i];
    }
    double avg = sum / nppl;
    std::cout << std::endl;
    for (unsigned i = 0; i < nppl; ++i) {
        if (vec[i] > avg) {
            std::cout << i << std::endl;
        }
    }
    return 0;
}
