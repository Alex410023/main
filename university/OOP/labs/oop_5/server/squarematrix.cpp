#include "squarematrix.h"

// Default constructor
SquareMatrix::SquareMatrix()
    : Matrix() {}

// Constructor with size parameter
SquareMatrix::SquareMatrix(const int size)
    : Matrix(size, size) {}

// Copy constructor
SquareMatrix::SquareMatrix(const SquareMatrix& other)
    : Matrix(other) {}

// Set matrix dimension
void SquareMatrix::setDimension(const int size) {
    Matrix::setRows(size);
    Matrix::setCols(size);
}

// Get matrix dimension
int SquareMatrix::getDimension() const {
    return Matrix::getRows();
}
