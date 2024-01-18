#include "Keeper.h"

// Default constructor
Keeper::Keeper()
    : animals(nullptr)
    , numAnimals(0) {
    std::cout << "Keeper constructor was called" << std::endl;
}

// Copy constructor
Keeper::Keeper(const Keeper& keeper) {
    numAnimals = keeper.numAnimals;
    animals = new Animal*[numAnimals];
    
    for (int i = 0; i < numAnimals; i++) {
        if (dynamic_cast<Bird*>(keeper.animals[i])) {
            animals[i] = new Bird(*dynamic_cast<Bird*>(keeper.animals[i]));
        } else if (dynamic_cast<Cat*>(keeper.animals[i])) {
            animals[i] = new Cat(*dynamic_cast<Cat*>(keeper.animals[i]));
        } else if (dynamic_cast<Fish*>(keeper.animals[i])) {
            animals[i] = new Fish(*dynamic_cast<Fish*>(keeper.animals[i]));
        }
    }
    std::cout << "Keeper copy constructor was called" << std::endl;
}

// Destructor
Keeper::~Keeper() {
    for (int i = 0; i < numAnimals; ++i) {
        delete animals[i];
    }
    delete[] animals;
    std::cout << "Keeper destructor was called" << std::endl;
}

int Keeper::animalsCount() {
    return numAnimals;
}

Animal* Keeper::getAnimal(int index) {
    return animals[index];
}

void Keeper::addAnimal(Animal* animal) {
    Animal** newAnimals = new Animal*[numAnimals + 1];
    for (int i = 0; i < numAnimals; i++) {
        newAnimals[i] = animals[i];
    }
    newAnimals[numAnimals++] = animal;

    delete [] animals;
    animals = newAnimals;
}

bool Keeper::removeAnimal(const int index) {
    if (index >= 0) {
        if (index < numAnimals) {
            Animal** newAnimals = new Animal*[numAnimals--];
            
            for (int i = 0; i <= numAnimals; i++) {
                if (i == index) {
                    continue;
                }
                if (i > index) {
                    newAnimals[i - 1] = animals[i];
                    continue;
                }
                newAnimals[i] = animals[i];
            }
            
            delete [] animals;
            animals = newAnimals;
            return true;
        } else {
            std::cerr << "Error: No animals to remove." << std::endl;
        }
    } else {
        std::cerr << "Error: Index cannot be less than 0." << std::endl;
    }
    return false;
}

void Keeper::displayAnimals() const {
    if (numAnimals > 0) {
        for (int i = 0; i < numAnimals; ++i) {
            std::cout << "[" << i << "] - ";
            animals[i]->displayInfo();
        }
    } else {
        std::cout << "No animals in the Keeper." << std::endl;
    }
}

void Keeper::displayByType(const std::string& type) const {
    if (type == "fish" || type == "cat" || type == "bird") {
        if (numAnimals > 0) {
            for (int i = 0; i < numAnimals; i++) {
                // Check the type of the animal and display only if it matches the specified type.
                if (type == "fish" && dynamic_cast<Fish*>(animals[i])) {
                    animals[i]->displayInfo();
                } else if (type == "cat" && dynamic_cast<Cat*>(animals[i])) {
                    animals[i]->displayInfo();
                } else if (type == "bird" && dynamic_cast<Bird*>(animals[i])) {
                    animals[i]->displayInfo();
                }
            }
        } else {
            std::cout << "No animals of type " << type << " in the Keeper." << std::endl;
        }
    } else {
        throw InputValidationException("There's no such type.");
    }
}


void Keeper::modifyAnimal(const int index) {
    if (index < 0) {
        std::cerr << "The index cannot be less than 0." << std::endl;
    } else if (index > numAnimals) {
        std::cerr << "The index cannot be greater than the total number of animals." << std::endl;
    } else {
        animals[index]->modify();
    }
}

void Keeper::checkIfEqual(const int index1, const int index2) {
    if (index1 >= 0 && index1 < numAnimals && index2 >= 0 && index2 < numAnimals) {
        Animal* animal1 = getAnimal(index1);
        Animal* animal2 = getAnimal(index2);

        if (animal1 && animal2) {
            const std::type_info& type1 = typeid(*animal1);
            const std::type_info& type2 = typeid(*animal2);

            if (*animal1 == *animal2) {
                std::cout << "The animals are equal." << std::endl;
            } else if (type1 != type2) {
                std::cout << "The animals have different types." << std::endl;
            } else {
                std::cout << "he animals are NOT equal" << std::endl;
            }
        } else {
            std::cerr << "At least one of the animals is nullptr." << std::endl;
        }
    } else {
        std::cerr << "Incorrect index." << std::endl;
    }
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << numAnimals << std::endl;
        for (int i = 0; i < numAnimals; ++i) {
            animals[i]->saveToFile(file);
        }
        file.close();
        std::cout << "Saved " << numAnimals << " animals to " << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open the file for saving." << std::endl;
    }
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        int loadedNumAnimals;
        file >> loadedNumAnimals;
        file.ignore();  // Consume the newline character
        for (int i = 0; i < loadedNumAnimals; ++i) {
            std::string type;
            file >> type;
            file.ignore();  // Consume the space character
            Animal* animal = nullptr;
            if (type == "Fish") {
                animal = new Fish();
            } else if (type == "Bird") {
                animal = new Bird();
            } else if (type == "Cat") {
                animal = new Cat();
            }

            if (animal) {
                animal->loadFromFile(file);
                addAnimal(animal);
            }
        }
        std::cout << "Loaded " << numAnimals << " animal(-s) from " << filename << std::endl;

        file.close();
    } else {
        std::cerr << "Error: Unable to open the file for loading." << std::endl;
    }
}
