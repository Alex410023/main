#pragma once

#include "number.h"

class SquareMatrix {
private:
    int dimension;
    number** matrix;

public:
    // Constructors and Destructor
    SquareMatrix();
    SquareMatrix(const int size);
    SquareMatrix(const SquareMatrix& other);
    ~SquareMatrix();

    // Getter and Setter for matrix dimension
    void setDimension(const int size);
    int getDimension() const;

    void setAt(const int row, const int col, const number num); // ADDED
    number getAt(const int row, const int col) const; // ADDED

    // Set default values for the matrix
    void setDefaultMatrix();
    // Initialize the matrix with user input
    void initialize();
    // Calculate determinant of the matrix
    number calculateDeterminant() const;
    // Transpose the matrix
    SquareMatrix transpose() const;
    // Calculate rank of the matrix
    int calculateRank() const;
    // Print the matrix
    void printMatrix() const;
};
