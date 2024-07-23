#pragma once

#include "matrix.h"

template <class number>
class SquareMatrix : public Matrix<number> {
public:
    // Constructors and Destructor
    SquareMatrix();
    SquareMatrix(const int size);
    SquareMatrix(const SquareMatrix& other);

    // Getter and Setter for matrix dimension
    void setDimension(const int size);
    int getDimension() const;

    // Calculate determinant of the matrix
    number calculateDeterminant() const;
};


// Default constructor
template <class number>
SquareMatrix<number>::SquareMatrix()
    : Matrix<number>() {}

// Constructor with size parameter
template <class number>
SquareMatrix<number>::SquareMatrix(const int size)
    : Matrix<number>(size, size) {}

// Copy constructor
template <class number>
SquareMatrix<number>::SquareMatrix(const SquareMatrix& other)
    : Matrix<number>(other) {}

// Set matrix dimension
template <class number>
void SquareMatrix<number>::setDimension(const int size) {
    Matrix<number>::setRows(size);
    Matrix<number>::setCols(size);
}

// Get matrix dimension
template <class number>
int SquareMatrix<number>::getDimension() const {
    return Matrix<number>::getRows();
}

// Calculate determinant of the matrix
template<class number>
number SquareMatrix<number>::calculateDeterminant() const {
    if (getDimension() == 1) {
        return this->getAt(0, 0);
    }

    SquareMatrix<number> copy(*this); // Create a copy to avoid modifying the original
    number det = 1.0;

    for (int i = 0; i < getDimension(); i++) {
        // Find the pivot for the current column
        int pivotRow = i;
        while (pivotRow < getDimension() && copy.getAt(pivotRow, i) == 0) {
            pivotRow++;
        }

        if (pivotRow == getDimension()) {
            // If no pivot found, the determinant is 0
            return 0.0;
        }

        // Swap rows to move the pivot to the current row
        if (pivotRow != i) {
            for (int j = 0; j < getDimension(); j++) {
                number temp = copy.getAt(i, j);
                copy.setAt(i, j, copy.getAt(pivotRow, j));
                copy.setAt(pivotRow, j, temp);
            }

            det *= -1; // Swap changes the sign of the determinant
        }

        // Scale the pivot row to make the pivot element 1
        // number pivotElement = copy.matrix[i][i];
        number pivotElement = copy.getAt(i, i);
        det *= pivotElement;
        for (int j = i; j < getDimension(); j++) {
            copy.setAt(i, j, copy.getAt(i, j) / pivotElement);
        }

        // Eliminate other rows
        for (int k = i + 1; k < getDimension(); k++) {
            // number factor = copy.matrix[k][i];
            number factor = copy.getAt(k, i);
            for (int j = i; j < getDimension(); j++) {
                copy.setAt(k, j, copy.getAt(k, j) - factor * copy.getAt(i, j));
            }
        }
    }

    return det;
}
