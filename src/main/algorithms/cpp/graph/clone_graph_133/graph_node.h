#ifndef GRAPH_CLONE_GRAPH_133_GRAPH_NODE_H
#define GRAPH_CLONE_GRAPH_133_GRAPH_NODE_H

#include "../../head.h"

/*
// Definition for a Node.
*/
class Node {
public:
    int val;
    std::vector<Node*> neighbors;

    Node(); 

    Node(int _val);

    Node(int _val, std::vector<Node*> const & _neighbors);
};
#endif
