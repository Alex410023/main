#pragma once

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    
    Node();
    Node(int value);
};

class BinaryTree {
public:
    Node *insertToLeft(Node *curNode, int value);
    Node *insertToRight(Node *curNode, int value);
    
    void treePrint(Node *root, int maxHeight);
    
    void preorder(Node *root);
    
    Node *treeCreate();
};
