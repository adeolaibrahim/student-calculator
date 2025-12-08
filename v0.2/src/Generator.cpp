#include "Generator.h"
#include <fstream>
#include <stdexcept>
#include <random>
#include <sstream>
#include <iomanip>

// Generates file with lines like: NameX SurnameX hw1 hw2 ... hwN exam
// We stream directly to file and do not keep memory for all records.
void generateStudentFile(const std::string& filename, size_t count, int hwCount) {
    std::ofstream ofs(filename, std::ios::out);
    if (!ofs) throw std::runtime_error("Cannot open file for writing: " + filename);
    // write simple header
    ofs << "Name Surname";
    for (int i = 1; i <= hwCount; ++i) ofs << " HW" << i;
    ofs << " Exam\n";

    // optionally use a fast RNG
    std::mt19937_64 rng(123456789ULL);
    std::uniform_real_distribution<double> dist(0.0, 10.0);

    for (size_t i = 1; i <= count; ++i) {
        ofs << "Name" << i << ' ' << "Surname" << i;
        for (int h = 0; h < hwCount; ++h) {
            double val = dist(rng);
            ofs << ' ' << std::fixed << std::setprecision(2) << val;
        }
        double exam = dist(rng);
        ofs << ' ' << std::fixed << std::setprecision(2) << exam << '\n';
        if (!ofs) throw std::runtime_error("Write failed mid-file for: " + filename);
    }
    ofs.flush();
}
