#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include "Binary Tree.h"

using namespace std;
    
Node::Node() {
    data = NULL;
    left = nullptr;
    right = nullptr;
}

Node::Node(int value) {
    data = value;
    left = nullptr;
    right = nullptr;
}


// Insert to the left of the parent vertex:
Node * BinaryTree::insertToLeft(Node *curNode, int value) {
    Node *node = new Node(value);
    curNode->left = node;
    return node;
}

// Insert to the right of the parent vertex:
Node * BinaryTree::insertToRight(Node *curNode, int value) {
    Node *node = new Node(value);
    curNode->right = node;
    return node;
}

void BinaryTree::treePrint(Node *root, int maxHeight) {
    ofstream fout;
    fout.open("txts//bin_tree.txt");
    if (!fout.is_open()) {
        cout << "File has not been opened.\n";
    }
    
    Node **nodeArr, **lrNodeArr;
    nodeArr = (Node **)malloc(sizeof(Node *));
    lrNodeArr = (Node **)malloc(2 * sizeof(Node *));
    cout << sizeof(nodeArr) << "   " << sizeof(lrNodeArr) << "\n";
 
    Node *curNode = new Node;
    
    nodeArr[0] = root;
    for (int height = 0; height < maxHeight; ) {
        for (int i = 0; i < pow(2, height); i++) {
            curNode = nodeArr[i];
            
            int spaceNum = pow(2, maxHeight - height + 1);
            if (i != 0 && height != 0) {
                spaceNum = spaceNum * 2;
            }
            
            if (curNode != NULL) {
                cout << setw(spaceNum) << curNode->data;
                fout << setw(spaceNum) << curNode->data;
            } else {
                cout << setw(spaceNum) << "";
                fout << setw(spaceNum) << "";
            }
            
            if (curNode != NULL) {
                lrNodeArr[2 * i] = curNode->left;
            } else {
                lrNodeArr[2 * i] = NULL;
            }
            
            if (curNode != NULL) {
                lrNodeArr[2 * i + 1] = curNode->right;
            } else {
                lrNodeArr[2 * i + 1] = NULL;
            }
        }

        cout << "\n";
        fout << "\n";
        
        height++;
        int curSize = 2 * pow(2, height) * sizeof(Node *);
        nodeArr = (Node **)realloc(nodeArr, curSize);

        for (int i = 0; i < 2 * pow(2, height); i++) {
            nodeArr[i] = lrNodeArr[i];
        }
        lrNodeArr = (Node **)realloc(lrNodeArr, curSize);
        
    }
    
    cout << " ";
    fout << " ";
    
    int spaceNum = pow(2, 2);
    
    bool prevWereBlank = true;
    
    for (int i = 0; i < pow(2, maxHeight); i++) {
        curNode = lrNodeArr[i];
        if (curNode != NULL) {
            if (i == 0) {
                cout << curNode->data;
                fout << curNode->data;
                prevWereBlank = false;
                
            } else if (prevWereBlank) {
                cout << curNode->data;
                fout << curNode->data;
                prevWereBlank = false;
                
            } else if (!prevWereBlank) {
                cout << setw(spaceNum) << curNode->data;
                fout << setw(spaceNum) << curNode->data;
            }
        } else {
            cout << setw(spaceNum) << "";
            fout << setw(spaceNum) << "";
        }
    }
    cout << "\n\n";
    
    fout.close();
}


void BinaryTree::preorder(Node *root) { // root, left kin, right kin
    if (root == NULL) {
       return;
    }
    
    cout << root->data << "  ";
    preorder(root->left);
    preorder(root->right);
}


Node * BinaryTree::treeCreate() {
    ifstream fin;
    fin.open("txts//brackets_input.txt");
    if (!fin.is_open()) {
        cout << "File has not been opened.\n";
    }
    
    string str;
    getline(fin, str);
        
    bool rootExists = false;
    
    Node *root = new Node;
    Node *curNode = new Node;
    
    int maxHeight = 0;
    int i = 0, height = 0, num = 0;
    while (i < str.length()) {
        num = 0;
        if (str[i] == '(') {
            height++;
            if (maxHeight < height) {
                maxHeight = height;
            }
            i++;
        } else if (str[i] == ')') {
            height--;
            i++;
        } else {
            while (str[i] != '(' && str[i] != ')') {
                num *= 10;
                num += ((str[i]) - '0');
                i++;
            }
            if (!rootExists) {
                root->data = num;
                rootExists = true;
                i++;
            } else {
                curNode = root;
                
                // Shift to a certain level:
                for (int k = 0; k < height - 1; k++) {
                    if (curNode->right == nullptr) {
                        curNode = curNode->left;
                    } else {
                        curNode = curNode->right;
                    }
                }
                
                // New node creation:
                if (curNode->left == nullptr) {
                    insertToLeft(curNode, num);
                } else {
                    insertToRight(curNode, num);
                }
            }
        }
    }
    
    
    treePrint(root, maxHeight);
        
    fin.close();
    
    return root;
}

