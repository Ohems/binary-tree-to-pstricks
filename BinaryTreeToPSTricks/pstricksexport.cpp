#include <iostream>
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

        void addHeader(stringstream& ss, BinaryTree& tree)
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
            float countY = static_cast<float>(tree.getLayerCount());
            float marginsY = tree.getLayerCount() > 1 ? getMargin() * (countY - 1.0f) : 0.0f;

            float width = tree.getWidth();
            float height = NODE_HEIGHT * countY + marginsY;

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

        void addNode(stringstream& ss, Node* node, bool indent)
        {
            /*
             *  \treenode{cornerX}{cornerY}{nodeWidth}{textX}{content}
             */

            float cornerX = node->getX();
            float cornerY = getNodeY(node);
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

        void addConnection(stringstream& ss, Node* a, Node* b, bool indent)
        {
            /*
             *  \psline{-}(x1,y1)(x2,y2)
             */

            float x1 = a->getX() + getNodeWidth(a) / 2.0f;
            float y1 = getNodeY(a) + NODE_HEIGHT / 2.0f;

            float x2 = b->getX() + getNodeWidth(b) / 2.0f;
            float y2 = getNodeY(b) + NODE_HEIGHT / 2.0f;

            if (indent) addIndent(ss, b);

            ss << "\\psline{-}(" << x1 << "," << y1 << ")(" << x2 << "," << y2 << ")\n";
        }

        void addNodesRecursive(stringstream& ss, Node* node, bool indent)
        {
            for (size_t i = 0 ; i < node->getChildren().size() ; ++i) {
                addConnection(ss, node, node->getChildren()[i], indent);
                addNodesRecursive(ss, node->getChildren()[i], indent);
            }

            addNode(ss, node, indent);
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

    float getNodeY(Node* node)
    {
        return (node->getDepth() + 1) * NODE_HEIGHT + node->getDepth() * getMargin();
    }

    bool setExportDirectory(const string& path)
    {
        directoryPath = path;
        return true;
    }

    bool exportTreeToFile(BinaryTree& tree, const string& filename,
                          bool indent /*= false*/, bool wrapDocument /*= false*/)
    {
        cout << "Tree exporting not yet ready, nothing done and returning true" << endl;
        return true;
    }

    bool exportTreeToConsole(BinaryTree& tree, bool indent /*= false*/,
                             bool wrapDocument /*= false*/)
    {
        cout << "Tree exporting not yet ready, expect weird results!" << endl << endl;

        stringstream ss;

        addHeader(ss, tree);

        if (tree.getRootNode()) {
            addNodesRecursive(ss, tree.getRootNode(), indent);
        }

        addFooter(ss);

        cout << ss.str() << endl;
        return true;
    }
}
