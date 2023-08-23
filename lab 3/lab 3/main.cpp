#include <iostream>

#include "Binary Tree.h"
#include "Bracket Parsing.h"
#include "AVL Tree.h"

int main(int argc, const char * argv[]) {
    if (parsingIsPossible()) {
        BinaryTree bin_object;
        Node *binRoot = bin_object.treeCreate();
        
        AVL_Tree avl_object;
        avl_object.workWithAVL_Tree(binRoot);
    }
    return 0;
}
