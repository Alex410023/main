#pragma once

#include "StackNode.h"

#include <iostream>

template <typename T>
class Stack {
private:
	StackNode<T>* top;
public:
    // Default constructor
	Stack() : top(nullptr) {}

    // Constructor with a parameter
    Stack(const int size, const int seed) {
        srand(seed);
        for (int i = 0; i < size; i++) {
            T value{};
            int num = rand() % 61 - 30; // values = [-30..30]
            if constexpr (std::is_same_v<T, int>) {
                value = num;
            }
            else if constexpr (std::is_same_v<T, char>) {
                num = num % 26 + 'a'; // values = [a..Z]
                value = static_cast<char>(num);
            }
            else if constexpr (std::is_same_v<T, float>) {
                int degree = rand() % 4 * 8 + 1; // degree = [1..32]
                value = static_cast<float>(num) / static_cast<float>(pow(2.0, degree));
            }
            else if constexpr (std::is_same_v<T, double>) {
                int degree = rand() % 8 * 8 + 1;
                value = static_cast<double>(num) / static_cast<double>(pow(2.0, degree));
            }
            else if constexpr (std::is_same_v<T, char*>) {
                const char* characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
                const int charCount = strlen(characters);

                int strLength = rand() % 10 + 1; // Random length of the string [1..10]
                value = new char[strLength + 1]; // Allocate memory for the character array

                for (int j = 0; j < strLength; j++) {
                    value[j] = characters[rand() % charCount]; // Fill the character array 
                    // with random characters
                }
                value[strLength] = '\0'; // Null-terminate the character array
            }
            push(value);
        }
    }


    // Copy constructor
    Stack(const Stack& other)
        : top(nullptr) {
        *this = other;  // Delegate to assignment operator
    }

    // Destructor
    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    // Adding to the top function
    void push(const T value) {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->setNextNode(getTop());
        setTop(newNode);
    }

    // Deleting the top element function
    void pop() {
        if (empty()) {
            std::cout << "The stack is empty." << std::endl;
            return;
        }

        StackNode<T>* temp = getTop();
        setTop(getTop()->getNextNode());
        delete temp;
    }

    // Top element getter function
    StackNode<T>* getTop() const {
        return top;
    }

    // Top element setter function
    void setTop(StackNode<T>* node) {
        top = node;
    }

    // Function to check if the stack is empty
    bool empty() const {
        return getTop() == nullptr;
    }

    // Stack printing function
    void print() const {
        StackNode<T>* temp = getTop();
        while (temp != nullptr) {
            std::cout << temp->getData() << " ";
            temp = temp->getNextNode();
        }
        std::cout << std::endl;
    }

    // Stack inverting function
    void invert() {
        Stack<T> result;

        while (!empty()) {
            result.push(getTop()->getData());
            pop();
        }

        *this = result;
    }


    // Removing of the first instance of element in the stack function
    void remove(const T value) {
        if (!empty()) {
            if (getTop()->getData() == value) {
                pop();
            }
            else {
                StackNode<T>* curr = getTop();
                StackNode<T>* prev = nullptr;

                while (curr != nullptr) {
                    if (curr->getData() == value) {
                        prev->setNextNode(curr->getNextNode());
                        delete curr;
                        break;
                    }
                    prev = curr;
                    curr = curr->getNextNode();
                }
            }
        }
        else {
            std::cout << "The stack is empty.\n";
        }
    }

    // Operator '=' overloading
    Stack<T>& operator=(const Stack<T>& other) {
        if (this == &other) {
            return *this;  // Self-assignment check
        }

        // Clear the current stack
        while (!empty()) {
            pop();
        }

        // Copy elements from other stack to the current stack
        StackNode<T>* temp = other.getTop();
        StackNode<T>* prev = nullptr;

        while (temp != nullptr) {
            StackNode<T>* newNode = new StackNode<T>(*temp);

            if (prev == nullptr) {
                top = newNode;
            }
            else {
                prev->setNextNode(newNode);
            }

            prev = newNode;
            temp = temp->getNextNode();
        }

        return *this;
    }


    // Operator '+' overloading
    Stack<T> operator+(const Stack<T>& other)  {
         Stack<T> result = other;
        invert();

        StackNode<T>* temp = getTop();
        while (temp != nullptr) {
            result.push(temp->getData());
            temp = temp->getNextNode();
        }

        invert();
        return result;
    }

    // Operator '==' overloading
    bool operator==(const Stack<T>& other) const {
        StackNode<T>* temp1 = getTop();
        StackNode<T>* temp2 = other.getTop();

        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->getData() != temp2->getData()) {
                return false;
            }
            temp1 = temp1->getNextNode();
            temp2 = temp2->getNextNode();
        }

        return temp1 == nullptr && temp2 == nullptr;
    }

    // Operator '-' overloading
    Stack<T> operator-(const Stack<T>& other) const {
        Stack<T> result = *this;
        StackNode<T>* curr = other.getTop();

        while (curr != nullptr) {
            result.remove(curr->getData());
            curr = curr->getNextNode();
        }

        return result;
    }
};
