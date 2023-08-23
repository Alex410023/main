#define _USE_MATH_DEFINES

#include "Ball.h"
#include <math.h>


// Default constructor 
Ball::Ball() 
    : radius(0)
{
}

// Constructor with parameters
Ball::Ball(const double _radius) 
    : radius(_radius)
{
}

// Copy constructor
Ball::Ball(const Ball& other) 
    : radius(other.radius)
{
}

double Ball::getRadius() const
{
    return radius;
}

// Overridden function
double Ball::surface_area() const {
    return 4.0 * M_PI * pow(getRadius(), 2);
}
