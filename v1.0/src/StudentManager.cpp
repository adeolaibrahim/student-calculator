#include "StudentManager.h"
#include "Utils.h"

#include <fstream>
#include <sstream>
#include <algorithm>

// add student
void StudentManager::addStudent(const Student& s) {
    students.push_back(s);
}

// load students
void StudentManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw FileException("Cannot open file: " + filename);
    }

    students.clear();
    std::string line;
    std::getline(in, line); // skip header

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        Student s;
        iss >> s.name >> s.surname;

        double value;
        std::vector<double> grades;
        while (iss >> value) {
            grades.push_back(value);
        }

        if (!grades.empty()) {
            s.exam = grades.back();
            grades.pop_back();
            s.homeworks = grades;
        }

        students.push_back(s);
    }
}

// save students
void StudentManager::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw FileException("Cannot write file: " + filename);
    }

    out << "Name Surname Final\n";
    for (const auto& s : students) {
        out << s.name << " " << s.surname << " "
            << s.finalByAverage() << "\n";
    }
}

// sort
void StudentManager::sortByName() {
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            if (a.surname != b.surname)
                return a.surname < b.surname;
            return a.name < b.name;
        }
    );
}

// strategy 1: copy
void StudentManager::splitPassedFailedCopy(std::vector<Student>& passed,
                                           std::vector<Student>& failed) const {
    passed.clear();
    failed.clear();

    for (const auto& s : students) {
        if (s.finalByAverage() >= 5.0)
            passed.push_back(s);
        else
            failed.push_back(s);
    }
}

// strategy 2: move
void StudentManager::splitPassedFailedMove(std::vector<Student>& failed) {
    failed.clear();

    auto it = std::partition(students.begin(), students.end(),
        [](const Student& s) {
            return s.finalByAverage() >= 5.0;
        });

    failed.insert(failed.end(),
                  std::make_move_iterator(it),
                  std::make_move_iterator(students.end()));

    students.erase(it, students.end());
}

const std::vector<Student>& StudentManager::getStudents() const {
    return students;
}

void StudentManager::clear() {
    students.clear();
}
