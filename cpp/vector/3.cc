#include <iostream>
#include <vector>

static inline void vecswap(std::vector<int> &vec, unsigned el1, unsigned el2) {
    int temp = vec[el1];
    vec[el1] = vec[el2];
    vec[el2] = temp;
}

void sortier(std::vector<int> &vec) {
    for (unsigned i = 1; i < vec.size(); ++i) {
        for (unsigned j = i; j > 0; --j) {
            if (vec[j] > vec[j - 1]) {
                vecswap(vec, j, j - 1);
            } else {
                break;
            }
        }
    }
}

int main() {
    unsigned nelem {};
    std::cin >> nelem;
    std::vector<int> vec;
    for (unsigned i = 0; i < nelem; ++i) {
        int temp {};
        std::cin >> temp;
        vec.push_back(temp);
    }
    sortier(vec);
    for (unsigned i = 0; i < nelem; ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
