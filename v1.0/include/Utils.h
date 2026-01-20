#ifndef UTILS_H
#define UTILS_H

#include <stdexcept>
#include <string>
#include <chrono>

class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class Timer {
    std::chrono::high_resolution_clock::time_point startTime;

public:
    void start() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(end - startTime).count();
    }
};

#endif
