#include <iostream>

#include "Queue.h"


Queue::Queue()
    : head(nullptr) 
    , tail(nullptr)
{
}


Queue::~Queue() {
    while (!empty()) {
        pop();
    }
}


bool Queue::empty() {
    return head == nullptr;
}


QueueNode* Queue::back() {
    if (!empty()) {
        return tail;
    }
    else {
        std::cout << "The queue is empty.\n";
        return NULL;
    }
}

QueueNode* Queue::front() {
    if (!empty()) {
        return head;
    }
    else {
        std::cout << "The queue is empty.\n";
        return NULL;
    }
}


void Queue::push(const int value) {
    QueueNode* newNode = new QueueNode;
    newNode->data = value;

    // If there are no items in the queue, new node becomes both head and tail
    if (empty()) {
        tail = newNode;
        head = newNode;
    }

    else {
        newNode->prev = tail;
        tail = newNode;
    }
}


void Queue::pop() {
    if (empty()) {
        std::cout << "The queue is empty.\n";
        return;
    }
    QueueNode* cur = new QueueNode; // Item to be deleted
    cur = tail;
    QueueNode* prev = new QueueNode; // Item before 'cur'
    prev = NULL;

    while (cur != head) {
        prev = cur;
        cur = cur->prev;
    }
    if (prev == NULL) {
        head = tail = NULL;
    }
    else {
        prev->prev = NULL;
        head = prev;
    }
    delete cur;
}

