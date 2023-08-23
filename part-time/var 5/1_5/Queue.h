#pragma once

#include "Queue_item.h"

class Queue {
private:
    QueueItem* tail; // Last added element
    QueueItem* head; // First added element
public:
    // Constructor and destructor:
    Queue();
    ~Queue();
    
    // Not necessary functions, but they should be in a queue realisation:
    void clear(); // Deletes all the elements of the queue
    bool empty(); // Checks if there are any alements in the queue
    QueueItem* back(); // Returns the last element of the queue
    QueueItem* front(); // Returns the first element of the queue

    // Required functions:
    void push(const int value); // Adding an element
    void pop(); // Deleting an element
};

