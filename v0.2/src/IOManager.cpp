#include "IOManager.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>  // for std::setprecision, std::fixed

// Reads a list of students from a file
std::vector<Student> readStudentsFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw FileOpenError("Cannot open file for reading: " + filename);
    }

    std::vector<Student> students;
    std::string line;

    while (std::getline(ifs, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        Student s;

        if (!(iss >> s.name >> s.surname)) {
            // Skip malformed lines
            continue;
        }

        double value;
        std::vector<double> nums;

        while (iss >> value) nums.push_back(value);

        if (!nums.empty()) {
            s.exam = nums.back();
            nums.pop_back();
            s.homeworks = std::move(nums);
        } else {
            s.exam = 0.0;
            s.homeworks.clear();
        }

        students.push_back(std::move(s));
    }

    return students;
}

// Writes a list of students to a file
void writeStudentsToFile(const std::string& filename, const std::vector<Student>& students) {
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
