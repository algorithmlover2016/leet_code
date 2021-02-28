#include "../../head.h"
#include "../randlinked_node.h"


class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (nullptr == head) {
            return head;
        }
        Node* newHead = new Node(0);
        std::unordered_map<Node*, Node*> randPointer;
        Node* cur = newHead;
        Node* old = head;
        while (nullptr != old) {
            cur->next = new Node(old->val);
            cur->next->random = old->random;
            randPointer[old] = cur->next;
            cur = cur->next;
            old = old->next;
        }
        cur = newHead->next;
        while (nullptr != cur) {
            if (nullptr != cur->random) {
                cur->random = randPointer[cur->random];
            }
            cur = cur->next;
        }
        return newHead->next;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return head;
        }
        Node* current = head;
        Node* temp;

        while (current != nullptr) {
            temp = current->next;
            // add a new deep copy node and its random is nullptr
            current->next = new Node(current->val, nullptr, nullptr);
            current->next->next = temp;
            current = temp;
        }

        current = head;

        while (current) {
            if (current->next && current->random) {
                /*it's not a copy node and it's random not be empty*/
                current->next->random = current->random->next;
            }
            // each time take two step, unless untill to end end(nullptr);
            current = current->next ? current->next->next : current->next;
        }

        Node* old_node = head;
        Node* new_node = head->next;
        Node* new_head = head->next;

        while (old_node != nullptr && new_node != nullptr) {
            old_node->next = old_node->next != nullptr ? old_node->next->next : old_node->next;
            new_node->next = new_node->next != nullptr ? new_node->next->next : new_node->next;

            old_node = old_node->next;
            new_node = new_node->next;
        }

        return new_head;
    }
};
