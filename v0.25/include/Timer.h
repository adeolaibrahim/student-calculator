#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start;

public:
    // Constructor starts the timer
    Timer() { reset(); }

    // Reset the timer
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }

    // Get elapsed time in seconds
    double elapsedSeconds() const {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = now - start;
        return diff.count();
    }

    // Format seconds as string, e.g., "1.23 s"
    static std::string formatSeconds(double sec) {
        std::ostringstream out;
        out << std::fixed << std::setprecision(2) << sec << " s";
        return out.str();
    }
};

#endif // TIMER_H

