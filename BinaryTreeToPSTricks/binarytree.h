#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>

#include "node.h"

using namespace std;

class BinaryTree
{
public:
    // This is just a recommendation now, change when implementing
    BinaryTree(string data);

    ~BinaryTree();

private:
    Node* root = nullptr;
};

#endif // BINARYTREE_H
