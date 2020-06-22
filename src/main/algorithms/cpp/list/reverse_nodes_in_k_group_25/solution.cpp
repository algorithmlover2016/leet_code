#include "../../head.h"
#include "../singly_linked_list.h"


class SolutionRecursive {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // plagiarizing from https://leetcode.com/problems/reverse-nodes-in-k-group/discuss/11423/Short-but-recursive-Java-code-with-comments
        ListNode *cur = head;
        int step = 0;
        while (nullptr != cur && step != k) {
            cur = cur->next;
            step++;
        }
        if (step == k) {
            cur = reverseKGroup(cur, k);
            while (step-- > 0) {
                ListNode *tmp = head->next;
                head->next = cur;
                cur = head;
                head = tmp;
            }
            head = cur;
            // at end, head = recursive cur;
        }
        return head;
    }
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // plagiarizing from https://leetcode.com/problems/reverse-nodes-in-k-group/discuss/11423/Short-but-recursive-Java-code-with-comments
        ListNode *newHead = nullptr, *pre = nullptr;
        ListNode *cur = head;
        while (nullptr != cur) {
            ListNode * reverseHead = cur;
            int step = 0;
            while (nullptr != cur && step != k) {
                cur = cur->next;
                step++;
            }
            if (step == k) { // step = k and cur = nullptr
                ListNode * nextPre = reverseHead;
                // cur = reverseKGroup(cur, k);
                ListNode * tail = cur;
                while (step-- > 0) { // when step = 0, reverseHead = cur;
                    ListNode *tmp = reverseHead->next;
                    // std::cout << "head to end: " << reverseHead->val << "\t";
                    reverseHead->next = tail;
                    // if (tail) {
                    //     std::cout << "tail: " << tail->val << "\t";
                    // }
                    tail = reverseHead;
                    reverseHead = tmp;
                    // std::cout << "head: " << reverseHead->val << "\t";
                }
                // std::cout << "\n";
                if (nullptr == pre) {
                    newHead = tail;
                } else {
                    pre->next = tail;
                }
                pre = nextPre;
                
            }
        }
        return newHead;
    }
};

class SolutionForwardKExchange {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int len = 0;
        for (ListNode * cur = head; cur != nullptr; cur = cur->next) {
            len++;
        }
        ListNode * dummyHead = new ListNode(0);
        dummyHead->next = head;
        for (ListNode * pre = dummyHead, * tail = head; len >= k; len -= k) {
            // step from 1 not 0, because tail already is reversed
            for (int step = 1; step < k; step++) {
                ListNode * next = tail->next->next;
                tail->next->next = pre->next;
                pre->next = tail->next;
                tail->next = next;
            }
            pre = tail;
            tail = tail->next;
        }
        return dummyHead->next;
    }
};
