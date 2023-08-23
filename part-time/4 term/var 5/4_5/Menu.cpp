#include "Menu.h"
#include "Array.h"
#include "Stack.h"

#include <iostream>

using namespace std;

// Task 1: array inversion
template <typename T>
void Menu::workWithArr() {
    srand(static_cast<unsigned>(time(NULL)));
    int arrSize = rand() % 30 + 1;

    T* arr = new T[arrSize];
    
    fillArrayRandom(arr, arrSize);

    cout << "\nOriginal " << typeid(T).name() << " array: ";
    printArray(arr, arrSize);

    arrayInversion(arr, arrSize);

    cout << "\nInverted " << typeid(T).name() << " array: ";
    printArray(arr, arrSize);
    cout << endl;

    if constexpr (std::is_same_v<T, char*>) { // To handle char* array case
        for (int i = 0; i < arrSize; i++) {
            delete[] arr[i];
        }
    }
    delete[] arr;
}


// Task 2: work with stack
template <typename T>
void Menu::workWithStack() {
    cout << "Input stack size\n";
    int stackSize;
    while (!(cin >> stackSize) || (cin.peek() != '\n') ||
        (stackSize < 1)) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "You have entered an incorrect number\n";
    }

    // Two different time seeds for stacks
    unsigned seed1 = static_cast<unsigned>(time(NULL));
    unsigned seed2 = static_cast<unsigned>(time(NULL)) + 1;

    Stack<T> stackA(stackSize, seed1);
    Stack<T> stackB(stackSize, seed2);

    bool runAgain_1 = true;

    while (runAgain_1) {
        cout << endl << "Choose option:" << endl;

        cout << "1. Assign Stack A to Stack B" << endl;
        cout << "2. Assign Stack B to Stack A" << endl;
        cout << "3. Add Stack A and Stack B" << endl;
        cout << "4. Compare Stack A and Stack B" << endl;
        cout << "5. Subtract Stack B from Stack A" << endl;
        cout << "6. Subtract Stack A from Stack B" << endl;
        cout << "7. Print both stacks" << endl;
        cout << "8. Exit" << endl;

        int option;
        while (!(cin >> option) || (cin.peek() != '\n') ||
            (option < 1) || (option > 8)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        switch (option) {
        case 1:
            stackB = stackA;
            cout << "Stack A assigned to Stack B." << endl;
            break;
        case 2:
            stackA = stackB;
            cout << "Stack B assigned to Stack A." << endl;
            break;
        case 3:
            cout << "Stack A + Stack B: ";
            (stackA + stackB).print();
            break;
        case 4:
            cout << "Stack A and Stack B are " << (stackA == stackB ? "" :
                "not ") << "equal" << endl;
            break;
        case 5:
            cout << "Stack A - Stack B: ";
            (stackA - stackB).print();
            break;
        case 6:
            cout << "Stack B - Stack A: ";
            (stackB - stackA).print();
            break;
        case 7:
            cout << endl;
            stackA.print();
            stackB.print();
            break;
        case 8:
            runAgain_1 = false;
            break;
        }
    }
    cout << endl;
}

void Menu::mainMenu() {
    bool runAgain = true;

    while (runAgain) {
        cout << "Choose option:\n";
        cout << "1 - Array\n";
        cout << "2 - Stack\n";
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
            cout << "\nChoose what to fill the array with:\n";
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
                workWithArr<int>();
                break;
            case 2:
                workWithArr<char>();
                break;
            case 3:
                workWithArr<float>();
                break;
            case 4:
                workWithArr<double>();
                break;
            case 5:
                workWithArr<char*>();
                break;
            }
            break;
        case 2:
            switch (dataType) {
            case 1:
                workWithStack<int>();
                break;
            case 2:
                workWithStack<char>();
                break;
            case 3:
                workWithStack<float>();
                break;
            case 4:
                workWithStack<double>();
                break;
            case 5:
                workWithStack<char*>();
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
