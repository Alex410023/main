#pragma once

#include <iostream>

struct QueueItem {
    int data;
    QueueItem* next;


    QueueItem()
        : data(NULL)
        , next(nullptr)
    {
    }

    QueueItem(const int number)
        : data(number)
        , next(nullptr)
    {
    }
};