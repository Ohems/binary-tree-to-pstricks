#include <string>

#include "binarytree.h"

using namespace std;

BinaryTree::BinaryTree(string data)
{
    // THIS IS TEST DATA, REPLACE WITH ACTUAL DATA
    Node* root = new Node("root");
    root->addChild(new Node("lol"));
    root->addChild(new Node("wtf"));

    this->root = root;
}

BinaryTree::~BinaryTree() {
    delete root;
}
