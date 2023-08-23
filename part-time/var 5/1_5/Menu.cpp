#include "Menu.h"
#include "Queue1.h"

#include <iostream>

using namespace std;


// PUBLIC:


// Task execution
void Menu::task(Queue1& queue1) {
    if (queue1.empty()) {
        cout << "The queue is empty." << endl;
    } else {
        int max = queue1.findMax();
        queue1.printMax(max);
    }
}

// Printing the queue
void Menu::print(Queue1& queue) {
    if (queue.empty()) {
        cout << "The queue is empty." << endl;
    } else {
        QueueItem* temp = new QueueItem;
        temp = queue.back();
        cout << "Current queue: ";
        while (temp != queue.front()) {
            cout << temp->data << " -> ";
            temp = temp->prev;
        }
        cout << queue.front()->data << endl;
    }
}


// Creating a copy of the queue
void Menu::copy(Queue1& source, Queue1& target) {
    if (source.empty()) {
        cout << "The source queue is empty." << endl;
    } else {
        if (!target.empty()) {
            target.clear();
        }

        QueueItem* temp = new QueueItem;
        QueueItem* tempHead = new QueueItem; // This element will be counted as 
                                             // the last element we've processed

        tempHead = source.front(); // At first, the last element is the last 
                                   // possible element, which is the head of 
                                   // the queue

        while (tempHead != source.back()) {
            temp = source.back();
            while (temp->prev != tempHead) {
                temp = temp->prev;
            }
            target.push(tempHead->data);
            tempHead = temp;
        }
        target.push(tempHead->data);
        
        cout << "The queue has been copied successfully." << endl;
    }
}

// Merging two queues
void Menu::merge(Queue1& queue, Queue1& queue_1) {
    if (queue.empty() || queue_1.empty()) {
        if (queue.empty()) {
            cout << "The first queue is empty." << endl;
        }
        if (queue_1.empty()) {
            cout << "The second queue is empty." << endl;
        }
    } else {
        QueueItem* temp = new QueueItem;
        QueueItem* tempHead = new QueueItem;
        tempHead = queue_1.front();
        
        while (tempHead != queue_1.back()) {
            temp = queue_1.back();
            while (temp->prev != tempHead) {
                temp = temp->prev;
            }
            queue.push(tempHead->data);
            tempHead = temp;
        }
        queue.push(tempHead->data);

        cout << "The queues have been merged successfully." << endl;
    }
}



void Menu::mainMenu() {
    Queue1 queue1;
    Queue1 queueCopy;
    bool runAgain = true;

    do {
        cout << "Select an action: " << endl;
        cout << "1 - Adding new element to the queue" << endl;
        cout << "2 - Deleting an element from the queue" << endl;
        cout << "3 - Queue output" << endl;
        cout << "4 - Task execution" << endl;
        cout << "5 - Creating a copy of the queue" << endl;
        cout << "6 - Merging two queues" << endl;
        cout << "7 - Exit" << endl;
        cout << endl;
        int option = 0;
                
        // Number input excludes incorrect symbols
        while (!(cin >> option) || (cin.peek() != '\n') || (option < 1) || (option > 7))
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }
        
        switch (option) {
            case 1:
                cout << "Input a number: ";
                int num;
                while (!(cin >> num) || (cin.peek() != '\n'))
                {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "You have entered an incorrect number\n";
                }
                queue1.push(num);
                break;
            case 2:
                queue1.pop();
                break;
            case 3:
                print(queue1);
                break;
            case 4:
                task(queue1);
                break;
            case 5:
                copy(queue1, queueCopy);
                break;
            case 6:
                merge(queue1, queueCopy);
                break;
            case 7:
                runAgain = false;
                break;
        }
        cout << endl;
    } while (runAgain == true);
    cout << "Thank you for using the program." << endl;
}




// PRIVATE/PROTECTED:



//// Task execution
//void Menu::task(Queue1& queue1) {
//    if (queue1.prot_empty()) {
//        cout << "The queue is empty." << endl;
//    }
//    else {
//        int max = queue1.findMax();
//        queue1.printMax(max);
//    }
//}
//
//// Printing the queue
//void Menu::print(Queue1& queue) {
//    if (queue.prot_empty()) {
//        cout << "The queue is empty." << endl;
//    }
//    else {
//        QueueItem* temp = new QueueItem;
//        temp = queue.prot_back();
//        cout << "Current queue: ";
//        while (temp != queue.prot_front()) {
//            cout << temp->data << " -> ";
//            temp = temp->prev;
//        }
//        cout << queue.prot_front()->data << endl;
//    }
//}
//
//
///*
//    probably, it has to be 'const Queue queue', should fix that
//*/
//
//
//// Creating a copy of the queue
//void Menu::copy(Queue1& source, Queue1& target) {
//    if (source.prot_empty()) {
//        cout << "The source queue is empty." << endl;
//    }
//    else {
//        if (!target.prot_empty()) {
//            target.prot_clear();
//        }
//
//        QueueItem* temp = new QueueItem;
//        QueueItem* tempHead = new QueueItem;
//        tempHead = source.prot_front();
//
//
//        while (tempHead != source.prot_back()) {
//            temp = source.prot_back();
//            while (temp->prev != tempHead) {
//                temp = temp->prev;
//            }
//            target.prot_push(tempHead->data);
//            tempHead = temp;
//        }
//        target.prot_push(tempHead->data);
//
//        cout << "The queue has been copied successfully." << endl;
//    }
//}
//
//// Merging two queues
//void Menu::merge(Queue1& queue, Queue1& queue_1) {
//    if (queue.prot_empty() || queue_1.prot_empty()) {
//        if (queue.prot_empty()) {
//            cout << "The first queue is empty." << endl;
//        }
//        if (queue_1.prot_empty()) {
//            cout << "The second queue is empty." << endl;
//        }
//    }
//    else {
//        QueueItem* temp = new QueueItem;
//        QueueItem* tempHead = new QueueItem;
//        tempHead = queue_1.prot_front();
//
//        while (tempHead != queue_1.prot_back()) {
//            temp = queue_1.prot_back();
//            while (temp->prev != tempHead) {
//                temp = temp->prev;
//            }
//            queue.prot_push(tempHead->data);
//            tempHead = temp;
//        }
//        queue.prot_push(tempHead->data);
//
//        cout << "The queues have been merged successfully." << endl;
//    }
//}
//
//
//
//void Menu::mainMenu() {
//    Queue1 queue1;
//    Queue1 queueCopy;
//    bool runAgain = true;
//
//    do {
//        cout << "Select an action: " << endl;
//        cout << "1 - Adding new element to the queue" << endl;
//        cout << "2 - Deleting an element from the queue" << endl;
//        cout << "3 - Queue output" << endl;
//        cout << "4 - Task execution" << endl;
//        cout << "5 - Creating a copy of the queue" << endl;
//        cout << "6 - Merging two queues" << endl;
//        cout << "7 - Exit" << endl;
//        cout << endl;
//        int option = 0;
//
//        // Number input excludes incorrect symbols
//        while (!(cin >> option) || (cin.peek() != '\n') || (option < 1) || (option > 7))
//        {
//            cin.clear();
//            while (cin.get() != '\n');
//            cout << "You have entered an incorrect number\n";
//        }
//
//        switch (option) {
//        case 1:
//            cout << "Input a number: ";
//            int num;
//            while (!(cin >> num) || (cin.peek() != '\n'))
//            {
//                cin.clear();
//                while (cin.get() != '\n');
//                cout << "You have entered an incorrect number\n";
//            }
//            queue1.prot_push(num);
//            break;
//        case 2:
//            queue1.prot_pop();
//            break;
//        case 3:
//            print(queue1);
//            break;
//        case 4:
//            task(queue1);
//            break;
//        case 5:
//            copy(queue1, queueCopy);
//            break;
//        case 6:
//            merge(queue1, queueCopy);
//            break;
//        case 7:
//            runAgain = false;
//            break;
//        }
//        cout << endl;
//    } while (runAgain == true);
//    cout << "Thank you for using the program." << endl;
//}
//

