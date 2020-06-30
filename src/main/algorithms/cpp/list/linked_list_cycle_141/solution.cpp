#include "../../head.h"


class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (nullptr == head || nullptr == head->next) {
            return false;
        }
        ListNode * fast = head, * slow = fast;
        while (nullptr != fast && nullptr != fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }
        if (slow != fast) {
            return false;
        }
        return true;
    }
};
