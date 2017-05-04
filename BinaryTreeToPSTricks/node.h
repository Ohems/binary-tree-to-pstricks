#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

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

    Node* thread() { return thread_; }
    void thread(Node* thread, float mod);
    float threadMod() { return threadMod_; }

    Node* leftContour(float* threadMod = 0);
    Node* rightContour(float* threadMod = 0);

    Node* rightLast();
    Node* leftLast();

    void rightLast(Node* node);
    void leftLast(Node* node);

private:
    std::string content_;

    float x_ = 0.0f; /** X position of left edge in LaTeX units, check PSTricksExport for tools */
    float mod_ = 0.0f;
    unsigned int depth_ = 0; /** Depth in layers, top layer is 0 */

    std::vector<Node*> children_;

    Node* thread_ = nullptr;
    float threadMod_ = 0.0f;

    Node* rightLast_;
    Node* leftLast_;
};

#endif // NODE_H
