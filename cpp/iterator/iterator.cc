#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <set>

void func1(const std::vector<int> &vec, const int val) {
	std::vector<int>::const_iterator piv =
		std::find_if(vec.cbegin(), vec.cend(),
			     [val](int cmp_val){ return (cmp_val > val) ? true : false; });
	std::for_each(std::make_reverse_iterator(piv), vec.crend(),
		      [](int prnt_val){ std::cout << prnt_val << ' '; });
	std::cout << std::endl;
}

void func2(const std::string &str) {
	std::string::const_iterator cur = str.cbegin(), end = str.cend();
	while (true) {
		if (*cur == ' ') {
			cur += 1;
			continue;
		}
		std::string::const_iterator forcur =
				std::find(cur, end, ' ');
		std::for_each(cur, forcur, [](char symb){ std::cout << symb; });
		std::cout << std::endl;
		if (forcur == end)
			break;
		cur = forcur + 1;
	}
}

template<typename T>
std::vector<T> func3(const std::set<T> &set, T val) {
	std::vector<T> vec{};
	typename std::set<T>::const_iterator piv = set.upper_bound(val);
	if (piv == set.cend())
		return vec;
	std::for_each(set.crbegin(), std::make_reverse_iterator(piv),
		      [&vec](const T &elem){ vec.push_back(elem); });
	return vec;
}

int main() {
	const std::vector<int> vec{1, 2, 3, 5, 6, 8, 12};
	std::for_each(vec.cbegin(), vec.cend(), [](int val){ std::cout << val << ' '; });
	std::cout << std::endl;
	func1(vec, 7);

	const std::string str{"do not   go gentle  into that good night."};
	std::cout << std::endl << str << std::endl;
	func2(str);

	const std::set<int> set{1, 12, 4, 5, 8, 11, 64};
	std::cout << std::endl;
	std::for_each(set.cbegin(), set.cend(), [](int val){ std::cout << val << ' '; });
	std::vector<int> vec2 = func3(set, 4);
	std::cout << std::endl;
	std::for_each(vec2.cbegin(), vec2.cend(), [](int val){ std::cout << val << ' '; });
	std::cout << std::endl;

	return 0;
}
