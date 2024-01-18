#include "Menu.h"

using namespace std;

void Menu::task_1() {
    AEROFLOT* flights = nullptr;
    
    while (true) {
        cout << "\nOptions:" << endl;
        cout << "1. Add a new flight" << endl;
        cout << "2. Edit a flight" << endl;
        cout << "3. Delete a flight" << endl;
        cout << "4. Display all flights" << endl;
        cout << "5. Display flights to a specific destination" << endl;
        cout << "6. Exit" << endl;
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        try {
            switch (choice) {
                case 1: { // Add a new flight
                    AEROFLOT newFlight; 
                    try {
                        cin >> newFlight; // Use the overloaded '>>' operator
                        flights = flights + newFlight;
                        cout << "The flight was added." << endl;
                    } catch (const invalid_argument& e) {
                        cerr << "Error: " << e.what() << endl;
                        continue;
                    }
                    break;
                }
                case 2: {
                    try {
                        int indexToEdit;
                    
                        while (true) {
                            try {
                                cout << "Input an index of the flight to be edited: ";
                                cin >> indexToEdit;

                                if (cin.fail()) { // If input is not an integer
                                    throw invalid_argument("Flight number must be an integer.");
                                }

                                break; // If valid input, exit the loop
                            } catch (const exception& e) {
                                cerr << "Error:" << e.what() << endl;
                                cin.clear(); // Clear the error flag
                                cin.ignore(); // Discard invalid input
                            }
                        }
                        
                        flights->editFlight(flights, indexToEdit);
                    } catch (const exception& e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 3: {
                    try {
                        flights = flights - (*flights); // A plug to make things work (turns a pointer into an object)
                    } catch (const exception& e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 4: {
                    try {
                        flights->displayAllFlights(flights);
                    } catch (const exception& e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 5: {
                    try {
                        string destination;
                        cin.ignore();
                        cout << "Enter the destination to display flights: ";
                        getline(cin, destination);
                        
                        flights->displayFlightsToDest(flights, destination);
                    } catch (const exception& e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 6:
                    return;
                    break;
                default:
                    throw invalid_argument("Not a number in range [1, 6].");
                    break;
            }
        } catch (const invalid_argument& e) {
            cerr << "Invalid input: " << e.what() << endl;
            cin.clear();
            cin.ignore();
        }
    }
}

void Menu::task_2() {
    string fileName;
        cout << "Enter the file name to read from: ";
        getline(cin, fileName);
    
    try {
        ifstream inputFile(fileName);  
        if (!inputFile.is_open()) {
            throw runtime_error("Error opening the file.");
        }

        string word;
        while (inputFile >> word) {
            int i = 0;
            while (i < word.length() && !isalpha(word[i])) {
                i++;
            }
            
            if (i < word.length() && word.find_first_of("AEIOUaeiou", i) == i) {
                cout << word << endl;
            }
        }
        inputFile.close();
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

void Menu::mainMenu() {
    char option;
    
    while (true) {
         try {
            cout << "========== Main menu ==========" << endl;
            cout << "1. Run Task 1" << endl;
            cout << "2. Run Task 2" << endl;
            cout << "0. Exit" << endl;
            cout << "===============================" << endl;
            cout << "Enter the option: ";
            
            cin >> option;
            cin.ignore();  // Clear the input buffer
            
            switch (option) {
                case '1':
                    task_1();
                    break;
                case '2':
                    task_2();
                    break;
                case '0':
                    cout << "Exiting the program." << endl;
                    return;
                default:
                    throw invalid_argument("Incorrect value");
            }
        }
        catch (const exception& e) {
            cerr << "Invalid input: " << e.what() << endl;
        }
    }
}
