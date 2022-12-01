#include <iostream>
#include <vector>

class stoodie_t {
private:
    unsigned age;
    double avscr;
    std::string name;
public:
    stoodie_t() {
        std::cout << "i am alive" << std::endl;
    }
    ~stoodie_t() {
        std::cout << "tweny wone" << std::endl;
    }
    void set_age(unsigned age_) {
        if (age_ > 50) {
            std::cout << "u ass (age)" << std::endl;
        } else {
            age = age_;
        }
    }
    unsigned get_age() {
        return age;
    }
    void set_avscr(double avscr_) {
        if (avscr_ < 2 || avscr_ > 10) {
            std::cout << "u ass (avscr)" << std::endl;
        } else {
            avscr = avscr_;
        }
    }
    double get_avscr() {
        return avscr;
    }
    void set_name(std::string name_) {
        name = name_;
    }
    std::string get_name() {
        return name;
    }
    void BOTAY() {
        avscr = (avscr > 9) ? 10 : avscr + 1;
    }
};

int main() {
    unsigned nstood{};
    std::cin >> nstood;
    std::vector<stoodie_t> vec(nstood);
    for (unsigned i = 0; i < nstood; ++i) {
        unsigned age;
        double avscr;
        std::string name;
        std::cin >> name >> age >> avscr;
        vec[i].set_name(name);
        vec[i].set_age(age);
        vec[i].set_avscr(avscr);
    }
    double scr_sum{0};
    for (auto &st : vec) {
        scr_sum += st.get_avscr();
    }
    std::cout << "average --> " << scr_sum / nstood << std::endl;
    std::cout << "time to botat" << std::endl;
    for (unsigned i = 0; i < nstood; ++i) {
        std::cout << vec[i].get_name() << " botaet... ";
        unsigned bot{};
        std::cin >> bot;
        for (unsigned j = 0; j < bot; ++j) {
            vec[i].BOTAY();
        }
    }
    scr_sum = 0;
    for (auto &st : vec) {
        scr_sum += st.get_avscr();
    }
    std::cout << "average --> " << scr_sum / nstood << std::endl;
    return 0;
}
