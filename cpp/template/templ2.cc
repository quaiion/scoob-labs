#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

template<typename Tcont>
bool f1(const Tcont& cont, typename Tcont::value_type key) {
        return std::any_of(cont.cbegin(), cont.cend(),
                           [key](auto elem) { return (elem == key); });
}

template<typename Tcont>
inline bool f2(const Tcont& cont) { return (cont.size() % 2 == 0); }

class checker {
        unsigned counter{0};
public:
        ~checker() {
                std::cout << counter << std::endl;
        }

        template<typename Tbinpredic, typename Tcont>
        void check(Tbinpredic predic, const std::vector<Tcont>& vec,
                   typename Tcont::value_type key) {
                counter += std::count_if(vec.cbegin(), vec.cend(),
                                         [key, predic](Tcont cont) {
                                                return predic(cont, key); });
        }

        template<typename Tunpredic, typename Tcont>
        void check(Tunpredic predic, const std::vector<Tcont>& vec) {
                counter += std::count_if(vec.cbegin(), vec.cend(), predic);
        }
};

int main() {
        checker ch{};
        std::vector<std::vector<int>> vec1{{2, 1, 1}, {}, {12, 23, 1}, {4}};
        std::vector<std::map<int, int>> vec2{{{1, 2}, {1, 3}, {12, 12}},
                                             {{3, 0}, {14, 44}}, {}};
        ch.check(f1<std::vector<int>>, vec1, 1);
        ch.check(f2<std::vector<int>>, vec1);
        ch.check(f1<std::map<int, int>>, vec2, {1, 2});
        ch.check(f2<std::map<int, int>>, vec2);
        return 0;
}
