#include <iostream>

#include "binarytree.h"
#include "pstricksexport.h"

using namespace std;

int main()
{
    string input = "";

    // TODO: read input data

    BinaryTree tree = BinaryTree(input);

    PSTricksExport::exportTreeToConsole(tree);

    return 0;
}
