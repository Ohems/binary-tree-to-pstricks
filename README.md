# Binary Tree to PSTricks

Binary Tree to PSTricks is an application written in C++ that takes in binary trees in JSON format and outputs LaTeX documents where the binary tree is drawn using PSTricks.

 - [PSTricks web page](http://tug.org/PSTricks/main.cgi)
 - [Binary tree algorithm](https://llimllib.github.io/pymag-trees/)

Libraries used:
 - [JSON for Modern C++](https://github.com/nlohmann/json)

BTPST has been designed and tested with binary trees in mind, but also features untested support for N-trees. This is because the underlying system doesn't really care about the node child counts and all algorithms used in the project should work with N-trees as well.

BTPST has been developed an exercise for a course at the Technical University of Tampere and the developers offer no support or functioning guarantees for the code. Use at your own risk.