#ifndef LIST_DLINKED_NODE_H
#define LIST_DLINKED_NODE_H
struct DLinkedNode {
    int key;
    int value;
    DLinkedNode* pre;
    DLinkedNode* next;
    DLinkedNode() : key(0), value(0), pre(nullptr), next(nullptr) {}
    DLinkedNode(int key, int value) : key(key), value(value), pre(nullptr), next(nullptr) {}
}
#endif
