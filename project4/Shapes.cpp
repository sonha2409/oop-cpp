#include "Shapes.h"
#include <iostream> 

// destructor 
Shape:: ~Shape() {
    std::cout << "Shape destroyed" << std::endl;
}

Circle :: Circle(double r)
    : radius(r) { 
        if (r <= 0) { 
            std::cout << "Error: r must be positive" << std::endl; 
        }
    }

double Circle :: area() const { 
    double a = 3.14 * radius * radius;
    return a; 
}

double Circle :: perimeter() const { 
    double p = 2 * 3.14 * radius;
    return p; 
}

std::string Circle :: getName() const { 
    return "circle";
}

Rectangle :: Rectangle(double w, double h)
    : width(w), height(h) { 
        if (w <= 0 || h <= 0) { 
            std::cout << "width and height has to be positive" << std::endl;
        }
    }

double Rectangle :: area() const { 
    double a = width * height;
    return a;
}

double Rectangle :: perimeter() const { 
    double p = 2 * (width + height);
    return p;
}

std::string Rectangle :: getName() const { 
    return "rectangle "; 
}

Triangle :: Triangle(double a, double b, double c) 
    :sideA(a), sideB(b), sideC(c) { 
        if (a <= 0 || b <= 0 || c <= 0) { 
            std:: cout << "all values have to be posiitive" << std: endl;
        }
    }

double Triangle :: area() const { 
    double s = (sideA + sideB + sideC) / 2; 
    double a = sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
    return a;
}

double Triangle :: perimeter() const { 
    double p = sideA + sideB + sideC; 
    return p;
}

std::string Triangle :: getName() const { 
    return "triangle";
}

void ShapeCalculator :: printReport(const std::vector<std::unique_ptr<Shape>>& shapes) const { 
    
}