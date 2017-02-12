#include <string>

#include "binarytree.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

namespace {
    void buildNode(Node* current, json j)
    {
        current->setContent(j["content"].get<string>());

        json children = j["children"];

        for(json::iterator it = children.begin(); it != children.end(); ++it) {
            Node* child = new Node();
            current->addChild(child);
            buildNode(child, *it);
        }
    }
}

BinaryTree::BinaryTree(json j)
{
    buildNode(this->root, j);
}

BinaryTree::~BinaryTree()
{
    delete root;
}
