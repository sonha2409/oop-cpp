# Employee Management System — Function Specification

This document describes how each function should behave so you can implement them correctly. Use it together with `Employee.h`.

---

## Concepts in This Project

| Concept | Where it appears |
|--------|-------------------|
| **Parent and child classes** | `Employee` is parent; `Manager`, `Developer`, `Intern` are children. `SeniorManager` is child of `Manager`. |
| **Method overriding** | `calculateSalary()`, `getResponsibilities()`, `getRole()` (and optionally `displayInfo()`) are overridden in derived classes. |
| **“Super” in C++** | C++ has no `super` keyword. To call the base implementation, use the base class name and `::`, e.g. `Manager::calculateSalary()`, or from a member function `Employee::displayInfo()`. |
| **Single inheritance** | Each of Manager, Developer, Intern inherits only from `Employee`. |
| **Multilevel inheritance** | `SeniorManager` inherits from `Manager`, which inherits from `Employee`: Employee → Manager → SeniorManager. |
| **Hierarchical inheritance** | Multiple derived classes share one base: Manager, Developer, Intern (and SeniorManager via Manager) all use `Employee` as common base. |

---

## 1. Base Class: `Employee`

### 1.1 Constructor  
`Employee(const std::string& id, const std::string& name, const std::string& email, const std::string& hireDate, const std::string& dept)`

- **Purpose:** Set up all attributes that every employee has.
- **Behavior:** Assign `id` → `employeeId`, `name` → `name`, `email` → `email`, `hireDate` → `hireDate`, `dept` → `department`. You may copy parameters into members in the initializer list or in the body; keep it simple and clear.
- **Edge cases:** No validation required in this spec; storing empty strings is acceptable.

---

### 1.2 Destructor  
`virtual ~Employee()`

- **Purpose:** Allow derived objects to be deleted safely via `Employee*`.
- **Behavior:** Can be empty `{}`, or you may add a simple log/trace if you wish. Must be `virtual` so that when you `delete` a `Manager*` or `Developer*` through an `Employee*`, the correct destructor chain runs.

---

### 1.3 Getters  
`getEmployeeId()`, `getName()`, `getEmail()`, `getHireDate()`, `getDepartment()`

- **Purpose:** Read the corresponding member without allowing external modification.
- **Behavior:** Return a copy of the respective member (or `const std::string&` if you prefer and document it). All are `const` member functions.

---

### 1.4 Setters  
`setDepartment(const std::string& dept)`, `setEmail(const std::string& email)`

- **Purpose:** Allow changing department or email.
- **Behavior:** Assign the argument to `department` or `email` respectively. No validation required.

---

### 1.5 `virtual double calculateSalary() const`

- **Purpose:** Provide a default salary when the object is used as a generic `Employee`.
- **Behavior:** Return `0.0` or another fixed default (e.g. a small base amount). Derived classes override this with role-specific formulas.

---

### 1.6 `virtual std::string getResponsibilities() const`

- **Purpose:** Describe what this employee is responsible for.
- **Behavior:** Return a string like `"General employee duties and assigned tasks."` or similar. Derived classes override with role-specific text.

---

### 1.7 `virtual std::string getRole() const`

- **Purpose:** Identify the employee type for reports and UI.
- **Behavior:** Return `"Employee"`. Overridden in derived classes to return `"Manager"`, `"Developer"`, `"Intern"`, `"SeniorManager"`.

---

### 1.8 `virtual void displayInfo() const`

- **Purpose:** Print a readable summary to `std::cout`.
- **Behavior:** Print lines that include at least: role, employee ID, name, department, salary (via `calculateSalary()`), and responsibilities (via `getResponsibilities()`). Format example:

  ```
  Role: Employee
  ID: E001
  Name: Jane Doe
  Department: HR
  Salary: 0.00
  Responsibilities: General employee duties and assigned tasks.
  ```

  Use the getters and `calculateSalary()`/`getResponsibilities()` so that when you call `displayInfo()` on a `Manager*` held as `Employee*`, the overridden methods are used.

---

## 2. Derived Class: `Manager`

**Inheritance:** `class Manager : public Employee`

Use the **base initializer list** to pass id, name, email, hireDate, dept to `Employee`, then initialize `teamSize`, `managementLevel`, `annualBonus`.

### 2.1 Constructor  
`Manager(..., int teamSize, const std::string& level, double annualBonus)`

- **Purpose:** Build a Manager by initializing the Employee part and Manager-specific data.
- **Behavior:** In the member initializer list, call `Employee(id, name, email, hireDate, dept)` and set `teamSize`, `managementLevel`, `annualBonus`. This is the C++ way of “calling super”: the base subobject is built first.

---

### 2.2 `double calculateSalary() const override`

- **Purpose:** Manager salary = base + bonus.
- **Behavior:** Return `MANAGER_BASE_SALARY + annualBonus`. Define `MANAGER_BASE_SALARY` in your .cpp (e.g. `const double Manager::MANAGER_BASE_SALARY = 80000.0;`). Use the stored `annualBonus`; no need to call `Employee::calculateSalary()`.

---

### 2.3 `std::string getResponsibilities() const override`

- **Purpose:** Describe management duties.
- **Behavior:** Return a string that mentions leading the team, oversight, planning, and ideally incorporates `teamSize` and `managementLevel`, e.g.  
  `"Lead team of " + std::to_string(teamSize) + " members; " + managementLevel + " management oversight and planning."`

---

### 2.4 `std::string getRole() const override`

- Return `"Manager"`.

---

### 2.5 Manager getters/setters  
`getTeamSize()`, `getManagementLevel()`, `getAnnualBonus()`, `setTeamSize(int)`, `setAnnualBonus(double)`

- **Purpose:** Access and modify Manager-specific data.
- **Behavior:** Standard get/set for `teamSize`, `managementLevel`, `annualBonus`. Implement only what is declared in the header.

---

## 3. Derived Class: `Developer`

**Inheritance:** `class Developer : public Employee`

### 3.1 Constructor  
`Developer(..., const std::string& language, int projectCount, const std::string& expertise)`

- **Purpose:** Initialize Employee base and developer-specific fields.
- **Behavior:** In the initializer list, call `Employee(...)` and set `programmingLanguage`, `projectCount`, `expertiseLevel`.

---

### 3.2 `double calculateSalary() const override`

- **Purpose:** Salary depends on expertise level and number of projects.
- **Behavior:** Use a simple formula, for example:
  - Base by level: e.g. Junior 50_000, Mid 70_000, Senior 95_000 (you can use constants or a small helper).
  - Add a per-project amount, e.g. `projectCount * 2000`.
  - Return `levelBase + projectCount * 2000` (or your chosen constants). Define the numbers in the .cpp so they are easy to change.

---

### 3.3 `std::string getResponsibilities() const override`

- **Purpose:** Describe developer duties.
- **Behavior:** Return a string that includes `programmingLanguage` and `expertiseLevel`, e.g.  
  `"Software development in " + programmingLanguage + " as " + expertiseLevel + " developer; contribute to " + std::to_string(projectCount) + " project(s)."`

---

### 3.4 `std::string getRole() const override`

- Return `"Developer"`.

---

### 3.5 Developer getters/setter  
`getProgrammingLanguage()`, `getProjectCount()`, `getExpertiseLevel()`, `setProjectCount(int)`

- **Purpose:** Access and optionally change developer-specific data.
- **Behavior:** Return or set the corresponding member. `setProjectCount` updates `projectCount`.

---

## 4. Derived Class: `Intern`

**Inheritance:** `class Intern : public Employee`

### 4.1 Constructor  
`Intern(..., const std::string& university, int durationMonths, const std::string& mentorName)`

- **Purpose:** Initialize Employee base and intern-specific fields.
- **Behavior:** Call `Employee(...)` in the initializer list, then set `university`, `durationMonths`, `mentorName`.

---

### 4.2 `double calculateSalary() const override`

- **Purpose:** Interns get a fixed stipend.
- **Behavior:** Return `INTERN_STIPEND`. Define in .cpp, e.g.  
  `const double Intern::INTERN_STIPEND = 2500.0;`

---

### 4.3 `std::string getResponsibilities() const override`

- **Purpose:** Describe intern duties and learning.
- **Behavior:** Return a string that includes `university`, `durationMonths`, and `mentorName`, e.g.  
  `"Learning and support tasks; " + std::to_string(durationMonths) + "-month internship from " + university + "; mentored by " + mentorName + "."`

---

### 4.4 `std::string getRole() const override`

- Return `"Intern"`.

---

### 4.5 Intern getters  
`getUniversity()`, `getDurationMonths()`, `getMentorName()`

- **Purpose:** Read-only access to intern-specific data.
- **Behavior:** Return the corresponding member.

---

## 5. Derived Class: `SeniorManager` (Multilevel Inheritance)

**Inheritance:** `class SeniorManager : public Manager`

This shows **multilevel** inheritance: `Employee` → `Manager` → `SeniorManager`.  
To “call the base” from `SeniorManager`, use `Manager::` (e.g. `Manager::calculateSalary()`).

### 5.1 Constructor  
`SeniorManager(..., double annualBonus, const std::string& scope)`

- **Purpose:** Build a SeniorManager by reusing Manager (and thus Employee) and adding scope.
- **Behavior:** In the initializer list, call  
  `Manager(id, name, email, hireDate, dept, teamSize, level, annualBonus)`  
  then set `scope`. This uses the “super” pattern at two levels: Manager calls Employee, SeniorManager calls Manager.

---

### 5.2 `double calculateSalary() const override`

- **Purpose:** Senior manager salary = manager salary + scope bonus.
- **Behavior:** Return `Manager::calculateSalary() + SCOPE_BONUS`. Define  
  `const double SeniorManager::SCOPE_BONUS = 15000.0;` (or similar) in the .cpp. This is an example of **calling the base (super) implementation** and then adding more.

---

### 5.3 `std::string getResponsibilities() const override`

- **Purpose:** Include scope and higher-level duties.
- **Behavior:** You may:
  - Call `Manager::getResponsibilities()` and append scope-related text, or
  - Build a new string that includes `scope` and strategic/leadership responsibilities, e.g.  
    `"Strategic and " + scope + " leadership; " + Manager::getResponsibilities()`  
  or a similar composition.

---

### 5.4 `std::string getRole() const override`

- Return `"SeniorManager"`.

---

### 5.5 `std::string getScope() const`

- **Purpose:** Read the scope (e.g. "Regional", "Division", "Global").
- **Behavior:** Return the `scope` member.

---

## 6. Static Constants (define in .cpp)

Define these in your implementation file so the linker can find them:

- `Manager::MANAGER_BASE_SALARY`  (e.g. `80000.0`)
- `Intern::INTERN_STIPEND`        (e.g. `2500.0`)
- `SeniorManager::SCOPE_BONUS`    (e.g. `15000.0`)

Developer salary tiers can be local constants or helper functions in the .cpp; they do not need to be static members unless you add them to the header.

---

## 7. Summary Checklist for Students

- [ ] **Employee:** Constructor, destructor, getters, setters, default `calculateSalary`/`getResponsibilities`/`getRole`, and `displayInfo()` that use those methods.
- [ ] **Manager:** Constructor calling `Employee(...)`, override `calculateSalary`, `getResponsibilities`, `getRole`; implement Manager getters/setters; define `MANAGER_BASE_SALARY`.
- [ ] **Developer:** Constructor calling `Employee(...)`, override `calculateSalary`, `getResponsibilities`, `getRole`; implement Developer getters/setter; use a clear level + project formula.
- [ ] **Intern:** Constructor calling `Employee(...)`, override `calculateSalary`, `getResponsibilities`, `getRole`; implement Intern getters; define `INTERN_STIPEND`.
- [ ] **SeniorManager:** Constructor calling `Manager(...)`, override `calculateSalary` using `Manager::calculateSalary()`, override `getResponsibilities` (optionally using `Manager::getResponsibilities()`), override `getRole`; implement `getScope()`; define `SCOPE_BONUS`.
- [ ] Use **override** on every overridden function in derived classes.
- [ ] Use the **base initializer list** in every derived constructor to call the direct base constructor (that is your “super” call in C++).

Once these are done, you can add a small `main()` that creates one of each type, assigns to `Employee*` or `Manager*`, and calls `displayInfo()` and `calculateSalary()` to verify polymorphism and inheritance.
