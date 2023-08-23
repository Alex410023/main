#pragma once

#include "Queue.h"

// PUBLIC INHERITANCE:

class Queue1 : public Queue {
public:
	double findArithmeticMean(); // Returns the arithmetic mean of the queue
	void taskOutput(const double num); // 
};


// PRIVATE/PROTECTED INHERITANCE:

//class Queue1 : protected /*private*/ Queue {
//public:
//	double findArithmeticMean(); // Finding arithmetic mean of the queue
//	void taskOutput(const double num); // Printing the result on the screen
//
//	void plug_push(const int value) {
//		push(value); 
//	}
//	void plug_pop() {
//		pop(); 
//	}
//	bool plug_empty() {
//		return empty(); 
//	}
//	QueueNode* plug_back() {
//		return back(); 
//	}
//	QueueNode* plug_front() {
//		return front(); 
//	}
//};