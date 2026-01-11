// FileGenerator.h
#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <string>

class FileGenerator {
public:
    static void generateRandomFile(const std::string& filename, size_t count, int hwCount);
};

#endif // FILE_GENERATOR_H
