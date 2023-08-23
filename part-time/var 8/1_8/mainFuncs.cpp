#include <iostream>

#include "mainFuncs.h"
#include "Queue1.h"

using namespace std;


// PUBLIC INHERITANCE:

void task(Queue1& queue1) {
    if (queue1.empty()) {
        cout << "The queue is empty.\n";
    }
    else {
        queue1.taskOutput(queue1.findArithmeticMean());
    }
}

// Printing the queue
void print(Queue1& queue) {
    if (queue.empty()) {
        cout << "The queue is empty.\n";
    }
    else {
        QueueNode* cur = new QueueNode; // Temporary item to be printed
        cur = queue.back();
        cout << "Current queue: ";
        while (cur != queue.front()) {
            cout << cur->data << " -> ";
            cur = cur->prev;
        }
        cout << queue.front()->data << "\n";
    }
}


// Creating a copy of the queue
void copy(Queue1& source, Queue1& target) {
    if (source.empty()) {
        cout << "The source queue is empty.\n";
    }
    else {
        // If there are any items in the copied queue, it has to be cleared
        while (!target.empty()) {
            target.pop();
        }

        QueueNode* cur; // Current processed item

        // The last item we've pushed to the target queue
        QueueNode* tempHead;

        // At first, the last item is the last possible source queue item 
        // (which is the head of the queue)
        tempHead = source.front();

        // While not tail of 'source', pushing item's data to the target
        while (tempHead != source.back()) {
            cur = source.back();
            while (cur->prev != tempHead) {
                cur = cur->prev;
            }
            target.push(tempHead->data);
            tempHead = cur;
        }
        target.push(tempHead->data); // Pushing the remaining item ('source.tail')

        cout << "The queue has been copied successfully.\n";
    }
}

// Merging two queues
void merge(Queue1& queue, Queue1& queue_1) {
    // Unlike the main queue, queue_1 cannot be empty
    if (queue_1.empty()) {
        cout << "The second queue is empty.\n";
    }
    else {
        QueueNode* cur; // Current processed item
        QueueNode* tempHead; // The last item we've pushed to the main queue

        // At first, the last item is the last possible main queue item 
        // (which is the head of the queue)
        tempHead = queue_1.front();

        // Starting from the head of queue1, push every item's data of queue1 to 
        // the main queue
        while (tempHead != queue_1.back()) {
            cur = queue_1.back();
            while (cur->prev != tempHead) {
                cur = cur->prev;
            }
            queue.push(tempHead->data);
            tempHead = cur;
        }
        queue.push(tempHead->data); // Pushing the remaining item ('queue1.tail')

        cout << "Two queues have been merged successfully.\n";
    }
}



// PRIVATE/PROTECTED INHERITANCE:

//// Task execution
//void task(Queue1& queue1) {
//    if (queue1.plug_empty()) {
//        cout << "The queue is empty.\n";
//    }
//    else {
//        queue1.taskOutput(queue1.findArithmeticMean());
//    }
//}
//
//// Printing the queue
//void print(Queue1& queue) {
//    if (queue.plug_empty()) {
//        cout << "The queue is empty.\n";
//    }
//    else {
//        QueueNode* cur = new QueueNode; // Temporary item to be printed
//        cur = queue.plug_back();
//        cout << "Current queue: ";
//        while (cur != queue.plug_front()) {
//            cout << cur->data << " -> ";
//            cur = cur->prev;
//        }
//        cout << queue.plug_front()->data << "\n";
//    }
//}
//
//
//// Creating a copy of the queue
//void copy(Queue1& source, Queue1& target) {
//    if (source.plug_empty()) {
//        cout << "The source queue is empty.\n";
//    }
//    else {
//        // If there are any items in the copied queue, it has to be cleared
//        while (!target.plug_empty()) {
//            target.plug_pop();
//        }
//
//        QueueNode* cur; // Current processed item
//
//        // The last item we've pushed to the target queue
//        QueueNode* tempHead;
//
//        // At first, the last item is the last possible source queue item 
//        // (which is the head of the queue)
//        tempHead = source.plug_front();
//
//        // While not tail of 'source', pushing item's data to the target
//        while (tempHead != source.plug_back()) {
//            cur = source.plug_back();
//            while (cur->prev != tempHead) {
//                cur = cur->prev;
//            }
//            target.plug_push(tempHead->data);
//            tempHead = cur;
//        }
//        target.plug_push(tempHead->data); // Pushing the remaining item ('source.tail')
//
//        cout << "The queue has been copied successfully.\n";
//    }
//}
//
//// Merging two queues
//void merge(Queue1& queue, Queue1& queue_1) {
//    // Unlike the main queue, queue_1 cannot be empty
//    if (queue_1.plug_empty()) {
//        cout << "The second queue is empty.\n";
//    }
//    else {
//        QueueNode* cur; // Current processed item
//        QueueNode* tempHead; // The last item we've pushed to the main queue
//
//        // At first, the last item is the last possible main queue item 
//        // (which is the head of the queue)
//        tempHead = queue_1.plug_front();
//
//        // Starting from the head of queue1, push every item's data of queue1 to 
//        // the main queue
//        while (tempHead != queue_1.plug_back()) {
//            cur = queue_1.plug_back();
//            while (cur->prev != tempHead) {
//                cur = cur->prev;
//            }
//            queue.plug_push(tempHead->data);
//            tempHead = cur;
//        }
//        queue.plug_push(tempHead->data); // Pushing the remaining item ('queue1.tail')
//
//        cout << "Two queues have been merged successfully.\n";
//    }
//}