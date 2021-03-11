#include "../../head.h"


class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (nullptr == head || nullptr == head->next) {
            return head;
        }
        ListNode* pre = head;
        ListNode* cur = head->next;
        while (nullptr != cur) {
            ListNode* tmp = nullptr;
            if (pre->val == cur->val) {
                pre->next = cur->next;
                tmp = cur;
            } else {
                pre = pre->next;
            }
            cur = cur->next;
            if (nullptr != tmp) {
                delete tmp;
                tmp = nullptr;
            }
        }
        return head;
    }
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // limit judge
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *curr = head;

        do {
            ListNode * tmp = nullptr;
            if (curr->val == curr->next->val) {
                tmp = cur->next;
                curr->next = curr->next->next;
            } else {
                curr = curr->next;
            }
            if (nullptr != tmp) {
                delete tmp;
                tmp = nullptr;
            }
        } while (curr->next != nullptr);

        return head;
    }
};
