#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <thread>

constexpr unsigned default_age = 21U;
constexpr unsigned long default_slry = 500UL;
constexpr unsigned long min_slry = 100UL;
constexpr char default_name[] = "виталик";
constexpr char default_logfile_name[] = "work.log";

class worker_t {
public:
	worker_t(const std::string &name_, unsigned age_, unsigned long slry_,
		 std::ofstream *logfile_) {
		age = age_;
		slry = slry_;
		name = name_;
		logfile = logfile_;
		logfile->fill('.');
	}
	worker_t(const std::string &name_, unsigned age_,
		 std::ofstream *logfile_) {
		age = age_;
		slry = default_slry;
		name = name_;
		logfile = logfile_;
		logfile->fill('.');
	}
	worker_t(const std::string &name_, unsigned age_,
		 unsigned long slry_) {
		age = age_;
		slry = slry_;
		name = name_;
		logfile->open(default_logfile_name, std::ios::out);
		logfile->fill('.');
	}
	worker_t(const std::string &name_, unsigned age_) {
		age = age_;
		slry = default_slry;
		name = name_;
		logfile->open(default_logfile_name, std::ios::out);
		logfile->fill('.');
	}
	worker_t() {
		age = default_age;
		slry = default_slry;
		name = default_name;
		logfile->open(default_logfile_name, std::ios::out);
		logfile->fill('.');
	}

	void do_work() {
		(*logfile) << name << std::setw(16) << std::right << age << \
			std::setw(8) << std::right << slry << std::endl;
		if (slry < min_slry) {
			throw std::underflow_error("no money no cookies bro");
		}
		slry -= 1UL;
	}
	void report_stop() {
		(*logfile) << name << \
			" stopped working, starting a socialistic party..." << \
			std::endl;
	}
private:
	unsigned age;
	unsigned long slry;
	std::string name;
	std::ofstream *logfile;
};

typedef std::vector<worker_t> brigade_t;
typedef std::vector<std::thread> thrvec_t;

static inline brigade_t form_brigade(const unsigned nppl) {
	brigade_t brigade(nppl);
	std::ofstream *logfile = new std::ofstream;
	logfile->open(default_logfile_name, std::ios::out);
	for (unsigned i = 0; i < nppl; ++i) {
		std::string wname{};
		unsigned wage{};
		unsigned long wslry{};
		std::cin >> wname >> wage >> wslry;
		brigade.at(i) = worker_t(wname, wage, wslry, logfile);
	}
	return brigade;
}

static inline thrvec_t start_shift(brigade_t &brigade, const unsigned nppl) {
	thrvec_t thrvec(nppl);
	for (unsigned i = 0; i < nppl; ++i) {
		thrvec.at(i) = std::thread([&]() {
			worker_t worker = brigade.at(i);
			while (true) {
				try {
					worker.do_work();
				}
				catch(const std::underflow_error &exc) {
					worker.report_stop();
					break;
				}
			}
		});
	}
	return thrvec;
}

static inline void end_shift(thrvec_t &thrvec, const unsigned nppl) {
	for (unsigned i = 0; i < nppl; ++i) {
		thrvec[i].join();
	}
}

int main() {
	unsigned nppl{};
	std::cin >> nppl;

	brigade_t brigade = form_brigade(nppl);
	thrvec_t thrvec = start_shift(brigade, nppl);
	end_shift(thrvec, nppl);

	return 0;
}
