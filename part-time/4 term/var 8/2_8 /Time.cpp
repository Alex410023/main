#include "Time.h"

#include <iostream>

// Default constructor
Time::Time()
    : seconds(new int(NULL))
    , minutes(new int(NULL))
    , hours(new int(NULL))
{
}

// Constructor with parameters
Time::Time(const int sec, const int min, const int hrs)
    : seconds(new int(sec))
    , minutes(new int(min))
    , hours(new int(hrs))
{
}

// Copy constructor
Time::Time(const Time& time)
    : seconds(new int(time.getSec()))
    , minutes(new int(time.getMin()))
    , hours(new int(time.getHrs()))
{
}

// Destructor
Time::~Time() {
    delete seconds;
    delete minutes;
    delete hours;
}

// Seconds getter function
int Time::getSec() const{
    return *seconds;
}
// Seconds setter function
void Time::setSec(const int value) {
    *seconds = value;
}

// Minutes getter function
int Time::getMin() const {
    return *minutes;
}

// Minutes setter function
void Time::setMin(const int value) {
    *minutes = value;
}

// Hours getter function
int Time::getHrs() const {
    return *hours;
}

// Hours setter function
void Time::setHrs(const int value) {
    *hours = value;
}


// Queue print
void Time::print() const {
    std::cout << "Current time instance:\n";
    std::cout << "Seconds:\t" << getSec() << "\n";
    std::cout << "Minutes:\t" << getMin() << "\n";
    std::cout << "Hours:\t\t" << getHrs() << "\n\n";
}

// Increase sec/min/hrs by 1
Time& operator++(Time& time) {
    std::cout << "Choose what to increase by 1\n";
    std::cout << "1 - Seconds, 2 - Minutes, 3 - Hours\n";
    int choice;
    while (!(std::cin >> choice) || (std::cin.peek() != '\n') || (choice < 1) || (choice > 3)) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "You have entered an incorrect number\n";
    }
    std::cout << "\n";

    switch (choice) {
        case 1:
            time.setSec(time.getSec() + 1);
            break;
        case 2:
            time.setMin(time.getMin() + 1);
            break;
        case 3:
            time.setHrs(time.getHrs() + 1);
            break;
    }
    return time;
}

// Decrease sec/min/hrs by 1
Time& operator--(Time& time) {
    std::cout << "Choose what to decrease by 1\n";
    std::cout << "1 - Seconds, 2 - Minutes, 3 - Hours\n";
    int choice;
    while (!(std::cin >> choice) || (std::cin.peek() != '\n') || (choice < 1) || (choice > 3)) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "You have entered an incorrect number\n";
    }
    std::cout << "\n";

    switch (choice) {
        case 1:
            time.setSec(time.getSec() - 1);
            break;
        case 2:
            time.setMin(time.getMin() - 1);
            break;
        case 3:
            time.setHrs(time.getHrs() - 1);
            break;
    }
    return time;
}

// Increase sec/min/hrs by user's value
Time& Time::operator++(int) {
    std::cout << "Choose what to increase\n";
    std::cout << "1 - Seconds, 2 - Minutes, 3 - Hours\n";
    int choice;
    while (!(std::cin >> choice) || (std::cin.peek() != '\n') || (choice < 1) || (choice > 3)) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "You have entered an incorrect number\n";
    }
    
    std::cout << "Input value\n";
    int input;
    while (!(std::cin >> input) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "You have entered an incorrect number\n";
    }
    
    switch (choice) {
        case 1:
            setSec(getSec() + input);
            break;
        case 2:
            setMin(getMin() + input);
            break;
        case 3:
            setHrs(getHrs() + input);
            break;
    }
    return *this;
}

// Increase sec/min/hrs by user's value
Time& Time::operator--(int) {
    std::cout << "Choose what to decrease\n";
    std::cout << "1 - Seconds, 2 - Minutes, 3 - Hours\n";
    int choice;
    while (!(std::cin >> choice) || (std::cin.peek() != '\n') || (choice < 1) || (choice > 3)) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "You have entered an incorrect number\n";
    }
    
    std::cout << "Input value\n";
    int input;
    while (!(std::cin >> input) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "You have entered an incorrect number\n";
    }
    
    switch (choice) {
        case 1:
            setSec(getSec() - input);
            break;
        case 2:
            setMin(getMin() - input);
            break;
        case 3:
            setHrs(getHrs() - input);
            break;
    }
    return *this;
}
