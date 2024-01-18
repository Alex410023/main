#pragma once

#include <iostream>
#include <string>

class AEROFLOT {
public:
    AEROFLOT(); // Default constructor
    AEROFLOT(const std::string& destination, int flightNumber, const std::string& aircraftType); // Constructor with parameters
    AEROFLOT(const AEROFLOT& AEROFLOT); // Copy constructor
    ~AEROFLOT(); // Destructor

    // Getter and setter methods
    const std::string& getDestination() const;
    int getFlightNumber() const;
    const std::string& getAircraftType() const;
    int getNumFlights() const;
    
    void setDestination(const std::string& destination);
    void setFlightNumber(const int flightNumber);
    void setAircraftType(const std::string& aircraftType);
    void setNumFlights(const int num);
    
    void displayAllFlights(const AEROFLOT* flights);
    void displayFlightsToDest(const AEROFLOT* flights, const std::string& dest);
    void editFlight(AEROFLOT* flights, const int index);
    void addFlightToPosition(int position, const AEROFLOT& flight);
    
    void sort(AEROFLOT* flights, const int count);

    // Operator overloads
    friend std::ostream& operator<<(std::ostream& out, const AEROFLOT& AEROFLOT);
    friend std::istream& operator>>(std::istream& in, AEROFLOT& AEROFLOT);
    
    // Overloaded + operator to add a flight to the array
    friend AEROFLOT* operator+(AEROFLOT* flights, const AEROFLOT& newFlight);
    // Overloaded - operator to delete a flight by index
    friend AEROFLOT* operator-(AEROFLOT* flights, const AEROFLOT& plugFlight);
    
private:
    int numFlights;
    std::string destination;
    int flightNumber;
    std::string aircraftType;
};
