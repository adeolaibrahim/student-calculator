#include "StudentManager.h"
#include "FileGenerator.h"
#include "Utils.h"

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

// ================= VECTOR TEST =================
void testVector(const std::string& filename) {
    std::cout << "\n===== VECTOR =====\n";

    Timer t;
    StudentManager manager;

    t.start();
    manager.loadFromFile(filename);
    std::cout << "Loaded in " << t.elapsedSeconds() << " s\n";

    t.start();
    manager.sortByName();
    std::cout << "Sorted in " << t.elapsedSeconds() << " s\n";

    // Strategy 1: copy
    std::vector<Student> passed1, failed1;
    t.start();
    manager.splitPassedFailedCopy(passed1, failed1);
    std::cout << "Split (copy) in " << t.elapsedSeconds() << " s\n";

    // Strategy 2: move
    std::vector<Student> failed2;
    t.start();
    manager.splitPassedFailedMove(failed2);
    std::cout << "Split (move) in " << t.elapsedSeconds() << " s\n";

    t.start();
    manager.saveToFile("vector_passed.txt");
    std::cout << "Saved in " << t.elapsedSeconds() << " s\n";
}

// ================= LIST TEST =================
void testList(const std::string& filename) {
    std::cout << "\n===== LIST =====\n";

    Timer t;
    StudentManager manager;

    t.start();
    manager.loadFromFile(filename);
    std::cout << "Loaded in " << t.elapsedSeconds() << " s\n";

    // Convert vector -> list
    std::list<Student> students(manager.getStudents().begin(),
                                manager.getStudents().end());

    // Strategy 1: copy
    std::list<Student> passed, failed;
    t.start();
    std::copy_if(students.begin(), students.end(),
                 std::back_inserter(passed),
                 [](const Student& s){ return s.finalByAverage() >= 5.0; });
    std::copy_if(students.begin(), students.end(),
                 std::back_inserter(failed),
                 [](const Student& s){ return s.finalByAverage() < 5.0; });
    std::cout << "Split (copy) in " << t.elapsedSeconds() << " s\n";

    // Strategy 2: move
    t.start();
    students.remove_if([&failed](const Student& s){
        if (s.finalByAverage() < 5.0) {
            failed.push_back(s);
            return true;
        }
        return false;
    });
    std::cout << "Split (move) in " << t.elapsedSeconds() << " s\n";
}

// ================= DEQUE TEST =================
void testDeque(const std::string& filename) {
    std::cout << "\n===== DEQUE =====\n";

    Timer t;
    StudentManager manager;

    t.start();
    manager.loadFromFile(filename);
    std::cout << "Loaded in " << t.elapsedSeconds() << " s\n";

    std::deque<Student> students(manager.getStudents().begin(),
                                 manager.getStudents().end());

    // Strategy 1: copy
    std::deque<Student> passed, failed;
    t.start();
    std::copy_if(students.begin(), students.end(),
                 std::back_inserter(passed),
                 [](const Student& s){ return s.finalByAverage() >= 5.0; });
    std::copy_if(students.begin(), students.end(),
                 std::back_inserter(failed),
                 [](const Student& s){ return s.finalByAverage() < 5.0; });
    std::cout << "Split (copy) in " << t.elapsedSeconds() << " s\n";

    // Strategy 2: move
    t.start();
    auto it = std::partition(students.begin(), students.end(),
                             [](const Student& s){
                                 return s.finalByAverage() >= 5.0;
                             });
    failed.insert(failed.end(), it, students.end());
    students.erase(it, students.end());
    std::cout << "Split (move) in " << t.elapsedSeconds() << " s\n";
}

// ================= MAIN =================
int main() {
    try {
        std::vector<std::string> files = {
            "students1000.txt",
            "students10000.txt",
            "students100000.txt"
        };

        // Generate test files if missing
        for (auto& f : files) {
            FileGenerator::generateRandomFile(
                f,
                std::stoi(f.substr(8, f.find('.') - 8)),
                5
            );
        }

        for (const auto& f : files) {
            std::cout << "\n==============================";
            std::cout << "\nTesting file: " << f << "\n";

            testVector(f);
            testList(f);
            testDeque(f);
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
