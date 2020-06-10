#include "./graph_node.h"

Node::Node() : val(0),
 neighbors(std::vector<Node*>()) {
    
}

Node::Node(int _val) : val(_val),
 neighbors(std::vector<Node*>()) {
}

Node::Node(int _val, std::vector<Node*> const & _neighbors): val(_val),
 neighbors(_neighbors) {
}
