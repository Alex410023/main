#include "App.h"
#include "BinaryTree.h"
#include "LinearSearch.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


template <typename T>
bool App::convertValue(const std::string& input, T& value) {
    std::istringstream iss(input);
    if constexpr (std::is_same_v<T, int>) { // Int case
        int intValue; // Create a value of the chosen type
        if ((iss >> intValue) && iss.eof()) { // Compare that value with what we 
                                              // have as input (iss)
            value = static_cast<T>(intValue); // Turn 'T value' into value with 
                                              //the chosen data type
            return true;
        }
        return false;
    }
    else if constexpr (std::is_same_v<T, float>) { // Float case
        float floatValue;                          // Described above
        if ((iss >> floatValue) && iss.eof()) {
            value = static_cast<T>(floatValue);
            return true;
        }
        return false;
    }
    else if constexpr (std::is_same_v<T, double>) { // Double case
        double doubleValue;                         // Described above
        if ((iss >> doubleValue) && iss.eof()) {
            value = static_cast<T>(doubleValue);
            return true;
        }
        return false;
    }
    /* 
        Chars do not include digits
    */
    else if constexpr (std::is_same_v<T, char>) { // Char case
        // If there's only one element in 'input' array
        if (input.length() == 1 && !std::isspace(input[0]) && (input[0] - '0') > 9) {
            value = static_cast<T>(input[0]);
            return true;
        }
        return false;
    }
    /*
        Char*'s do not include single char symbols
    */
    else if constexpr (std::is_same_v<T, char*>) { // Char* case
        // Copying symbols from 'input' to 'value'
        if (!input.empty()) {
            value = new char[input.length() + 1]; // Turning 'T value' into char array
            strcpy_s(value, input.length() + 1, input.c_str());
            return true;
        }
        return false;
    }
}


template <typename T>
void App::workWithBinTree() {
    BinaryTree<T> tree;

    bool runTree = true;
    while (runTree) {
        cout << endl;
        cout << "1. Add an element" << endl;
        cout << "2. Traverse in descending order" << endl;
        cout << "3. Traverse in ascending order" << endl;
        cout << "4. Search for a value" << endl;
        cout << "5. Delete an element" << endl;
        cout << "6. Exit" << endl;

        int option;
        while (!(cin >> option) || (cin.peek() != '\n') ||
            (option < 1) || (option > 6)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        T value {};
        string input, input1, input2;
        bool correctDataType;

        switch (option) {
        case 1:
            cout << endl << "Input the value to be added" << endl;
            cin.ignore(); // Ignore any previous newline character
            getline(cin, input);

            correctDataType = convertValue<T>(input, value);

            // If the chosen data type corresponds with the data type of 'input'
            if (correctDataType) {
                // If there's no the same element
                if (!tree.searchValue(value)) {
                    tree.addElement(value);
                }
                else {
                    cout << "You cannot add duplicates" << endl;
                }
            }
            else {
                cout << "Symbols do not correspond with the chosen data type" << endl;
            }

            break;
        case 2:
            tree.traverseDescending();
            break;
        case 3:
            tree.traverseAscending();
            break;
        case 4:
            cout << endl << "Input the value to be searched" << endl;
            cin.ignore(); // Ignore any previous newline character
            getline(cin, input1);

            correctDataType = convertValue<T>(input1, value);

            // If the chosen data type corresponds with the data type of 'input1'
            if (correctDataType) {
                cout << "The element was" << (tree.searchValue(value) ? " " :
                    " not ") << "found." << endl;
            }
            else {
                cout << "Symbols do not correspond with the chosen data type" << endl;
            }
            break;
        case 5:
            cout << endl << "Input the value to be deleted" << endl;
            cin.ignore(); // Ignore any previous newline character
            getline(cin, input2);

            correctDataType = convertValue<T>(input2, value);

            // If the chosen data type corresponds with the data type of 'input2'
            if (correctDataType) {
                tree.deleteElement(value);
            }
            else {
                cout << "Symbols do not correspond with the chosen data type" << endl;
            }        
            break;
        case 6:
            runTree = false;
            break;
        }
    }
}


template <typename T>
void App::workWithLinSearch() {
    srand(static_cast<unsigned>(time(NULL)));

    int arrSize = rand() % 101 + 30;

    T* arr = new T[arrSize];

    fillArray(arr, arrSize);

    cout << "\n" << typeid(T).name() << " array: ";
    printArray(arr, arrSize);

    T value {};
    string input;
    bool correctDataType;

    bool runArr = true;
    while (runArr) {
        cout << "\nInput value to be checked: ";
        cin.ignore(); // Ignore any previous newline character
        getline(cin, input);

        correctDataType = convertValue<T>(input, value);

        // If the chosen data type corresponds with the data type of 'input'
        if (correctDataType) {
            cout << "The element was" << (linearSearch(arr, arrSize, value)
                ? " " : " not ") << "found" << endl;
        }
        else {
            cout << "Symbols do not correspond with the chosen data type" << endl;
        }

        cout << "Do you want to continue? (1 - Yes / 0 - No): ";
        int cont;
        while (!(cin >> cont) || (cin.peek() != '\n') ||
            (cont < 0) || (cont > 1)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }
        if (!cont) {
            runArr = false;
        }
        
    }

    if constexpr (std::is_same_v<T, char*>) { // To handle char* array deleting case
        for (int i = 0; i < arrSize; i++) {
            delete[] arr[i];
        }
    }
    delete[] arr;
}

void App::mainMenu() {
    bool runAgain = true;

    while (runAgain) {
        cout << "\nChoose option:\n";
        cout << "1 - Binary Tree\n";
        cout << "2 - Linear Search\n";
        cout << "3 - Exit\n";

        int choice;
        while (!(cin >> choice) || (cin.peek() != '\n') ||
            (choice < 1) || (choice > 3)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        int dataType;
        if (choice != 3) {
            cout << "\nChoose what to fill a class with:\n";
            cout << "1 - int, 2 - char, 3 - float, 4 - double, 5 - char*\n";

            while (!(cin >> dataType) || (cin.peek() != '\n') ||
                (dataType < 1) || (dataType > 5)) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "You have entered an incorrect number\n";
            }
        }

        switch (choice) {
        case 1:
            switch (dataType) {
            case 1:
                workWithBinTree<int>();
                break;
            case 2:
                workWithBinTree<char>();
                break;
            case 3:
                workWithBinTree<float>();
                break;
            case 4:
                workWithBinTree<double>();
                break;
            case 5:
                workWithBinTree<char*>();
                break;
            }
            break;
        case 2:
            switch (dataType) {
            case 1:
                workWithLinSearch<int>();
                break;
            case 2:
                workWithLinSearch<char>();
                break;
            case 3:
                workWithLinSearch<float>();
                break;
            case 4:
                workWithLinSearch<double>();
                break;
            case 5:
                workWithLinSearch<char*>();
                break;
            }
            break;
        case 3:
            runAgain = false;
            break;
        }
    }
    cout << "Thank you for using the program.\n";
}