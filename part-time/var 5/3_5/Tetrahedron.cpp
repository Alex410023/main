#include "Tetrahedron.h"

#include <math.h>

// Default constructor
Tetrahedron::Tetrahedron() 
    : edge(0) 
{
}

// Constructor with parameters
Tetrahedron::Tetrahedron(const double _edge) 
    : edge(_edge) 
{
}

// Copy constructor
Tetrahedron::Tetrahedron(const Tetrahedron& other)
    : edge(other.edge) 
{
}

double Tetrahedron::getEdge() const
{
    return edge;
}

// Overridden function
double Tetrahedron::surface_area() const {
    return sqrt(3) * pow(getEdge(), 2);
}