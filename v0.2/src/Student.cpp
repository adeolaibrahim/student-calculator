#include "Student.h"
#include <numeric>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <random>

Student::Student(const std::string& n, const std::string& s, const std::vector<double>& hw, double e)
    : name(n), surname(s), homeworks(hw), exam(e) {}

double Student::finalByAverage() const {
    double hwAverage = 0.0;
    if (!homeworks.empty()) {
        hwAverage = std::accumulate(homeworks.begin(), homeworks.end(), 0.0) / homeworks.size();
    }
    return 0.4 * hwAverage + 0.6 * exam;
}

double Student::finalByMedian() const {
    if (homeworks.empty()) {
        return 0.6 * exam;
    }
    std::vector<double> hwCopy = homeworks;
    std::sort(hwCopy.begin(), hwCopy.end());
    size_t n = hwCopy.size();
    double median = (n % 2 == 0) ? (hwCopy[n/2 - 1] + hwCopy[n/2]) / 2.0 : hwCopy[n/2];
    return 0.4 * median + 0.6 * exam;
}

std::string Student::toOutputString() const {
    std::ostringstream oss;
    oss << name << ' ' << surname << ' ' << std::fixed << std::setprecision(2) << finalByAverage();
    return oss.str();
}

// Randomize homework and exam grades
void Student::randomize(unsigned int seed, int hwCount, double minVal, double maxVal) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(minVal, maxVal);

    homeworks.resize(hwCount);
    for (int i = 0; i < hwCount; ++i) {
        homeworks[i] = dist(rng);
    }

    exam = dist(rng);
}
