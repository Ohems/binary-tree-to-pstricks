#include "node.h"

Node::Node()
{
    rightLast_ = this;
    leftLast_ = this;
}

void Node::thread(Node* thread, float mod)
{
    thread_ = thread;
    threadMod_ = mod;
}


void Node::addChild(Node* node)
{
    node->depth_ = depth() + 1;

    children_.push_back(node);
}


Node* Node::leftContour(float* threadMod /*= 0*/)
{
    if (threadMod) *threadMod = 0.0f;
    if (children_.size() == 0) {
        if (threadMod && thread_) *threadMod = threadMod_;
        return thread_;
    }
    return children_.front();
}

Node* Node::rightContour(float* threadMod /*= 0*/)
{
    if (threadMod) *threadMod = 0.0f;
    if (children_.size() == 0) {
        if (threadMod && thread_) *threadMod = threadMod_;
        return thread_;
    }
    return children_.back();
}

Node* Node::rightLast()
{
    return rightLast_;
}

Node* Node::leftLast()
{
    return leftLast_;
}

void Node::rightLast(Node* node)
{
    rightLast_ = node;
}

void Node::leftLast(Node* node)
{
    leftLast_ = node;
}
