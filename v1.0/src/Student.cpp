#include "Student.h"
#include <algorithm>
#include <numeric>
#include <cstdlib>

Student::Student() : name(""), surname(""), exam(0.0) {}
Student::Student(const std::string& n, const std::string& s, const std::vector<double>& hw, double e)
    : name(n), surname(s), homeworks(hw), exam(e) {}
Student::Student(const Student& other) = default;
Student& Student::operator=(const Student& other) = default;
Student::~Student() = default;

double Student::finalByAverage() const {
    double hwAverage = homeworks.empty() ? 0.0 :
        std::accumulate(homeworks.begin(), homeworks.end(), 0.0) / homeworks.size();
    return 0.4 * hwAverage + 0.6 * exam;
}

double Student::finalByMedian() const {
    if (homeworks.empty()) return 0.6 * exam;
    std::vector<double> hwCopy = homeworks;
    std::sort(hwCopy.begin(), hwCopy.end());
    size_t n = hwCopy.size();
    double median = (n % 2 == 0) ? (hwCopy[n/2-1] + hwCopy[n/2])/2.0 : hwCopy[n/2];
    return 0.4 * median + 0.6 * exam;
}

void Student::randomize(unsigned int seed, int hwCount, double minVal, double maxVal) {
    std::srand(seed);
    homeworks.clear();
    for (int i = 0; i < hwCount; ++i)
        homeworks.push_back(minVal + (std::rand() / (double)RAND_MAX) * (maxVal - minVal));
    exam = minVal + (std::rand() / (double)RAND_MAX) * (maxVal - minVal);
}
