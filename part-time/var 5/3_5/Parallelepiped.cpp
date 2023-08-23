#include "Parallelepiped.h"

// Default constructor
Parallelepiped::Parallelepiped()
    : length(0)
    , width(0)
    , height(0) 
{
}

// Constructor with parameters
Parallelepiped::Parallelepiped(const double _length, const double _width, const double _height)
    : length(_length)
    , width(_width)
    , height(_height)
{
}

// Copy constructor
Parallelepiped::Parallelepiped(const Parallelepiped& other)
    : length(other.length)
    , width(other.width)
    , height(other.height) 
{
}

double Parallelepiped::getLength() const
{
    return length;
}


double Parallelepiped::getWidth() const
{
    return width;
}


double Parallelepiped::getHeight() const
{
    return height;
}


// Overridden function
double Parallelepiped::surface_area() const {
    if (getLength() != 0 && getWidth() != 0 && getHeight() != 0) {
        return 2.0 *(getLength() * getWidth() + getWidth() * getHeight() +
            getHeight() * getLength());
    }
    else {
        return 0;
    }
}
