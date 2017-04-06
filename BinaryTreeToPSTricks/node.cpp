#include "node.h"

void Node::addChild(Node* node)
{
    node->depth_ = depth() + 1;

    children_.push_back(node);
}

Node* Node::leftContour()
{
    return children_.size() > 0 ? children_.front() : thread_;
}

Node* Node::rightContour()
{
    return children_.size() > 0 ? children_.back() : thread_;
}
