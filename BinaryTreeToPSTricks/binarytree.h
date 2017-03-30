#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"
#include "json.hpp"

class BinaryTree
{
public:
    BinaryTree(nlohmann::json j);
    ~BinaryTree();

    float width() const { return 10; } // TODO
    unsigned int layers() const { return 10; } // TODO

    Node* root() const { return root_; }

private:
    Node* root_ = new Node();
};

#endif // BINARYTREE_H
