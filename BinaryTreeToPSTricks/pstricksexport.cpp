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

        bool indent_ = false;
        bool wrapDocument_ = false;
        bool showThreads_ = false;
        bool escapeSpecialCharacters_ = true;

        string targetFile_ = "";

        float treeHeight(const BinaryTree& tree) {
            float layerCount = static_cast<float>(tree.layers());
            float marginsY = layerCount > 0 ? margin() * (layerCount - 1.0f) : 0.0f;

            return NODE_HEIGHT * layerCount + marginsY;
        }

        string escapeContent(const string& input) {
            /*
             * BEFORE YOU EDIT:
             * The code below assumes that all characters to be escaped
             * are exactly one character long. Change the algorithm
             * if this is not the case.
             */

            string escapes[] = {
                "&", "\\&",
                "%", "\\%",
                "$", "\\$",
                "#", "\\#",
                "_", "\\_",
                "{", "\\{",
                "}", "\\}",
                "~", "\\textasciitilde{}",
                "^", "\\textasciicircum{}",
                "\\", "\\textbackslash{}"
            };

            size_t elements = sizeof(escapes)/sizeof(escapes[0]);

            stringstream ss;

            bool match;

            for(const char& c : input) {
                match = false;

                for(size_t i = 0 ; i < elements ; i += 2) {
                    if (c == escapes[i].at(0)) {
                        ss << escapes[i + 1];

                        match = true;
                        break;
                    }
                }

                if (!match) {
                    ss << c;
                }
            }

            return ss.str();
        }

        void addDocumentStart(stringstream& ss)
        {
            ss  << "\\documentclass{article}\n\n"
                << "\\usepackage{pstricks}\n\n"
                << "\\begin{document}\n"
                << "\\framebox{\n\n";
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

            float width = tree.width();
            float height = treeHeight(tree);

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

        void addNode(const BinaryTree& tree, stringstream& ss, Node* node)
        {
            /*
             *  \treenode{cornerX}{cornerY}{nodeWidth}{textX}{content}
             */

            float cornerX = node->x();
            float cornerY = nodeY(tree, node);
            float width = nodeWidth(node);
            float textX = width / 2.0f;

            string content = node->content();
            if (escapeSpecialCharacters_) content = escapeContent(content);

            if (indent_) addIndent(ss, node);

            ss   << "\\treenode{"
                 << cornerX << "}{" << cornerY << "}{"
                 << width << "}{"
                 << textX << "}{"
                 << content
                 << "}\n";
        }

        void addConnection(
                const BinaryTree& tree,
                stringstream& ss,
                Node* a, Node* b,
                bool dashed = false
        ) {
            /*
             *  \psline{-}(x1,y1)(x2,y2)
             */

            float x1 = a->x() + nodeWidth(a) / 2.0f;
            float y1 = nodeY(tree, a) + NODE_HEIGHT / 2.0f;

            float x2 = b->x() + nodeWidth(b) / 2.0f;
            float y2 = nodeY(tree, b) + NODE_HEIGHT / 2.0f;

            if (indent_) addIndent(ss, b);

            ss << "\\psline";

            if (dashed) {
                ss << "[linestyle=dashed,dash=3pt 3pt]";
            }

            ss << "{-}(" << x1 << "," << y1
               << ")(" << x2 << "," << y2 << ")\n";
        }

        void addNodesRecursive(
                const BinaryTree& tree,
                stringstream& nodeStream,
                stringstream& connectionStream,
                Node* node
        ) {
            addNode(tree, nodeStream, node);

            if (node->thread() && showThreads_) {
                addConnection(tree, connectionStream, node, node->thread(), true);
            }

            for (Node* child : node->children()) {
                addConnection(tree, connectionStream, node, child);
                addNodesRecursive(tree, nodeStream, connectionStream, child);
            }
        }
    }

    float margin()
    {
        return 0.3f;
    }

    float nodeWidth(Node* node)
    {
        return 0.5f + 0.17f * static_cast<float>(node->content().length());
    }

    float nodeY(const BinaryTree& tree, Node* node)
    {
        // TODO throw if depth > count
        float indexFromBottom = static_cast<float>(tree.layers() - node->depth() - 1);
        return indexFromBottom * NODE_HEIGHT
                + indexFromBottom * margin();
    }

    void indent(bool value) { indent_ = value; }

    void wrapDocument(bool value) { wrapDocument_ = value; }

    void showThreads(bool value) { showThreads_ = value; }

    void escapeSpecialCharacters(bool value) { escapeSpecialCharacters_ = value; }

    void targetFile(std::string value) { targetFile_ = value; }

    bool exportTree(const BinaryTree& tree)
    {
        if (targetFile_.empty()) {
            return exportTreeToOutput(tree, cout);
        }

        ofstream file;
        file.open(targetFile_);

        if (!file.is_open()) {
            cerr << "Unable to open file " << targetFile_;
            return false;
        }

        bool success = exportTreeToOutput(tree, file);

        file.close();

        return success;
    }

    bool exportTreeToOutput(const BinaryTree& tree, ostream& out)
    {
        stringstream ss;

        ss << '\n';

        if (wrapDocument_) addDocumentStart(ss);

        addHeader(tree, ss);

        {
            stringstream nodeStream;
            stringstream connectionStream;

            if (tree.root()) {
                addNodesRecursive(tree, nodeStream, connectionStream, tree.root());
            }

            ss << connectionStream.str() << nodeStream.str();
        }

        addFooter(ss);

        if (wrapDocument_) addDocumentEnd(ss);

        out << ss.str() << endl;
        return true;
    }
}
