#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "pstricksexport.h"
#include "binarytree.h"
#include "node.h"

using namespace std;

namespace PSTricksExport
{
    namespace
    {
        const float NODE_HEIGHT = 0.7f;

        string directoryPath = "";

        void addHeader(const BinaryTree& tree, stringstream& ss)
        {
            /*
             *  \newcommand{\treenode}[5]{
             *      \rput(#1,#2){
             *          \psframe[fillstyle=solid,fillcolor=white,framearc=1](0,0)(#3,NODE_HEIGHT)
             *          \rput[b](#4,0.2){#5}
             *      }
             *  }
             *
             *  \begin{pspicture}(width,height)
             */
            float layerCount = static_cast<float>(tree.getLayerCount());
            float marginsY = layerCount > 0 ? getMargin() * (layerCount - 1.0f) : 0.0f;

            float width = tree.getWidth();
            float height = NODE_HEIGHT * layerCount + marginsY;

            ss << "\\newcommand{\\treenode}[5]{\n"
                   << "\t\\rput(#1,#2){\n"
                       << "\t\t\\psframe[fillstyle=solid,fillcolor=white,framearc=1](0,0)(#3," << NODE_HEIGHT << ")\n"
                       << "\t\t\\rput[b](#4,0.2){#5}\n"
                   << "\t}\n"
               << "}\n\n"
               << "\\begin{pspicture}(" << width << "," << height << ")\n";
        }

        void addFooter(stringstream& ss)
        {
            ss << "\\end{pspicture}\n";
        }

        void addIndent(stringstream& ss, Node* node)
        {
            for (unsigned int i = 0 ; i <= node->getDepth() ; i++) {
                ss << "  ";
            }
        }

        void addNode(const BinaryTree& tree, stringstream& ss, Node* node, bool indent)
        {
            /*
             *  \treenode{cornerX}{cornerY}{nodeWidth}{textX}{content}
             */

            float cornerX = node->getX();
            float cornerY = getNodeY(tree, node);
            float nodeWidth = getNodeWidth(node);
            float textX = nodeWidth / 2.0f;

            string content = node->getContent();

            if (indent) addIndent(ss, node);

            ss   << "\\treenode{"
                 << cornerX << "}{" << cornerY << "}{"
                 << nodeWidth << "}{"
                 << textX << "}{"
                 << content
                 << "}\n";
        }

        void addConnection(const BinaryTree& tree, stringstream& ss, Node* a, Node* b, bool indent)
        {
            /*
             *  \psline{-}(x1,y1)(x2,y2)
             */

            float x1 = a->getX() + getNodeWidth(a) / 2.0f;
            float y1 = getNodeY(tree, a) + NODE_HEIGHT / 2.0f;

            float x2 = b->getX() + getNodeWidth(b) / 2.0f;
            float y2 = getNodeY(tree, b) + NODE_HEIGHT / 2.0f;

            if (indent) addIndent(ss, b);

            ss << "\\psline{-}(" << x1 << "," << y1 << ")(" << x2 << "," << y2 << ")\n";
        }

        void addNodesRecursive(const BinaryTree& tree, stringstream& ss, Node* node, bool indent)
        {
            for (size_t i = 0 ; i < node->getChildren().size() ; ++i) {
                addConnection(tree, ss, node, node->getChildren()[i], indent);
                addNodesRecursive(tree, ss, node->getChildren()[i], indent);
            }

            addNode(tree, ss, node, indent);
        }
    }

    float getMargin()
    {
        return 0.7f;
    }

    float getNodeWidth(Node* node)
    {
        return 0.5f + 0.2f * static_cast<float>(node->getContent().length());
    }

    float getNodeY(const BinaryTree& tree, Node* node)
    {
        float indexFromBottom = tree.getLayerCount() - node->getDepth();
        return indexFromBottom * NODE_HEIGHT
                + (indexFromBottom - 1.0f) * getMargin();
    }

    bool setExportDirectory(const string& path)
    {
        directoryPath = path;
        return true;
    }

    bool exportTreeToFile(const BinaryTree& tree, const string& filename,
                          bool indent /*= false*/, bool wrapDocument /*= false*/)
    {
        cout << "Tree exporting not yet ready, nothing done and returning true" << endl;
        return true;
    }

    bool exportTreeToConsole(const BinaryTree& tree, bool indent /*= false*/,
                             bool wrapDocument /*= false*/)
    {
        cout << "Tree exporting not yet ready, expect weird results!" << endl << endl;

        stringstream ss;

        addHeader(tree, ss);

        if (tree.getRootNode()) {
            addNodesRecursive(tree, ss, tree.getRootNode(), indent);
        }

        addFooter(ss);

        cout << ss.str() << endl;
        return true;
    }
}
