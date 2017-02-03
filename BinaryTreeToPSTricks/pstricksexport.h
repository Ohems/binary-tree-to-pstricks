#ifndef PSTRICKSEXPORT_H
#define PSTRICKSEXPORT_H

#include "binarytree.h"

namespace PSTricksExport
{
    /**
     * @brief Set the directory path to which new export files are created
     * @param path Path to the folder
     * @return True if successful
     */
    bool setExportDirectory(const string &path);

    /**
     * @brief Exports the binary tree to a text file in PSTricks format
     * @param tree Tree to be exported
     * @param filename Name of the file to be created
     * @return True if successful
     */
    bool exportTreeToFile(const BinaryTree &tree, const string &filename);

    /**
     * @brief Converts the binary tree to PSTricks format and prints it to console
     * @param tree Tree to be exported
     * @return True if successful
     */
    bool exportTreeToConsole(const BinaryTree &tree);
}

#endif // PSTRICKSEXPORT_H
