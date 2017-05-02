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
            float overlay = leftMod + nodeWidth(left) + margin() - rightMod;

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

        // Check children total width
        Node* firstChild = current->children().front();
        Node* lastChild = current->children().back();
        float childrenWidth = lastChild->locX() + nodeWidth(lastChild) - firstChild->locX();

        // Center children below the parent node
        float offset = childrenWidth / 2.0f - nodeWidth(current) / 2.0f;
        for (Node* child : current->children()) {
            child->mod() -= offset;
        }

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

float BinaryTree::findSmallestMod(Node* current, float mod /*= 0.0f*/)
{
    // Record the offset of this subtree
    mod += current->mod();

    float leftThreadMod;
    Node* leftContour = current->leftContour(&leftThreadMod);
    mod += leftThreadMod;

    if (leftContour) {

        // If has left contour, recursively check its smallest mod
        float childSmallestMod = findSmallestMod(leftContour, mod);

        // Return either left contour mod or this mod
        // depending on which one is smaller
        return mod < childSmallestMod ? mod : childSmallestMod;

    } else {
        // No left contour, just return this mod
        return mod;
    }
}

void BinaryTree::applyModRecursive(Node* current, float mod /*= 0.0f*/)
{
    // Record the offset of this subtree
    mod += current->mod();

    // Convert mod into location
    current->x() += mod;
    current->mod() = 0.0f;

    // At this point we shouldn't have any negative coordinates,
    // but floating points are sometimes nasty
    if (current->x() < 0.0f) current->x() = 0.0f;

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
    // Build tree
    buildNodesRecursive(root_, j);

    // Calculate tree locations
    placeNodesRecursive(root_);

    // Find the smallest (usually negative) mod value
    float smallestMod = findSmallestMod(root_);

    // Apply calculated locations
    applyModRecursive(root_, -smallestMod);
}

BinaryTree::~BinaryTree()
{
    delete root_;
}
