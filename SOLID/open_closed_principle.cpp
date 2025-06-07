Open Closed Principle: 
The Open/Closed Principle (OCP) states that software entities (like classes, modules, functions) should be open for extension, but closed for modification.

What it means:
=> Open for Extension: You should be able to add new functionality or behavior to a module without altering its existing source code.
=> Closed for Modification: Once a module has been developed and tested, its existing code should ideally not change.

Problem it Solves:
OCP aims to prevent a common problem: when you modify existing, working code to add a new feature, you risk introducing bugs into that stable code (regressions). This also often leads to a cascade of re-testing for all dependent parts of the system.

Why we want this (and not just modify existing code):
=> Stability & Reduced Risk: By not changing existing, proven code, we minimize the risk of breaking something that already works.
=> Maintainability: It's easier to add new features when they can be plugged in as extensions, rather than interwoven into complex existing logic.
=> Reduced Testing Effort: You primarily need to test the new extension, rather than re-testing the entire modified module and its dependencies.
=> Flexibility: The system becomes more flexible and adaptable to future changes.

How is it typically achieved?
The most common ways to achieve OCP are through abstraction and polymorphism:

1. Abstraction (Interfaces/Abstract Classes): Code against abstract interfaces rather than concrete implementations. New functionality can be added by creating new classes that implement these interfaces.
2. Polymorphism (Inheritance): Design a base class with virtual methods. New behaviors can be introduced by creating new derived classes that override these methods.
3. Other patterns like the Strategy pattern or Template Method pattern also facilitate OCP.

Use Case: We need a system to calculate the area of shapes. Initially, we only support rectangles, but we anticipate adding more shapes later (like circles).
Before OCP (Modification Required for New Shapes)
#include <iostream>
#include <string>
#include <vector>
#include <cmath> // For M_PI if we add Circle

// --- Before OCP ---
// This class directly handles area calculation for different shapes.
// To add a new shape (e.g., Circle), we MUST MODIFY this class's calculateArea method.
// This violates OCP because the class is not closed for modification.
class AreaCalculator_BeforeOCP {
public:
    // This method needs to be changed every time a new shape is added.
    double calculateArea(const std::string& shapeType, double param1, double param2 = 0) {
        if (shapeType == "rectangle") {
            double width = param1;
            double height = param2;
            return width * height;
        }
        // If we want to add a Circle:
        // else if (shapeType == "circle") {
        //     double radius = param1;
        //     return M_PI * radius * radius;
        // }
        // And so on for other shapes...
        else {
            std::cerr << "Unsupported shape type!" << std::endl;
            return 0.0;
        }
    }
};

int main_before() {
    AreaCalculator_BeforeOCP calculator;

    std::cout << "Rectangle Area: " << calculator.calculateArea("rectangle", 5.0, 4.0) << std::endl;

    // To add a Circle, we would need to go back and modify the AreaCalculator_BeforeOCP class.
    // std::cout << "Circle Area: " << calculator.calculateArea("circle", 3.0) << std::endl; // This would fail or require modification
    return 0;
}

After Applying OCP (Extension without Modification)

#include <iostream>
#include <string>
#include <vector>
#include <cmath> // For M_PI
#include <memory> // For std::unique_ptr

// --- After OCP ---

// Step 1: Create an abstraction (Interface or Abstract Base Class)
// This defines the contract for all shapes.
class Shape {
public:
    virtual ~Shape() = default; // Important for proper cleanup with polymorphism
    virtual double calculateArea() const = 0; // Pure virtual function
};

// Step 2: Create concrete implementations for each shape.
// These are "extensions."
class Rectangle : public Shape {
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double calculateArea() const override {
        return width * height;
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double calculateArea() const override {
        return M_PI * radius * radius;
    }
};

// (Optional) A class to work with shapes, but it doesn't need to know concrete types.
// This part is "closed for modification" regarding new shape types.
class ShapeProcessor {
public:
    void printArea(const Shape& shape) { // Works with any Shape object
        std::cout << "Area: " << shape.calculateArea() << std::endl;
    }
};


int main_after() {
    ShapeProcessor processor;

    std::unique_ptr<Shape> rect = std::make_unique<Rectangle>(5.0, 4.0);
    std::cout << "Rectangle ";
    processor.printArea(*rect);

    std::unique_ptr<Shape> circ = std::make_unique<Circle>(3.0);
    std::cout << "Circle ";
    processor.printArea(*circ);

    // To add a new shape (e.g., Triangle):
    // 1. Create a new class: class Triangle : public Shape { ... implement calculateArea() ... };
    // 2. Use it: std::unique_ptr<Shape> tri = std::make_unique<Triangle>(base, h); processor.printArea(*tri);
    // NO MODIFICATION is needed for the Shape base class or the ShapeProcessor class.
    // We only ADDED new code (the Triangle class).
    return 0;
}

// To run one of them:
int main() {
    std::cout << "--- Running Before OCP ---" << std::endl;
    main_before();
    std::cout << "\n--- Running After OCP ---" << std::endl;
    main_after();
    return 0;
}
