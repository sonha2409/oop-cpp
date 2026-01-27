# Project 3: Employee Management System

C++ project for practicing **inheritance**, **method overriding**, and **calling base class methods** (the C++ equivalent of “super”).

## Files for Students

| File | Purpose |
|------|--------|
| **Employee.h** | Class declarations (base `Employee` and derived `Manager`, `Developer`, `Intern`, `SeniorManager`). **Do not change** unless instructed. |
| **FUNCTION_SPECIFICATION.md** | Detailed behavior of every function. Use this to implement each member function correctly. |
| **README.md** | This file — project overview and how to build/run. |

## Concepts Covered

- **Parent and child classes:** `Employee` is the base; `Manager`, `Developer`, `Intern` derive from it.
- **Method overriding:** Override `calculateSalary()`, `getResponsibilities()`, and `getRole()` in each derived class.
- **“Super” in C++:** Call the base implementation with the base class name and `::`, e.g.  
  `Manager::calculateSalary()` inside `SeniorManager::calculateSalary()`.
- **Single inheritance:** Each of Manager, Developer, Intern inherits only from `Employee`.
- **Multilevel inheritance:** `SeniorManager` inherits from `Manager` (Employee → Manager → SeniorManager).
- **Hierarchical inheritance:** Several classes (Manager, Developer, Intern) share one base (`Employee`).

## Your Task

1. **Implement** all functions declared in `Employee.h` in one or more `.cpp` files (e.g. `Employee.cpp`).
2. **Follow** the behavior described in `FUNCTION_SPECIFICATION.md` for each function.
3. **Define** static constants in your `.cpp` where the header declares them  
   (`MANAGER_BASE_SALARY`, `INTERN_STIPEND`, `SCOPE_BONUS`).
4. **Add** a small `main()` (e.g. in `main.cpp`) that constructs at least one of each type, stores them in base pointers if desired, and calls `displayInfo()` and `calculateSalary()` to test polymorphism.

## Suggested Build

- **Single .cpp:** Put all implementations in `Employee.cpp`, then compile e.g.  
  `g++ -std=c++17 -Wall -Wextra main.cpp Employee.cpp -o employee_demo`
- **With CMake:** Add `Employee.cpp` and `main.cpp` to your `add_executable(...)` and `target_include_directories(...)` so `#include "Employee.h"` works.

## Example Usage (after implementation)

```cpp
#include "Employee.h"
#include <iostream>
#include <memory>

int main() {
    Employee* e1 = new Manager("M001", "Alice", "alice@co.com", "2020-03-01", "Engineering", 5, "Senior", 12000.0);
    Employee* e2 = new Developer("D001", "Bob", "bob@co.com", "2021-06-15", "Engineering", "C++", 3, "Mid");
    Employee* e3 = new Intern("I001", "Carol", "carol@co.com", "2024-01-10", "Engineering", "State Univ", 6, "Alice");

    e1->displayInfo();
    std::cout << "\n";
    e2->displayInfo();
    std::cout << "\n";
    e3->displayInfo();

    delete e1;
    delete e2;
    delete e3;
    return 0;
}
```

Implement the classes and functions as specified so that this (or similar) code runs correctly and shows different roles, salaries, and responsibilities.
