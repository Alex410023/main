#pragma once

#include "Animal.h"
#include "Bird.h"
#include "Fish.h"
#include "Cat.h"
#include "Exception.h"

class Keeper {
private:
    Animal** animals;
    int numAnimals;
    
public:
    // Default constructor
    Keeper();
    
    // Copy constructor
    Keeper(const Keeper& keeper);

    // Destructor
    ~Keeper();
    
    int animalsCount();
    Animal* getAnimal(int index);

    void addAnimal(Animal* animal);
    bool removeAnimal(const int index);
    void displayAnimals() const;
    void displayByType(const std::string& type) const;
    void modifyAnimal(const int index);
    
    void checkIfEqual(const int index1, const int index2);
    
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
