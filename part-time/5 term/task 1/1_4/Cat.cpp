#include "Cat.h"

// Default constructor
Cat::Cat()
    : breed("Unknown")
    , color("Unknown")
    , ownerName("Unknown")
    , nickname("Unknown")
{
    std::cout << "Cat constructor was called" << std::endl;
}

// Constructor with parameters
Cat::Cat(const std::string& breed, const std::string& color, const std::string& ownerName, const std::string& nickname)
    : breed(breed)
    , color(color)
    , ownerName(ownerName)
    , nickname(nickname)
{
    std::cout << "Cat constructor with parameters was called" << std::endl;
}

// Copy constructor
Cat::Cat(const Cat& cat)
    : Animal(cat)
    , breed(cat.breed)
    , color(cat.color)
    , ownerName(cat.ownerName)
    , nickname(cat.nickname)
{
    std::cout << "Cat copy constructor was called" << std::endl;
}

// Destructor
Cat::~Cat() {
    std::cout << "Cat destructor was called" << std::endl;
}

std::string Cat::getBreed() {
    return breed;
}

std::string Cat::getColor() {
    return color;
}

std::string Cat::getOwnerName() {
    return ownerName;
}

std::string Cat::getNickname() {
    return nickname;
}


void Cat::setBreed(std::string breed) {
    this->breed = breed;
}

void Cat::setColor(std::string color) {
    this->color = color;
}

void Cat::setOwnerName(std::string ownerName) {
    this->ownerName = ownerName;
}

void Cat::setNickname(std::string nickname) {
    this->nickname = nickname;
}

bool Cat::operator==(const Animal& animal) const {
    if (dynamic_cast<const Cat*>(&animal)) {
        const Cat& cat = dynamic_cast<const Cat&>(animal);
        return breed == cat.breed && color == cat.color && ownerName == cat.ownerName && nickname == cat.nickname;
    }
    return false;
}

void Cat::displayInfo() const {
    std::cout << "Cat: Breed: " << breed
              << ", Color: " << color
              << ", Owner: " << ownerName
              << ", Nickname: " << nickname << std::endl;
}

void Cat::modify() {
    std::string option;
    std::cout << "Choose what you want to change (breed, color, ownername, or nickname): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, option);

    // Convert option to lowercase
    for (auto& ch : option) {
        ch = tolower(ch);
    }

    if (option != "breed" && option != "color" && option != "ownername" && option != "nickname") {
        std::cerr << "You have entered an incorrect trait." << std::endl;
    } else {
        std::cout << "Enter the new trait: ";
        std::string trait;
        std::getline(std::cin, trait);

        if (option == "breed") {
            setBreed(trait);
        } else if (option == "color") {
            setColor(trait);
        } else if (option == "nickname") {
            setNickname(trait);
        } else {
            setOwnerName(trait);
        }
    }
}


void Cat::saveToFile(std::ofstream& file) const {
    file << "Cat " << breed << " " << color << " " << ownerName << " " << nickname << std::endl;
}

void Cat::loadFromFile(std::ifstream& file) {
    file >> breed >> color >> ownerName >> nickname;
}
