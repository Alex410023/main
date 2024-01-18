#include "Fish.h"

// Default constructor
Fish::Fish()
    : breed("Unknown")
    , color("Unknown")
    , foodType("Unknown")
{
    std::cout << "Fish constructor was called" << std::endl;
}

// Constructor with parameters
Fish::Fish(const std::string& breed, const std::string& color, const std::string& foodType)
    : breed(breed)
    , color(color)
    , foodType(foodType)
{
    std::cout << "Fish constructor with parameters was called" << std::endl;
}

// Copy constructor
Fish::Fish(const Fish& fish)
    : Animal(fish)
    , breed(fish.breed)
    , color(fish.color)
    , foodType(fish.foodType)
{
    std::cout << "Fish copy constructor was called" << std::endl;
}

// Destructor
Fish::~Fish() {
    std::cout << "Fish destructor was called" << std::endl;
}

std::string Fish::getBreed() {
    return breed;
}

std::string Fish::getColor() {
    return color;
}

std::string Fish::getFoodType() {
    return foodType;
}

void Fish::setBreed(std::string breed) {
    this->breed = breed;
}

void Fish::setColor(std::string color) {
    this->color = color;
}

void Fish::setFoodType(std::string foodType) {
    this->foodType = foodType;
}

bool Fish::operator==(const Animal& animal) const {
    if (dynamic_cast<const Fish*>(&animal)) {
        const Fish& fish = dynamic_cast<const Fish&>(animal);
        return breed == fish.breed && color == fish.color && foodType == fish.foodType;
    }
    return false;
}

void Fish::displayInfo() const {
    std::cout << "Fish: Breed: " << breed
              << ", Color: " << color
              << ", Food: " << foodType
              << std::endl;
}

void Fish::modify() {
    std::cout << "Choose what you want to change (breed, color or foodtype): ";
    std::string option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, option);

    // Convert the option to lowercase
    for (auto& ch : option) {
        ch = tolower(ch);
    }

    if (option != "breed" && option != "color" && option != "foodtype") {
        std::cerr << "You have entered an incorrect trait." << std::endl;
    } else {
        std::cout << "Enter the new trait: ";
        std::string trait;
        std::getline(std::cin, trait);

        if (option == "breed") {
            setBreed(trait);
        } else if (option == "color") {
            setColor(trait);
        } else {
            setFoodType(trait);
        }
    }
}


void Fish::saveToFile(std::ofstream& file) const {
    file << "Fish " << breed << " " << color << " " << foodType << std::endl;
}

void Fish::loadFromFile(std::ifstream& file) {
    file >> breed >> color >> foodType;
}
