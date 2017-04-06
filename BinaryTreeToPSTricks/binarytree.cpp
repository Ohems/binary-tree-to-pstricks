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

    float findGreatestErrorInContour(Node* current, Node* sibling)
    {
        float error = 0.0f;

        while(true) {
                 float diff = sibling->x() + nodeWidth(sibling) + margin() - current->x();
                 if (diff > error) {
                     error = diff;
                 }

                 if (current->children().size() == 0 || sibling->children().size() == 0) {
                     break;
                 }

                 current = current->children().front();
                 sibling = sibling->children().back();
        }

        return error;
    }

    void placeNodesRecursive(Node* current, const vector<Node*>& siblings)
    {
        float xOffset = current->x();
        for (Node* child : current->children()) {
            child->x(xOffset);
            placeNodesRecursive(child, current->children());
            xOffset += nodeWidth(child) + margin();

        }

        float childWidth = 0.0f;
        for (Node* child : current->children()) {
            childWidth += nodeWidth(child);
            if (child != current->children().back()) {
                childWidth += margin();
            }
        }
        current->x(current->x() + childWidth / 2.0f - nodeWidth(current) / 2.0f);

        for (Node* sibling : siblings) {
            if (sibling == current) break;

            current->mod(findGreatestErrorInContour(current, sibling));
        }

    }

    void applyModRecursive(Node* current, float mod = 0.0f)
    {
        mod += current->mod();

        current->x(current->x() + mod);

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
