#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>

#include "node.h"
#include "json.hpp"

using namespace std;

class BinaryTree
{
public:
    BinaryTree(nlohmann::json j);
    ~BinaryTree();

    float getWidth() { return 10; } // TODO
    unsigned int getLayerCount() { return 1; } // TODO

    Node* getRootNode() { return root; }

private:
    Node* root = new Node();
};

#endif // BINARYTREE_H
