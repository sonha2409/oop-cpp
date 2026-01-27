#include "Employee.h"
#include <iostream> 

// For general employee class
// constructor 
Employee:: Employee(const std::string& id, const std::string& name, 
                   const std::string& email, const std::string& hireDate, 
                   const std::string& dept) { 
    this->employeeId = id;
    this->name = name;
    this->email = email;
    this->hireDate = hireDate;
    this->department = dept;
}

// destructor 
Employee:: ~Employee() {
    std::cout << "Employee: " << this->name << " destroyed" << std::endl;
}

// getters 
std::string Employee:: getEmployeeId() const { 
    return this-> employeeId;
}

std::string Employee:: getName() const { 
    return this -> name; 
}

std::string Employee:: getEmail() const { 
    return this -> email; 
}

std::string Employee:: getHireDate() const { 
    return this -> hireDate; 
}

std::string Employee:: getDepartment() const { 
    return this -> department;
}

// setters
void Employee:: setDepartment(const std::string& dept) { 
    this-> department = dept;
}

void Employee:: setEmail(const std::string& email) { 
    this-> email = email; 
}

// compute salary 
double Employee:: calculateSalary() const { 
    return 0; 
}

// responsibilities
std::string Employee:: getResponsibilities() const { 
    return "all people have responsibilities"; 
}

// role of employee
std::string Employee:: getRole() const { 
    return "Employee";
}

// display 
void Employee:: displayInfo() const { 
    std::cout << "Employee ID is " << this->employeeId << std::endl;
    std::cout << "Name is  " << this->name << std::endl;
    std::cout << "Email: " << this->email << std::endl;
    std::cout << "Hire Date is  " << this->hireDate << std::endl;
    std::cout << "Department is  " << this->department << std::endl;  
}

// For Manager  class 
// constructor
Manager:: Manager(const std::string& id, const std::string& name, 
                  const std::string& email, const std::string& hireDate, 
                  const std::string& dept, int teamSize, 
                  const std::string& level, double annualBonus) 
    : Employee(id, name, email, hireDate, dept) { 
        this-> teamSize = teamSize; 
        this-> level = level; 
        this-> annualBonus = annualBonus; 
}

double Manager::calculateSalary() const { 
    if (annualBonus < 0) { 
        annualBonus = 0; 
    }
    return MANAGER_BASE_SALARY + annualBonus;
}

// getters
std::string Manager:: getResponsibilities() const { 
    return "leading a team of size " + std::to_string(teamSize) + 
           " with management level: " + managementLevel + 
           " with management duties as leading team.";
}

std::string Manager:: getRole() const { 
    return "Manager";
}

int Manager:: getTeamSize() const { 
    return this -> teamSize; 
}

std::string Manager:: getManagementLevel() const { 
    return this -> managementLevel; 
}

double Manager:: getAnnualBonus() const { 
    return this-> annualBonus; 
}

// setter
void Manager:: setTeamSize(int size) { 
    if (size < 0) { 
        size = 0;
    }
    this-> teamSize = size; 
}

void Manager:: setAnnualBonus(double bonus) { 
    if (bonus < 0) { 
        bonus = 0;
    }
    this-> annualBonus = bonus; 
}

// For developer class 
// constructor 
Developer::Developer(const std::string& id, const std::string& name,
                    const std::string& email, const std::string& hireDate,
                    const std::string& dept, const std::string& language,
                    int projectCount, const std::string& expertise)
    : Employee(id, name, email, hireDate, dept) {
        this->programmingLanguage = language;
        this->projectCount = projectCount;
        this->expertiseLevel = expertise;
}

double Developer:: calculateSalary() const { 
    double baseSalary = 10000.0;
    if (expertiseLevel == "Junior") { 
        baseSalary = 50000.0
    } else if (expertiseLevel == "Mid") {
        baseSalary = 70000.0;
    } else if (expertiseLevel == "Senior") {
        baseSalary = 95000.0;
    }
    return baseSalary + (projectCount * 2000.0);
}

std::string Developer:: getResponsibilities() const { 
    return "Developing using " + programmingLanguage + " with expertise level" 
    + expertiseLevel + " doing " + std::to_string(projectCount) + " projects";
}

std::string Developer:: getRole() const { 
    return "Developer";
}

std::string Developer:: getProgrammingLanguage() const { 
    return this-> programmingLanguage;
}

int Developer:: getProjectCount() const { 
    return this-> projectCount; 
}

std::string Developer:: getExpertiseLevel() const { 
    return this-> expertiseLevel; 
}

void Developer:: setProjectCount(int count) { 
    if (count < 0) { 
        count = 0; 
    }
    this-> projectCount = count; 
}

// For intern class 
// constructor 
Intern:: Intern (const std::string& id, const std::string& name, 
                const std::string& email, const std::string& hireDate, 
                const std::string& dept, const std::string& university, 
                int durationMonths, const std::string& mentorName) 
    : Employee(id, name, email, hireDate, dept) { 
        this-> university = university; 
        this-> durationMonths = durationMonths; 
        this-> mentorName = mentorName; 
}

double Intern:: calculateSalary() const { 
    return INTERN_STIPEND;
}

std::string Intern:: getResponsibilities() const { 
    return "doing with " + mentorName + 
           " and studying at " + university;
}   

std:string Intern:: getRole() const { 
    return "Intern";
}

std::string Intern:: getUniversity() const { 
    return this-> university; 
}

int getDurationMonths() const { 
    return this-> durationMonths; 
}

std::string Intern:: getMentorName() const { 
    return this-> mentorName; 
}

//For senior manager class 
//constructor 
SeniorManager::SeniorManager(const std::string& id,const std::string& name,
        const std::string& email, const std::string& hireDate, const std::string& dept,
        int teamSize, const std::string& level, double annualBonus, const std::string& scope) 
    : Manager(id, name, email, hireDate, dept, teamSize, level, annualBonus) {
        this-> scope = scope;
}

double SeniorManager:: calculateSalary() const { 
    return Manager::calculateSalary() + SCOPE_BONUS;
}

std::string SeniorManager:: getResponsibilities() const { 
    return Manager::getResponsibilities() + "with scope" + scope;
}

std::string SeniorManager:: getRole() const { 
    return "Senior Manager";
}

std::string SeniorManager:: getScope() const { 
    return this-> scope; 
}