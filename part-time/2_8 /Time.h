#pragma once

class Time {
private:
    int* seconds;
    int* minutes;
    int* hours;
    
public:
    // Default constructor
    Time();

    // Constructor with parameters
    explicit Time(const int sec, const int min, const int hrs);

    // Copy constructor
    Time(const Time& time);

    // Destructor
    ~Time();
    
    // Seconds getter function
    int getSec() const;
    // Seconds setter function
    void setSec(const int value);
    
    // Minutes getter function
    int getMin() const;
    // Minutes setter function
    void setMin(const int value);
    
    // Hours getter function
    int getHrs() const;
    // Hours setter function
    void setHrs(const int value);
    
    // Queue print
    void print() const;
    
    // Increase sec/min/hrs by 1
    friend Time& operator++(Time& time);

    // Decrease sec/min/hrs by 1
    friend Time& operator--(Time& time);

    // Increase sec/min/hrs by user's value
    Time& operator++(int);

    // Decrease sec/min/hrs by user's value
    Time& operator--(int);
};
