#ifndef PSTRICKSEXPORT_H
#define PSTRICKSEXPORT_H

#include "binarytree.h"
#include "node.h"

namespace PSTricksExport
{
    /**
     * @brief Gives the minimum margin that should be between two nodes
     * @return Margin as float in default LaTeX units
     */
    float getMargin();

    /**
     * @brief Calculates the width this node will require considering its content
     * @param node The node for which the size is calculated
     * @return Size as float in default LaTeX units
     */
    float getNodeWidth(Node* node);

    /**
     * @brief Set the directory path to which new export files are created
     * @param path Path to the folder
     * @return True if successful
     */
    bool setExportDirectory(const string& path);

    /**
     * @brief Exports the binary tree to a .tex file in PSTricks format
     * @param tree Tree to be exported
     * @param filename Name of the file to be created
     * @param indent Should nodes be indented in the output based on their level
     * @param wrapDocument Should output be wrapped in basic LaTeX syntax so that it becomes a valid document
     * @return True if successful
     */
    bool exportTreeToFile(BinaryTree& tree, const string& filename,
                          bool indent = true, bool wrapDocument = false);

    /**
     * @brief Converts the binary tree to PSTricks format and prints it to console
     * @param tree Tree to be exported
     * @param indent Should nodes be indented in the output based on their level
     * @return True if successful
     */
    bool exportTreeToConsole(BinaryTree& tree, bool indent = true);
}

#endif // PSTRICKSEXPORT_H
