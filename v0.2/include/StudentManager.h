// StudentManager.h
#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <vector>
#include <string>

class StudentManager {
    std::vector<Student> students;

public:
    void addStudent(const Student& s);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    void sortByName();
    void splitPassedFailed(std::vector<Student>& passed, std::vector<Student>& failed) const;
    const std::vector<Student>& getStudents() const { return students; }
    void clear() { students.clear(); }
};

#endif // STUDENT_MANAGER_H
