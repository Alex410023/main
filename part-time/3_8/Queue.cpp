#include "Queue.h"

// Default constructor
Queue::Queue() 
    : head(nullptr)
    , tail(nullptr) 
{
} 

// Constructor with parameter
Queue::Queue(const int value) 
    : head(new Node(value))
    , tail(head) 
{
} 

// Queue copy constructor
Queue::Queue(const Queue& other) {
    if (other.head != nullptr) {
        Node* curr = other.tail;
        while (curr != head) {
            insert(curr->data);
            curr = curr->next;
        }
        insert(curr->data);
    }
    else {
        head = nullptr;
        tail = nullptr;
    }
}

// Queue destructor
Queue::~Queue() {
    while (getHead() != nullptr) {
        extract();
    }
}

// Head setter function
void Queue::setHead(Node& node) {
    head = &node;
}

// Head getter function
Queue::Node* Queue::getHead() const {
    return head;
}

// Tail setter function
void Queue::setTail(Node& node) {
    tail = &node;
}

// Tail getter function
Queue::Node* Queue::getTail() const {
    return tail;
}

// Insert an element into the queue
void Queue::insert(const int value) {
    Node* newData = new Node(value);
    if (getHead() == nullptr) {
        setTail(*newData);
        setHead(*newData);
    }
    else {
        newData->next = getTail();
        setTail(*newData);
    }
}

// Extract an element from the queue
void Queue::extract() {
    if (head == nullptr) {
        cout << "The queue is empty" << endl;
    } 
    else {
        Node* curr = new Node;
        curr = getTail();
        Node* prev = nullptr;
        while (curr != getHead()) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == nullptr) {
            head = tail = nullptr;
        }
        else {
            prev->next = nullptr;
            setHead(*prev);
        }
        delete curr;
    }
}

// Print the queue
void Queue::print() const {
    if (getHead() == nullptr) {
        cout << "The queue is empty" << endl;
        return;
    }
    Node* temp = getTail();
    while (temp != getHead()) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << getHead()->data << endl;

}



// Save the queue to a file
void Queue::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Cannot open file";
        return;
    }
    Node* node = getTail();
    while (node != nullptr) {
        outFile << node->data << " ";
        node = node->next;
    }
    outFile.close();
}

// Load the queue from a file
void Queue::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Cannot open file";
        return;
    }

    // Delete current queue
    while (head != nullptr) {
        extract();
    }

    // Read from file
    int data;
    while (inFile >> data) {
        insert(data);
    }
    inFile.close();
}