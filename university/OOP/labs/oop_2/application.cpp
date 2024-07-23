#include "application.h"
#include "number.h"
#include "matrix.h"
#include <iostream>

using namespace std;

int ConsoleApplication::run() {

    // //
    // TComplex complex1 = {1, 2};
    // TComplex complex2 = {3, 4};
    // complex1 /= complex2;
    // cout << complex1;
    // //



    // Create a SquareMatrix object
    SquareMatrix squareMatrix;
    // Set default values for the matrix
    squareMatrix.setDefaultMatrix();

    int option;

    while (true) {
        // Display menu options
        cout << "\nOptions:" << endl;
        cout << "1. Initialize the matrix" << endl;
        cout << "2. Print the determinant" << endl;
        cout << "3. Print the transposed matrix" << endl;
        cout << "4. Print the matrix rank" << endl;
        cout << "5. Print the matrix" << endl;
        cout << "0. Exit" << endl;

        // User input for menu selection
        cin >> option;

        switch (option) {
        case 1: {
            // Initialize the matrix
            squareMatrix.initialize();
            break;
        }
        case 2: {
            // Print the determinant of the matrix
            cout << "Determinant: " << squareMatrix.calculateDeterminant() << endl;
            break;
        }
        case 3: {
            // Print the transposed matrix
            cout << "Transposed ";
            squareMatrix.transpose().printMatrix();
            break;
        }
        case 4: {
            // Print the rank of the matrix
            cout << "Rank: " << squareMatrix.calculateRank() << endl;
            break;
        }
        case 5: {
            // Print the matrix
            squareMatrix.printMatrix();
            break;
        }
        case 0: {
            // Exit the application
            cout << "Exiting the application..." << endl;
            return 0;
        }
        default: {
            // Invalid choice message
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }
    return 0;
}
