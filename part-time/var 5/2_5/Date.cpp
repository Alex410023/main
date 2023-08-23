#include "Date.h"

#include <iostream>

// Default constructor
Date::Date()
    : day(new int(NULL))
    , month(new int(NULL))
    , year(new int(NULL))
{
}

// Constructor with parameters
Date::Date(const int _day, const int _month, const int _year)
    : day(new int(_day))
    , month(new int(_month))
    , year(new int(_year))
{
}

// Copy constructor
Date::Date(const Date& date)
    : day(new int(date.getDay()))
    , month(new int(date.getMonth()))
    , year(new int(date.getYear()))
{
}

// Destructor
Date::~Date() {
    delete day;
    delete month;
    delete year;
}

// Day getter function
int Date::getDay() const {
    return *day;
}
// Day setter function
void Date::setDay(const int value) {
    *day = value;
}

// Month getter function
int Date::getMonth() const {
    return *month;
}

// Month setter function
void Date::setMonth(const int value) {
    *month = value;
}

// Year getter function
int Date::getYear() const {
    return *year;
}

// Year setter function
void Date::setYear(const int value) {
    *year = value;
}


// Class print
void Date::print() const {
    std::cout << "Current date instance:\n";
    std::cout << "Days:\t" << getDay() << "\n";
    std::cout << "Months:\t" << getMonth() << "\n";
    std::cout << "Years:\t" << getYear() << "\n\n";
}

                    
void Date::dateCheck() {
    if (getDay() > 30 || getDay() < 0) {
        int extraDay = 0;
        extraDay = abs(getDay()) / 31;

        if (getDay() < 0) {
            extraDay *= -1;
        }

        setDay(getDay() % 31);
        setMonth(getMonth() + extraDay);
    }

    if (getMonth() > 12 || getMonth() < 0) {
        int extraMonth = 0;
        extraMonth = abs(getMonth()) / 12;

    if (getMonth() < 0) {
        extraMonth *= -1;
    }

    setMonth(getMonth() % 12);
    setYear(getYear() + extraMonth);
    }
}

// Increase day/month/year by 1
Date& Date::operator++() {
    std::cout << "Choose what to increase by 1\n";
    std::cout << "1 - Days, 2 - Months, 3 - Years\n";
    int choice;
    while (!(std::cin >> choice) || (std::cin.peek() != '\n') || (choice < 1) || (choice > 3)) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "You have entered an incorrect number\n";
    }
    std::cout << "\n";

    switch (choice) {
    case 1:
        setDay(getDay() + 1);
        break;
    case 2:
        setMonth(getMonth() + 1);
        break;
    case 3:
        setYear(getYear() + 1);
        break;
    }
    dateCheck();
    return *this;
}

// Decrease day/month/year by 1
Date& Date::operator--() {
    std::cout << "Choose what to decrease by 1\n";
    std::cout << "1 - Days, 2 - Months, 3 - Years\n";
    int choice;
    while (!(std::cin >> choice) || (std::cin.peek() != '\n') || (choice < 1) || (choice > 3)) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "You have entered an incorrect number\n";
    }
    std::cout << "\n";

    switch (choice) {
    case 1:
        setDay(getDay() - 1);
        break;
    case 2:
        setMonth(getMonth() - 1);
        break;
    case 3:
        setYear(getYear() - 1);
        break;
    }
    dateCheck();
    return *this;
}

// Increase day/month/year by user's value
Date& operator++(Date& date, int) {
    std::cout << "Choose what to increase\n";
    std::cout << "1 - Days, 2 - Months, 3 - Years\n";
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
        date.setDay(date.getDay() + input);
        break;
    case 2:
        date.setMonth(date.getMonth() + input);
        break;
    case 3:
        date.setYear(date.getYear() + input);
        break;
    }
    date.dateCheck();
    return date;
}

// Increase day/month/year by user's value
Date& Date::operator--(int) {
    std::cout << "Choose what to decrease\n";
    std::cout << "1 - Days, 2 - Months, 3 - Years\n";
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
        setDay(getDay() - input);
        break;
    case 2:
        setMonth(getMonth() - input);
        break;
    case 3:
        setYear(getYear() - input);
        break;
    }
    dateCheck();
    return *this;
}
