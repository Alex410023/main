#pragma once
#include "Binary Tree.h"



class AVL_Node {
public:
    int data;
    AVL_Node *left;
    AVL_Node *right;

    AVL_Node();
    AVL_Node(int value);
};

class AVL_Tree {
public:
    AVL_Node *root;
    AVL_Tree();

    bool isTreeEmpty();

    int getHeight(AVL_Node *root);

    int getBalanceFactor(AVL_Node *avl_node);

    AVL_Node *rightRotate(AVL_Node *y);
    AVL_Node *leftRotate(AVL_Node *x);

    AVL_Node *insert(AVL_Node *root, AVL_Node *new_node);

    AVL_Node *minValueNode(AVL_Node* node);

    AVL_Node *deleteNode(AVL_Node *root, int value);

    void printPreorder(AVL_Node *root); // current node, left, right
    void printInorder(AVL_Node *root); //  left, current node, right
    void printPostorder(AVL_Node *root); // left, right, root

    void printGivenLevel(AVL_Node *root, int level);

    void printLevelOrderBFS(AVL_Node *root);

    AVL_Node *iterativeSearch(int value);
    AVL_Node *recursiveSearch(AVL_Node *root, int val);
    
    AVL_Node binaryIntoAVL(Node *root, AVL_Node *avl_root);
    void pre_order(AVL_Node *root);
    
    void workWithAVL_Tree(Node *root);
    
    AVL_Node *postorderIterative(Node* root);
    
    void treePrint(AVL_Node* root, int maxHeight);
};


