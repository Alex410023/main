#include <iostream>

#include "Queue.h"

// Default constructor
Queue::Queue()
    : head(nullptr)
    , tail(nullptr)
{
}

// Constructor with a parameter
Queue::Queue(const int size)
    : head(nullptr)
    , tail(nullptr)
{
    for (int i = 0; i < size; i++) {
        push(i);
    }
}

// Copy constructor
Queue::Queue(const Queue& object) {
    if (!object.empty()) {
        QueueNode* curr = object.back();
        while (curr != front()) {
            push(curr->data);
            curr = curr->next;
        }
        push(curr->data);
    }
    else {
        head = nullptr;
        tail = nullptr;
    }
}

// Destructor
Queue::~Queue() {
    while (!empty()) {
        pop();
    }
}

// Head getter function
QueueNode* Queue::front() const {
    return head;
}

// Head setter function
void Queue::front(QueueNode& object) {
    head = &object;
}

// Tail getter function
QueueNode* Queue::back() const {
    return tail;
}

// Tail setter function
void Queue::back(QueueNode& object) {
    tail = &object;
}

// Add to the end of the queue
void Queue::push(const int value) {
    QueueNode* newData = new QueueNode(value);
        if (empty()) {
            front(*newData);
            back(*newData);
        }
        else {
            newData->next = back();
            back(*newData);
        }
}

// Delete the first added element
void Queue::pop() {
    QueueNode* curr = new QueueNode;
    curr = back();
    QueueNode* prev = nullptr;
    while (curr != front()) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == nullptr) {
        head = tail = nullptr;
    }
    else {
        prev->next = nullptr;
        front(*prev);
    }
    delete curr;
}


// Check if the queue is empty
bool Queue::empty() const {
    return front() == nullptr;
}

// Print the queue
void Queue::print() const {
    if (empty()) {
        std::cout << "The queue is empty.\n";
    }
    else {
        QueueNode* temp = back();
        std::cout << "Current queue: ";
        while (temp != front()) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << front()->data << "\n";
    }
}

// Add element to the queue
void operator+=(Queue& queue, const int addValue) {
    queue.push(addValue);
    return;
}

// Add two queues
Queue Queue::operator+(const Queue& queue) const {
    Queue result;
    if (empty() && queue.empty()) { // Both queues are empty
        std::cout << "Both queues are empty\n\n";
    }
    else {
        QueueNode* temp_1 = back();
        QueueNode* temp_2 = queue.back();

        // TempHead elements are used so we know what was the last pushed element 
        QueueNode* tempHead_1 = front();
        QueueNode* tempHead_2 = queue.front();


        // Function pushes to the 'result' all the "paired" elements 
        while (tempHead_1 != back() && tempHead_2 != queue.back()) {
            temp_1 = back();
            temp_2 = queue.back();
            while (temp_1->next != tempHead_1) {
                temp_1 = temp_1->next;
            }
            while (temp_2->next != tempHead_2) {
                temp_2 = temp_2->next;
            }
            result.push(tempHead_1->data + tempHead_2->data);
            tempHead_1 = temp_1;
            tempHead_2 = temp_2;
        }
        result.push(tempHead_1->data + tempHead_2->data);



        // If the first queue is larger:

        // If the last pushed element is not a nullptr (queue is not empty) 
        // and is not the last in the queue
        if (tempHead_1 != nullptr && tempHead_1 != back()) { 
            // If the last pushed element is not a penultimate element
            if (back()->next != tempHead_1) { 
                while (tempHead_1 != back()) {
                    temp_1 = back();
                    while (temp_1->next != tempHead_1) {
                        temp_1 = temp_1->next;
                    }
                    result.push(tempHead_1->data);
                    tempHead_1 = temp_1;
                }
            }
            result.push(back()->data);
        }

        // If the second queue is larger:

        // If the last pushed element is not a nullptr (queue is not empty) 
        // and is not the last in the queue
        if (tempHead_2 != nullptr && tempHead_2 != queue.back()) {
            // If the last pushed element is not a penultimate element
            while (tempHead_2 != queue.back()) {
                temp_2 = queue.back();
                while (temp_2->next != tempHead_2) {
                    temp_2 = temp_2->next;
                }
                result.push(tempHead_2->data);
                tempHead_2 = temp_2;
            }
            result.push(tempHead_2->data);
        }
    }

    return result;
}





// If 'extracting from the queue' implies simple deletion of the head,
// the code is:

/*
* if (!empty()) {
*   pop();
* }
* return *this;
*/


// Delete user's element from the queue
Queue& Queue::operator=(const int value) {
    bool found = false;
    if (!empty()) {
        
        QueueNode* temp = back(); // Node to be deleted (containing given value)
        QueueNode* pre_temp = back(); // Node before temporary
        while (temp != front() && !found) {
            if (temp->data == value) {
                // Common situation, value to be deleted is somewhere 
                // in the middle of the queue
                if (temp != back()) { 
                    while (pre_temp->next != temp) {
                        pre_temp = pre_temp->next;
                    }
                    pre_temp->next = temp->next;
                    delete temp;
                }

                // Value to be deleted is the last one added
                else { 
                    temp = temp->next;
                    delete pre_temp;
                    back(*temp); 
                }
                found = true;
            }
            else {
                temp = temp->next;
            }
        }
        if (front()->data == value) { // To avoid going through the entire queue
            pop();
            found = true;
        }
        
        
    }

    found ? (std::cout << "The value has been deleted successfully\n\n")
          : (std::cout << "The value has not been found\n\n");

    return *this;
}


// Subtract two queues
Queue operator-(const Queue& queue_1, const Queue& queue_2) {
    Queue result;
    if (queue_1.empty() && queue_2.empty()) { // Both queues are empty
        std::cout << "Both queues are empty\n\n";
    }
    else {
        QueueNode* temp_1 = queue_1.back();
        QueueNode* temp_2 = queue_2.back();

        // TempHead elements are used so we know what was the last pushed element 
        QueueNode* tempHead_1 = queue_1.front();
        QueueNode* tempHead_2 = queue_2.front();


        // Function pushes to the 'result' all the "paired" elements 
        while (tempHead_1 != queue_1.back() && tempHead_2 != queue_2.back()) {
            temp_1 = queue_1.back();
            temp_2 = queue_2.back();
            while (temp_1->next != tempHead_1) {
                temp_1 = temp_1->next;
            }
            while (temp_2->next != tempHead_2) {
                temp_2 = temp_2->next;
            }
            result.push(tempHead_1->data - tempHead_2->data);
            tempHead_1 = temp_1;
            tempHead_2 = temp_2;
        }
        result.push(tempHead_1->data - tempHead_2->data);



        // If the first queue is larger:

        // If the last pushed element is not a nullptr (queue is not empty) 
        // and is not the last in the queue
        if (tempHead_1 != nullptr && tempHead_1 != queue_1.back()) {
            // If the last pushed element is not a penultimate element
            if (queue_1.back()->next != tempHead_1) {
                while (tempHead_1 != queue_1.back()) {
                    temp_1 = queue_1.back();
                    while (temp_1->next != tempHead_1) {
                        temp_1 = temp_1->next;
                    }
                    result.push(tempHead_1->data);
                    tempHead_1 = temp_1;
                }
            }
            result.push(queue_1.back()->data);
        }

        // If the second queue is larger:

        // If the last pushed element is not a nullptr (queue is not empty) 
        // and is not the last in the queue
        if (tempHead_2 != nullptr && tempHead_2 != queue_2.back()) {
            // If the last pushed element is not a penultimate element
            while (tempHead_2 != queue_2.back()) {
                temp_2 = queue_2.back();
                while (temp_2->next != tempHead_2) {
                    temp_2 = temp_2->next;
                }
                result.push(-tempHead_2->data);
                tempHead_2 = temp_2;
            }
            result.push(-tempHead_2->data);
        }
    }

    return result;
}


// Multiply two queues
Queue Queue::operator*(const Queue& queue) const {
    Queue result;

    if (!empty() && !queue.empty()) {
        QueueNode* temp_1;
        QueueNode* temp_2;

        QueueNode* tempHead_1 = front();
        QueueNode* tempHead_2 = queue.front();

        while (tempHead_1 != back() && tempHead_2 != queue.back()) {
            temp_1 = back();
            temp_2 = queue.back();
            while (temp_1->next != tempHead_1) {
                temp_1 = temp_1->next;
            }
            while (temp_2->next != tempHead_2) {
                temp_2 = temp_2->next;
            }
            result.push(tempHead_1->data * tempHead_2->data);
            tempHead_1 = temp_1;
            tempHead_2 = temp_2;

        }
        result.push(tempHead_1->data * tempHead_2->data);
        
    }
    return result;
}

// Divide a queue by a number
Queue Queue::operator/(const int number) const {
    Queue result;

    QueueNode* temp = back();
    QueueNode* tempHead = front();

    while (tempHead != back()) {
        temp = back();
        while (temp->next != tempHead) {
            temp = temp->next;
        }
        result.push(tempHead->data / number);
        tempHead = temp;
    }
    result.push(tempHead->data / number);

    return result;
}
