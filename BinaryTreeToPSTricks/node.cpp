#include "node.h"

Connection Connection::copy(float modDiff /*= 0.0f*/) const
{
    Connection thread = *this;
    thread.mod += modDiff;
    return thread;
}

Node::Node() : thread_({nullptr, 0.0f})
{
    rightLast_ = { this, 0.0f };
    leftLast_ = { this, 0.0f };
}

void Node::thread(const Connection& thread)
{
    thread_ = thread;
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
        if (threadMod && thread_) *threadMod = thread_.mod;
        return thread_.target;
    }
    return children_.front();
}

Node* Node::rightContour(float* threadMod /*= 0*/)
{
    if (threadMod) *threadMod = 0.0f;
    if (children_.size() == 0) {
        if (threadMod && thread_) *threadMod = thread_.mod;
        return thread_.target;
    }
    return children_.back();
}

Connection Node::rightLast() { return rightLast_; }
Connection Node::leftLast() { return leftLast_; }

void Node::rightLast(const Connection& thread)
{
    rightLast_ = thread;
}

void Node::leftLast(const Connection& thread)
{
    leftLast_ = thread;
}
