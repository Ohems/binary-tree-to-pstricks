#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "binarytree.h"
#include "pstricksexport.h"
#include "inputparser.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[])
{
    if (argc < 2){
        cerr << "Usage: " << argv[0] << "-i input [-o output] [-n] [-w]" << endl
             << left << endl
             << setw(21) << "\t-i input:"   << "Input file" << endl
             << setw(21) << "\t-o output:"  << "Output file, write to console if not defined" << endl
             << setw(21) << "\t-n:"         << "Indent PSTricks output according to tree depth" << endl
             << setw(21) << "\t-w:"         << "Wrap document with a minimal LaTeX document" << endl
             << setw(21) << "\t-t:"         << "Show threads (for debugging purposes)" << endl;
        return 0;
    }

    InputParser consoleInput(argc, argv);

    string inputFilePath = consoleInput.getCmdOption("-i");

    if (inputFilePath.empty()) {
        cerr << "No input file defined!" << endl;
        return 0;
    }

    ifstream fileInput(inputFilePath);

    if (!fileInput.is_open()) {
        cerr << "Error opening file " << inputFilePath << endl;
        return 0;
    }

    json j;
    fileInput >> j;

    fileInput.close();

    BinaryTree tree(j);

    PSTricksExport::targetFile(consoleInput.getCmdOption("-o"));

    PSTricksExport::indent(consoleInput.cmdOptionExists("-n"));
    PSTricksExport::wrapDocument(consoleInput.cmdOptionExists("-w"));
    PSTricksExport::showThreads(consoleInput.cmdOptionExists("-t"));

    PSTricksExport::exportTree(tree);

    return 0;
}
