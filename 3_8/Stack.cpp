#include "Stack.h"

// Default constructor
Stack::Stack() 
    : head(nullptr) 
{
}

// Constructor with parameter
Stack::Stack(const int value) 
    : head(new Node(value)) 
{
}


// Stack copy constructor
Stack::Stack(const Stack& other) {
    if (other.head == nullptr) {
        head = nullptr;
        return;
    }

    // Create new head node
    head = new Node(other.head->data);

    // Copy remaining nodes
    Node* node = head;
    Node* otherNode = other.head->next;
    while (otherNode != nullptr) {
        node->next = new Node(otherNode->data);
        node = node->next;
        otherNode = otherNode->next;
    }
}

// Stack destructor
Stack::~Stack() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}


// Head setter function
void Stack::setHead(Node& node) {
    head = &node;
}

// Head getter function
Stack::Node* Stack::getHead() const {
    return head;
}

// Insert an element into the stack
void Stack::insert(const int value) {
    Node* node = new Node(value);
    node->next = getHead();
    setHead(*node);
}

// Extract an element from the stack
void Stack::extract() {
    if (getHead() == nullptr) {
        cout << "The stack is empty";
    }

    Node* node = getHead();
    setHead(*getHead()->next);
    delete node;
}

// Print the stack
void Stack::print() const {
    Node* node = getHead();
    while (node != nullptr) {
        cout << node->data << endl;
        node = node->next;
    }
    cout << endl;
}

// Save the stack to a file
void Stack::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Cannot open file";
        return;
    }

    Node* node = getHead();
    while (node != nullptr) {
        outFile << node->data << endl;
        node = node->next;
    }
    outFile.close();
}

// Load the stack from a file
void Stack::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Cannot open file";
        return;
    }

    // Delete current stack
    while (getHead() != nullptr) {
        extract();
    }

    // Read from file
    int data;
    while (inFile >> data) {
        insert(data);
    }
    inFile.close();
}