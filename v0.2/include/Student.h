#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
public:
    std::string name;
    std::string surname;
    std::vector<double> homeworks;
    double exam = 0.0;

    Student() = default;
    Student(const std::string& n, const std::string& s, const std::vector<double>& hw, double e);

    double finalByAverage() const;
    double finalByMedian() const;

    std::string toOutputString() const; // single-line representation used for writing results

    // Randomly generate student data
    void randomize(unsigned int seed, int hwCount, double minVal, double maxVal);
};

inline bool studentNameCompare(const Student& a, const Student& b) {
    if (a.surname != b.surname) return a.surname < b.surname;
    return a.name < b.name;
}

#endif // STUDENT_H
