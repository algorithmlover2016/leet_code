#ifdef LIST_RANDLINKED_NODE_H
#define LIST_RANDLINKED_NODE_H
#include "../head.h"
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
#endif
