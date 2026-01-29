#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <memory>
#include <string>

/**
 * STEP 1: The Abstract Base Class
 * This is the "contract" that all shapes must follow.
 */
class Shape {
public:
    // --- TASK 1: The Virtual Destructor ---
    // Why: If we delete a Shape* that points to a Circle, we need 
    // to make sure the Circle part is cleaned up too.
    virtual ~Shape() /* FILL IN: Use = default or {} */

    // --- TASK 2: Pure Virtual Functions ---
    // Requirement: Use '= 0' to ensure this class cannot be instantiated.
    // These should be 'const' because calculating area doesn't change the shape.
    virtual double area() const /* FILL IN */ ;
    virtual double perimeter() const /* FILL IN */ ;
    virtual std::string getName() const /* FILL IN */ ;
};

/**
 * STEP 2: The Concrete Classes
 * Your friend needs to implement the specific math for each shape.
 */

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    
    // --- TASK 3: Overriding ---
    // Use the 'override' keyword. This helps the compiler catch typos.
    /* FILL IN: area(), perimeter(), and getName() */
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    /* FILL IN: area(), perimeter(), and getName() overrides */
};

class Triangle : public Shape {
private:
    double sideA, sideB, sideC;
public:
    Triangle(double a, double b, double c) : sideA(a), sideB(b), sideC(c) {}

    /* FILL IN: area(), perimeter(), and getName() overrides */
    // HINT: Use Heron's Formula for the area: sqrt(s*(s-a)*(s-b)*(s-c))
};

/**
 * STEP 3: The Calculator
 * This demonstrates polymorphism. It doesn't care WHAT shape it is,
 * just that it IS a shape.
 */
class ShapeCalculator {
public:
    /**
     * TASK 4: Implementation Logic
     * In the .cpp file, loop through this vector. 
     * Call getName(), area(), and perimeter() on each item.
     */
    void printReport(const std::vector<std::unique_ptr<Shape>>& shapes) const;
};

#endif