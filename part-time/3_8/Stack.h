#pragma once

#include "List.h"

// Stack class derived from List
class Stack : public List {
private:
    // Node struct for linked list
    struct Node {
        int data;
        Node* next;
        Node(const int value = NULL) : data(value), next(nullptr) {}
    };

    Node* head; // Pointer to the first element in the stack

public:
    // Default constructor
    Stack();

    // Constructor with parameter
    Stack(const int value);

    // Copy constructor
    Stack(const Stack& other); 

    // Destructor
    ~Stack(); 

    // Head setter and getter functions
    void setHead(Node& node);
    Node* getHead() const;

    // Insert an element into the stack
    void insert(const int value) override;

    // Extract an element from the stack
    void extract() override;

    // Print the stack
    void print() const override;

    // Save the stack to a file
    void saveToFile(const string& filename) const override;

    // Load the stack from a file
    void loadFromFile(const string& filename) override;
};