#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Animal.h"


class Fish : public Animal {
private:
    std::string breed;
    std::string color;
    std::string foodType;
    
public:
    // Default constructor
    Fish();

    // Constructor with parameters
    Fish(const std::string& breed, const std::string& color, const std::string& foodType);

    // Copy constructor
    Fish(const Fish& fish);
    
    // Destructor
    ~Fish() override;
    
    std::string getBreed();
    std::string getColor();
    std::string getFoodType();
    
    void setBreed(std::string breed);
    void setColor(std::string color);
    void setFoodType(std::string foodType);
    
    bool operator==(const Animal& animal) const override;
    
    void displayInfo() const override;
    void modify() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
};
