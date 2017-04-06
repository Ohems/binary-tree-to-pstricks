#include <string>

#include "binarytree.h"
#include "json.hpp"
#include "pstricksexport.h"

using PSTricksExport::nodeWidth;
using PSTricksExport::margin;

using namespace std;
using json = nlohmann::json;

namespace {
    void buildNodesRecursive(Node* current, json j)
    {
        string content = j["content"].get<string>();
        current->content(content);

        json children = j["children"];

        for (json::iterator it = children.begin(); it != children.end(); ++it) {
            Node* child = new Node();
            current->addChild(child);
            buildNodesRecursive(child, *it);
        }       
    }

    float findGreatestErrorInContour(Node* right, Node* left)
    {
        float error = 0.0f;

        float rightMod = 0.0f;
        float leftMod = 0.0f;

        while(true) {
            rightMod += right->mod();
            leftMod += left->mod();

            float diff =
                    left->x() + leftMod + nodeWidth(left) + margin()
                    - (right->x() + rightMod);

            if (diff > error) {
                error = diff;
            }

            if (right->children().size() == 0 || left->children().size() == 0) {
                break;
            }

            right = right->children().front();
            left = left->children().back();
        }

        return error;
    }

    void placeNodesRecursive(Node* current, const vector<Node*>& siblings)
    {
        // Process children first
        for (Node* child : current->children()) {
            placeNodesRecursive(child, current->children());
        }

        // Center based on children
        if (!current->children().empty()) {
            Node* firstChild = current->children().front();
            Node* lastChild = current->children().back();
            float childrenWidth = lastChild->locX() + nodeWidth(lastChild) - firstChild->locX();
            current->x() += firstChild->locX() + childrenWidth / 2.0f - nodeWidth(current) / 2.0f;
        }

        // Apply mod based on contour
        for (Node* sibling : siblings) {
            if (sibling == current) break;
            current->mod() += findGreatestErrorInContour(current, sibling);
        }

    }

    void applyModRecursive(Node* current, float mod = 0.0f)
    {
        mod += current->mod();

        current->x() += mod;
        current->mod() = 0;

        for (Node* child : current->children()) {
            applyModRecursive(child, mod);
        }
    }
}

BinaryTree::BinaryTree(json j)
{
    buildNodesRecursive(root_, j);

    placeNodesRecursive(root_, root_->children());
    applyModRecursive(root_);
}

BinaryTree::~BinaryTree()
{
    delete root_;
}
