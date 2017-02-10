#include "node.h"

void Node::addChild(Node* node)
{
    node->y = getY() + 1;

    children.push_back(node);
}
