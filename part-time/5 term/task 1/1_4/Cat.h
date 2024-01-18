#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Animal.h"

class Cat : public Animal {
private:
    std::string breed;
    std::string color;
    std::string ownerName;
    std::string nickname;
    
public:
    // Default constructor
    Cat();

    // Constructor with parameters
    Cat(const std::string& breed, const std::string& color, const std::string& ownerName, const std::string& nickname);

    // Copy constructor
    Cat(const Cat& cat);
    
    // Destructor
    ~Cat() override;
    
    std::string getBreed();
    std::string getColor();
    std::string getOwnerName();
    std::string getNickname();
    
    void setBreed(std::string breed);
    void setColor(std::string color);
    void setOwnerName(std::string ownerName);
    void setNickname(std::string nickname);
    
    bool operator==(const Animal& animal) const override;

    void displayInfo() const override;
    void modify() override;
    void saveToFile(std::ofstream& file) const override;
    void loadFromFile(std::ifstream& file) override;

};
