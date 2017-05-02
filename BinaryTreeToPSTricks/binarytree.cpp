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

    float findGreatestErrorInContour(Node* originalRight, Node* originalLeft)
    {
        float error = 0.0f;

        float rightMod = 0.0f;
        float leftMod = 0.0f;

        Node* right = originalRight;
        Node* left = originalLeft;

        while(right && left && right != left) {
            float diff = left->locX() + nodeWidth(left) + margin() - right->locX();

            if (diff > error) {
                error = diff;
            }

            rightMod += right->mod();
            leftMod += left->mod();

            right = right->leftContour();
            left = left->rightContour();

            if (!right && left) {
                originalRight->rightLast()->thread(left);
            }
            if (!left && right) {
                originalLeft->leftLast()->thread(right);
            }
        }

        return error;
    }
}

void BinaryTree::placeNodesRecursive(
        Node* current,
        const vector<Node*>& siblings /*= vector<Node*>()*/
) {
    if (!current->children().empty()) {
        // Process children first
        for (Node* child : current->children()) {
            placeNodesRecursive(child, current->children());
        }

        // Center based on children
        Node* firstChild = current->children().front();
        Node* lastChild = current->children().back();
        float childrenWidth = lastChild->locX() + nodeWidth(lastChild) - firstChild->locX();
        current->x() += firstChild->locX() + childrenWidth / 2.0f - nodeWidth(current) / 2.0f;

        // Parents lastLeft and lastRight are same as their left and right children
        current->addRightLast(current->children().back()->rightLast());
        current->addLeftLast(current->children().front()->leftLast());
    }

    // Apply mod based on contour
    for (Node* sibling : siblings) {
        if (sibling == current) break;
        current->mod() += findGreatestErrorInContour(current, sibling);
    }

    if (current->depth() + 1 > layers_) {
        layers_ = current->depth() + 1;
    }
}

void BinaryTree::applyModRecursive(Node* current, float mod /*= 0.0f*/)
{
    mod += current->mod();

    current->x() += mod;
    current->mod() = 0;

    // Find tree width
    float rightEdge = current->x() + nodeWidth(current);
    if (rightEdge > width_) {
        width_ = rightEdge;
    }

    for (Node* child : current->children()) {
        applyModRecursive(child, mod);
    }
}

BinaryTree::BinaryTree(json j)
{
    buildNodesRecursive(root_, j);

    placeNodesRecursive(root_);
    applyModRecursive(root_);
}

BinaryTree::~BinaryTree()
{
    delete root_;
}
