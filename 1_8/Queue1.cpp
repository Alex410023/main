#include <iostream>

#include "Queue1.h"

// Finding the arithmetic mean of the queue
double Queue1::findArithmeticMean() {
    // Before the loop, we add to the sum tail's value and increase 
    // the number of processed items from 0 to 1
    QueueNode* curNode = back();
    int curNum = 1;

    // While current node is not head, increase the sum and 
    // the number of processed items
    double sum = front()->data;
    while (curNode != front()) {
        curNum++;
        sum += curNode->data;
        curNode = curNode->prev;
    }
    return sum / curNum;
}

// Prining the last item which is less than the arithmetic mean
void Queue1::taskOutput(const double num) {
    // Current last item less than the arithmetic mean
    QueueNode* curLast = back();

    // Current item of the queue
    QueueNode* curNode = back();

    bool wasFound = false;

    // Comparison between all the items before head and the arithmetic mean
    while (curNode != front()) {
        if (curNode->data < num) {
            curLast = curNode;
            wasFound = true;
        }
        curNode = curNode->prev;
    }

    // Comparison with the head->data
    if (curNode->data < num) {
        curLast = curNode;
        wasFound = true;
    }

    if (wasFound) {
        std::cout << "The last item which is less than the arithmetic mean: ";
        std::cout << curLast->data << "\n";
    }
    else {
        std::cout << "The last item which is less than the arithmetic";
        std::cout << "mean was not found.\n";
    }
}