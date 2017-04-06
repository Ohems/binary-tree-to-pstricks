#ifndef PSTRICKSEXPORT_H
#define PSTRICKSEXPORT_H

#include <ostream>

#include "binarytree.h"
#include "node.h"

/**
 * State machine that converts binary trees to PSTricks format
 *
 * States:
 *      bool indent
 *      bool wrapDocument
 *      bool escapeSpecialCharacters
 *
 *      string filename
 */
namespace PSTricksExport
{
    /**
     * @brief Gives the minimum margin that should be between two nodes
     * @return Margin as float in default LaTeX units
     */
    float margin();

    /**
     * @brief Calculates the width this node will require considering its content
     * @param node The node for which the size is calculated
     * @return Size as float in default LaTeX units
     */
    float nodeWidth(Node* node);

    /**
     * @brief Returns the y position of the bottom left corner of the node
     *        in LaTeX units
     * @param tree Context of the node
     * @param node Node
     * @return Bottom left corner of the given node in the given tree in LaTeX units
     */
    float nodeY(const BinaryTree& tree, Node* node);

    /**
     * @brief Define if the output should be indented to depth
     * @param value New value
     */
    void indent(bool value);

    /**
     * @brief Define if the output should be wrapped with a basic LaTeX document
     * @param value New value
     */
    void wrapDocument(bool value);

    /**
     * @brief Define if special characters should be escaped
     * @param value New value
     */
    void escapeSpecialCharacters(bool value);

    /**
     * @brief Define the file to which the tree is exported
     * @param value Either local file or full path
     */
    void targetFile(std::string value);

    /**
     * @brief Converts the binary tree to PSTricks format and prints it according to the
     *        state of the exporter.
     * @param tree Tree to be exported
     * @return True if successful
     */
    bool exportTree(const BinaryTree& tree);

    /**
     * @brief Converts the binary tree to PSTricks format and prints it to the given output.
     *        Output format is defined by the state of the exporter.
     * @param tree Tree to be exported
     * @param out Output to which the result is exported
     * @return True if successful
     * @warning Doesn't close output stream
     */
    bool exportTreeToOutput(const BinaryTree& tree, std::ostream& out);
}

#endif // PSTRICKSEXPORT_H
