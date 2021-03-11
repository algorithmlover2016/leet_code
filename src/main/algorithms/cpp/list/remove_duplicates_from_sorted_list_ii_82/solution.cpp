#include "../../head.h"


// #define DEBUG
#define DELETE_REMOVE_NODE_MEMORY
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (nullptr == head || nullptr == head->next) {
            return head;
        }
        ListNode* pre = new ListNode(-1000);
        pre->next = head;

        ListNode* cur = head;
        ListNode* ans = pre;

        int preVal = pre->val;

        #ifdef DELETE_REMOVE_NODE_MEMORY
        ListNode * tmp = nullptr;
        #endif
        while (nullptr != cur) {
            #ifdef DEBUG
            std::cout << preVal << "\t";
            #endif
            if (cur->val == preVal || (nullptr != cur->next && cur->val == cur->next->val)) {
                #ifdef DEBUG
                std::cout << "need remove: " << cur->val << "\t";
                #endif
                pre->next = cur->next;
                #ifdef DEBUG
                std::cout << "need remove: " << pre->next->val << "\t";
                #endif
                #ifdef DELETE_REMOVE_NODE_MEMORY
                tmp = cur;
                #endif
            } else {
                pre = pre->next;
            }
            preVal = cur->val;
            cur = cur->next;

            #ifdef DELETE_REMOVE_NODE_MEMORY
            if (nullptr != tmp) {
                delete tmp;
                tmp = nullptr;
            }
            #endif
        }
        return ans->next;
    }
};

// #define DELETE_REMOVE_NODE_MEMORY
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // no delete memory operation, so there will exists memory leak
        if (!head || !head->next) {
            return head;
        }

        ListNode *dummy = new ListNode(-1), *pre = dummy;
        dummy->next = head;

        while(pre->next) {
            ListNode *cur = pre->next;

            while (cur->next && cur->next->val == cur->val) {
                ListNode* tmp = cur;
                cur = cur->next;
                #ifdef DELETE_REMOVE_NODE_MEMORY
                delete tmp;
                tmp = nullptr;
                #endif
            }

            if (cur != pre->next) {
                pre->next = cur->next;
                #ifdef DELETE_REMOVE_NODE_MEMORY
                delete cur;
                cur = nullptr;
                #endif
            } else {
                pre = pre->next;
            }
        }
        return dummy->next;
    }
};
