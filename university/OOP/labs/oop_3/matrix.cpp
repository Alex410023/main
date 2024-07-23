#include "matrix.h"
#include "number.h"
#include <iostream>

// Default constructor
SquareMatrix::SquareMatrix()
    : dimension(0)
    , matrix(nullptr) {}

// Constructor with size parameter
SquareMatrix::SquareMatrix(const int size)
    : dimension(size) {
    // Allocate memory for the matrix
    matrix = new number*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new number[size]();
    }
}

// Copy constructor
SquareMatrix::SquareMatrix(const SquareMatrix& other)
    : dimension(other.dimension) {
    // Allocate memory for the new matrix
    matrix = new number*[dimension];
    for (int i = 0; i < dimension; i++) {
        matrix[i] = new number[dimension]();
    }

    // Copy the elements from the other matrix to the new matrix
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

// Destructor to deallocate memory
SquareMatrix::~SquareMatrix() {
    for (int i = 0; i < dimension; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Set matrix dimension
void SquareMatrix::setDimension(const int size) {
    dimension = size;
}

// Get matrix dimension
int SquareMatrix::getDimension() const {
    return dimension;
}

void SquareMatrix::setAt(const int row, const int col, const number num) {
    matrix[row][col] = num;
}

number SquareMatrix::getAt(const int row, const int col) const {
    return matrix[row][col];
}

// Set default values for the matrix
void SquareMatrix::setDefaultMatrix() {
    // Set default dimension and values for the matrix
    dimension = 3;
    matrix = new number*[dimension];
    for (int i = 0; i < dimension; i++) {
        matrix[i] = new number[dimension]();
    }

    // Example matrix initialization
    number tempval = 9.5;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matrix[i][j] = tempval;
            tempval += 1.1 * i - j; // some values
        }
    }

    // matrix = { {9.5, 9.5, 8.5},
    //            {6.5, 7.6, 7.7},
    //            {6.8, 9.0, 10.2} };
}

// Initialize the matrix with user input
void SquareMatrix::initialize() {
    // User input for matrix size
    std::cout << "Input the size of the matrix (positive number): ";
    int size;
    do {
        std::cin >> size;
        if (size <= 0) {
            std::cout << "Invalid input. Please enter a positive number." << std::endl;
        }
    } while (size <= 0);

    // Set matrix dimension
    dimension = size;

    // Deallocate existing matrix memory if needed
    if (!matrix) {
        for (int i = 0; i < dimension; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Allocate memory for the matrix
    matrix = new number*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new number[size]();
    }

    std::cout << "Enter matrix elements:" << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << "Matrix[" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
}

// Calculate determinant of the matrix
number SquareMatrix::calculateDeterminant() const {
    if (dimension == 1) {
        return matrix[0][0];
    }

    SquareMatrix copy(*this); // Create a copy to avoid modifying the original
    number det = 1.0;

    for (int i = 0; i < dimension; i++) {
        // Find the pivot for the current column
        int pivotRow = i;
        while (pivotRow < dimension && copy.matrix[pivotRow][i] == 0) {
            pivotRow++;
        }

        if (pivotRow == dimension) {
            // If no pivot found, the determinant is 0
            return 0.0;
        }

        // Swap rows to move the pivot to the current row
        if (pivotRow != i) {
            std::swap(copy.matrix[i], copy.matrix[pivotRow]);
            det *= -1; // Swap changes the sign of the determinant
        }

        // Scale the pivot row to make the pivot element 1
        number pivotElement = copy.matrix[i][i];
        det *= pivotElement;
        for (int j = i; j < dimension; j++) {
            copy.matrix[i][j] /= pivotElement;
        }

        // Eliminate other rows
        for (int k = i + 1; k < dimension; k++) {
            number factor = copy.matrix[k][i];
            for (int j = i; j < dimension; j++) {
                copy.matrix[k][j] -= factor * copy.matrix[i][j];
            }
        }
    }

    return det;
}

// Transpose the matrix
SquareMatrix SquareMatrix::transpose() const {
    SquareMatrix transposedMatrix(dimension);

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            transposedMatrix.matrix[i][j] = matrix[j][i];
        }
    }

    return transposedMatrix;
}

// Calculate rank of the matrix
int SquareMatrix::calculateRank() const {
    // Create a copy of the matrix to avoid modifying the original
    SquareMatrix copy(*this);

    int rank = 0;
    for (int i = 0; i < dimension; i++) {
        // Find the pivot for the current column
        int pivotRow = i;
        while (pivotRow < dimension && copy.matrix[pivotRow][i] == 0) {
            pivotRow++;
        }

        if (pivotRow == dimension) {
            // If no pivot found, move to the next column
            continue;
        }

        // Swap rows to move the pivot to the current row
        std::swap(copy.matrix[i], copy.matrix[pivotRow]);

        // Scale the pivot row to make the pivot element 1
        number pivotElement = copy.matrix[i][i];
        for (int j = i; j < dimension; j++) {
            copy.matrix[i][j] /= pivotElement;
        }

        // Eliminate other rows
        for (int k = 0; k < dimension; k++) {
            if (k != i) {
                number factor = copy.matrix[k][i];
                for (int j = i; j < dimension; j++) {
                    copy.matrix[k][j] -= factor * copy.matrix[i][j];
                }
            }
        }

        // Move to the next row and column
        rank++;
    }

    return rank;
}

// Print the matrix
void SquareMatrix::printMatrix() const{
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
