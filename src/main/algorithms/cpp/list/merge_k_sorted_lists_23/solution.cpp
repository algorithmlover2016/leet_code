#include "../../head.h"
#include "../singly_linked_list.h"


class SolutionNKK {
public:
    ListNode* mergeKLists(std::vector<ListNode*> & lists) {
        int listsSize = lists.size();
        if (0 == listsSize) {
            return static_cast<ListNode*>(nullptr);
        }
        if (1 == listsSize) {
            return lists[0];
        }
        ListNode* head = new ListNode(0);
        ListNode* cur = head;
        int curMinIndex = 0;
        bool next = true;
        while (next)  {
            next = false;
            for (int index = 0; index < lists.size(); index++) {
                if (nullptr != lists[index]) {
                    if (nullptr == cur->next) {
                        cur->next = lists[index];
                        curMinIndex = index;
                        // std::cout << "next null: " << curMinIndex << "\t" << cur->next->val << "\t";
                    } else if (cur->next->val > lists[index]->val) {
                        cur->next = lists[index];
                        curMinIndex = index;
                        // std::cout << "greater: " << curMinIndex << "\t" << cur->next->val << "\n";
                    }
                    next = true;
                }
            }
            // std::cout << curMinIndex << "\tcurVal: " << cur->val << "\n";
            cur = cur->next;
            if (next) {
                lists[curMinIndex] = lists[curMinIndex]->next;
                // can be set nullptr only when next = true and update lists[curMinIndex]
                // set to nullptr for the stable order which means if lists[i]->val = lists[j]->val
                // then i is before j
                // cur->next = nullptr;

            }
        }
        return head->next;

    }
};

class SolutionNlgK {
public:
    ListNode* mergeKLists(std::vector<ListNode*> & lists) {
        return merge_lists(lists, 0, lists.size()-1);
    }
private:
    ListNode* merge_lists(std::vector<ListNode*> & lists, int start, int end) {
        if(start > end) return nullptr;
        if(start == end) return lists[start];

        int mid = (start+end)/2;
        ListNode* l1 = merge_lists(lists, start, mid);
        ListNode* l2 = merge_lists(lists, mid+1, end);

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
