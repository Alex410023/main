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
        QueueItem* curr = object.back();
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
QueueItem* Queue::front() const {
    return head;
}

// Head setter function
void Queue::front(QueueItem& object) {
    head = &object;
}

// Tail getter function
QueueItem* Queue::back() const {
    return tail;
}

// Tail setter function
void Queue::back(QueueItem& object) {
    tail = &object;
}

// Add to the end of the queue
void Queue::push(int value) {
    QueueItem* newData = new QueueItem(value);
    if (empty()) {
        tail = newData;
        head = newData;
    }
    else {
        newData->next = tail;
        tail = newData;
    }
}

// Delete the first added element
void Queue::pop() {
    QueueItem* curr = new QueueItem;
    curr = tail;
    QueueItem* prev = NULL;
    while (curr != head) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {
        head = tail = NULL;
    }
    else {
        prev->next = NULL;
        head = prev;
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
        QueueItem* temp = back();
        std::cout << "Current queue: ";
        while (temp != front()) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << front()->data << "\n";
    }
}

// Get queue's size
int Queue::size() const {
    int size = 0;
    if (!empty()) {
        QueueItem* temp = back();
        while (temp != front()) {
            temp = temp->next;
            size++;
        }
        size++;
    }
    return size;
}

// Add element to the queue
Queue& Queue::operator+(const int addValue) {
    push(addValue);
    return *this;
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
Queue Queue::operator-(const int value) {
    bool found = false;
    if (!empty()) {
        if (front()->data == value) { // To avoid going through the entire queue
            pop();
            found = true;
        }
        else {
            QueueItem* temp = back(); // Node to be deleted (containing given value)
            QueueItem* pre_temp = back(); // Node before temporary
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
        }

    }

    found ? (std::cout << "The value has been deleted successfully\n\n")
        : (std::cout << "The value has not been found\n\n");

    return *this;
}


// Multiply a queue by a number
Queue Queue::operator*(const int number) {
    Queue result;

    QueueItem* temp = back();
    QueueItem* tempHead = front();

    while (tempHead != back()) {
        temp = back();
        while (temp->next != tempHead) {
            temp = temp->next;
        }
        result.push(tempHead->data * number);
        tempHead = temp;
    }
    result.push(tempHead->data * number);

    return result;
}



bool Queue::operator==(Queue& right) const {
    if (size() != right.size()) {
        return false;
    }
    else {
        bool areEqual = true;

        QueueItem* temp1 = back();
        QueueItem* temp2 = right.back();

        while (temp1 != head && temp2 != right.head && areEqual) {
            if (temp1->data == temp2->data) {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            else
            {
                areEqual = false;
            }
        }
        if (front()->data != right.front()->data) {
            areEqual = false;
        }

        return areEqual;
    }
}

bool Queue::operator!=(Queue& right) const {
    if (size() != right.size()) {
        return false;
    }
    else {
        bool areEqual = true;

        QueueItem* temp1 = back();
        QueueItem* temp2 = right.back();

        while (temp1 != head && temp2 != right.head && areEqual) {
            if (temp1->data == temp2->data) {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            else
            {
                areEqual = false;
            }
        }
        if (front()->data != right.front()->data) {
            areEqual = false;
        }

        return areEqual;
    }
}





std::ostream& operator<<(std::ostream& os, const Queue& queue) {
    QueueItem* current = queue.back();
    while (current != queue.front()) {
        os << current->data << " -> ";
        current = current->next;
    }
    os << current->data;
    return os;
}

std::istream& operator>>(std::istream& is, Queue& queue) {
    int data;
    while (is >> data) {
        queue.push(data);
    }
    return is;
}