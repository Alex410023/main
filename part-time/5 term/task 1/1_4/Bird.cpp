#include "Bird.h"

// Default constructor
Bird::Bird()
    : breed("Unknown")
    , color("Unknown")
    , eats("Unknown")
    , habitat("Unknown")
{
    std::cout << "Bird constructor was called" << std::endl;
}

// Constructor with parameters
Bird::Bird(const std::string& breed, const std::string& color, const std::string& eats, const std::string& habitat)
    : breed(breed)
    , color(color)
    , eats(eats)
    , habitat(habitat)
{
    std::cout << "Bird constructor with parameters was called" << std::endl;
}

// Copy constructor
Bird::Bird(const Bird& bird)
    : Animal(bird)
    , breed(bird.breed)
    , color(bird.color)
    , eats(bird.eats)
    , habitat(bird.habitat)
{
    std::cout << "Bird copy constructor was called" << std::endl;
}

// Destructor
Bird::~Bird() {
    std::cout << "Bird destructor was called" << std::endl;
}

std::string Bird::getBreed() {
    return breed;
}

std::string Bird::getColor() {
    return color;
}

std::string Bird::getEats() {
    return eats;
}

std::string Bird::getHabitat() {
    return habitat;
}


void Bird::setBreed(std::string breed) {
    this->breed = breed;
}

void Bird::setColor(std::string color) {
    this->color = color;
}

void Bird::setEats(std::string eats) {
    this->eats = eats;
}

void Bird::setHabitat(std::string habitat) {
    this->habitat = habitat;
}

bool Bird::operator==(const Animal& animal) const {
    if (dynamic_cast<const Bird*>(&animal)) {
        const Bird& bird = dynamic_cast<const Bird&>(animal);
        return breed == bird.breed && color == bird.color && eats == bird.eats && habitat == bird.habitat;
    }
    return false;
}


void Bird::displayInfo() const {
    std::cout << "Bird: Breed: " << breed
              << ", Color: " << color
              << ", Eats: " << eats
              << ", Habitat: " << habitat << std::endl;
}

void Bird::modify() {
    std::cout << "Choose what you want to change (breed, color, eats or habitat): ";
    std::string option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, option);
    
    for (auto& ch : option) {
        ch = tolower(ch);
    }
    
    if (option != "breed" && option != "color" && option != "eats" && option != "habitat") {
        std::cerr << "You have entered incorrect trait." << std::endl;
    } else {
        std::cout << "Enter the trait: ";
        std::string trait;
        std::getline(std::cin, trait);
        
        if (option == "breed") {
            setBreed(trait);
        } else if (option == "color") {
            setColor(trait);
        } else if (option == "eats") {
            setEats(trait);
        } else {
            setHabitat(trait);
        }
    }
}

void Bird::saveToFile(std::ofstream& file) const {
    file << "Bird " << breed << " " << color << " " << eats << " " << habitat << std::endl;
}

void Bird::loadFromFile(std::ifstream& file) {
    file >> breed >> color >> eats >> habitat;
}
