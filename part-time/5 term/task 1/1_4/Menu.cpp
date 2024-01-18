#include "Menu.h"

using namespace std;


int Menu::getInt() {
    while (true) {
        try {
            string input;
            cin >> input;

            // Attempt to convert the input to an integer
            int number = stoi(input);

            // If the conversion succeeds, return the integer
            return number;
        } catch (const invalid_argument& e) {
            // The input couldn't be converted to an integer
            cerr << "Invalid input. Please enter an integer." << endl;
            // Clear the error state of cin and ignore the remaining characters in the input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Menu::mainMenu() {
    Keeper animalKeeper;
    
    char option;
    do {
        cout << "========== Menu ==========" << endl;
        cout << "1. Add an animal" << endl;
        cout << "2. Remove an animal" << endl;
        cout << "3. Display animals" << endl;
        cout << "4. Save animals to a file" << endl;
        cout << "5. Load animals from a file" << endl;
        cout << "6. Display animals by type" << endl;
        cout << "7. Modify animal's data" << endl;
        cout << "8. Compare two animals" << endl;
        cout << "9. Exit" << endl;
        cout << "===========================" << endl;
        cout << "Enter the option: ";

        try {
            cin >> option;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer

            switch (option) {
                case '1': {
                    // Add an animal
                    cout << "Enter the type of animal (Fish, Bird, or Cat): ";
                    string type;
                    getline(cin, type);
                    
                    // converting string to lowercase
                    for (auto& ch : type) {
                        ch = tolower(ch);
                    }
                    
                    if (type == "fish") {
                        string breed, color, foodType;
                        cout << "Enter the breed: ";
                        getline(cin, breed);
                        cout << "Enter the color: ";
                        getline(cin, color);
                        cout << "Enter the food type: ";
                        getline(cin, foodType);
                        Animal* fish = new Fish(breed, color, foodType);
                        animalKeeper.addAnimal(fish);
                        cout << "Fish added to the Keeper." << endl;
                    } else if (type == "bird") {
                        string breed, color, eats, habitat;
                        cout << "Enter the breed: ";
                        getline(cin, breed);
                        cout << "Enter the color: ";
                        getline(cin, color);
                        cout << "Enter what it eats: ";
                        getline(cin, eats);
                        cout << "Enter where it lives: ";
                        getline(cin, habitat);
                        Animal* bird = new Bird(breed, color, eats, habitat);
                        animalKeeper.addAnimal(bird);
                        cout << "Bird added to the Keeper." << endl;
                    } else if (type == "cat") {
                        string breed, color, ownerName, nickname;
                        cout << "Enter the breed: ";
                        getline(cin, breed);
                        cout << "Enter the color: ";
                        getline(cin, color);
                        cout << "Enter owner's name: ";
                        getline(cin, ownerName);
                        cout << "Enter nickname: ";
                        getline(cin, nickname);
                        Animal* cat = new Cat(breed, color, ownerName, nickname);
                        animalKeeper.addAnimal(cat);
                        cout << "Cat added to the Keeper." << endl;
                    } else {
                        throw InputValidationException("Invalid animal type. Please enter Fish, Bird, or Cat.");
                    }
                    break;
                }
                case '2': {
                    // Remove an animal
                    cout << "Enter the index of the animal to be deleted: ";
                    int index = getInt();
                    if (animalKeeper.removeAnimal(index)) {
                        cout << "The animal is removed from the Keeper." << endl;
                    }
                    break;
                }
                case '3':
                    // Display animals
                    if (animalKeeper.animalsCount() > 0) {
                        cout << "Animals in the Keeper:" << endl;
                        animalKeeper.displayAnimals();
                    }
                    break;
                case '4': {
                    // Save animals to a file
                    cout << "Enter the filename to save to: ";
                    string filename;
                    getline(cin, filename);
                    animalKeeper.saveToFile(filename);
                    break;
                }
                case '5': {
                    // Load animals from a file
                    cout << "Enter the filename to load from: ";
                    string filename;
                    getline(cin, filename);
                    animalKeeper.loadFromFile(filename);
                    break;
                }
                case '6': {
                    cout << "Enter animal type: ";
                    string type;
                    getline(cin, type);
                    
                    for (auto& ch : type) {
                        ch = tolower(ch);
                    }
                    
                    animalKeeper.displayByType(type);
                    break;
                }
                case '7': {
                    cout << "Enter the index of the animal to be modified: ";
                    int index = getInt();
                    animalKeeper.modifyAnimal(index);
                    break;
                }
                case '8': {
                    cout << "Enter two indexes of animals to be compared:" << endl;
                    int index1 = getInt();
                    int index2 = getInt();
                    animalKeeper.checkIfEqual(index1, index2);
                    break;
                }
                case '9':
                    cout << "Exiting the program." << endl;
                    break;
                default:
                    throw InputValidationException("Invalid input. Please enter a number.");
            }
        } catch (const InputValidationException& e) {
            cerr << "Error: " << e.what() << " Try again." << endl;
        }
    } while (option != '9');
}
