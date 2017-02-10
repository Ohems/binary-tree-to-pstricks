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
    Node(const string& content) : content(content) {}

    string& getContent() { return content; }

    void addChild(Node* node);
    vector<Node*>& getChildren() { return children; }

    float getX() { return x; }
    unsigned int getY() { return y; }

private:
    string content;

    float x = 0.0f; /** X position  of center in LaTeX units, check PSTricksExport for tools */
    unsigned int y = 0; /** Y position in layers, top layer is 0 */

    vector<Node*> children;
};

#endif // NODE_H
