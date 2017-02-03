#include "node.h"

void Node::addChild(const Node &node)
{
    children.push_back(node);
}
