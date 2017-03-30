#include <iostream>
#include <fstream>
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

        void addDocumentStart(stringstream& ss)
        {
            ss  << "\\documentclass{article}\n\n"
                << "\\usepackage{pstricks}\n\n"
                << "\\begin{document}\n"
                << "\\framebox[\\textwidth]{\n\n";
        }

        void addDocumentEnd(stringstream& ss)
        {
            ss  << "\n\n"
                << "}\n"
                << "\\end{document}";
        }

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
            float layerCount = static_cast<float>(tree.layers());
            float marginsY = layerCount > 0 ? getMargin() * (layerCount - 1.0f) : 0.0f;

            float width = tree.width();
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
            ss << "\\end{pspicture}";
        }

        void addIndent(stringstream& ss, Node* node)
        {
            for (unsigned int i = 0 ; i <= node->depth() ; i++) {
                ss << "  ";
            }
        }

        void addNode(const BinaryTree& tree, stringstream& ss, Node* node, bool indent)
        {
            /*
             *  \treenode{cornerX}{cornerY}{nodeWidth}{textX}{content}
             */

            float cornerX = node->x();
            float cornerY = getNodeY(tree, node);
            float nodeWidth = getNodeWidth(node);
            float textX = nodeWidth / 2.0f;

            string content = node->content();

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

            float x1 = a->x() + getNodeWidth(a) / 2.0f;
            float y1 = getNodeY(tree, a) + NODE_HEIGHT / 2.0f;

            float x2 = b->x() + getNodeWidth(b) / 2.0f;
            float y2 = getNodeY(tree, b) + NODE_HEIGHT / 2.0f;

            if (indent) addIndent(ss, b);

            ss << "\\psline{-}(" << x1 << "," << y1 << ")(" << x2 << "," << y2 << ")\n";
        }

        void addNodesRecursive(const BinaryTree& tree, stringstream& ss, Node* node, bool indent)
        {
            for (size_t i = 0 ; i < node->children().size() ; ++i) {
                addConnection(tree, ss, node, node->children()[i], indent);
                addNodesRecursive(tree, ss, node->children()[i], indent);
            }

            addNode(tree, ss, node, indent);
        }
    }

    float getMargin()
    {
        return 0.3f;
    }

    float getNodeWidth(Node* node)
    {
        return 0.5f + 0.2f * static_cast<float>(node->content().length());
    }

    float getNodeY(const BinaryTree& tree, Node* node)
    {
        // TODO throw if depth > count
        float indexFromBottom = static_cast<float>(tree.layers() - node->depth());
        return indexFromBottom * NODE_HEIGHT
                + (indexFromBottom - 1.0f) * getMargin();
    }

    bool setExportDirectory(const string& path)
    {
        directoryPath = path;
        return true;
    }

    bool exportTreeToFile(const BinaryTree& tree,
                          const string& filename,
                          bool indent /*= false*/,
                          bool wrapDocument /*= false*/)
    {
        ofstream file;
        file.open(filename);

        if (!file.is_open()) {
            cerr << "Unable to open file " << filename;
            return false;
        }

        bool success = exportTreeToOutput(tree, file, indent, wrapDocument);

        file.close();

        return success;
    }

    bool exportTreeToConsole(const BinaryTree& tree,
                             bool indent /*= false*/,
                             bool wrapDocument /*= false*/)
    {
        return exportTreeToOutput(tree, cout, indent, wrapDocument);
    }

    bool exportTreeToOutput(const BinaryTree& tree,
                            ostream& out,
                            bool indent /*= false*/,
                            bool wrapDocument /*= false*/)
    {
        stringstream ss;

        if (wrapDocument) addDocumentStart(ss);

        addHeader(tree, ss);

        if (tree.root()) {
            addNodesRecursive(tree, ss, tree.root(), indent);
        }

        addFooter(ss);

        if (wrapDocument) addDocumentEnd(ss);

        out << ss.str() << endl;
        return true;
    }
}
