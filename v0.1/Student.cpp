#include "Student.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>

// Default constructor
Student::Student() : name(""), surname(""), homeworks(), exam(0.0) {}

// Parameterized constructor
Student::Student(const std::string& name_, const std::string& surname_,
                 const std::vector<double>& hw, double exam_)
    : name(name_), surname(surname_), homeworks(hw), exam(exam_) {}

// Copy constructor
Student::Student(const Student& other)
    : name(other.name), surname(other.surname), homeworks(other.homeworks), exam(other.exam) {}

// Copy assignment
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        homeworks = other.homeworks;
        exam = other.exam;
    }
    return *this;
}

// Destructor
Student::~Student() {
    // nothing special to release (vector will manage itself)
}

// Overloaded input: expects: Name Surname hw1 hw2 ... exam
std::istream& operator>>(std::istream& in, Student& s) {
    // We'll read name and surname, then read the rest of the line into values
    if (!(in >> s.name >> s.surname)) return in;

    s.homeworks.clear();
    std::string restOfLine;
    std::getline(in, restOfLine); // rest contains homework and exam
    if (restOfLine.empty()) {
        // nothing more on this line
        s.exam = 0.0;
        return in;
    }

    // parse numbers from restOfLine
    std::istringstream iss(restOfLine);
    double value;
    std::vector<double> all;
    while (iss >> value) all.push_back(value);
    if (!all.empty()) {
        if (all.size() >= 1) {
            s.exam = all.back();
            all.pop_back();
        } else s.exam = 0.0;
        s.homeworks = all;
    } else {
        s.exam = 0.0;
        s.homeworks.clear();
    }
    return in;
}

// Overloaded output: will print name and surname only (other output done in main)
std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << s.name << " " << s.surname;
    return out;
}

double Student::finalByAverage() const {
    double hwAvg = 0.0;
    if (!homeworks.empty()) {
        hwAvg = std::accumulate(homeworks.begin(), homeworks.end(), 0.0) / homeworks.size();
    }
    return 0.4 * hwAvg + 0.6 * exam;
}

double Student::finalByMedian() const {
    if (homeworks.empty()) {
        return finalByAverage();
    }
    std::vector<double> tmp = homeworks;
    std::sort(tmp.begin(), tmp.end());
    double median;
    size_t n = tmp.size();
    if (n % 2 == 1) median = tmp[n/2];
    else median = (tmp[n/2 - 1] + tmp[n/2]) / 2.0;
    return 0.4 * median + 0.6 * exam;
}

void Student::randomize(unsigned int seed, size_t hwCount, double minVal, double maxVal) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    homeworks.clear();
    for (size_t i = 0; i < hwCount; ++i) homeworks.push_back(std::round(dist(rng) * 10.0) / 10.0);
    exam = std::round(dist(rng) * 10.0) / 10.0;
}
