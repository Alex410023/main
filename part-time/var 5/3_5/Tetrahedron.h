#pragma once

#include "Shape.h"

class Tetrahedron : public Shape {
private:
    double edge;
public:
    // Default constructor
    Tetrahedron();

    // Constructor with parameters
    Tetrahedron(const double _edge);

    // Copy constructor
    Tetrahedron(const Tetrahedron& other);

    // Destructor
    ~Tetrahedron() {};

    // Edge getter function
    double getEdge() const;

    // Overridden function
    double surface_area() const override;
};

