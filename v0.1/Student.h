#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>

class Student {
public:
    // data members
    std::string name;
    std::string surname;
    std::vector<double> homeworks;
    double exam;

    // constructors & rule of three
    Student();
    Student(const std::string& name, const std::string& surname,
            const std::vector<double>& hw, double exam);
    Student(const Student& other);            // copy constructor
    Student& operator=(const Student& other); // copy assignment
    ~Student();                               // destructor

    // input/output
    friend std::istream& operator>>(std::istream& in, Student& s);
    friend std::ostream& operator<<(std::ostream& out, const Student& s);

    // grade calculations
    double finalByAverage() const; // uses average of homeworks
    double finalByMedian() const;  // uses median of homeworks

    // utility
    void randomize(unsigned int seed, size_t hwCount = 5, double minVal = 0, double maxVal = 10);
};

#endif // STUDENT_H
