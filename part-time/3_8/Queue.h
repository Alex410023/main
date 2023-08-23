#pragma once

#include "List.h"

// Queue class derived from List
class Queue : public List {
private:
    // Node struct for linked list
    struct Node {
        int data;
        Node* next;
        Node(const int value = NULL) : data(value), next(nullptr) {}
    };

    Node* head; // Pointer to the first element in the queue
    Node* tail; // Pointer to the last element in the queue

public:
    // Default constructor
    Queue(); 

    // Constructor with parameter
    Queue(const int value); 

    // Copy constructor
    Queue(const Queue& other); 

    // Destructor
    ~Queue(); 

    // Head setter and getter functions
    void setHead(Node& node);
    Node* getHead() const;

    // Tail setter and getter functions
    void setTail(Node& node);
    Node* getTail() const;

    // Insert an element into the queue
    void insert(const int value) override; 

    // Extract an element from the queue
    void extract() override;

    // Print the queue
    void print() const override;

    // Save the queue to a file
    void saveToFile(const string& filename) const override;

    // Load the queue from a file
    void loadFromFile(const string& filename) override;
};