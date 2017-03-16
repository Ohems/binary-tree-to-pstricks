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
    Node() {}

    void setContent(std::string& content) { this->content = content; }
    const std::string& getContent() const { return content; }

    void addChild(Node* node);
    std::vector<Node*>& getChildren() { return children; }

    float getX() const { return x; }
    unsigned int getDepth() const { return depth; }

private:
    std::string content;

    float x = 0.0f; /** X position  of center in LaTeX units, check PSTricksExport for tools */
    unsigned int depth = 0; /** Depth in layers, top layer is 0 */

    std::vector<Node*> children;
};

#endif // NODE_H
