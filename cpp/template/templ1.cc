#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>

template<typename T>
std::string to_string(const T& cont, char delim) {
        std::stringstream str{};
        std::for_each(std::cbegin<T>(cont), std::cend<T>(cont),
                      [&str, delim](typename T::value_type elem){ str << elem << delim << ' '; });
        return str.str();
} 

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& exemp) {
        return os << '[' << exemp.first << "; " << exemp.second << ']';
}

template<typename Tkey, typename Tval>
std::ostream& operator<<(std::ostream& os, const std::map<Tkey, Tval>& exemp) {
        return os << to_string<std::map<Tkey, Tval>>(exemp, ';') << std::endl;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& exemp) {
        return os << to_string<std::vector<T>>(exemp, ';') << std::endl;
}

int main() {
        std::map<int, int> map{};
        map.insert({{1, 1}, {2, 2}, {3, 1}, {6, 33}, {13, 11}, {11, 12}});
        std::cout << map;
        return 0;
}
