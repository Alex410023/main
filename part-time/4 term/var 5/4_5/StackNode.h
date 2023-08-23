#pragma once

template <typename T>
class StackNode {
private:
    T data; // Stack node's value
    StackNode<T>* next; // Pointer to the next stack element
public:
    // Default constructor
    StackNode()
        : data(T())
        , next(nullptr)
    {
    }

    // Constructor with a standard argument
    StackNode(const T value)
        : data(value)
        , next(nullptr)
    {
    }

    StackNode(const StackNode<T>& node) 
        : data(node.getData())
        , next(node.getNextNode())
    {    
    }

    // Destructor
    ~StackNode() {}

    // Data getter function
    T getData() const {
        return data;
    }
    // Data setter function
    void setData(const T value) {
        data = value;
    }

    // Next node getter function
    StackNode* getNextNode() const {
        return next;
    }
    // Next node setter function
    void setNextNode(StackNode* node) {
        next = node;
    }

};