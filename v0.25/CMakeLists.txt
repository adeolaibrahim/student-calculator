cmake_minimum_required(VERSION 3.10)

project(StudentCalculator_v0.2 LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable warnings (good for school projects)
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Collect source files
set(SOURCES
    src/main.cpp
    src/Student.cpp
    src/StudentManager.cpp
    src/FileGenerator.cpp
)

# Create executable
add_executable(StudentCalculator ${SOURCES})

# Tell compiler where to find headers
target_include_directories(StudentCalculator PRIVATE ${PROJECT_SOURCE_DIR}/include)
