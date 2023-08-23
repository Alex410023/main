#pragma once

#include <iostream>

template <typename T>
class Node {
private:
    T data;
    Node<T>* left; // Left node
    Node<T>* right; // Right node

public:
    // Default constructor
    Node() 
        : data(T())
        , left(nullptr)
        , right(nullptr)
    {
    }

    // Constructor with a parameter
    Node(const T value)
        : data(value)
        , left(nullptr)
        , right(nullptr)
    {
    }

    // Copy constructor
    Node(const Node<T>& node) 
        : data(node->getData())
        , left(nullptr)
        , right(nullptr)
    {
    }

    // Data getter function
    T getData() const {
        return data;
    }

    // Data setter function
    void setData(const T value) {
        data = value;
    }

    // Left node getter function
    Node<T>* getLeft() const {
        return left;
    }
    // Left node setter function
    void setLeft(Node<T>* node) {
        left = node;
    }

    // Right node getter function
    Node<T>* getRight() const {
        return right;
    }
    // Right node setter function
    void setRight(Node<T>* node) {
        right = node;
    }
};