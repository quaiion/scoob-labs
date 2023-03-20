/**
 * The following implementation of a list may seem to you a bit
 * awkward, using slightly inefficient or unconvenient solutions.
 * The reason is that the code below was written precisely
 * following the technical specifications, proceeded by the teacher,
 * which were developed at first place being easy to understand -
 * sometimes at the expense of final program's elegance and
 * efficiency.
 */

#ifndef LIST_INCLUDED
#define LIST_INCLUDED

#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <cassert>

template<typename T>
class list {
private:
        unsigned long size_;

        class node {
        private:
                friend class list<T>;

                node *next = nullptr;
                node *prev = nullptr;
                T data;

                node(const T& data_, node *next_, node *prev_) :
                                                          next(next_),
                                                          prev(prev_),
                                                          data(data_) {}
        public:
                node() = default;
        };

        node *head;
        node *tail;
        node *pastend;

        void push_empty(const T &data_) {
                assert(head != nullptr && tail != nullptr
                       && pastend != nullptr);
                assert(head == pastend && tail == pastend);
                head = new node(data_, pastend, nullptr);
                pastend->prev = tail = head;
        }
        void pop_single() {
                assert(head != nullptr && tail != nullptr
                       && pastend != nullptr);
                assert(head == tail && head != pastend && tail != pastend);
                delete tail;
                pastend->prev = nullptr;
                head = tail = pastend;
        }

public:
        list() : size_(0) {
                pastend = new node;
                head = tail = pastend;
        }
        list(const std::vector<T>& vect) : list() {
                std::for_each(vect.cbegin(), vect.cend(),
                              [](auto elem) { push_back(elem); });
        }
        ~list() {
                assert(head != nullptr && tail != nullptr
                       && pastend != nullptr);
                assert(head->prev == nullptr && pastend->next == nullptr);
                for (node *curr = head; curr != nullptr; ) {
                        node *to_del = curr;
                        curr = curr->next;
                        delete to_del;
                }
                head = tail = pastend = nullptr;
                size_ = 0;
        }

        unsigned long size() { return size_; }
        bool empty() { return (size_ == 0); }

        class iterator {
        private:
                node *nd = nullptr;
                node *pe = nullptr;
                iterator(node *nd_, node *pe_) : nd(nd_), pe(pe_) {}
        public:
                iterator() = default;

                T& operator*() {
                        if (nd == nullptr || pe == nullptr) {
                                throw std::invalid_argument("invalid iterator \
                                                            to dereference");
                                return T();     // there might be a better solution
                        }
                        return nd->data;
                }

                iterator& operator=(const iterator& it) {
                        nd = it.nd;
                        pe = it.pe;
                        return *this;
                }

                bool operator==(const iterator& it) {
                        return (nd == it.nd && pe == it.pe);
                }
                bool operator!=(const iterator& it) {
                        return !operator==(it);
                }

                iterator& operator+=(int shft) {
                        if (nd == nullptr || pe == nullptr) {
                                throw std::invalid_argument("invalid iterator \
                                                            to perform +=");
                                return *this;
                        }
                        if (shft >= 0) {
                                for (int i = 0; i < shft && nd != pe;
                                                                ++i) {
                                        nd = nd->next;
                                }
                        } else {
                                for (int i = 0; i > shft && nd != nullptr;
                                                                --i) {
                                        nd = nd->prev;
                                }
                                if (nd == nullptr) {
                                        nd = pe;
                                }
                        }
                        return *this;
                }
                iterator& operator-=(int shft) {
                        if (nd == nullptr || pe == nullptr) {
                                throw std::invalid_argument("invalid iterator \
                                                            to perform -=");
                                return end();           // somehow this compiles, need to figure out how
                        }
                        if (shft >= 0) {
                                for (int i = 0; i < shft && nd != nullptr;
                                                                ++i) {
                                        nd = nd->prev;
                                }
                                if (nd == nullptr) {
                                        nd = pe;
                                }
                        } else {
                                for (int i = 0; i > shft && nd != pe;
                                                                --i) {
                                        nd = nd->next;
                                }
                        }
                        return *this;
                }
                iterator operator+(int shft) {
                        if (nd == nullptr || pe == nullptr) {
                                throw std::invalid_argument("invalid iterator \
                                                            to perform +");
                                return *this;
                        }
                        iterator it = *this;
                        return (it += shft);
                }
                iterator operator-(int shft) {
                        if (nd == nullptr || pe == nullptr) {
                                throw std::invalid_argument("invalid iterator \
                                                            to perform -");
                                return *this;
                        }
                        iterator it = *this;
                        return (it -= shft);
                }
                iterator& operator++() {
                        if (nd == nullptr || pe == nullptr) {
                                throw std::invalid_argument("invalid iterator \
                                                            to increment");
                                return *this;
                        }
                        if (nd != pe) {
                                nd = nd->next;
                        }
                        return *this;
                }
                iterator& operator--() {
                        if (nd == nullptr || pe == nullptr) {
                                throw std::invalid_argument("invalid iterator \
                                                            to decrement");
                                return *this;
                        }
                        nd = nd->prev;
                        if (nd == nullptr) {
                                nd = pe;
                        }
                        return *this;
                }
                iterator operator++(int) {
                        iterator it = *this;
                        operator++();
                        return it;
                }
                iterator operator--(int) {
                        iterator it = *this;
                        operator--();
                        return it;
                }
        };

private:
        iterator make_it(node *nd) {     // clearer code but copying too much, may be not the best decision
                return iterator(nd, pastend);
        }

public:
        iterator begin() { return make_it(head); }
        iterator end() { return make_it(pastend); }
        iterator fin() { return make_it(tail); }

        list& operator=(const list& ls) {
                assert(head != nullptr && tail != nullptr
                       && pastend != nullptr);
                assert(head->prev == nullptr && pastend->next == nullptr);
                for (node *curr = head; curr != pastend; ) {
                        node *to_del = curr;
                        curr = curr->next;
                        delete to_del;
                }
                head = tail = pastend;
                pastend->prev = nullptr;
                size_ = 0;
                std::for_each(ls.begin(), ls.end(),
                              [](const T& elem) { push_back(elem); });
                return *this;
        }

        bool operator==(const list& ls) {
                assert(head != nullptr && tail != nullptr
                       && pastend != nullptr);
                assert(head->prev == nullptr && pastend->next == nullptr);
                return std::equal(begin(), end(), ls.begin(), ls.end());
        }
        bool operator!=(const list& ls) {
                assert(head != nullptr && tail != nullptr
                       && pastend != nullptr);
                assert(head->prev == nullptr && pastend->next == nullptr);
                return !operator==(ls);
        }

        void push_back(const T& data_);
        void push_front(const T& data_);
        T pop_back();
        T pop_front();
        iterator insert(iterator pos, const T& data_);
        iterator erase(iterator pos);
        void print();
};

template<typename T>
void list<T>::push_back(const T& data_) {
        assert(head != nullptr && tail != nullptr
                && pastend != nullptr);
        assert(head->prev == nullptr && pastend->next == nullptr);
        if (empty()) {
                push_empty(data_);
        } else {
                assert(tail->next == pastend
                        && pastend->prev == tail);
                tail->next = new node(data_, pastend, tail);
                tail = tail->next;
                pastend->prev = tail;
        }
        size_ += 1;
}

template<typename T>
void list<T>::push_front(const T& data_) {
        assert(head != nullptr && tail != nullptr
                && pastend != nullptr);
        assert(head->prev == nullptr && pastend->next == nullptr);
        if (empty()) {
                push_empty(data_);
        } else {
                assert(tail->next == pastend
                        && pastend->prev == tail);
                head->prev = new node(data_, head, nullptr);
                head = head->prev;
        }
        size_ += 1;
}

template<typename T>
T list<T>::pop_back() {
        assert(head != nullptr && tail != nullptr
                && pastend != nullptr);
        assert(head->prev == nullptr && pastend->next == nullptr);
        if (empty()) {
                assert(head == pastend && tail == pastend);
                throw std::underflow_error("tail popped empty");
                return T();                     // there might be a better solution
        }
        assert(tail->next == pastend && pastend->prev == tail);
        T temp = tail->data;                    // maybe should use value assignment here
        size_ -= 1;
        if (size_ == 0) {
                pop_single();
        } else {
                tail = tail->prev;
                delete tail->next;
                tail->next = pastend;
                pastend->prev = tail;
        }
        return temp;
}

template<typename T>
T list<T>::pop_front() {
        assert(head != nullptr && tail != nullptr
                && pastend != nullptr);
        assert(head->prev == nullptr && pastend->next == nullptr);
        if (empty()) {
                assert(head == pastend && tail == pastend);
                throw std::underflow_error("head popped empty");
                return T();                     // there might be a better solution
        }
        assert(tail->next == pastend && pastend->prev == tail);
        T temp = head->data;                    // maybe should use value assignment here
        size_ -= 1;
        if (size_ == 0) {
                pop_single();
        } else {
                head = head->next;
                delete head->prev;
                head->prev = nullptr;
        }
        return temp;
}

template<typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T& data_) {
        assert(head != nullptr && tail != nullptr
                && pastend != nullptr);
        assert(head->prev == nullptr && pastend->next == nullptr);
        if (pos == pastend) {
                throw std::range_error("inserted after past-end");
                return end();
        }
        assert(tail->next == pastend && pastend->prev == tail);
        pos->nd->next->prev = new node(data_, pos->nd->next, pos->nd);
        pos->nd->next = pos->nd->next->prev;
        if (pos->nd == tail) {
                tail = pos->nd->next;
        }
        size_ += 1;
        return make_it(pos->nd->next->next);
}

template<typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
        assert(head != nullptr && tail != nullptr
                && pastend != nullptr);
        assert(head->prev == nullptr && pastend->next == nullptr);
        if (pos == pastend) {
                throw std::range_error("erased past-end node");
                return end();
        }
        assert(tail->next == pastend && pastend->prev == tail);
        size_ -= 1;
        if (size_ == 0) {
                pop_single();
                return end();
        }
        assert(head != tail);
        if (pos->nd == head) {
                head = head->next;
        } else {
                pos->nd->prev->next = pos->nd->next;
                if (pos->nd == tail) {
                        tail = tail->prev;
                }
        }
        pos->nd->next->prev = pos->nd->prev;
        iterator it = make_it(pos->nd->next);
        delete pos->nd;
        return it;
}

template<typename T>
void list<T>::print() {
        assert(head != nullptr && tail != nullptr
                && pastend != nullptr);
        assert(head->prev == nullptr && pastend->next == nullptr);
        std::for_each(begin(), end(), [](const T& elem) {
                std::cout << "[ " << elem << " ]->"; });
        std::cout << "[ PAST-END_NODE ]" << std::endl;
}

#endif
