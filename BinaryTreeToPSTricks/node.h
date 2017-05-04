#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node;

struct Connection {
    Node* target;
    float mod;

    operator bool() const { return target != nullptr; }

    Connection copy(float modDiff = 0.0f) const;
};

/**
 * @brief Class representing one node in the tree
 */
class Node
{
public:
    Node();

    void content(std::string& content) { this->content_ = content; }
    const std::string& content() const { return content_; }

    void addChild(Node* node);
    std::vector<Node*>& children() { return children_; }

    float x() const { return x_; }
    float& x() { return x_; }

    float mod() const { return mod_; }
    float& mod() { return mod_; }

    float locX() { return x_ + mod_; }

    unsigned int depth() const { return depth_; }

    Connection thread() { return thread_; }
    void thread(const Connection& thread);

    Node* leftContour(float* threadMod = 0);
    Node* rightContour(float* threadMod = 0);

    Connection rightLast();
    Connection leftLast();

    void rightLast(const Connection& thread);
    void leftLast(const Connection& thread);

private:
    std::string content_;

    float x_ = 0.0f; /** X position of left edge in LaTeX units, check PSTricksExport for tools */
    float mod_ = 0.0f;
    unsigned int depth_ = 0; /** Depth in layers, top layer is 0 */

    std::vector<Node*> children_;

    Connection thread_;
    Connection rightLast_;
    Connection leftLast_;
};

#endif // NODE_H
