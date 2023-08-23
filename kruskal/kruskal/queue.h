#pragma once

#include <iostream>

using namespace std;

class Queue {
public:
    Queue();
    ~Queue();
    
    int size();
    void push(const int& value);
    void pop();
    bool empty();
    int front();
    void print();
private:
    int count;
    int* data;
};
