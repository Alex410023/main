#pragma once

#include <cstdlib>  
#include <iostream>
#include <iomanip>


#include "Node.h"

template <typename T>
class BinaryTree {
private:
    Node<T>* root;

public:
    // Default constructor
    BinaryTree() : root(nullptr) {}

    // Constructor with size parameter (creates a binary tree with random data)
    BinaryTree(const int size) : root(nullptr) {
        for (int i = 0; i < size; i++) {
            int value = rand() % 100;  // Generating random numbers between 0 and 99
            addElement(value);
        }
    }

    // Copy constructor
    BinaryTree(const BinaryTree& other) : root(nullptr) {
        // Call a helper function to perform a deep copy of the tree
        setRoot(copyTree(other.getRoot()));
    }

    // Destructor
    ~BinaryTree() {
        // Call a helper function to delete all nodes in the tree
        deleteTree(root);
    }

    void deleteTree(Node<T>* node) {
        if (node != nullptr) {
            deleteTree(node->getLeft());
            deleteTree(node->getRight());
            delete node;
        }
    }

    // Root getter function
    Node<T>* getRoot() const {
        return root;
    }

    // Root setter function
    void setRoot(Node<T>* node) {
        root = node;
    }

    // Function to add an element to the tree
    void addElement(T value) {
        setRoot(addElementHelper(getRoot(), value));
    }

    // Helper function to recursively add an element to the tree
    Node<T>* addElementHelper(Node<T>* node, T value) {
        if (node == nullptr) {
            // Create a new node if the current node is null
            node = new Node<T>(value);
        }
        else if (value < node->getData()) {
            // Recursively add the element to the left subtree
            node->setLeft(addElementHelper(node->getLeft(), value));
        }
        else if (value > node->getData()) {
            // Recursively add the element to the right subtree
            node->setRight(addElementHelper(node->getRight(), value));
        }
        // Ignore duplicate values (no action required)

        return node;
    }

    // Function to traverse the tree in descending order
    void traverseDescending() const {
        if (getRoot()) {
            std::cout << "Current tree: ";
            traverseDescendingHelper(getRoot());
            std::cout << std::endl;
        }
        else {
            std::cout << "The tree is empty." << std::endl;
        }
        std::defaultfloat;
    }

    // Helper function to recursively traverse the tree in descending order
    void traverseDescendingHelper(const Node<T>* node) const {
        if (node != nullptr) {
            // Recursively traverse the right subtree
            traverseDescendingHelper(node->getRight());

            // Display the data of the current node
            std::cout << std::fixed << std::setprecision(7) << node->getData() << " ";

            // Recursively traverse the left subtree
            traverseDescendingHelper(node->getLeft());
        }
    }

    // Function to traverse the tree in ascending order
    void traverseAscending() const {
        if (getRoot()) {
            std::cout << "Current tree: ";
            traverseAscendingHelper(getRoot());
            std::cout << std::endl;
        }
        else {
            std::cout << "The tree is empty." << std::endl;
        }
        std::defaultfloat;
    }

    // Helper function to recursively traverse the tree in ascending order
    void traverseAscendingHelper(const Node<T>* node) const {
        if (node != nullptr) {
            // Recursively traverse the left subtree
            traverseAscendingHelper(node->getLeft());

            // Display the data of the current node
            std::cout << std::fixed << std::setprecision(7) << node->getData() << " ";

            // Recursively traverse the right subtree
            traverseAscendingHelper(node->getRight());
        }
    }

    // Function to search for a value in the tree
    bool searchValue(T value) {
        return searchValueHelper(getRoot(), value);
    }

    // Helper function to recursively search for a value in the tree
    bool searchValueHelper(const Node<T>* node, T value) const {
        if (node == nullptr) {
            return false;  // Value not found
        }
        else if constexpr (std::is_same_v<T, char*>) { // To handle char* values
            if (strcmp(value, node->getData()) == 0) {
                return true;  // Value found
            }
        }
        else if (value == node->getData()) {
            return true;  // Value found
        }
        else if (value < node->getData()) {
            // Recursively search in the left subtree
            return searchValueHelper(node->getLeft(), value);
        }
        else {
            // Recursively search in the right subtree
            return searchValueHelper(node->getRight(), value);
        }
    }

    // Helper function to perform a deep copy of the tree
    Node<T>* copyTree(Node<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }

        Node<T>* newNode = new Node<T>(node->getData());
        newNode->setLeft(copyTree(node->getLeft()));
        newNode->setRight(copyTree(node->getRight()));

        return newNode;
    }

    void deleteElement(T value) {
        setRoot(deleteElementHelper(getRoot(), value));
    }

    Node<T>* deleteElementHelper(Node<T>* node, T value) {
        if (node == nullptr) {
            std::cout << "There's no such element" << std::endl; // Element not found
            return node;
        }

        if (value < node->getData()) {
            node->setLeft(deleteElementHelper(node->getLeft(), value)); // Recursively search in the left subtree
        }
        else if (value > node->getData()) {
            node->setRight(deleteElementHelper(node->getRight(), value)); // Recursively search in the right subtree
        }
        else {
            if (node->getLeft() == nullptr) {
                Node<T>* temp = node->getRight();
                delete node; // Delete the node
                std::cout << "The element was deleted" << std::endl;
                return temp; // Return the right child to replace the deleted node
            }
            else if (node->getRight() == nullptr) {
                Node<T>* temp = node->getLeft();
                delete node; // Delete the node
                std::cout << "The element was deleted" << std::endl;
                return temp; // Return the left child to replace the deleted node
            }

            Node<T>* temp = findMinValueNode(node->getRight()); // Find the minimum value node in the right subtree
            node->setData(temp->getData()); // Replace the data of the node to be deleted with the data of the minimum value node
            node->setRight(deleteElementHelper(node->getRight(), temp->getData())); // Recursively delete the minimum value node from the right subtree
        }

        return node;
    }

    Node<T>* findMinValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->getLeft() != nullptr) {
            current = current->getLeft(); // Keep traversing left until the leftmost node is reached
        }
        return current; // Return the leftmost node (minimum value node)
    }
};