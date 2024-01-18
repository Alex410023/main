#include "AEROFLOT.h"

using namespace std;

AEROFLOT::AEROFLOT() 
    : numFlights(0)
    , destination("None")
    , flightNumber(0)
    , aircraftType("None")
{
    cout << "Default AEROFLOT constructor called." << endl;
}

AEROFLOT::AEROFLOT(const string& dest, int flight, const string& type)
    : destination(dest)
    , flightNumber(flight)
    , aircraftType(type)
{
    cout << "Constructor with parameters called." << endl;
}

AEROFLOT::AEROFLOT(const AEROFLOT& AEROFLOT) 
    : destination(AEROFLOT.destination)
    , flightNumber(AEROFLOT.flightNumber)
    , aircraftType(AEROFLOT.aircraftType)
{
    cout << "Copy constructor called." << endl;
}

AEROFLOT::~AEROFLOT() {
    cout << "Destructor called." << endl;
}

const string& AEROFLOT::getDestination() const {
    return destination;
}

int AEROFLOT::getFlightNumber() const {
    return flightNumber;
}

const string& AEROFLOT::getAircraftType() const {
    return aircraftType;
}

int AEROFLOT::getNumFlights() const {
    return numFlights;
}

void AEROFLOT::setDestination(const string& dest) {
    destination = dest;
}

void AEROFLOT::setFlightNumber(const int flight) {
    if (flight < 0) {
        throw invalid_argument("Flight number cannot be negative.");
    }
    flightNumber = flight;
}

void AEROFLOT::setAircraftType(const string& type) {
    aircraftType = type;
}

void AEROFLOT::setNumFlights(const int num) {
    try {
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(); // Discard invalid input
            throw invalid_argument("Invalid input. Please enter an integer.");
        }

        numFlights = num;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Function to display all flights
void AEROFLOT::displayAllFlights(const AEROFLOT* flights) {
    if (flights) {
        cout << "------ All Flights ------" << endl;
        for (int i = 0; i < numFlights; i++) {
            cout << flights[i] << endl;
        }
    } else {
        cout << "No flights available." << endl;
    }
}

void AEROFLOT::displayFlightsToDest(const AEROFLOT* flights, const string& dest) {
    if (!flights) {
        throw out_of_range("No flights in the array.");
    }
    
    bool found = false;
    for (int i = 0; i < numFlights; i++) {
        if (flights[i].getDestination() == dest) {
            cout << "Flight number: " << flights[i].flightNumber << "\tAircraft type: " << flights[i].aircraftType << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No flights to the specified destination." << endl;
    }
}


void AEROFLOT::editFlight(AEROFLOT* flights, const int index) {
    if (!flights) {
        throw out_of_range("No flights in the array.");
    }
    
    if (index < 0 || index >= numFlights) {
        throw out_of_range("Invalid index for editing a flight.");
    }
    cout << "Editing Flight at index " << index << endl;
    
    try {
        cout << "Choose what to change:\n";
        cout << "1. Destination\n";
        cout << "2. Flight Number\n";
        cout << "3. Aircraft Type\n";
        
        cin.clear();
        cin.ignore();
        int choice;
        cin >> choice;

        if (cin.fail()) {
            throw invalid_argument("Invalid input. Please enter an integer.");
        }

        switch (choice) {
            case 1:
                // Change Destination
                cout << "Enter new Destination: ";
                cin.ignore();
                getline(cin, flights[index].destination);
                break;
            case 2:
                // Change Flight Number
                int newFlightNumber;
                while (true) {
                    try {
                        cout << "Enter Flight Number: ";
                        cin >> newFlightNumber;

                        if (cin.fail()) { // If input is not an integer
                            throw invalid_argument("Flight number must be an integer.");
                        } else if (newFlightNumber < 0) {
                            throw invalid_argument("Flight number cannot be negative.");
                        }

                        break; // If valid input, exit the loop
                    } catch (const exception& e) {
                        cerr << e.what() << endl;
                        cin.clear(); // Clear the error flag
                        cin.ignore(); // Discard invalid input
                    }
                }
                flights[index].setFlightNumber(newFlightNumber);
                break;
            case 3:
                // Change Aircraft Type
                cout << "Enter new Aircraft Type: ";
                cin.ignore();
                getline(cin, flights[index].aircraftType);
                break;
            default:
                throw invalid_argument("Invalid choice. Please choose 1, 2, or 3.");
        }

        cout << "Flight at index " << index << " successfully edited.\n";
        
        flights->sort(flights, flights->getNumFlights() - 1);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        // Clear input buffer to avoid infinite loop in case of non-integer input
        cin.clear();
        cin.ignore();
    }

}

void AEROFLOT::sort(AEROFLOT* flights, const int count) {
    // Bubble sort
    bool wasSorted = false;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - i; j++) {
            if (flights[j].getFlightNumber() > flights[j + 1].getFlightNumber()) {
                // Swap newFlights[j] and newFlights[j + 1]
                AEROFLOT temp = flights[j];
                flights[j] = flights[j + 1];
                flights[j + 1] = temp;
                wasSorted = true;
            }
        }
    }
    cout << "\nThe flights were" << (wasSorted ? " " : " not ") << "sorted." << endl;
}


ostream& operator<<(ostream& out, const AEROFLOT& AEROFLOT) {
    out << "Destination: " << AEROFLOT.destination << "\tFlight Number: " << AEROFLOT.flightNumber << "\tAircraft Type: " << AEROFLOT.aircraftType << endl;
    return out;
}

istream& operator>>(istream& in, AEROFLOT& AEROFLOT) {
    cin.ignore();
    cout << "Enter Destination: ";
    getline(in, AEROFLOT.destination);
    
    int flightNumber;
    while (true) {
        try {
            cout << "Enter Flight Number: ";
            cin >> flightNumber;

            if (cin.fail()) { // If input is not an integer
                throw invalid_argument("Flight number must be an integer.");
            } else if (flightNumber < 0) {
                throw invalid_argument("Flight number cannot be negative.");
            }

            break; // If valid input, exit the loop
        } catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(); // Discard invalid input
        }
    }
    
    AEROFLOT.flightNumber = flightNumber;
    
    cin.ignore();
    cout << "Enter Aircraft Type: ";
    getline(in, AEROFLOT.aircraftType);
    
    return in;
}

// Overloaded + operator to add a flight to the array
AEROFLOT* operator+(AEROFLOT* flights, const AEROFLOT& newFlight) {
    try {
        int count = flights ? flights->getNumFlights() : 0;

        int position = 0;
        while (true) {
            try {
                cout << "Enter the position to add the new flight (0 to " << count << "): ";
                cin >> position;
                
                if (cin.fail()) { // If input is not an integer
                    throw invalid_argument("Flight number must be an integer.");
                } else if (position < 0) {
                    throw invalid_argument("Flight number cannot be negative.");
                } else if (position > count) {
                    throw invalid_argument("Flight number cannot be greater than the total number of flights.");
                }
                
                break; // If valid input, exit the loop
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(); // Discard invalid input
            }
        }
        
        AEROFLOT* newFlights = nullptr;
        try {
            newFlights = new AEROFLOT[count + 1];
        } catch (const bad_alloc& ba) {
            cerr << "Memory allocation error: " << ba.what() << endl;
            return flights;
        }
        
        
        int j = 0;
        for (int i = 0; i < count + 1; ++i) {
            if (i == position) {
                newFlights[i] = newFlight;
            } else {
                newFlights[i] = flights[j++];
            }
        }
        
        delete [] flights;
                
        newFlights->sort(newFlights, count);
                
        newFlights->setNumFlights(count + 1);
        
        return newFlights;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return flights;
}

// Overloaded - operator to delete a flight by index
AEROFLOT* operator-(AEROFLOT* flights, const AEROFLOT& plugFlight) {
    if (!flights) {
        throw out_of_range("No flights in the array.");
    }
    
    try {
        int indexToRemove;
        cout << "Input an index of the flight to be removed: ";
        cin >> indexToRemove;

        int numFlights = flights->getNumFlights();
        
        if (indexToRemove < 0 || indexToRemove >= numFlights) {
            throw out_of_range("Invalid index for removing a flight.");
        }

        
        // Create a new array with reduced size
        AEROFLOT* newFlights = nullptr;
        try {
            newFlights = new AEROFLOT[numFlights - 1];
        } catch (const bad_alloc& ba) {
            cerr << "Memory allocation error: " << ba.what() << endl;
            return flights;
        }
        
        
        // Copy existing flights to the new array excluding the specified index
        int newIndex = 0;
        for (int i = 0; i < numFlights; i++) {
            if (i != indexToRemove) {
                newFlights[newIndex] = flights[i];
                newIndex++;
            }
        }

        // Deallocate memory for the old flights array
        delete[] flights;

        // Update flights pointer to point to the new array
        flights = newFlights;

        // Update the number of flights
        flights->setNumFlights(numFlights - 1);

        cout << "Flight at index " << indexToRemove << " successfully removed.\n";
        
        return flights;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return flights;
}
