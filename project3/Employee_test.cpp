/**
 * @file Employee_test.cpp
 * @brief Comprehensive unit tests for the Employee Management System.
 *
 * Covers: Employee, Manager, Developer, Intern, SeniorManager;
 * inheritance, method overriding, polymorphism, virtual destructor.
 */

#include <gtest/gtest.h>
#include "Employee.h"
#include <sstream>
#include <iostream>
#include <string>
#include <functional>
#include <vector>

// =============================================================================
// Test Fixtures
// =============================================================================

class EmployeeTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper: capture stdout from a callable, return as string
static std::string captureStdout(std::function<void()> fn) {
    std::ostringstream buf;
    std::streambuf* orig = std::cout.rdbuf(buf.rdbuf());
    fn();
    std::cout.rdbuf(orig);
    return buf.str();
}

// =============================================================================
// Employee (Base Class) Tests
// =============================================================================

TEST_F(EmployeeTest, Employee_Constructor_StoresAllFields) {
    Employee e("E001", "Jane Doe", "jane@co.com", "2024-01-15", "HR");
    EXPECT_EQ(e.getEmployeeId(), "E001");
    EXPECT_EQ(e.getName(), "Jane Doe");
    EXPECT_EQ(e.getEmail(), "jane@co.com");
    EXPECT_EQ(e.getHireDate(), "2024-01-15");
    EXPECT_EQ(e.getDepartment(), "HR");
}

TEST_F(EmployeeTest, Employee_SetDepartment_UpdatesValue) {
    Employee e("E001", "Jane", "j@c.com", "2024-01-01", "HR");
    e.setDepartment("Engineering");
    EXPECT_EQ(e.getDepartment(), "Engineering");
}

TEST_F(EmployeeTest, Employee_SetEmail_UpdatesValue) {
    Employee e("E001", "Jane", "old@c.com", "2024-01-01", "HR");
    e.setEmail("new@co.com");
    EXPECT_EQ(e.getEmail(), "new@co.com");
}

TEST_F(EmployeeTest, Employee_CalculateSalary_ReturnsZero) {
    Employee e("E001", "Jane", "j@c.com", "2024-01-01", "HR");
    EXPECT_DOUBLE_EQ(e.calculateSalary(), 0.0);
}

TEST_F(EmployeeTest, Employee_GetResponsibilities_ReturnsDefault) {
    Employee e("E001", "Jane", "j@c.com", "2024-01-01", "HR");
    std::string r = e.getResponsibilities();
    EXPECT_TRUE(r.find("General employee duties") != std::string::npos) << "Expected default responsibilities";
}

TEST_F(EmployeeTest, Employee_GetRole_ReturnsEmployee) {
    Employee e("E001", "Jane", "j@c.com", "2024-01-01", "HR");
    EXPECT_EQ(e.getRole(), "Employee");
}

TEST_F(EmployeeTest, Employee_DisplayInfo_ContainsRoleIdNameDeptSalaryResponsibilities) {
    Employee e("E001", "Jane Doe", "jane@co.com", "2024-01-15", "HR");
    std::string out = captureStdout([&e]() { e.displayInfo(); });
    EXPECT_TRUE(out.find("Employee") != std::string::npos) << "Role";
    EXPECT_TRUE(out.find("E001") != std::string::npos) << "ID";
    EXPECT_TRUE(out.find("Jane Doe") != std::string::npos) << "Name";
    EXPECT_TRUE(out.find("HR") != std::string::npos) << "Department";
    EXPECT_TRUE(out.find("0") != std::string::npos) << "Salary";
    EXPECT_TRUE(out.find("Responsibilities") != std::string::npos) << "Responsibilities label";
}

TEST_F(EmployeeTest, Employee_DisplayInfo_DoesNotThrow) {
    Employee e("E001", "Jane", "j@c.com", "2024-01-01", "HR");
    EXPECT_NO_THROW(e.displayInfo());
}

// =============================================================================
// Manager Tests
// =============================================================================

TEST_F(EmployeeTest, Manager_Constructor_InitializesBaseAndDerived) {
    Manager m("M001", "Alice", "alice@co.com", "2020-03-01", "Engineering", 5, "Senior", 12000.0);
    EXPECT_EQ(m.getEmployeeId(), "M001");
    EXPECT_EQ(m.getName(), "Alice");
    EXPECT_EQ(m.getDepartment(), "Engineering");
    EXPECT_EQ(m.getTeamSize(), 5);
    EXPECT_EQ(m.getManagementLevel(), "Senior");
    EXPECT_DOUBLE_EQ(m.getAnnualBonus(), 12000.0);
}

TEST_F(EmployeeTest, Manager_CalculateSalary_BasePlusBonus) {
    Manager m("M001", "Alice", "a@c.com", "2020-01-01", "Eng", 5, "Senior", 12000.0);
    // MANAGER_BASE_SALARY = 80000, so 80000 + 12000 = 92000
    EXPECT_DOUBLE_EQ(m.calculateSalary(), 92000.0);
}

TEST_F(EmployeeTest, Manager_CalculateSalary_ZeroBonus) {
    Manager m("M002", "Bob", "b@c.com", "2021-01-01", "Eng", 3, "Junior", 0.0);
    EXPECT_DOUBLE_EQ(m.calculateSalary(), 80000.0);
}

TEST_F(EmployeeTest, Manager_GetResponsibilities_ContainsTeamSizeAndLevel) {
    Manager m("M001", "Alice", "a@c.com", "2020-01-01", "Eng", 7, "Director", 15000.0);
    std::string r = m.getResponsibilities();
    EXPECT_TRUE(r.find("7") != std::string::npos) << "team size";
    EXPECT_TRUE(r.find("Director") != std::string::npos) << "level";
    EXPECT_TRUE(r.find("Lead team") != std::string::npos || r.find("members") != std::string::npos);
}

TEST_F(EmployeeTest, Manager_GetRole_ReturnsManager) {
    Manager m("M001", "Alice", "a@c.com", "2020-01-01", "Eng", 5, "Senior", 10000.0);
    EXPECT_EQ(m.getRole(), "Manager");
}

TEST_F(EmployeeTest, Manager_GettersSetters_TeamSizeAndBonus) {
    Manager m("M001", "A", "a@c.com", "2020-01-01", "Eng", 5, "Senior", 10000.0);
    m.setTeamSize(10);
    m.setAnnualBonus(20000.0);
    EXPECT_EQ(m.getTeamSize(), 10);
    EXPECT_DOUBLE_EQ(m.getAnnualBonus(), 20000.0);
    EXPECT_DOUBLE_EQ(m.calculateSalary(), 100000.0);  // 80000 + 20000
}

TEST_F(EmployeeTest, Manager_DisplayInfo_ViaBasePointer_ShowsManagerData) {
    Employee* p = new Manager("M001", "Alice", "a@c.com", "2020-01-01", "Eng", 5, "Senior", 12000.0);
    std::string out = captureStdout([p]() { p->displayInfo(); });
    EXPECT_TRUE(out.find("Manager") != std::string::npos);
    EXPECT_TRUE(out.find("92000") != std::string::npos);  // salary
    delete p;
}

// =============================================================================
// Developer Tests
// =============================================================================

TEST_F(EmployeeTest, Developer_Constructor_InitializesBaseAndDerived) {
    Developer d("D001", "Bob", "bob@co.com", "2021-06-15", "Engineering", "C++", 3, "Mid");
    EXPECT_EQ(d.getEmployeeId(), "D001");
    EXPECT_EQ(d.getName(), "Bob");
    EXPECT_EQ(d.getProgrammingLanguage(), "C++");
    EXPECT_EQ(d.getProjectCount(), 3);
    EXPECT_EQ(d.getExpertiseLevel(), "Mid");
}

TEST_F(EmployeeTest, Developer_CalculateSalary_JuniorBasePlusProjects) {
    Developer d("D001", "Bob", "b@c.com", "2023-01-01", "Eng", "C++", 2, "Junior");
    // 50000 + 2*2000 = 54000
    EXPECT_DOUBLE_EQ(d.calculateSalary(), 54000.0);
}

TEST_F(EmployeeTest, Developer_CalculateSalary_MidBasePlusProjects) {
    Developer d("D002", "Carol", "c@c.com", "2022-01-01", "Eng", "Python", 3, "Mid");
    // 70000 + 3*2000 = 76000
    EXPECT_DOUBLE_EQ(d.calculateSalary(), 76000.0);
}

TEST_F(EmployeeTest, Developer_CalculateSalary_SeniorBasePlusProjects) {
    Developer d("D003", "Dave", "d@c.com", "2020-01-01", "Eng", "Rust", 5, "Senior");
    // 95000 + 5*2000 = 105000
    EXPECT_DOUBLE_EQ(d.calculateSalary(), 105000.0);
}

TEST_F(EmployeeTest, Developer_CalculateSalary_UnknownLevel_DefaultsToMid) {
    Developer d("D004", "Eve", "e@c.com", "2022-01-01", "Eng", "Go", 1, "Lead");
    // unknown level uses MID_BASE = 70000, so 70000 + 2000 = 72000
    EXPECT_DOUBLE_EQ(d.calculateSalary(), 72000.0);
}

TEST_F(EmployeeTest, Developer_GetResponsibilities_ContainsLanguageExpertiseProjects) {
    Developer d("D001", "Bob", "b@c.com", "2021-01-01", "Eng", "C++", 3, "Mid");
    std::string r = d.getResponsibilities();
    EXPECT_TRUE(r.find("C++") != std::string::npos);
    EXPECT_TRUE(r.find("Mid") != std::string::npos);
    EXPECT_TRUE(r.find("3") != std::string::npos);
    EXPECT_TRUE(r.find("Software development") != std::string::npos || r.find("developer") != std::string::npos);
}

TEST_F(EmployeeTest, Developer_GetRole_ReturnsDeveloper) {
    Developer d("D001", "Bob", "b@c.com", "2021-01-01", "Eng", "C++", 3, "Mid");
    EXPECT_EQ(d.getRole(), "Developer");
}

TEST_F(EmployeeTest, Developer_SetProjectCount_UpdatesSalary) {
    Developer d("D001", "Bob", "b@c.com", "2021-01-01", "Eng", "C++", 2, "Mid");
    EXPECT_DOUBLE_EQ(d.calculateSalary(), 74000.0);  // 70000 + 4000
    d.setProjectCount(4);
    EXPECT_EQ(d.getProjectCount(), 4);
    EXPECT_DOUBLE_EQ(d.calculateSalary(), 78000.0);  // 70000 + 8000
}

TEST_F(EmployeeTest, Developer_DisplayInfo_ViaBasePointer_ShowsDeveloperData) {
    Employee* p = new Developer("D001", "Bob", "b@c.com", "2021-01-01", "Eng", "C++", 3, "Mid");
    std::string out = captureStdout([p]() { p->displayInfo(); });
    EXPECT_TRUE(out.find("Developer") != std::string::npos);
    EXPECT_TRUE(out.find("76000") != std::string::npos);
    delete p;
}

// =============================================================================
// Intern Tests
// =============================================================================

TEST_F(EmployeeTest, Intern_Constructor_InitializesBaseAndDerived) {
    Intern i("I001", "Carol", "carol@co.com", "2024-01-10", "Engineering", "State Univ", 6, "Alice");
    EXPECT_EQ(i.getEmployeeId(), "I001");
    EXPECT_EQ(i.getName(), "Carol");
    EXPECT_EQ(i.getUniversity(), "State Univ");
    EXPECT_EQ(i.getDurationMonths(), 6);
    EXPECT_EQ(i.getMentorName(), "Alice");
}

TEST_F(EmployeeTest, Intern_CalculateSalary_ReturnsStipend) {
    Intern i("I001", "Carol", "c@c.com", "2024-01-01", "Eng", "State Univ", 6, "Alice");
    EXPECT_DOUBLE_EQ(i.calculateSalary(), 2500.0);  // INTERN_STIPEND
}

TEST_F(EmployeeTest, Intern_GetResponsibilities_ContainsUniversityDurationMentor) {
    Intern i("I001", "Carol", "c@c.com", "2024-01-01", "Eng", "State Univ", 6, "Alice");
    std::string r = i.getResponsibilities();
    EXPECT_TRUE(r.find("State Univ") != std::string::npos);
    EXPECT_TRUE(r.find("6") != std::string::npos);
    EXPECT_TRUE(r.find("Alice") != std::string::npos);
    EXPECT_TRUE(r.find("internship") != std::string::npos || r.find("mentored") != std::string::npos);
}

TEST_F(EmployeeTest, Intern_GetRole_ReturnsIntern) {
    Intern i("I001", "Carol", "c@c.com", "2024-01-01", "Eng", "State Univ", 6, "Alice");
    EXPECT_EQ(i.getRole(), "Intern");
}

TEST_F(EmployeeTest, Intern_DisplayInfo_ViaBasePointer_ShowsInternData) {
    Employee* p = new Intern("I001", "Carol", "c@c.com", "2024-01-01", "Eng", "State Univ", 6, "Alice");
    std::string out = captureStdout([p]() { p->displayInfo(); });
    EXPECT_TRUE(out.find("Intern") != std::string::npos);
    EXPECT_TRUE(out.find("2500") != std::string::npos);
    delete p;
}

// =============================================================================
// SeniorManager (Multilevel Inheritance) Tests
// =============================================================================

TEST_F(EmployeeTest, SeniorManager_Constructor_InitializesViaManager) {
    SeniorManager sm("SM001", "Dave", "dave@co.com", "2018-01-15", "Engineering", 12, "Director", 20000.0, "Regional");
    EXPECT_EQ(sm.getEmployeeId(), "SM001");
    EXPECT_EQ(sm.getName(), "Dave");
    EXPECT_EQ(sm.getTeamSize(), 12);
    EXPECT_EQ(sm.getManagementLevel(), "Director");
    EXPECT_DOUBLE_EQ(sm.getAnnualBonus(), 20000.0);
    EXPECT_EQ(sm.getScope(), "Regional");
}

TEST_F(EmployeeTest, SeniorManager_CalculateSalary_ManagerSalaryPlusScopeBonus) {
    SeniorManager sm("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Regional");
    // Manager: 80000 + 20000 = 100000; SeniorManager: 100000 + 15000 = 115000
    EXPECT_DOUBLE_EQ(sm.calculateSalary(), 115000.0);
}

TEST_F(EmployeeTest, SeniorManager_GetResponsibilities_ContainsScopeAndStrategic) {
    SeniorManager sm("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Global");
    std::string r = sm.getResponsibilities();
    EXPECT_TRUE(r.find("Strategic") != std::string::npos);
    EXPECT_TRUE(r.find("Global") != std::string::npos);
    EXPECT_TRUE(r.find("Lead team") != std::string::npos || r.find("10") != std::string::npos);
}

TEST_F(EmployeeTest, SeniorManager_GetRole_ReturnsSeniorManager) {
    SeniorManager sm("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Regional");
    EXPECT_EQ(sm.getRole(), "SeniorManager");
}

TEST_F(EmployeeTest, SeniorManager_GetScope_ReturnsScope) {
    SeniorManager sm("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Division");
    EXPECT_EQ(sm.getScope(), "Division");
}

TEST_F(EmployeeTest, SeniorManager_DisplayInfo_ViaBasePointer_ShowsSeniorManagerData) {
    Employee* p = new SeniorManager("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Regional");
    std::string out = captureStdout([p]() { p->displayInfo(); });
    EXPECT_TRUE(out.find("SeniorManager") != std::string::npos);
    EXPECT_TRUE(out.find("115000") != std::string::npos);
    delete p;
}

TEST_F(EmployeeTest, SeniorManager_DisplayInfo_ViaManagerPointer_ShowsSeniorManagerData) {
    Manager* p = new SeniorManager("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Regional");
    EXPECT_EQ(p->getRole(), "SeniorManager");
    EXPECT_DOUBLE_EQ(p->calculateSalary(), 115000.0);
    delete p;
}

// =============================================================================
// Polymorphism Tests
// =============================================================================

TEST_F(EmployeeTest, Polymorphism_EmployeePointerToManager_CallsOverriddenMethods) {
    Employee* p = new Manager("M001", "Alice", "a@c.com", "2020-01-01", "Eng", 5, "Senior", 12000.0);
    EXPECT_EQ(p->getRole(), "Manager");
    EXPECT_DOUBLE_EQ(p->calculateSalary(), 92000.0);
    EXPECT_TRUE(p->getResponsibilities().find("Lead team") != std::string::npos || p->getResponsibilities().find("5") != std::string::npos);
    delete p;
}

TEST_F(EmployeeTest, Polymorphism_EmployeePointerToDeveloper_CallsOverriddenMethods) {
    Employee* p = new Developer("D001", "Bob", "b@c.com", "2021-01-01", "Eng", "C++", 3, "Mid");
    EXPECT_EQ(p->getRole(), "Developer");
    EXPECT_DOUBLE_EQ(p->calculateSalary(), 76000.0);
    delete p;
}

TEST_F(EmployeeTest, Polymorphism_EmployeePointerToIntern_CallsOverriddenMethods) {
    Employee* p = new Intern("I001", "Carol", "c@c.com", "2024-01-01", "Eng", "State Univ", 6, "Alice");
    EXPECT_EQ(p->getRole(), "Intern");
    EXPECT_DOUBLE_EQ(p->calculateSalary(), 2500.0);
    delete p;
}

TEST_F(EmployeeTest, Polymorphism_EmployeePointerToSeniorManager_CallsOverriddenMethods) {
    Employee* p = new SeniorManager("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Regional");
    EXPECT_EQ(p->getRole(), "SeniorManager");
    EXPECT_DOUBLE_EQ(p->calculateSalary(), 115000.0);
    delete p;
}

TEST_F(EmployeeTest, Polymorphism_DeleteThroughBasePointer_NoUndefinedBehavior) {
    Employee* p = new Manager("M001", "Alice", "a@c.com", "2020-01-01", "Eng", 5, "Senior", 12000.0);
    EXPECT_NO_THROW(delete p);
}

TEST_F(EmployeeTest, Polymorphism_VectorOfBasePointers_EachCallsCorrectOverride) {
    std::vector<Employee*> staff = {
        new Manager("M001", "Alice", "a@c.com", "2020-01-01", "Eng", 5, "Senior", 12000.0),
        new Developer("D001", "Bob", "b@c.com", "2021-01-01", "Eng", "C++", 3, "Mid"),
        new Intern("I001", "Carol", "c@c.com", "2024-01-01", "Eng", "State Univ", 6, "Alice"),
        new SeniorManager("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Regional")
    };
    EXPECT_EQ(staff[0]->getRole(), "Manager");
    EXPECT_EQ(staff[1]->getRole(), "Developer");
    EXPECT_EQ(staff[2]->getRole(), "Intern");
    EXPECT_EQ(staff[3]->getRole(), "SeniorManager");
    EXPECT_DOUBLE_EQ(staff[0]->calculateSalary(), 92000.0);
    EXPECT_DOUBLE_EQ(staff[1]->calculateSalary(), 76000.0);
    EXPECT_DOUBLE_EQ(staff[2]->calculateSalary(), 2500.0);
    EXPECT_DOUBLE_EQ(staff[3]->calculateSalary(), 115000.0);
    for (Employee* e : staff) delete e;
}

// =============================================================================
// Inheritance Chain (Multilevel) Tests
// =============================================================================

TEST_F(EmployeeTest, Inheritance_SeniorManagerIsAKindOfManager) {
    SeniorManager sm("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Regional");
    Manager& m = sm;
    EXPECT_EQ(m.getTeamSize(), 10);
    EXPECT_DOUBLE_EQ(m.getAnnualBonus(), 20000.0);
    // Virtual call through Manager reference still dispatches to SeniorManager
    EXPECT_EQ(m.getRole(), "SeniorManager");
    EXPECT_DOUBLE_EQ(m.calculateSalary(), 115000.0);
}

TEST_F(EmployeeTest, Inheritance_SeniorManagerIsAKindOfEmployee) {
    SeniorManager sm("SM001", "Dave", "d@c.com", "2018-01-01", "Eng", 10, "Director", 20000.0, "Regional");
    Employee& e = sm;
    EXPECT_EQ(e.getEmployeeId(), "SM001");
    EXPECT_EQ(e.getRole(), "SeniorManager");
    EXPECT_DOUBLE_EQ(e.calculateSalary(), 115000.0);
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST_F(EmployeeTest, EdgeCase_EmptyStrings_Accepted) {
    Employee e("", "", "", "", "");
    EXPECT_EQ(e.getEmployeeId(), "");
    EXPECT_EQ(e.getName(), "");
    EXPECT_EQ(e.getDepartment(), "");
    EXPECT_DOUBLE_EQ(e.calculateSalary(), 0.0);
}

TEST_F(EmployeeTest, EdgeCase_Developer_ZeroProjects) {
    Developer d("D001", "Bob", "b@c.com", "2021-01-01", "Eng", "C++", 0, "Junior");
    EXPECT_DOUBLE_EQ(d.calculateSalary(), 50000.0);  // 50000 + 0
}

TEST_F(EmployeeTest, EdgeCase_Manager_LargeBonus) {
    Manager m("M001", "Alice", "a@c.com", "2020-01-01", "Eng", 100, "Director", 50000.0);
    EXPECT_DOUBLE_EQ(m.calculateSalary(), 130000.0);
}

// =============================================================================
// Main
// =============================================================================

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
