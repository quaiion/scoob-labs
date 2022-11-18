#include <iostream>
#include <vector>

unsigned min_greater(std::vector<int> &vec, int thresh) {
    int seek = INT32_MAX;
    unsigned ans = UINT32_MAX;
    for (unsigned i = 0; i < vec.size(); ++i) {
        if (vec[i] > thresh && vec[i] < seek) {
            seek = vec[i];
            ans = i;
        }
    }
    return ans;
}

int main() {
    int thresh {};
    unsigned nelem {};
    std::cin >> thresh >> nelem;
    std::vector<int> vec(nelem);
    for (unsigned i = 0; i < nelem; ++i) {
        std::cin >> vec[i];
    }
    unsigned ans = min_greater(vec, thresh);
    if (ans == UINT32_MAX) {
        std::cout << "amogus" << std::endl;
    } else {
        std::cout << ans << std::endl;
    }
    return 0;
}
