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
    Node(const string &content) : content(content) {}

    void addChild(const Node &node);

private:
    string content;

    float x = 0.0f;
    unsigned int level = 0; /** Level in which this node is, top level is 0 */

    vector<Node> children;
};

#endif // NODE_H
