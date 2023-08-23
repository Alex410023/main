#pragma once

#include <iostream>

struct QueueNode {
    int data;
    QueueNode* next;
    
    QueueNode()
        : data(NULL)
        , next(nullptr)
    {
    }
    
    QueueNode(const int value)
        : data(value)
        , next(nullptr)
    {
    }
};
