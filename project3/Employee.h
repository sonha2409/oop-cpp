/**
 * @file Employee.h
 * @brief Employee Management System - Header and class declarations
 *
 * Concepts demonstrated:
 *   - Parent and child classes (Employee -> Manager, Developer, Intern)
 *   - Method overriding (calculateSalary, getResponsibilities)
 *   - Calling base class (Employee:: or BaseClass:: in C++; no "super" keyword)
 *   - Single inheritance: Manager, Developer, Intern each inherit only from Employee
 *   - Multilevel inheritance: SeniorManager inherits from Manager, which inherits from Employee
 *   - Hierarchical inheritance: Manager, Developer, Intern all inherit from the same base Employee
 *
 * Students: Implement all declared member functions in Employee.cpp (or separate .cpp files).
 * See FUNCTION_SPECIFICATION.md for detailed behavior of each function.
 */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

// =============================================================================
// BASE CLASS: Employee
// =============================================================================
// All employee types share: id, name, email, hire date, department.
// Derived classes override salary calculation and responsibilities.
// =============================================================================

class Employee {
public:
    /**
     * Constructor. Initialize all common employee attributes.
     * @param id       Unique employee identifier
     * @param name     Full name
     * @param email    Work email
     * @param hireDate Hire date as string (e.g. "2024-01-15")
     * @param dept     Department name
     */
    Employee(const std::string& id,
             const std::string& name,
             const std::string& email,
             const std::string& hireDate,
             const std::string& dept);

    /**
     * Virtual destructor. Ensures derived objects are destroyed correctly
     * when deleted through a base-class pointer. Can be empty or log.
     */
    virtual ~Employee();

    // --- Getters (common properties) ---
    std::string getEmployeeId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getHireDate() const;
    std::string getDepartment() const;

    // --- Setters (common properties) ---
    void setDepartment(const std::string& dept);
    void setEmail(const std::string& email);

    /**
     * Compute salary for this employee. Base version may return 0 or a default.
     * Override in Manager, Developer, Intern (and SeniorManager) with role-specific logic.
     * @return Salary amount as a non-negative value
     */
    virtual double calculateSalary() const;

    /**
     * Return a human-readable description of this employee's main duties.
     * Override in each derived class to reflect role-specific responsibilities.
     * @return String describing responsibilities
     */
    virtual std::string getResponsibilities() const;

    /**
     * Return a short string suitable for reporting (e.g. "Employee" or "Manager").
     * Override in derived classes to return "Manager", "Developer", "Intern", "SeniorManager".
     */
    virtual std::string getRole() const;

    /**
     * Print a summary to standard output: role, id, name, department, salary, responsibilities.
     * Can call getRole(), getEmployeeId(), getName(), getDepartment(), calculateSalary(),
     * getResponsibilities(). May be overridden to add role-specific lines.
     */
    virtual void displayInfo() const;

protected:
    std::string employeeId;
    std::string name;
    std::string email;
    std::string hireDate;
    std::string department;
};

// =============================================================================
// DERIVED CLASS: Manager (Single + Hierarchical inheritance from Employee)
// =============================================================================
// Adds: team size, management level, annual bonus. Salary = base + bonus.
// =============================================================================

class Manager : public Employee {
public:
    /**
     * Constructor. Initialize Employee part via base constructor, then
     * teamSize, managementLevel, annualBonus. Use member initializer list
     * to call Employee::Employee(...).
     */
    Manager(const std::string& id,
            const std::string& name,
            const std::string& email,
            const std::string& hireDate,
            const std::string& dept,
            int teamSize,
            const std::string& level,
            double annualBonus);

    /**
     * Override: salary = baseSalary + annualBonus.
     * baseSalary can be a fixed constant for managers or stored in the class.
     */
    double calculateSalary() const override;

    /**
     * Override: return string describing management duties, e.g. leading team,
     * oversight, planning. Include team size and level if helpful.
     */
    std::string getResponsibilities() const override;

    std::string getRole() const override;

    int getTeamSize() const;
    std::string getManagementLevel() const;
    double getAnnualBonus() const;
    void setTeamSize(int size);
    void setAnnualBonus(double bonus);

protected:
    int teamSize;
    std::string managementLevel;  // e.g. "Senior", "Junior", "Director"
    double annualBonus;
    static const double MANAGER_BASE_SALARY;  // define in .cpp
};

// =============================================================================
// DERIVED CLASS: Developer (Single + Hierarchical inheritance from Employee)
// =============================================================================
// Adds: programming language, project count, expertise level. Salary by level + projects.
// =============================================================================

class Developer : public Employee {
public:
    /**
     * Constructor. Initialize Employee base and developer-specific fields.
     */
    Developer(const std::string& id,
              const std::string& name,
              const std::string& email,
              const std::string& hireDate,
              const std::string& dept,
              const std::string& language,
              int projectCount,
              const std::string& expertise);  // e.g. "Junior", "Mid", "Senior"

    double calculateSalary() const override;
    std::string getResponsibilities() const override;
    std::string getRole() const override;

    std::string getProgrammingLanguage() const;
    int getProjectCount() const;
    std::string getExpertiseLevel() const;
    void setProjectCount(int count);

protected:
    std::string programmingLanguage;
    int projectCount;
    std::string expertiseLevel;
    // Define in .cpp: base salary per level and per-project bonus (or formula constants)
};

// =============================================================================
// DERIVED CLASS: Intern (Single + Hierarchical inheritance from Employee)
// =============================================================================
// Adds: university, duration in months, mentor name. Fixed stipend or low salary.
// =============================================================================

class Intern : public Employee {
public:
    /**
     * Constructor. Initialize Employee base and intern-specific fields.
     */
    Intern(const std::string& id,
           const std::string& name,
           const std::string& email,
           const std::string& hireDate,
           const std::string& dept,
           const std::string& university,
           int durationMonths,
           const std::string& mentorName);

    double calculateSalary() const override;
    std::string getResponsibilities() const override;
    std::string getRole() const override;

    std::string getUniversity() const;
    int getDurationMonths() const;
    std::string getMentorName() const;

protected:
    std::string university;
    int durationMonths;
    std::string mentorName;
    static const double INTERN_STIPEND;  // define in .cpp
};

// =============================================================================
// DERIVED CLASS: SeniorManager (Multilevel: Employee -> Manager -> SeniorManager)
// =============================================================================
// Inherits from Manager. Extra responsibility scope and possibly higher bonus.
// =============================================================================

class SeniorManager : public Manager {
public:
    /**
     * Constructor. Call Manager::Manager(...) for base parts, then set
     * scope (e.g. "Regional", "Division", "Global").
     */
    SeniorManager(const std::string& id,
                  const std::string& name,
                  const std::string& email,
                  const std::string& hireDate,
                  const std::string& dept,
                  int teamSize,
                  const std::string& level,
                  double annualBonus,
                  const std::string& scope);

    /**
     * Override: e.g. Manager::calculateSalary() + scope bonus, or higher base.
     */
    double calculateSalary() const override;

    /**
     * Override: include scope and strategic/leadership responsibilities.
     */
    std::string getResponsibilities() const override;

    std::string getRole() const override;

    std::string getScope() const;

protected:
    std::string scope;  // "Regional", "Division", "Global", etc.
    static const double SCOPE_BONUS;  // define in .cpp
};

#endif // EMPLOYEE_H
