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

class SolutionMinHeap {
protected:
    class MyCompareInNode {
    private:
        bool _reverse;
    public:
        MyCompareInNode(bool reverse = false) : _reverse(reverse) {
        }
        bool operator()(ListNode const * const left, ListNode const * const right) {
            if (nullptr == right) {
                return _reverse;
            }
            if (nullptr == left || left->val <= right->val) {
                return !_reverse;
            } else {
                return _reverse;
            }
        }
    };

public:
    ListNode* mergeKLists(std::vector<ListNode*> & lists) {
        // time complexity
        // Klog(K) + 2NKlog(K), K = lists.size(), K = listsSize
        // first construct a minHeap with size K, need Klog(K)
        // second, all the left element will be push into and pop out of the minHeap, which need 2logK

        if (lists.empty()) {
            return static_cast<ListNode*>(nullptr);
        }

        int const listsSize = lists.size();
        if (JUST_ONE_ELE == listsSize) {
            return lists[0];
        }
        typedef std::priority_queue<ListNode*, std::vector<ListNode*>, MyCompareInNode> Heap;
        Heap minHeap(MyCompareInNode(true));

        ListNode* dummyHead = new ListNode(-1);
        ListNode* cur = dummyHead;
        for (int idx = 0; idx < listsSize; idx++) {
            if (nullptr != lists[idx]) {
                minHeap.push(lists[idx]);
            }
        }
        while (!minHeap.empty()) {
            // find the min ele
            ListNode* next = minHeap.top(); minHeap.pop();
            // add a new ele into minHeap
            if (nullptr != next->next) {
                minHeap.push(next->next);
            }
            // link the min ele to the result list
            cur->next = next;
            cur = cur->next;
        }
        return dummyHead->next;
    }
private:
    static int const JUST_ONE_ELE = 1;
};
