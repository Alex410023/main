#pragma once

#include "Shape.h"

class Parallelepiped : public Shape {
private:
    double length, width, height;
public:
    // Default constructor
    Parallelepiped();

    // Constructor with parameters
    Parallelepiped(const double _length, const double _width, const double _height);

    // Copy constructor
    Parallelepiped(const Parallelepiped& other);

    // Destructor
    ~Parallelepiped() {};

    // Length getter function
    double getLength() const;

    // Width getter function
    double getWidth() const;

    // Height getter function
    double getHeight() const;

    // Overridden function
    double surface_area() const override;
};
