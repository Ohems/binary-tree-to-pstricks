#include "node.h"

Node::Node()
{
    rightLast_ = this;
    leftLast_ = this;
}


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

Node* Node::rightLast()
{
    return rightLast_;
}

Node* Node::leftLast()
{
    return leftLast_;
}

void Node::addRightLast(Node* node)
{
    rightLast_ = node;
}

void Node::addLeftLast(Node* node)
{
    leftLast_ = node;
}
