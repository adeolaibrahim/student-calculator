#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <variant>
#include <algorithm>
#include <functional>
#include <filesystem>

#include "Student.h"
#include "IOManager.h"
#include "Generator.h"
#include "Timer.h"
#include "Exceptions.h"

namespace fs = std::filesystem;

using ContainerVariant = std::variant<std::vector<Student>, std::list<Student>, std::deque<Student>>;

// helpers to convert vector result into other containers
std::list<Student> vectorToList(const std::vector<Student>& v) {
    return std::list<Student>(v.begin(), v.end());
}
std::deque<Student> vectorToDeque(const std::vector<Student>& v) {
    return std::deque<Student>(v.begin(), v.end());
}

// Sorting helpers
void sortContainer(std::vector<Student>& c) {
    std::sort(c.begin(), c.end(), studentNameCompare);
}
void sortContainer(std::deque<Student>& c) {
    std::sort(c.begin(), c.end(), studentNameCompare);
}
void sortContainer(std::list<Student>& c) {
    c.sort(studentNameCompare);
}

// Split helpers: return two vectors (passed, failed)
std::pair<std::vector<Student>, std::vector<Student>> splitToVectors(const std::vector<Student>& src) {
    std::vector<Student> passed, failed;
    passed.reserve(src.size());
    failed.reserve(src.size()/4 + 10);
    for (const auto& s : src) {
        if (s.finalByAverage() >= 5.0) passed.push_back(s);
        else failed.push_back(s);
    }
    return {std::move(passed), std::move(failed)};
}
std::pair<std::vector<Student>, std::vector<Student>> splitToVectors(const std::deque<Student>& src) {
    std::vector<Student> passed, failed;
    passed.reserve(src.size());
    for (const auto& s : src) {
        if (s.finalByAverage() >= 5.0) passed.push_back(s);
        else failed.push_back(s);
    }
    return {std::move(passed), std::move(failed)};
}
std::pair<std::vector<Student>, std::vector<Student>> splitToVectors(const std::list<Student>& src) {
    std::vector<Student> passed, failed;
    passed.reserve(std::distance(src.begin(), src.end()));
    for (const auto& s : src) {
        if (s.finalByAverage() >= 5.0) passed.push_back(s);
        else failed.push_back(s);
    }
    return {std::move(passed), std::move(failed)};
}

// Write helpers: we standardize output format using vector
void writeSplitResults(const std::string& baseOutName, const std::vector<Student>& passed, const std::vector<Student>& failed) {
    std::string passFile = baseOutName + "_passed.txt";
    std::string failFile = baseOutName + "_failed.txt";
    writeStudentsToFile(passFile, passed);
    writeStudentsToFile(failFile, failed);
}

void printUsage(const char* prog) {
    std::cout << "Usage: " << prog << " [generate <count> <hwCount> <outFile>] | [process <container> <inFile> <outBase>]\n";
    std::cout << "  container: vector | list | deque\n";
    std::cout << "Examples:\n";
    std::cout << "  " << prog << " generate 10000 5 Students_10000.txt\n";
    std::cout << "  " << prog << " process vector Students_10000.txt results_10000\n";
}

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            printUsage(argv[0]);
            return 1;
        }
        std::string cmd = argv[1];
        if (cmd == "generate") {
            if (argc < 5) {
                printUsage(argv[0]);
                return 1;
            }
            size_t count = std::stoull(argv[2]);
            int hwCount = std::stoi(argv[3]);
            std::string outFile = argv[4];
            std::cout << "Generating " << count << " students to " << outFile << " (hwCount=" << hwCount << ")\n";
            Timer t;
            generateStudentFile(outFile, count, hwCount);
            std::cout << "Generation completed in " << Timer::formatSeconds(t.elapsedSeconds()) << "\n";
            return 0;
        } else if (cmd == "process") {
            if (argc < 5) {
                printUsage(argv[0]);
                return 1;
            }
            std::string container = argv[2];
            std::string inFile = argv[3];
            std::string outBase = argv[4];

            if (!fs::exists(inFile)) throw FileOpenError("Input file doesn't exist: " + inFile);

            Timer t_total; // total time for whole pipeline
            Timer t;

            // 1) Read
            t.reset();
            std::vector<Student> base = readStudentsFromFile(inFile); // read into vector first (fast streaming)
            double readSec = t.elapsedSeconds();
            std::cout << "Read " << base.size() << " records in " << Timer::formatSeconds(readSec) << "\n";

            // Convert to chosen container
            ContainerVariant containerVar;
            if (container == "vector") containerVar = std::move(base);
            else if (container == "list") containerVar = vectorToList(base);
            else if (container == "deque") containerVar = vectorToDeque(base);
            else throw std::invalid_argument("Invalid container: " + container);

            // 2) Sort
            t.reset();
            if (std::holds_alternative<std::vector<Student>>(containerVar)) {
                auto &c = std::get<std::vector<Student>>(containerVar);
                sortContainer(c);
            } else if (std::holds_alternative<std::list<Student>>(containerVar)) {
                auto &c = std::get<std::list<Student>>(containerVar);
                sortContainer(c);
            } else {
                auto &c = std::get<std::deque<Student>>(containerVar);
                sortContainer(c);
            }
            double sortSec = t.elapsedSeconds();
            std::cout << "Sorted in " << Timer::formatSeconds(sortSec) << "\n";

            // 3) Split into passed/failed and measure
            t.reset();
            std::vector<Student> passed, failed;
            if (std::holds_alternative<std::vector<Student>>(containerVar)) {
                std::tie(passed, failed) = splitToVectors(std::get<std::vector<Student>>(containerVar));
            } else if (std::holds_alternative<std::list<Student>>(containerVar)) {
                std::tie(passed, failed) = splitToVectors(std::get<std::list<Student>>(containerVar));
            } else {
                std::tie(passed, failed) = splitToVectors(std::get<std::deque<Student>>(containerVar));
            }
            double splitSec = t.elapsedSeconds();
            std::cout << "Split -> passed: " << passed.size() << " failed: " << failed.size()
                      << " in " << Timer::formatSeconds(splitSec) << "\n";

            // 4) Write passed/failed to files
            t.reset();
            writeSplitResults(outBase, passed, failed);
            double writeSec = t.elapsedSeconds();
            std::cout << "Wrote results in " << Timer::formatSeconds(writeSec) << "\n";

            std::cout << "Total pipeline time: " << Timer::formatSeconds(t_total.elapsedSeconds()) << "\n";
            // Additionally print breakdown
            std::cout << "Timings breakdown (s): read=" << readSec
                      << " sort=" << sortSec << " split=" << splitSec << " write=" << writeSec << "\n";
            return 0;
        } else {
            printUsage(argv[0]);
            return 1;
        }
    } catch (const FileOpenError& e) {
        std::cerr << "File error: " << e.what() << '\n';
        return 2;
    } catch (const ParseError& e) {
        std::cerr << "Parse error: " << e.what() << '\n';
        return 3;
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << '\n';
        return 99;
    }
}
