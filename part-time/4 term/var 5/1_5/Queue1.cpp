#include "Queue1.h"
#include "Queue_item.h"

#include <iostream>

// Task execution
int Queue1::findMax() {
    QueueItem* temp = back();
    int max = back()->data;

    /*
        It does not work with 'while (temp != NUll)' loop
    */
    while (temp != front()) {
        if (temp->data > max) {
            max = temp->data;
        }
        temp = temp->prev;
    }
    if (front()->data > max) {
        max = front()->data;
    }
    return max;
}

void Queue1::printMax(const int num) {
    std::cout << "The largest element in the queue is: " << num << std::endl;
}
