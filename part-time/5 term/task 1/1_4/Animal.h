#pragma once

#include <iostream>
#include <fstream>
#include <string>

// Define the Animal class as the base class
class Animal {
public:
    // Default constructor
    Animal() {
        std::cout << "Animal base constructor was called" << std::endl;
    }

    virtual void displayInfo() const = 0;
    virtual void modify() = 0;
    virtual void saveToFile(std::ofstream& file) const = 0;
    virtual void loadFromFile(std::ifstream& file) = 0;
    
    // Base class comparison operator
    virtual bool operator==(const Animal& animal) const = 0;
    
    // Virtual destructor
    virtual ~Animal() {
        std::cout << "Animal base destructor was called" << std::endl;
    }
};
