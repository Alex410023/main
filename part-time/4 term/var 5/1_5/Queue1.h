#pragma once

#include "Queue.h"

class Queue1 : public Queue {
public:
    int findMax();
    void printMax(const int num);
};

//class Queue1 : protected Queue {
//public:
//    void prot_clear() {
//        clear();
//    }
//    bool prot_empty() {
//        return empty();
//    }
//    QueueItem* prot_back() {
//        return back();
//    }
//    QueueItem* prot_front() {
//        return front();
//    }
//
//    void prot_push(const int value) {
//        push(value);
//    }
//    void prot_pop() {
//        pop();
//    }
//
//
//	int findMax();
//    void printMax(const int num);
//};
