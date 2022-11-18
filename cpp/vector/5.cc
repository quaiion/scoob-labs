#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<std::string> vec(3);
    for (unsigned i = 0; i < 3; ++i) {
        std::cin >> vec[i];
    }
    std::cout << std::endl;

    unsigned nO = 0;
    for (auto symb : vec[1]) {
        if (symb == 'o') {
            nO += 1;
        }
    }
    std::cout << nO << std::endl;

    std::sort(vec.begin(), vec.end());
    for (unsigned i = 0; i < 3; ++i) {
        std::cout << vec[i] << std::endl;
    }
}
