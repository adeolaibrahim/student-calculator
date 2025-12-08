#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "Student.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Exceptions.h"

// Read students from file (returns std::vector)
std::vector<Student> readStudentsFromFile(const std::string& filename);

// Template function: works with vector, list, deque, etc.
template <typename Container>
void writeStudentsToFile(const std::string& filename, const Container& students) {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw FileOpenError("Cannot open file for writing: " + filename);
    }

    // Optional header
    ofs << "Name Surname FinalAvg\n";

    for (const auto& s : students) {
        ofs << s.name << ' ' 
            << s.surname << ' ' 
            << std::fixed << std::setprecision(2) 
            << s.finalByAverage() << '\n';
    }
}

#endif // IOMANAGER_H
