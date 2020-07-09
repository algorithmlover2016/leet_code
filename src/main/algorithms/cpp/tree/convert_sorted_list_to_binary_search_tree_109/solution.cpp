#include "../../head.h"


class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return recursiveTraversal(head);
    }
    TreeNode* recursiveTraversal(ListNode* head = nullptr) {
        // empty
        if (nullptr == head) {
            return nullptr;
        }

        // only one ListNode.
        if (nullptr == head->next) {
            return new TreeNode(head->val);
        }

        // at least two listNdoe
        ListNode * fast = head, * slow = fast, * preSlow = nullptr;
        while (nullptr != fast && nullptr != fast->next) {
            fast = fast->next->next;
            preSlow = slow;
            slow = slow->next;
        }
        TreeNode * root = new TreeNode(slow->val);
        preSlow->next = nullptr;
        root->left = recursiveTraversal(head);
        root->right = recursiveTraversal(slow->next);
        return root;
    }

};

class SolutionWithOutChange {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return recursiveTraversal(head, nullptr);
    }
    TreeNode* recursiveTraversal(ListNode* head, ListNode * const end = nullptr) {
        if (end == head) {
            return nullptr;
        }

        ListNode * fast = head, * slow = fast;
        while (end != fast && end != fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        TreeNode * root = new TreeNode(slow->val);
        root->left = recursiveTraversal(head, slow);
        root->right = recursiveTraversal(slow->next, end);
        return root;
    }
};

class SolutionSame {
public:
    ListNode *start,*end;
    ListNode *find(ListNode *start,ListNode *end) {
        ListNode *slow = start,*fast = start;
        while (slow != end &&fast != end && fast->next != end) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    TreeNode* con(ListNode *start,ListNode *end) {
        TreeNode *root=NULL;
        if (start == end) {
            return root;
        }
        ListNode *mid = find(start,end);
        root = new TreeNode(mid->val);
        root->left = con(start, mid);
        root->right = con(mid->next, end);
        return root;

    }
    TreeNode* sortedListToBST(ListNode* head) {
        start=head, end=NULL;
        return con(start,end);
    }
};
