#pragma once

#include <iostream>

template<class number>
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
    // Transpose the matrix
    Matrix<number> transpose() const;
    // Calculate rank of the matrix
    int calculateRank() const;
    // Print the matrix
    void printMatrix() const;
};


// Default constructor
template<class number>
Matrix<number>::Matrix()
    : rows(0)
    , cols(0)
    , matrix(nullptr) {}

// Constructor with size parameter
template<class number>
Matrix<number>::Matrix(const int rowNum, const int colNum)
    : rows(rowNum)
    , cols(colNum) {
    // Allocate memory for the matrix
    matrix = new number*[rowNum];
    for (int i = 0; i < rowNum; i++) {
        matrix[i] = new number[colNum]();
    }
}

// Copy constructor
template<class number>
Matrix<number>::Matrix(const Matrix& other)
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
template<class number>
Matrix<number>::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Set number of rows
template<class number>
void Matrix<number>::setRows(int rowsNum) {
    rows = rowsNum;
}

// Get number of rows
template<class number>
int Matrix<number>::getRows() const {
    return rows;
}

// Set number of columns
template<class number>
void Matrix<number>::setCols(int colsNum) {
    cols = colsNum;
}

// Get number of columns
template<class number>
int Matrix<number>::getCols() const {
    return cols;
}

template<class number>
void Matrix<number>::setAt(const int row, const int col, const number num) {
    matrix[row][col] = num;
}

template<class number>
number Matrix<number>::getAt(const int row, const int col) const {
    return matrix[row][col];
}

// Set default values for the matrix
template<class number>
void Matrix<number>::setDefaultMatrix() {
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
template<class number>
void Matrix<number>::initialize() {
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

// Transpose the matrix
template<class number>
Matrix<number> Matrix<number>::transpose() const {
    Matrix<number> transposedMatrix(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposedMatrix.matrix[i][j] = matrix[j][i];
        }
    }

    return transposedMatrix;
}

// Calculate rank of the matrix
template<class number>
int Matrix<number>::calculateRank() const {
    // Create a copy of the matrix to avoid modifying the original
    Matrix<number> copy(*this);

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
template<class number>
void Matrix<number>::printMatrix() const {
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
