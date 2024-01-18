#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Animal.h"

class Bird : public Animal {
private:
    std::string breed;
    std::string color;
    std::string eats;
    std::string habitat;
    
public:
    // Default constructor
    Bird();

    // Constructor with parameters
    Bird(const std::string& breed, const std::string& color, const std::string& eats, const std::string& habitat);

    // Copy constructor
    Bird(const Bird& bird);
    
    // Destructor
    ~Bird() override;
    
    std::string getBreed();
    std::string getColor();
    std::string getEats();
    std::string getHabitat();
    
    void setBreed(std::string breed);
    void setColor(std::string color);
    void setEats(std::string eats);
    void setHabitat(std::string habitat);
    
    bool operator==(const Animal& animal) const override;

    void displayInfo() const override;
    void modify() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;
};
