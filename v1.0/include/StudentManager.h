#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <vector>
#include <string>

class StudentManager {
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& s);

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    void sortByName();

    // Strategy 1: copy
    void splitPassedFailedCopy(std::vector<Student>& passed,
                               std::vector<Student>& failed) const;

    // Strategy 2: move failed students out
    void splitPassedFailedMove(std::vector<Student>& failed);

    const std::vector<Student>& getStudents() const;
    void clear();
};

#endif // STUDENT_MANAGER_H
