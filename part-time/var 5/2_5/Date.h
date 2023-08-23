#pragma once

class Date {
private:
    int* day;
    int* month;
    int* year;

public:
    // Default constructor
    Date();

    // Constructor with parameters
    explicit Date(const int _day, const int _month, const int _year);

    // Copy constructor
    Date(const Date& date);

    // Destructor
    ~Date();

    // Day getter function
    int getDay() const;
    // Day setter function
    void setDay(const int value);

    // Month getter function
    int getMonth() const;
    // Month setter function
    void setMonth(const int value);

    // Year getter function
    int getYear() const;
    // Year setter function
    void setYear(const int value);

    // Instance print
    void print() const;

    // Check if data fields are filled correctly;
    void dateCheck();

    // Increase day/month/year by 1
    Date& operator++();

    // Decrease day/month/year by 1
    Date& operator--();

    // Increase day/month/year by user's value
    friend Date& operator++(Date& date, int);

    // Decrease day/month/year by user's value
    Date& operator--(int);
};
