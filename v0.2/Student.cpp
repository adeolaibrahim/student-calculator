#include "Student.h"
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>

// ---------------- CONSTRUCTORS ----------------
Student::Student() : name(""), surname(""), exam(0.0) {}

Student::Student(const std::string& n, const std::string& s,
                 const std::vector<double>& hw, double e)
    : name(n), surname(s), homeworks(hw), exam(e) {}

// ---------------- COPY CONSTRUCTOR ----------------
Student::Student(const Student& other)
    : name(other.name), surname(other.surname),
      homeworks(other.homeworks), exam(other.exam) {}

// ---------------- ASSIGNMENT OPERATOR ----------------
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        homeworks = other.homeworks;
        exam = other.exam;
    }
    return *this;
}

// ---------------- DESTRUCTOR ----------------
Student::~Student() {
    // Nothing special to clean up (vector cleans itself)
}

// ---------------- FINAL BY AVERAGE ----------------
double Student::finalByAverage() const {
    double hwAverage = 0.0;
    if (!homeworks.empty()) {
        hwAverage = std::accumulate(homeworks.begin(), homeworks.end(), 0.0) / homeworks.size();
    }
    return 0.4 * hwAverage + 0.6 * exam;  // example: 40% HW + 60% exam
}

// ---------------- FINAL BY MEDIAN ----------------
double Student::finalByMedian() const {
    if (homeworks.empty()) return 0.6 * exam; // no homework
    std::vector<double> hwCopy = homeworks;
    std::sort(hwCopy.begin(), hwCopy.end());
    double median = 0.0;
    size_t n = hwCopy.size();
    if (n % 2 == 0) {
        median = (hwCopy[n/2 -1] + hwCopy[n/2]) / 2.0;
    } else {
        median = hwCopy[n/2];
    }
    return 0.4 * median + 0.6 * exam; // 40% HW median + 60% exam
}

// ---------------- RANDOMIZE ----------------
void Student::randomize(unsigned int seed, int hwCount, double minVal, double maxVal) {
    std::srand(seed);
    homeworks.clear();
    for (int i = 0; i < hwCount; ++i) {
        double val = minVal + (std::rand() / (double)RAND_MAX) * (maxVal - minVal);
        homeworks.push_back(val);
    }
    exam = minVal + (std::rand() / (double)RAND_MAX) * (maxVal - minVal);
}
