#pragma once

#include "QueueItem.h"

class Queue {
private:
    QueueItem* head;
    QueueItem* tail;

public:
    // Default constructor
    Queue();

    // Constructor with a parameter
    explicit Queue(const int size);

    // Copy constructor
    Queue(const Queue& object);

    // Destructor
    ~Queue();

    // Head getter function
    QueueItem* front() const;
    // Head setter function
    void front(QueueItem& object);

    // Tail getter function
    QueueItem* back() const;
    // Tail setter function
    void back(QueueItem& object);

    // Add to the end of the queue
    void push(int value);

    // Delete the first added element
    void pop();

    // Check if the queue is empty
    bool empty() const;

    // Print the queue
    void print() const;

    // Get queue's size
    int size() const;


    // Add element to the queue
    Queue& operator+(const int addValue);


    // Delete user's element from the queue
    Queue operator-(const int value);


    // Multiply a queue by a number
    Queue operator*(const int number);

    // Check if queues are equal
    bool operator==(Queue& right) const;

    // Check if queues are unequal
    bool operator!=(Queue& right) const;


    friend std::ostream& operator<<(std::ostream& os, const Queue& queue);
        
    friend std::istream& operator>>(std::istream& is, Queue& queue);
};
