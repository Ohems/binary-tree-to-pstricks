#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"
#include "json.hpp"

class BinaryTree
{
public:
    BinaryTree(nlohmann::json j);
    ~BinaryTree();

    float getWidth() const { return 10; } // TODO
    unsigned int getLayerCount() const { return 10; } // TODO

    Node* getRootNode() const { return root; }

private:
    Node* root = new Node();
};

#endif // BINARYTREE_H
