#pragma once

#include "QueueNode.h"

class Queue {
public:
	Queue(); // Constructor
	~Queue(); // Destructor

	void push(const int value); // Adding item to the end of the queue
	void pop(); // Deleting the first added item 

	bool empty(); // Checking if there are any items in the queue
	QueueNode* back(); // Returning queue's tail
	QueueNode* front(); // Returning queue's head

private:
	QueueNode* head; // The first added item
	QueueNode* tail; // The last added item
};