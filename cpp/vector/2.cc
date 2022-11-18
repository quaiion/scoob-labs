#include <iostream>
#include <vector>

void reverse(std::vector<int> &vec) {
    std::vector<int> temp(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) {
        temp[i] = vec[vec.size() - i - 1];
    }
    vec.swap(temp);
}

int main() {
    unsigned nelem {};
    std::cin >> nelem;
    std::vector<int> vec(nelem);
    for (unsigned i = 0; i < nelem; ++i) {
        std::cin >> vec[i];
    }
    reverse(vec);
    for (unsigned i = 0; i < nelem; ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
