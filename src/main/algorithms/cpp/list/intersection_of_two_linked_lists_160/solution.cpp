#include "../../head.h"
#include "../singly_linked_list.h"


class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (nullptr == headA || nullptr == headB) {
            return nullptr;
        }
        int ASize = getListLen(headA);
        int BSize = getListLen(headB);
        if (ASize < BSize) {
            // tmpA will always be the longer list
            std::swap(headA, headB);
            std::swap(ASize, BSize);
        }
        ListNode *tmpA = headA;
        ListNode *tmpB = headB;
        int diff = ASize - BSize;
        while (diff-- > 0) {
            headA = headA->next;
        }
        while (nullptr != headA && nullptr != headB && headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }
private:
    int getListLen(ListNode *head) {
        int size = 0;
        while (nullptr != head) {
            size++;
            head = head->next;
        }
        return size;
    }
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (nullptr == headA || nullptr == headB) {
            return nullptr;
        }
        ListNode *curA = headA;
        ListNode *curB = headB;
        // just need to judge curA != curB; even they are all empty, which means there is no intersection
        while (curA != curB) {
            curA = (nullptr == curA) ? headB : curA->next;
            curB = (nullptr == curB) ? headA : curB->next;
        }
        return curA;
    }
};
