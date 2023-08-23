#pragma once

#include "Queue1.h"
#include "Queue_item.h"

class Menu {
public:
    void mainMenu(); // Menu to work with queues
    
    /*
         The following arguments of functions are addresses, because otherwise,
         when a function finishes its work, destructor is called, which
         leads to data loss
     */
    void task(Queue1& queue1); // Task execution
    
    void print (Queue1& queue); // Printing the queue
    void copy(Queue1& source, Queue1& target); // Copying the first queue
                                               // into the second one
    void merge(Queue1& queue, Queue1& queue_1); // Merging two queues
};
