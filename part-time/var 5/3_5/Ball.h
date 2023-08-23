#pragma once

#include "Shape.h"

class Ball : public Shape {
private:
    double radius;
public:
    // Default constructor 
    Ball();

    // Constructor with parameters
    Ball(const double _radius);

    // Copy constructor
    Ball(const Ball& other);

    // Destructor
    ~Ball() {};

    // Radius getter function
    double getRadius() const;

    // Overridden function
    double surface_area() const override;
};

