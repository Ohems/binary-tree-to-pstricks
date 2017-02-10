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

    float getWidth() { return 10; } // TODO
    unsigned int getLayerCount() { return 1; } // TODO

    Node* getRootNode() { return root; }

private:
    Node* root = nullptr;
};

#endif // BINARYTREE_H
