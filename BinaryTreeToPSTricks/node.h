#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Class representing one node in the tree
 */
class Node
{
public:
    Node() {}

    void setContent(string& content) { this->content = content; }
    string& getContent() { return content; }

    void addChild(Node* node);
    vector<Node*>& getChildren() { return children; }

    float getX() { return x; }
    unsigned int getDepth() { return depth; }

private:
    string content;

    float x = 0.0f; /** X position  of center in LaTeX units, check PSTricksExport for tools */
    unsigned int depth = 0; /** Depth in layers, top layer is 0 */

    vector<Node*> children;
};

#endif // NODE_H
