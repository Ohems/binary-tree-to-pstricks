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
            // Account for the offset of the current subtrees
            rightMod += right->mod();
            leftMod += left->mod();

            // Calculate the overlay of the current nodes
            float overlay = left->x() + leftMod + nodeWidth(left) + margin()
                    - (right->x() + rightMod);

            // If overlay is greater than the largest current error, replace
            if (overlay > error) {
                error = overlay;
            }

            float rightThreadMod;
            float leftThreadMod;

            // Progress to the next nodes
            // If we jump over a thread, record the mod offset
            right = right->leftContour(&rightThreadMod);
            left = left->rightContour(&leftThreadMod);

            // Apply thread mod offset to the known mods
            rightMod += rightThreadMod;
            leftMod += leftThreadMod;

            // Check right tree ended but the left one is still going
            if (!right && left) {
                // Create a new thread from right to left
                originalRight->rightLast()->thread(
                            left,
                            leftMod - (rightMod + error)
                );
            }

            // Check left tree ended but the right one is still going
            if (!left && right) {
                // Create a new thread from left to right
                originalLeft->leftLast()->thread(
                            right,
                            (rightMod + error) - leftMod
                );
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

    // Keep track of the layer count
    if (current->depth() + 1 > layers_) {
        layers_ = current->depth() + 1;
    }
}

void BinaryTree::applyModRecursive(Node* current, float mod /*= 0.0f*/)
{
    // Record the offset of this subtree
    mod += current->mod();

    // Convert mod into location
    current->x() += mod;
    current->mod() = 0;

    // Find tree width
    float rightEdge = current->x() + nodeWidth(current);
    if (rightEdge > width_) {
        width_ = rightEdge;
    }

    // Recurse
    for (Node* child : current->children()) {
        applyModRecursive(child, mod);
    }
}

BinaryTree::BinaryTree(json j)
{
    buildNodesRecursive(root_, j);  // Build tree
    placeNodesRecursive(root_);     // Calculate tree locations
    applyModRecursive(root_);       // Apply calculated locations
}

BinaryTree::~BinaryTree()
{
    delete root_;
}
