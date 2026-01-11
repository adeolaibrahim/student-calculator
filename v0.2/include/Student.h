// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
public:
    std::string name;
    std::string surname;
    std::vector<double> homeworks;
    double exam;

    Student();
    Student(const std::string& n, const std::string& s,
            const std::vector<double>& hw, double e);
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    double finalByAverage() const;
    double finalByMedian() const;
    void randomize(unsigned int seed, int hwCount, double minVal, double maxVal);
};

#endif // STUDENT_H
