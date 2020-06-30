#include "../../head.h"

#include "../singly_linked_list.h"

class Solution {
public:
    ListNode* detectCycle(ListNode *head) {
        if (nullptr == head || nullptr == head->next) {
            return nullptr;
        }
        ListNode * fast = head, * slow = fast;
        while (nullptr != fast && nullptr != fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }
        // if (slow != fast) {
        //     return NULL;
        // }
        // equal to the follow statement
        if (nullptr == fast || nullptr == fast->next) {
            return nullptr;
        }
        fast = head;
        while (slow != fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};
