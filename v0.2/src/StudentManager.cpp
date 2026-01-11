// StudentManager.cpp
#include "StudentManager.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void StudentManager::addStudent(const Student& s) {
    students.push_back(s);
}

void StudentManager::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) throw FileException("Cannot open file: " + filename);

    students.clear();
    std::string line;
    std::getline(infile, line); // skip header if exists
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        Student s;
        if (!(iss >> s.name >> s.surname)) continue;

        std::vector<double> nums;
        double v;
        while (iss >> v) nums.push_back(v);
        if (!nums.empty()) {
            s.exam = nums.back();
            nums.pop_back();
            s.homeworks = nums;
        }
        students.push_back(s);
    }
}

void StudentManager::saveToFile(const std::string& filename) const {
    std::ofstream outfile(filename);
    if (!outfile) throw FileException("Cannot write file: " + filename);

    outfile << "Name Surname Final\n";
    for (const auto& s : students)
        outfile << s.name << " " << s.surname << " " << s.finalByAverage() << "\n";
}

void StudentManager::sortByName() {
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  if (a.surname != b.surname) return a.surname < b.surname;
                  return a.name < b.name;
              });
}

void StudentManager::splitPassedFailed(std::vector<Student>& passed, std::vector<Student>& failed) const {
    passed.clear();
    failed.clear();
    for (const auto& s : students)
        (s.finalByAverage() >= 5.0 ? passed : failed).push_back(s);
}
