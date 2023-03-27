#include "list.hh"
#include <iostream>
#include <vector>

int main() {
        std::vector<int> vec{1, 5, 2, 3, 11};
        list<int> ls(vec);
        ls.push_back(999);
        ls.push_front(111);
        list<int>::iterator it(ls.begin());
        ls.print();
        ls.insert(it += 2, 222);
        ls.print();
        it++;
        ++it;
        it -= 1;
        it += 2;
        ls.erase(it);
        ls.print();
        return 0;
}
