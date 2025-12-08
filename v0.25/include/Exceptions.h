#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class FileOpenError : public std::runtime_error {
public:
    explicit FileOpenError(const std::string& msg) : std::runtime_error(msg) {}
};

class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string& msg) : std::runtime_error(msg) {}
};

#endif // EXCEPTIONS_H
