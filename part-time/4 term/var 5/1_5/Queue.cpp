#include "Queue.h"
#include "Queue_item.h"

#include <iostream>


Queue::Queue()
    : head(nullptr) // probably, not needed
    , tail(nullptr)
{
}

Queue::~Queue() {
    clear();
}


void Queue::clear() {
    while (!empty()) {
        pop();
    }
}


bool Queue::empty() {
    return head == nullptr;
}


QueueItem* Queue::back(){
    if (!empty()) {
        return tail;
    } else {
        std::cout << "The queue is empty." << std::endl;
        return NULL;
    }
}

QueueItem* Queue::front(){
    if (!empty()) {
        return head;
    } else {
        std::cout << "The queue is empty." << std::endl;
        return NULL;
    }
}


// Adding an element to the end
void Queue::push(const int value) {
    QueueItem* newData = new QueueItem;
    newData->data = value;
    if (empty()) {
        tail = newData;
        head = newData;
    } else {
        newData->prev = tail;
        tail = newData;
    }
}

// Deleting the first element
void Queue::pop() {
    if (empty()) {
        std::cout << "The queue is empty." << std::endl;
        return;
    }
    QueueItem* curr = new QueueItem; 
    curr = tail;
    QueueItem* prev = new QueueItem;
    prev = NULL;
    while (curr != head) {
        prev = curr;
        curr = curr->prev;
    }
    if (prev == NULL) {
        head = tail = NULL;
    } else {
        prev->prev = NULL;
        head = prev;
    }
    delete curr;
}

