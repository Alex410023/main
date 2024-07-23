#pragma once

#include "number.h"

class Matrix {
private:
    int rows;
    int cols;
    number** matrix;

public:
    // Constructors and Destructor
    Matrix();
    Matrix(const int rowNum, const int colNum);
    Matrix(const Matrix& other);
    ~Matrix();

    // Getter and Setter for rows and columns
    void setRows(const int rowNum);
    int getRows() const;
    void setCols(const int colNum);
    int getCols() const;

    void setAt(const int row, const int col, const number num);
    number getAt(const int row, const int col) const;

    // Set default values for the matrix
    void setDefaultMatrix();
    // Initialize the matrix with user input
    void initialize();
    // Calculate determinant of the matrix
    number calculateDeterminant() const;
    // Transpose the matrix
    Matrix transpose() const;
    // Calculate rank of the matrix
    int calculateRank() const;
    // Print the matrix
    void printMatrix() const;
};
