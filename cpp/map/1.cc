#include <map>
#include <iostream>
#include <vector>

static inline void parse_word(std::string &word, std::map<char, unsigned> &map) {
    for (auto let : word) {
        map[let] += 1;
    }
}

int main() {
    unsigned npair{};
    std::cin >> npair;
    std::vector<bool> vect(npair);
    for (unsigned i = 0; i < npair; ++i) {
        std::string word1, word2;
        std::map<char, unsigned> map1, map2;
        std::cin >> word1 >> word2;
        parse_word(word1, map1);
        parse_word(word2, map2);
        if (map1 == map2) {
            vect[i] = true;
        } else {
            vect[i] = false;
        }
    }
    for (unsigned i = 0; i < npair; ++i) {
        if (vect[i] == true) {
            std::cout << "yep" << std::endl;
        } else {
            std::cout << "nop" << std::endl;
        }
    }
    return 0;
}
