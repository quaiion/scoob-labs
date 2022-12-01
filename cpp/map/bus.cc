#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

void new_bus(std::map<std::string, std::vector<std::string>> &busbase,
             std::unordered_map<std::string, std::vector<std::string>> &stopbase);
void buses_for_stop(std::unordered_map<std::string, std::vector<std::string>> &stopbase,
                    std::string &name);
void stops_for_bus(std::map<std::string, std::vector<std::string>> &busbase,
                   std::unordered_map<std::string, std::vector<std::string>> &stopbase,
                   std::string &name);
void all_buses(std::map<std::string, std::vector<std::string>> &busbase);

int main() {
    std::map<std::string, std::vector<std::string>> busbase;
    std::unordered_map<std::string, std::vector<std::string>> stopbase;
    unsigned nlines{};
    std::cin >> nlines;
    for (unsigned i = 0; i < nlines; ++i) {
        std::string com;
        std::cin >> com;
        if (com == "NEW_BUS") {
            new_bus(busbase, stopbase);
            break;
        } else if (com == "BUSES_FOR_STOP") {
            std::string name{};
            std::cin >> name;
            buses_for_stop(stopbase, name);
            break;
        } else if (com == "STOPS_FOR_BUS") {
            std::string name{};
            std::cin >> name;
            stops_for_bus(busbase, stopbase, name);
            break;
        } else if (com == "ALL_BUSES") {
            all_buses(busbase);
            break;
        } else {
            std::cout << "wrong input, command skipped" << std::endl;
            break;
        }
    }
    return 0;
}

void new_bus(std::map<std::string, std::vector<std::string>> &busbase,
             std::unordered_map<std::string, std::vector<std::string>> &stopbase) {
    std::string bus_name{};
    unsigned nstops;
    std::cin >> bus_name >> nstops;
    for (unsigned i = 0; i < nstops; ++i) {
        std::string stop_name{};
        std::cin >> stop_name;
        busbase[bus_name].push_back(stop_name);
        stopbase[stop_name].push_back(bus_name);
    }
}

void buses_for_stop(std::unordered_map<std::string, std::vector<std::string>> &stopbase,
                    std::string &name) {
    if (stopbase.count(name) == 0) {
        std::cout << "no stop" << std::endl;
        return;
    }
    std::vector<std::string> &vec = stopbase.at(name);
    for (unsigned i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void stops_for_bus(std::map<std::string, std::vector<std::string>> &busbase,
                   std::unordered_map<std::string, std::vector<std::string>> &stopbase,
                   std::string &name) {
    if (busbase.count(name) == 0) {
        std::cout << "no bus" << std::endl;
        return;
    }
    std::vector<std::string> &vec = busbase.at(name);
    for (unsigned i = 0; i < vec.size(); ++i) {
        std::cout << "stop " << vec[i] << ": ";
        std::vector<std::string> &subvec = stopbase.at(vec[i]);
        if (subvec.size() == 1) {
            std::cout << "no interchange" << std::endl;
            continue;
        }
        for (unsigned j = 0; j < subvec.size(); ++j) {
            if (subvec[j] != name) {
                std::cout << subvec[j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void all_buses(std::map<std::string, std::vector<std::string>> &busbase) {
    if (busbase.empty()) {
        std::cout << "no buses" << std::endl;
        return;
    }
    for (std::map<std::string, std::vector<std::string>>::iterator it = busbase.begin();
                                            it != busbase.end(); it++) {
        std::cout << "bus " << it->first << ": ";
        std::vector<std::string> &vec = it->second;
        for (unsigned i = 0; i < vec.size(); ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }
}
