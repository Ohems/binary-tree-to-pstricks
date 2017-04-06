#include "node.h"

void Node::addChild(Node* node)
{
    node->depth_ = depth() + 1;

    children_.push_back(node);
}

Node* Node::leftContour()
{
    return children_.empty() ? thread_ : children_.front();
}

Node* Node::rightContour()
{
    return children_.empty() ? thread_ : children_.back();
}
