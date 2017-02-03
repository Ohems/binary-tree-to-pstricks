#include <iostream>
#include <string>

#include "pstricksexport.h"
#include "binarytree.h"

using namespace std;

namespace PSTricksExport
{
    namespace
    {
        string directoryPath = "";
    }

    bool setExportDirectory(const string &path)
    {
        directoryPath = path;
        return true;
    }

    bool exportTreeToFile(const BinaryTree &tree, const string &filename)
    {
        cout << "Tree exporting not yet ready, nothing done and returning true" << endl;
        return true;
    }

    bool exportTreeToConsole(const BinaryTree &tree)
    {
        cout << "Tree exporting not yet ready, nothing done and returning true" << endl;
        return true;
    }
}
