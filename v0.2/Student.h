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

    // Constructors
    Student();
    Student(const std::string& n, const std::string& s,
            const std::vector<double>& hw, double e);

    // Copy constructor (Rule of Three)
    Student(const Student& other);

    // Assignment operator (Rule of Three)
    Student& operator=(const Student& other);

    // Destructor (Rule of Three)
    ~Student();

    // Methods
    double finalByAverage() const;
    double finalByMedian() const;
    void randomize(unsigned int seed, int hwCount, double minVal, double maxVal);
};

#endif // STUDENT_H
