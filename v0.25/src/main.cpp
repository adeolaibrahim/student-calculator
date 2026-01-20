#include <iostream>
#include "StudentManager.h"
#include "FileGenerator.h"
#include "Utils.h"

int main() {
    try {
        Timer timer;
        std::vector<std::string> files = {
            "students10000.txt",
            "students100000.txt",
            "students1000000.txt",
            "students10000000.txt"
        };

        // Generate random files (if needed)
        for (auto& f : files) {
            timer.start();
            FileGenerator::generateRandomFile(f, std::stoi(f.substr(8, f.find('.')-8)), 5);
            std::cout << "Generated " << f << " in " << timer.elapsedSeconds() << " s\n";
        }

        StudentManager manager;
        timer.start();
        manager.loadFromFile(files[0]);
        std::cout << "Loaded in " << timer.elapsedSeconds() << " s\n";

        timer.start();
        manager.sortByName();
        std::cout << "Sorted in " << timer.elapsedSeconds() << " s\n";

        std::vector<Student> passed, failed;
        timer.start();
        manager.splitPassedFailed(passed, failed);
        std::cout << "Split in " << timer.elapsedSeconds() << " s\n";

        timer.start();
        StudentManager pm, fm;
        for (auto& s : passed) pm.addStudent(s);
        for (auto& s : failed) fm.addStudent(s);

        pm.saveToFile("passed.txt");
        fm.saveToFile("failed.txt");
        std::cout << "Saved files in " << timer.elapsedSeconds() << " s\n";

    } catch (const FileException& fe) {
        std::cerr << "File error: " << fe.what() << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }
}
