#pragma once

class Shape {
public:
    // Constructor
    Shape() {};

    // Virtual destructor
    virtual ~Shape() {};

    // Pure virtual function
    virtual double surface_area() const = 0;
};