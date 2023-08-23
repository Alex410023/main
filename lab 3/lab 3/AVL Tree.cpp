#include <iostream>
#include <cmath>
#include <iomanip>
#include <stack>
#include "AVL Tree.h"

using namespace std;

AVL_Node::AVL_Node() {
    data = NULL;
    left = nullptr;
    right = nullptr;
}

AVL_Node::AVL_Node(int value) {
    data = value;
    left = nullptr;
    right = nullptr;
}

AVL_Tree::AVL_Tree() {
    root = NULL;
}
bool AVL_Tree::isTreeEmpty() {
    if (root == NULL) {
        return true;
    } else {
        return false;
    }
}

int AVL_Tree::getHeight(AVL_Node *root) {
    if (root == NULL) {
        return -1;
    } else {
        // claculate the height of each subtree
        int l_height = getHeight(root->left);
        int r_height = getHeight(root->right);

        if (l_height > r_height) {
            return (l_height + 1);
        } else {
            return (r_height + 1);
        }
    }
}

int AVL_Tree::getBalanceFactor(AVL_Node *avl_node) {
    if (avl_node == NULL) {
        return -1;
    }
    return getHeight(avl_node->left) - getHeight(avl_node->right);
}

AVL_Node *AVL_Tree::rightRotate(AVL_Node *y) {
    AVL_Node *x = y->left;
    AVL_Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    return x;
}

AVL_Node *AVL_Tree::leftRotate(AVL_Node *x) {
    AVL_Node *y = x->right;
    AVL_Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    return y;
}

AVL_Node *AVL_Tree::insert(AVL_Node *root, AVL_Node *newNode) {
    if (root == NULL) {
        root = newNode;
//        cout << "Value has been inserted.\n";
        return root;
    }

    if (newNode->data < root->data) {
        root->left = insert(root->left, newNode);
    } else if (newNode->data > root->data) {
        root->right = insert(root->right, newNode);
    } else {
        cout << "You cannot add duplicates.\n";
        return root;
    }

    int bf = getBalanceFactor(root);
    
    // Left Left Case
    if (bf > 1 && newNode->data < root->left->data) {
        return rightRotate(root);
    }
    
    // Right Right Case
    if (bf < -1 && newNode->data > root->right->data) {
        return leftRotate(root);
    }

    // Left Right Case
    if (bf > 1 && newNode->data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (bf < -1 && newNode->data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    /* return unchanged node pointer */
    return root;
}

AVL_Node *AVL_Tree::minValueNode(AVL_Node *node) {
    AVL_Node *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

AVL_Node *AVL_Tree::deleteNode(AVL_Node *root, int value) {
    if (root == NULL) {
        return NULL;
    }
    
    else if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
        
    } else {
        if (root->left == NULL) {
            AVL_Node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            AVL_Node *temp = root->left;
            delete root;
            return temp;
        } else {
            AVL_Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    int bf = getBalanceFactor(root);
    // Left Left Imbalance/Case or Right rotation
    if (bf == 2 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }
    // Left Right Imbalance/Case or LR rotation
    else if (bf == 2 && getBalanceFactor(root->left) == -1) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Imbalance/Case or Left rotation
    else if (bf == -2 && getBalanceFactor(root->right) <= -0) {
        return leftRotate(root);
    }
    // Right Left Imbalance/Case or RL rotation
    else if (bf == -2 && getBalanceFactor(root->right) == 1) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void AVL_Tree::printPreorder(AVL_Node *root) //     (current node, left, right)
{
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

void AVL_Tree::printInorder(AVL_Node *root) { //    (left, current node, right)
    if (root == NULL) {
        return;
    }
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}
void AVL_Tree::printPostorder(AVL_Node *root) {  //     (left, right, root)
    if (root == NULL) {
        return;
    }
    printPostorder(root->left);
    printPostorder(root->right);
    cout << root->data << " ";
}

// Print nodes of a given level
void AVL_Tree::printGivenLevel(AVL_Node *root, int level) {
    if (root == NULL) {
        return;
    } else if (level == 0) {
        cout << root->data << " ";
        
    } else {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

void AVL_Tree::printLevelOrderBFS(AVL_Node *root) {
    int h = getHeight(root);
    for (int i = 0; i <= h; i++) {
        printGivenLevel(root, i);
    }
}

AVL_Node *AVL_Tree::iterativeSearch(int value) {
    if (root == NULL) {
        return root;
    } else {
        AVL_Node *temp = root;
        while (temp != NULL) {
            if (value == temp->data) {
                return temp;
            } else if (value < temp->data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        return NULL;
    }
}

AVL_Node *AVL_Tree::recursiveSearch(AVL_Node *root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    } else if (value < root->data) {
        return recursiveSearch(root->left, value);
    } else {
        return recursiveSearch(root->right, value);
    }
}


void AVL_Tree::pre_order(AVL_Node *root) { // root, left kin, right kin
    if (root == NULL) {
       return;
    }
    cout << root->data << "  ";
    pre_order(root->left);
    pre_order(root->right);
}


AVL_Node *AVL_Tree::postorderIterative(Node* root) {
    AVL_Tree avl_tree;

    if (root == nullptr) {
        return NULL;
    }
 
    // Create an empty stack and put the root node in it
    stack<Node*> s;
    s.push(root);
 
    // Create another stack to store the traversal in reverse order
    stack<int> out;
 
    // While stack is not empty
    while (!s.empty()) {
        // Extract the node from the stack and put the data into the output stack
        Node* curr = s.top();
        s.pop();

        out.push(curr->data);
 
        // Put the left and right child elements of the extracted node in the stack
        if (curr->left) {
            s.push(curr->left);
        }
 
        if (curr->right) {
            s.push(curr->right);
        }
    }
 
    while (!out.empty()) {
        AVL_Node *newNode = new AVL_Node;
        newNode->data = out.top();
        avl_tree.root = avl_tree.insert(avl_tree.root, newNode);
        
        out.pop();
    }
    return avl_tree.root;
}



void AVL_Tree::treePrint(AVL_Node *root, int maxHeight) {
    AVL_Node **nodeArr, **lrNodeArr;
    nodeArr = (AVL_Node **)malloc(sizeof(AVL_Node *));
    lrNodeArr = (AVL_Node **)malloc(2 * sizeof(AVL_Node *));
 
//    Node *curNode = root;
    AVL_Node *curNode = new AVL_Node;
    
    nodeArr[0] = root;
    string spaces;
    for (int height = 0; height < maxHeight; ) {
        spaces = "";
//        nodeArr = (Node **)realloc(nodeArr, pow(2, height) * sizeof(Node *));
//        lrNodeArr = (Node **)realloc(lrNodeArr, 2 * pow(2, height) * sizeof(Node *));
        
        for (int i = 0; i < pow(2, height); i++) {
            curNode = nodeArr[i];
            
            int spaceNum = pow(2, maxHeight - height + 1);
            if (i != 0 && height != 0) {
                spaceNum = spaceNum * 2;
            }
            
            if (curNode != NULL) {
                cout << setw(spaceNum) << curNode->data;
            } else {
                cout << setw(spaceNum) << "";
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
        
        height++;
        int curSize = 2 * pow(2, height) * sizeof(AVL_Node *);
        nodeArr = (AVL_Node **)realloc(nodeArr, curSize);
        // nodeArr = lrNodeArr;
        for (int i = 0; i < 2 * pow(2, height); i++) {
            nodeArr[i] = lrNodeArr[i];
        }
        lrNodeArr = (AVL_Node **)realloc(lrNodeArr, curSize);
        
    }
    
    cout << " ";
    
    int spaceNum = pow(2, 2);
    
    bool prevWereBlank = true;
    
    for (int i = 0; i < pow(2, maxHeight); i++) {
        curNode = lrNodeArr[i];
        if (curNode != NULL) {
            if (i == 0) {
                cout << curNode->data;
                prevWereBlank = false;
                
            } else if (prevWereBlank) {
                cout << curNode->data;
                prevWereBlank = false;
                
            } else if (!prevWereBlank) {
                cout << setw(spaceNum) << curNode->data;
            }
        } else {
            cout << setw(spaceNum) << "";
        }
    }
    cout << "\n\n";
}


void AVL_Tree::workWithAVL_Tree(Node *root) {
    AVL_Tree avl_tree;
    int option = 0, value = 0;
    
    avl_tree.root = postorderIterative(root);

    int avlHeight = getHeight(avl_tree.root);
    
    cout << "\nAVL Tree from a Binary Tree:\n";
    treePrint(avl_tree.root, avlHeight);
    

        do {
            cout << "\nWhat do you want to do? Any other number - exit.\n";
            cout << "1. Insert Node\n";
            cout << "2. Search Node\n";
            cout << "3. Delete Node\n";
            cout << "4. Print/Traversal AVL Tree values\n";
            cout << "5. Height of Tree\n";

            cin >> option;
            AVL_Node *newNode = new AVL_Node();

            switch (option) {
                case 1: {
                    cout << "Enter value of tree node to insert in AVL Tree: ";
                    cin >> value;
                    newNode->data = value;
                    avl_tree.root = avl_tree.insert(avl_tree.root, newNode);
                    cout << "\n";
                    break;
                }
                case 2: {
                    cout << "Enter value of tree node to search in AVL Tree: ";
                    cin >> value;
                    //newNode = avl_tree.iterativeSearch(val);
                    newNode = avl_tree.recursiveSearch(avl_tree.root, value);
                    if (newNode != NULL) {
                        cout << "Value found\n";
                    } else {
                        cout << "Value not found\n";
                    }
                    break;
                }
                case 3: {
                    cout << "Enter value of tree node to delete in AVL: ";
                    cin >> value;
                    newNode = avl_tree.recursiveSearch(avl_tree.root, value);
                    if (newNode != NULL) {
                        avl_tree.root = avl_tree.deleteNode(avl_tree.root, value);
                        cout << "Value was deleted successfully.\n";
                    }
                    else {
                        cout << "Value not found.\n";
                    }
                    break;
                }
                case 4: {
                    treePrint(avl_tree.root, avlHeight);
                    
                    int otherOutput = 0;
                    cout << "Do you want to print other output orders? (0 - no, other input - yes)\n";
                    cin >> otherOutput;
                    
                    if (otherOutput != 0) {
                        cout << "Which order do you want to choose?\n";
                        cout << "1. Preorder Traversal\n";
                        cout << "2. Inorder Traversal\n";
                        cout << "3. Postorder Traversal\n";
                        cout << "4. Level Order Traversal\n";

                        int traversalOption = 0;
                        cin >> traversalOption;
                        switch (traversalOption) {
                            case 1:
                                printPreorder(avl_tree.root); // current node, left, right
                                break;
                            case 2:
                                printInorder(avl_tree.root); //  left, current node, right
                                break;
                            case 3:
                                printPostorder(avl_tree.root); // left, right, root
                                break;
                            case 4:
                                printLevelOrderBFS(avl_tree.root);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }
                case 5: {
                    cout << "Height: " << avl_tree.getHeight(avl_tree.root) << "\n";
                    break;
                }
                default:
                    break;
                }
            
        } while (option >= 1 && option <= 5);
}
