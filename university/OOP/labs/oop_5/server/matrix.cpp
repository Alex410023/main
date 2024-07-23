#include "matrix.h"
#include "number.h"

#include <iostream>

// Default constructor
Matrix::Matrix()
    : rows(0)
    , cols(0)
    , matrix(nullptr) {}

// Constructor with size parameter
Matrix::Matrix(const int rowNum, const int colNum)
    : rows(rowNum)
    , cols(colNum) {
    // Allocate memory for the matrix
    matrix = new number*[rowNum];
    for (int i = 0; i < rowNum; i++) {
        matrix[i] = new number[colNum]();
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
    : rows(other.rows)
    , cols(other.cols) {
    // Allocate memory for the new matrix
    matrix = new number*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new number[cols]();
    }

    // Copy the elements from the other matrix to the new matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

// Destructor to deallocate memory
Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Set number of rows
void Matrix::setRows(int rowsNum) {
    rows = rowsNum;
}

// Get number of rows
int Matrix::getRows() const {
    return rows;
}

// Set number of columns
void Matrix::setCols(int colsNum) {
    cols = colsNum;
}

// Get number of columns
int Matrix::getCols() const {
    return cols;
}

void Matrix::setAt(const int row, const int col, const number num) {
    matrix[row][col] = num;
}

number Matrix::getAt(const int row, const int col) const {
    return matrix[row][col];
}

// Set default values for the matrix
void Matrix::setDefaultMatrix() {
    // Set default dimension and values for the matrix
    rows = 3;
    cols = 3;
    matrix = new number*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new number[cols]();
    }

    // Example matrix initialization
    number tempval = 9.5;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = tempval;
            tempval += 1.1 * i - j; // some values
        }
    }

    // matrix = { {9.5, 9.5, 8.5},
    //            {6.5, 7.6, 7.7},
    //            {6.8, 9.0, 10.2} };
}

// Initialize the matrix with user input
void Matrix::initialize() {
    // User input for matrix size
    std::cout << "Input the number of rows and columns (positive numbers): ";
    int numRows, numCols;
    do {
        std::cin >> numRows >> numCols;
        if (numRows <= 0 || numCols <= 0) {
            std::cout << "Invalid input. Please enter positive numbers." << std::endl;
        }
    } while (numRows <= 0 || numCols <= 0);

    // Set matrix dimension
    rows = numRows;
    cols = numCols;

    // Deallocate existing matrix memory if needed
    if (matrix) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Allocate memory for the matrix
    matrix = new number*[numRows];
    for (int i = 0; i < numRows; i++) {
        matrix[i] = new number[numCols]();
    }

    std::cout << "Enter matrix elements:" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << "Matrix[" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
}

// Calculate determinant of the matrix
number Matrix::calculateDeterminant() const {
    if (rows != cols) {
        throw std::runtime_error("Cannot calculate determinant of a non-square matrix");
    }

    if (rows == 1) {
        return matrix[0][0];
    }

    Matrix copy(*this); // Create a copy to avoid modifying the original
    number det = 1.0;

    for (int row = 0; row < rows; row++) {
        // Find the pivot for the current column
        int pivotRow = row;
        while (pivotRow < rows && copy.matrix[pivotRow][row] == 0) {
            pivotRow++;
        }

        if (pivotRow == rows) {
            // If no pivot found, the determinant is 0
            return 0.0;
        }

        // Swap rows to move the pivot to the current row
        if (pivotRow != row) {
            std::swap(copy.matrix[row], copy.matrix[pivotRow]);
            det *= -1; // Swap changes the sign of the determinant
        }

        // Scale the pivot row to make the pivot element 1
        number pivotElement = copy.matrix[row][row];
        det *= pivotElement;
        for (int col = row; col < cols; col++) {
            copy.matrix[row][col] /= pivotElement;
        }

        // Eliminate other rows
        for (int k = row + 1; k < rows; k++) {
            number factor = copy.matrix[k][row];
            for (int col = row; col < cols; col++) {
                copy.matrix[k][col] -= factor * copy.matrix[row][col];
            }
        }
    }

    return det;
}

// Transpose the matrix
Matrix Matrix::transpose() const {
    Matrix transposedMatrix(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposedMatrix.matrix[i][j] = matrix[j][i];
        }
    }

    return transposedMatrix;
}

// Calculate rank of the matrix
int Matrix::calculateRank() const {
    // Create a copy of the matrix to avoid modifying the original
    Matrix copy(*this);

    int rank = 0;
    for (int leadRow = 0; leadRow < rows && rank < cols; leadRow++) {
        // Find the pivot for the current column
        int pivotRow = leadRow;
        while (pivotRow < rows && copy.matrix[pivotRow][leadRow] == 0) {
            pivotRow++;
        }

        if (pivotRow == rows) {
            // If no pivot found, move to the next column
            continue;
        }

        // Swap rows to move the pivot to the current row
        std::swap(copy.matrix[leadRow], copy.matrix[pivotRow]);

        // Scale the pivot row to make the pivot element 1
        number pivotElement = copy.matrix[leadRow][leadRow];
        for (int col = leadRow; col < cols; col++) {
            copy.matrix[leadRow][col] /= pivotElement;
        }

        // Eliminate other rows
        for (int row = 0; row < rows; row++) {
            if (row != leadRow) {
                number factor = copy.matrix[row][leadRow];
                for (int col = leadRow; col < cols; col++) {
                    copy.matrix[row][col] -= factor * copy.matrix[leadRow][col];
                }
            }
        }

        // Move to the next row and column
        rank++;
    }

    return rank;
}

// Print the matrix
void Matrix::printMatrix() const {
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
