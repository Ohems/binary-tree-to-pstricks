#include "node.h"

void Node::addChild(Node* node)
{
    node->depth_ = depth() + 1;

    children_.push_back(node);
}
