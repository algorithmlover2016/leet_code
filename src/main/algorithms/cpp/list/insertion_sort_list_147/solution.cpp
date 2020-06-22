#include "../../head.h"
#include "../single_linked_list.h"


class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode * dummyHead = new ListNode(0);
        dummyHead->next = head;
        bool exchange = true;
        while (exchange) {
            exchange = false;
            ListNode * pre = dummyHead, *cur = pre->next;
            while (nullptr != cur && nullptr != cur->next) {
                if (cur->val > cur->next->val) {
                    exchange = true;
                    ListNode * next = cur->next->next;
                    cur->next->next = pre->next;
                    pre->next = cur->next;
                    cur->next = next;
                } else {
                    cur = cur->next;
                }
                pre = pre->next;
            }
        }
        return dummyHead->next;
    }
};

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {

        // head means the list need to sort
        // pre->next means the lists already sorted
        // so at beginning, no need to link dummpy and head;
        ListNode* dummy = new ListNode(INT_MIN);
        ListNode* prev = dummy;

        while(head != NULL) {
            ListNode* tmp = head->next;

            if(prev != NULL && prev->val > head->val) {
                // need insert element at head
                prev = dummy;
            }

            while(prev->next != NULL && prev->next->val < head->val) {
                // find the first element that its next is greater or equal to the head->val
                prev = prev->next;
            }

            head->next = prev->next;
            prev->next = head;
            head = tmp;
        }

        return dummy->next;
    }
};
