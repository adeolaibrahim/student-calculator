# Student Calculator

## Project Description
This project manages and analyzes student data. It reads student records from files,
calculates final grades, sorts students, and separates them into "passed" and "failed"
groups. The project focuses on performance analysis using different STL containers and algorithms.

---

## Releases

### v0.1
- Basic student structure
- Manual input and simple calculations

### v0.2
- Refactored code into classes
- Added file input/output
- Generated large student datasets
- Performance measurement added

### v0.25
- Implemented `std::vector`, `std::list`, and `std::deque`
- Compared container performance

### v1.0
- Optimized algorithms using `<algorithm>`
- Implemented two splitting strategies:
  - Strategy 1: Copy into new containers
  - Strategy 2: Move + erase using `std::partition`
- Performance comparison completed
- Final optimized solution selected

---

## Performance Results Summary

- **Fastest container**: `std::vector`
- **Best strategy**: S
