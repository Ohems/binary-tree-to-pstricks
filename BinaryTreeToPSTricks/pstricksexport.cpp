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
            float countY = (float) tree.getLayerCount();
            float marginsY = tree.getLayerCount() > 1 ? getMargin() * (countY - 1.0f) : 0.0f;

            float width = tree.getWidth();
            float height = NODE_HEIGHT * countY + marginsY;

            ss << "\\begin{pspicture}(" << width << "," << height << ")\n";
        }

        void addFooter(stringstream& ss)
        {
            ss << "\\end{pspicture}\n";
        }

        void addIndent(stringstream& ss, Node* node)
        {
            for (int i = 0 ; i < node->getY() ; i++) {
                ss << "  ";
            }
        }

        void addNode(stringstream& ss, Node* node, bool indent)
        {
            /*
             * \rput(centerX,centerY){
             *     \rput(nodeX,nodeY){
             *         \psframe[framearc=1](0,0)(nodeWidth,nodeHeight)
             *     }
             *     \rput(textX,textY){content}
             * }
             */

            float centerX = 0;
            float centerY = 0;
            float nodeX = 0;
            float nodeY = 0;
            float nodeWidth = getNodeWidth(node);
            float nodeHeight = NODE_HEIGHT;
            float textX = 0;
            float textY = 0;

            string content = node->getContent();

            if (indent) addIndent(ss, node);

            ss   << "\\rput(" << centerX << "," << centerY << "){"
                    << "\\rput(" << nodeX << "," << nodeY << "){"
                        << "\\psframe[framearc=1](0,0)(" << nodeWidth << "," << nodeHeight << ")"
                    << "}"
                    << "\\rput(" << textX << "," << textY << "){" << content << "}"
                << "}\n";
        }

        void addConnection(stringstream& ss, Node* a, Node* b, bool indent)
        {
            /*
             * \psline{-}(x1,y1)(x2,y2)
             */

            float x1 = 0;
            float y1 = 0;
            float x2 = 0;
            float y2 = 0;

            if (indent) addIndent(ss, b);

            ss << "\\psline{-}(" << x1 << "," << y1 << ")(" << x2 << "," << y2 << ")\n";
        }

        void addNodesRecursive(stringstream& ss, Node* node, bool indent)
        {
            addNode(ss, node, indent);

            for (int i = 0 ; i < node->getChildren().size() ; ++i) {
                addConnection(ss, node, node->getChildren()[i], indent);
                addNodesRecursive(ss, node->getChildren()[i], indent);
            }
        }
    }

    float getMargin()
    {
        return 0.7f;
    }

    float getNodeWidth(Node* node)
    {
        return 0.5f + 0.2f * (float) node->getContent().length();
    }

    bool setExportDirectory(const string& path)
    {
        directoryPath = path;
        return true;
    }

    bool exportTreeToFile(BinaryTree& tree, const string& filename,
                          bool indent /*= true*/, bool wrapDocument /*= false*/)
    {
        cout << "Tree exporting not yet ready, nothing done and returning true" << endl;
        return true;
    }

    bool exportTreeToConsole(BinaryTree& tree, bool indent /*= true*/)
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
