#include "FileGenerator.h"
#include "Student.h"
#include "Utils.h"
#include <fstream>

void FileGenerator::generateRandomFile(const std::string& filename, size_t count, int hwCount) {
    std::ofstream outfile(filename);
    if (!outfile) throw FileException("Cannot open file: " + filename);

    outfile << "Name Surname HW1 HW2 ... HW" << hwCount << " Exam\n";
    for (size_t i = 1; i <= count; ++i) {
        Student s;
        s.name = "Name" + std::to_string(i);
        s.surname = "Surname" + std::to_string(i);
        s.randomize(i, hwCount, 0.0, 10.0);
        outfile << s.name << " " << s.surname;
        for (auto hw : s.homeworks) outfile << " " << hw;
        outfile << " " << s.exam << "\n";
    }
}
