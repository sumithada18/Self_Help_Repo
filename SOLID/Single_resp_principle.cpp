
// The Single Responsibility Principle (SRP) states that a class should have only one reason to change.
	// This means it should have one, and only one, specific job or responsibility within the application.

	// A class should do only one job, so that only one thing can affect why it needs to be modified.
	// example:
class Report {
public:
	void generate() { /* logic */ }
	void saveToFile() { /* file I/O */ }
};
/*
This class has 2 reasons to change:
 - If report generation logic changes.
 - If file saving logic changes.
*/
// fix:
class ReportGenerator {
public:
	void generate();
};

class FileSaver {
public:
	void saveToFile();
};
/*
Change in generation -> affects ReportGenerator.
Change in file saving -> affects FileSaver.

Each class has one clear responsibility and one reason to change.
*/

/*
Problem it Solves:
 - SRP solves the problem of creating classes that become complex, fragile, 
   and difficult to maintain. When a class juggles multiple unrelated responsibilities:
 - High Coupling: A change related to one responsibility can unintentionally 
   impact or break other unrelated responsibilities within the same class.
 - Low Cohesion: The class's parts aren't strongly related, making it harder to 
   understand what the class truly does.
 - Difficult Testing: Testing one responsibility might require setting up for all 
   others, making tests more complex.
 - Reduced Reusability: If you need just one of its responsibilities elsewhere, 
   you have to bring along all the others.
   
   
   Why Bifurcate responsibilities ?
 - We bifurcate responsibilities because:
 - Clarity & Understandability: Each class has a clear, well-defined purpose.
 - Maintainability: Changes related to one responsibility are isolated to one 
   class, reducing the risk of unintended side effects elsewhere. You only need 
   to modify and retest the class whose reason for change has occurred.
 - Testability: Smaller, focused classes are much easier to test in isolation.
 - Reusability: A class with a single, well-defined responsibility is more likely 
   to be reusable in other parts of the application or even in different projects.
*/



// Use Case: We need to store employee details and also calculate their tax.

// Before SRP (One Class, Multiple Responsibilities)
#include <iostream>
#include <string>
#include <fstream> // For a hypothetical "saving" later if we expanded

// --- Before SRP ---
// This class has two responsibilities:
// 1. Managing employee data (name, salary).
// 2. Calculating tax for the employee.
// A change in tax calculation logic OR a change in how employee data is stored/accessed
// would both require modifying this single class.
class Employee_BeforeSRP {
public:
    std::string name;
    double salary;

    Employee_BeforeSRP(const std::string& n, double s) : name(n), salary(s) {}

    // Responsibility 1: Data Access (simplified)
    void displayDetails() const {
        std::cout << "Employee: " << name << ", Salary: $" << salary << std::endl;
    }

    // Responsibility 2: Tax Calculation Logic
    // Reason to change: Tax laws change, different tax brackets are introduced, etc.
    double calculateTax() const {
        // Super simplified tax calculation
        if (salary > 50000) {
            return salary * 0.20; // 20% tax
        } else {
            return salary * 0.10; // 10% tax
        }
    }
};

int main_before() {
    Employee_BeforeSRP emp("Alice", 60000.0);
    emp.displayDetails();
    std::cout << "Tax to pay: $" << emp.calculateTax() << std::endl;

    // If tax rules change, Employee_BeforeSRP class needs to be modified.
    // If we want to store employee data differently (e.g. add employee ID),
    // Employee_BeforeSRP class also needs to be modified.
    return 0;
}


// After Applying SRP (Separate Classes for Separate Responsibilities)

#include <iostream>
#include <string>

// --- After SRP ---

// Responsibility 1: Managing employee data.
// Reason to change: How employee data is stored, what data is stored (e.g., add ID, department).
class Employee_AfterSRP {
public:
    std::string name;
    double salary;

    Employee_AfterSRP(const std::string& n, double s) : name(n), salary(s) {}

    void displayDetails() const {
        std::cout << "Employee: " << name << ", Salary: $" << salary << std::endl;
    }

    // Getter for salary, needed by TaxCalculator
    double getSalary() const {
        return salary;
    }
};

// Responsibility 2: Calculating tax.
// Reason to change: Tax laws change, different tax brackets, new deductions.
class TaxCalculator {
public:
    // Takes an Employee_AfterSRP object (or just relevant data like salary) to perform its task
    double calculateTax(const Employee_AfterSRP& employee) const {
        double salary = employee.getSalary();
        // Super simplified tax calculation
        if (salary > 50000) {
            return salary * 0.20; // 20% tax
        } else {
            return salary * 0.10; // 10% tax
        }
    }
};


int main_after() {
    Employee_AfterSRP emp("Bob", 40000.0);
    emp.displayDetails();

    TaxCalculator taxCalc; // Tax calculation is now handled by a separate class
    std::cout << "Tax to pay: $" << taxCalc.calculateTax(emp) << std::endl;

    // If tax rules change, only TaxCalculator needs to be modified.
    // If employee data structure changes, only Employee_AfterSRP needs to be modified.
    // These changes are now isolated.
    return 0;
}

// To run one of them:
int main() {
    std::cout << "--- Running Before SRP ---" << std::endl;
    main_before();
    std::cout << "\n--- Running After SRP ---" << std::endl;
    main_after();
    return 0;
}