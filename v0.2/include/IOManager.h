#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "Student.h"
#include <string>
#include <vector>

std::vector<Student> readStudentsFromFile(const std::string& filename);
void writeStudentsToFile(const std::string& filename, const std::vector<Student>& students);

#endif // IOMANAGER_H
