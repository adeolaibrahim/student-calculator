#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include "Student.h"
#include "IOManager.h"
#include "Timer.h"

// Uncomment one of the two container types to test
using StudentContainer = std::list<Student>;
// using StudentContainer = std::deque<Student>;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    const std::string filename = argv[1];

    StudentContainer students;

    Timer t_total;

    // 1. Read data
    Timer t_read;
    try {
        if constexpr (std::is_same<StudentContainer, std::list<Student>>::value) {
            auto temp = readStudentsFromFile(filename); // returns std::vector<Student>
            students.insert(students.end(), temp.begin(), temp.end());
        } else {
            auto temp = readStudentsFromFile(filename);
            students.insert(students.end(), temp.begin(), temp.end());
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading file: " << e.what() << "\n";
        return 1;
    }
    double readSec = t_read.elapsedSeconds();

    // 2. Sort data
    Timer t_sort;
    if constexpr (std::is_same<StudentContainer, std::list<Student>>::value) {
        students.sort(studentNameCompare);
    } else {
        std::sort(students.begin(), students.end(), studentNameCompare);
    }
    double sortSec = t_sort.elapsedSeconds();

    // 3. Split into two halves
    Timer t_split;
    StudentContainer firstHalf, secondHalf;
    auto it = students.begin();
    std::advance(it, students.size()/2);
    firstHalf.insert(firstHalf.end(), students.begin(), it);
    secondHalf.insert(secondHalf.end(), it, students.end());
    double splitSec = t_split.elapsedSeconds();

    // 4. Write results to files
    Timer t_write;
    try {
        writeStudentsToFile("firstHalf.txt", firstHalf);
        writeStudentsToFile("secondHalf.txt", secondHalf);
    } catch (const std::exception& e) {
        std::cerr << "Error writing file: " << e.what() << "\n";
        return 1;
    }
    double writeSec = t_write.elapsedSeconds();

    double totalSec = t_total.elapsedSeconds();

    // 5. Print timings
    std::cout << "Timing report for file: " << filename << "\n";
    std::cout << "Read:  " << Timer::formatSeconds(readSec) << "\n";
    std::cout << "Sort:  " << Timer::formatSeconds(sortSec) << "\n";
    std::cout << "Split: " << Timer::formatSeconds(splitSec) << "\n";
    std::cout << "Write: " << Timer::formatSeconds(writeSec) << "\n";
    std::cout << "Total: " << Timer::formatSeconds(totalSec) << "\n";

    return 0;
}
