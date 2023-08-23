#pragma once

#include "QueueNode.h"

class Queue {
private:
    QueueNode* head;
    QueueNode* tail;
    
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
    QueueNode* front() const;
    // Head setter function
    void front(QueueNode& object);

    // Tail getter function
    QueueNode* back() const;
    // Tail setter function
    void back(QueueNode& object);

    // Add to the end of the queue
    void push(int value);

    // Delete the first added element
    void pop();

    // Check if the queue is empty
    bool empty() const;

    // Print the queue
    void print() const;

    
    // Add element to the queue
    friend void operator+=(Queue& queue, const int addValue);

    // Add two queues
    Queue operator+(const Queue& queue) const;

    // Delete user's element from the queue
    Queue& operator=(const int value);

    // Subtract two queues
    friend Queue operator-(const Queue& queue_1, const Queue& queue_2);

    // Multiply two queues
    Queue operator*(const Queue& queue) const;

    // Divide a queue by a number
    Queue operator/(const int number) const;
};
