#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>

#include "node.h"
#include "json.hpp"

class BinaryTree
{
public:
    BinaryTree(nlohmann::json j);
    ~BinaryTree();

    float width() const { return width_; }
    unsigned int layers() const { return layers_; }

    Node* root() const { return root_; }

private:
    Node* root_ = new Node();

    float width_ = 0.0f;
    unsigned int layers_ = 0;

    void placeNodesRecursive(
            Node* current,
            const std::vector<Node*>& siblings = std::vector<Node*>()
    );

    void applyModRecursive(Node* current, float mod = 0.0f);
};

#endif // BINARYTREE_H
