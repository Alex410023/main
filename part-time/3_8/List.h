#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


// Base class List with virtual insert and extract functions
class List {
public:
    // Default constructor
    List() {}

    // Constructor with parameter
    List(const int data) {} 

    // Copy constructor
    List(const List& other) {} 

    // Virtual destructor
    virtual ~List() {} 

    // Virtual insert and extract functions
    virtual void insert(const int value) = 0;
    virtual void extract() = 0;

    // Print the list
    virtual void print() const = 0;

    // Save the list to a file
    virtual void saveToFile(const string& filename) const = 0;

    // Load the list from a file
    virtual void loadFromFile(const string& filename) = 0;
};