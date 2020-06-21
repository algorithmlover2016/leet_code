#include "../../head.h"
#include "../singly_linked_list.h"


class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // plagiarizing from https://leetcode.com/problems/sort-list/discuss/46714/Java-merge-sort-solution
        if (nullptr == head || nullptr == head->next) {
            return head;
        }
        ListNode* pre = nullptr, * slow = head, * fast = head;
        while (nullptr != fast && nullptr != fast->next) {
            pre = slow; // record the previous element;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = nullptr;
        ListNode* l1 = sortList(head);
        ListNode* l2 = sortList(slow);
        return mergeTwoLists(l1, l2);
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode pre_head(-1);
        ListNode* node = &pre_head;
        while(l1 && l2) {
            if(l1->val < l2->val) {
                node->next = l1;
                l1 = l1->next;
            } else {
                node->next = l2;
                l2 = l2->next;
            }
            node = node->next;
        }
        node->next = (nullptr == l2) ? l1 : l2;
        return pre_head.next;
    }
};
