#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Student.h"
#include <limits>

void printHeader(bool showMethod) {
    std::cout << std::left << std::setw(12) << "Name"
              << std::setw(14) << "Surname";
    if (showMethod) {
        std::cout << std::setw(16) << "Final (Avg.)"
                  << "| " << std::setw(12) << "Final (Med.)" << "\n";
        std::cout << std::string(58, '-') << "\n";
    } else {
        std::cout << std::setw(16) << "Final_Point(Aver.)" << "\n";
        std::cout << std::string(44, '-') << "\n";
    }
}

int main() {
    std::cout << "Student Calculator (v0.1) - beginner friendly\n\n";

    // Option menu
    std::cout << "Choose input mode:\n";
    std::cout << "  1) Enter students manually (keyboard)\n";
    std::cout << "  2) Load from Students folder\n";
    std::cout << "  3) Generate random students\n";
    std::cout << "Select (1/2/3): ";
    int mode;
    if (!(std::cin >> mode)) return 0;

    std::vector<Student> students;

    // ----------- MODE 1: MANUAL INPUT -----------
    if (mode == 1) {
        std::cout << "Enter students one per line in format:\n";
        std::cout << "Name Surname hw1 hw2 ... hwN exam\n";
        std::cout << "When done, enter an empty line.\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string line;
        while (true) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) break;
            if (line.empty()) break;

            std::istringstream iss(line);
            Student s;
            if (!(iss >> s.name >> s.surname)) continue;

            double v;
            std::vector<double> nums;
            while (iss >> v) nums.push_back(v);

            if (!nums.empty()) {
                s.exam = nums.back();
                nums.pop_back();
                s.homeworks = nums;
            } else {
                s.exam = 0.0;
            }
            students.push_back(s);
        }
    }

    // ----------- MODE 2: LOAD FROM FOLDER -----------
    else if (mode == 2) {
        std::cout << "\nSelect a file from the Students.txt folder:\n";
        std::cout << "  1) students10000.txt\n";
        std::cout << "  2) students100000.txt\n";
        std::cout << "  3) students1000000.txt\n";
        std::cout << "Choose (1/2/3): ";

        int choice;
        std::cin >> choice;

        std::string filename;

        if (choice == 1)
            filename = "Students.txt/students10000.txt";
        else if (choice == 2)
            filename = "Students.txt/students100000.txt";
        else if (choice == 3)
            filename = "Students.txt/students1000000.txt";
        else {
            std::cerr << "Invalid selection.\n";
            return 1;
        }

        std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Could not open file: " << filename << "\n";
            return 1;
        }

        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            Student s;

            if (!(iss >> s.name >> s.surname)) continue;

            double v;
            std::vector<double> nums;
            while (iss >> v) nums.push_back(v);

            if (!nums.empty()) {
                s.exam = nums.back();
                nums.pop_back();
                s.homeworks = nums;
            } else {
                s.exam = 0.0;
            }

            students.push_back(s);
        }
    }

    // ----------- MODE 3: RANDOM GENERATION -----------
    else if (mode == 3) {
        std::cout << "How many students to generate? ";
        int count; std::cin >> count;

        std::cout << "How many homework entries per student? ";
        int hwCount; std::cin >> hwCount;

        for (int i = 0; i < count; ++i) {
            Student s;
            s.name = "Name" + std::to_string(i+1);
            s.surname = "Surname" + std::to_string(i+1);
            s.randomize(static_cast<unsigned int>(i + 42), hwCount, 0.0, 10.0);
            students.push_back(s);
        }
    }

    else {
        std::cerr << "Invalid selection\n";
        return 1;
    }

    if (students.empty()) {
        std::cout << "No students loaded.\n";
        return 0;
    }

    // ----------- CHOOSE FINAL CALCULATION METHOD -----------
    std::cout << "\nChoose calculation method:\n";
    std::cout << "  1) Average only\n";
    std::cout << "  2) Median only\n";
    std::cout << "  3) Show both (Avg + Med)\n";
    std::cout << "Select (1/2/3): ";

    int calcMode;
    std::cin >> calcMode;

    bool showBoth = (calcMode == 3);
    bool showAvgOnly = (calcMode == 1);

    // Sort alphabetically
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  if (a.surname != b.surname) return a.surname < b.surname;
                  return a.name < b.name;
              });

    // ----------- PRINT RESULTS -----------
    printHeader(showBoth);
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& s : students) {
        std::cout << std::left << std::setw(12) << s.name
                  << std::setw(14) << s.surname;

        if (showBoth) {
            std::cout << std::setw(16) << s.finalByAverage()
                      << "| " << std::setw(12) << s.finalByMedian();
        } else if (showAvgOnly) {
            std::cout << std::setw(16) << s.finalByAverage();
        } else {
            std::cout << std::setw(16) << s.finalByMedian();
        }

        std::cout << "\n";
    }

    return 0;
}
