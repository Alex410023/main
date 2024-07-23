#pragma once

#include "matrix.h"

class SquareMatrix : public Matrix {
public:
    // Constructors and Destructor
    SquareMatrix();
    SquareMatrix(const int size);
    SquareMatrix(const SquareMatrix& other);

    // Getter and Setter for matrix dimension
    void setDimension(const int size);
    int getDimension() const;
};
