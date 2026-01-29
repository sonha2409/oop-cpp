/**
 * @file main.cpp
 * @brief Demo of Employee Management System: polymorphism and inheritance.
 */

#include "Employee.h"
#include <iostream>
#include <vector>

int main() {
    // Create one of each type; store in base pointers to show polymorphism
    Employee* e1 = new Manager("M001", "Alice", "alice@co.com", "2020-03-01",
                               "Engineering", 5, "Senior", 12000.0);
    Employee* e2 = new Developer("D001", "Bob", "bob@co.com", "2021-06-15",
                                "Engineering", "C++", 3, "Mid");
    Employee* e3 = new Intern("I001", "Carol", "carol@co.com", "2024-01-10",
                              "Engineering", "State Univ", 6, "Alice");
    Employee* e4 = new SeniorManager("SM001", "Dave", "dave@co.com", "2018-01-15",
                                     "Engineering", 12, "Director", 20000.0, "Regional");

    std::cout << "=== Employee Management System Demo ===\n\n";

    e1->displayInfo();
    std::cout << "\n";
    e2->displayInfo();
    std::cout << "\n";
    e3->displayInfo();
    std::cout << "\n";
    e4->displayInfo();

    // Polymorphism: same interface, different behavior
    std::cout << "\n=== Salary summary (via base pointer) ===\n";
    std::vector<Employee*> staff = { e1, e2, e3, e4 };
    for (Employee* p : staff) {
        std::cout << p->getName() << " (" << p->getRole() << "): $"
                  << p->calculateSalary() << "\n";
    }

    // Cleanup
    for (Employee* p : staff) {
        delete p;
    }

    return 0;
}
