#include "node.h"

void Node::addChild(Node* node)
{
    node->depth = getDepth() + 1;

    children.push_back(node);
}
