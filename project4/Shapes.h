#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <memory>
#include <string>

/**
 * @brief Abstract Base Class: Shape
 * Defines the interface for all geometric shapes.
 */
class Shape {
public:
    // Virtual destructor is crucial for proper cleanup of derived objects
    virtual ~Shape() {}

    // Pure virtual functions (must be implemented by children)
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string getName() const = 0;
};

// --- Derived Classes ---

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r);
    double area() const override;
    double perimeter() const override;
    std::string getName() const override { return "Circle"; }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h);
    double area() const override;
    double perimeter() const override;
    std::string getName() const override { return "Rectangle"; }
};

class Triangle : public Shape {
private:
    double sideA, sideB, sideC;
public:
    Triangle(double a, double b, double c);
    double area() const override;
    double perimeter() const override;
    std::string getName() const override { return "Triangle"; }
};

/**
 * @brief ShapeCalculator
 * Demonstrates polymorphism by processing a collection of different shapes.
 */
class ShapeCalculator {
public:
    // Uses unique_ptr for modern, safe memory management
    void printReport(const std::vector<std::unique_ptr<Shape>>& shapes) const;
};

#endif