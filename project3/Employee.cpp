/**
 * @file Employee.cpp
 * @brief Implementation of Employee Management System classes.
 */

#include "Employee.h"
#include <iostream>

// =============================================================================
// Static constants (define in .cpp for linker)
// =============================================================================
const double Manager::MANAGER_BASE_SALARY = 80000.0;
const double Intern::INTERN_STIPEND = 2500.0;
const double SeniorManager::SCOPE_BONUS = 15000.0;

// Developer salary tiers (local constants, not static members)
namespace {
const double JUNIOR_BASE = 50000.0;
const double MID_BASE    = 70000.0;
const double SENIOR_BASE = 95000.0;
const double PER_PROJECT_BONUS = 2000.0;
}

// =============================================================================
// Employee
// =============================================================================

Employee::Employee(const std::string& id,
                   const std::string& name,
                   const std::string& email,
                   const std::string& hireDate,
                   const std::string& dept)
    : employeeId(id), name(name), email(email), hireDate(hireDate), department(dept) {}

Employee::~Employee() = default;

std::string Employee::getEmployeeId() const { return employeeId; }
std::string Employee::getName() const { return name; }
std::string Employee::getEmail() const { return email; }
std::string Employee::getHireDate() const { return hireDate; }
std::string Employee::getDepartment() const { return department; }

void Employee::setDepartment(const std::string& dept) { department = dept; }
void Employee::setEmail(const std::string& email) { this->email = email; }

double Employee::calculateSalary() const {
    return 0.0;
}

std::string Employee::getResponsibilities() const {
    return "General employee duties and assigned tasks.";
}

std::string Employee::getRole() const {
    return "Employee";
}

void Employee::displayInfo() const {
    std::cout << "Role: " << getRole() << "\n"
              << "ID: " << getEmployeeId() << "\n"
              << "Name: " << getName() << "\n"
              << "Department: " << getDepartment() << "\n"
              << "Salary: " << calculateSalary() << "\n"
              << "Responsibilities: " << getResponsibilities() << "\n";
}

// =============================================================================
// Manager
// =============================================================================

Manager::Manager(const std::string& id,
                 const std::string& name,
                 const std::string& email,
                 const std::string& hireDate,
                 const std::string& dept,
                 int teamSize,
                 const std::string& level,
                 double annualBonus)
    : Employee(id, name, email, hireDate, dept),
      teamSize(teamSize),
      managementLevel(level),
      annualBonus(annualBonus) {}

double Manager::calculateSalary() const {
    return MANAGER_BASE_SALARY + annualBonus;
}

std::string Manager::getResponsibilities() const {
    return "Lead team of " + std::to_string(teamSize) + " members; " +
           managementLevel + " management oversight and planning.";
}

std::string Manager::getRole() const {
    return "Manager";
}

int Manager::getTeamSize() const { return teamSize; }
std::string Manager::getManagementLevel() const { return managementLevel; }
double Manager::getAnnualBonus() const { return annualBonus; }
void Manager::setTeamSize(int size) { teamSize = size; }
void Manager::setAnnualBonus(double bonus) { annualBonus = bonus; }

// =============================================================================
// Developer
// =============================================================================

Developer::Developer(const std::string& id,
                     const std::string& name,
                     const std::string& email,
                     const std::string& hireDate,
                     const std::string& dept,
                     const std::string& language,
                     int projectCount,
                     const std::string& expertise)
    : Employee(id, name, email, hireDate, dept),
      programmingLanguage(language),
      projectCount(projectCount),
      expertiseLevel(expertise) {}

double Developer::calculateSalary() const {
    double levelBase = MID_BASE;  // default
    if (expertiseLevel == "Junior") levelBase = JUNIOR_BASE;
    else if (expertiseLevel == "Mid") levelBase = MID_BASE;
    else if (expertiseLevel == "Senior") levelBase = SENIOR_BASE;
    return levelBase + projectCount * PER_PROJECT_BONUS;
}

std::string Developer::getResponsibilities() const {
    return "Software development in " + programmingLanguage + " as " +
           expertiseLevel + " developer; contribute to " +
           std::to_string(projectCount) + " project(s).";
}

std::string Developer::getRole() const {
    return "Developer";
}

std::string Developer::getProgrammingLanguage() const { return programmingLanguage; }
int Developer::getProjectCount() const { return projectCount; }
std::string Developer::getExpertiseLevel() const { return expertiseLevel; }
void Developer::setProjectCount(int count) { projectCount = count; }

// =============================================================================
// Intern
// =============================================================================

Intern::Intern(const std::string& id,
               const std::string& name,
               const std::string& email,
               const std::string& hireDate,
               const std::string& dept,
               const std::string& university,
               int durationMonths,
               const std::string& mentorName)
    : Employee(id, name, email, hireDate, dept),
      university(university),
      durationMonths(durationMonths),
      mentorName(mentorName) {}

double Intern::calculateSalary() const {
    return INTERN_STIPEND;
}

std::string Intern::getResponsibilities() const {
    return "Learning and support tasks; " + std::to_string(durationMonths) +
           "-month internship from " + university + "; mentored by " + mentorName + ".";
}

std::string Intern::getRole() const {
    return "Intern";
}

std::string Intern::getUniversity() const { return university; }
int Intern::getDurationMonths() const { return durationMonths; }
std::string Intern::getMentorName() const { return mentorName; }

// =============================================================================
// SeniorManager
// =============================================================================

SeniorManager::SeniorManager(const std::string& id,
                             const std::string& name,
                             const std::string& email,
                             const std::string& hireDate,
                             const std::string& dept,
                             int teamSize,
                             const std::string& level,
                             double annualBonus,
                             const std::string& scope)
    : Manager(id, name, email, hireDate, dept, teamSize, level, annualBonus),
      scope(scope) {}

double SeniorManager::calculateSalary() const {
    return Manager::calculateSalary() + SCOPE_BONUS;
}

std::string SeniorManager::getResponsibilities() const {
    return "Strategic and " + scope + " leadership; " + Manager::getResponsibilities();
}

std::string SeniorManager::getRole() const {
    return "SeniorManager";
}

std::string SeniorManager::getScope() const {
    return scope;
}
