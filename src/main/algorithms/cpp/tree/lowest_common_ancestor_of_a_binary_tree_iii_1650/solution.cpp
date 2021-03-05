#include "../../head.h"
#include "../tree.h"

// #define DEBUG
class Solution {
public:
    PTreeNode* lowestCommonAncestor(PTreeNode * p, PTreeNode * q) {
        std::unordered_set<PTreeNode*> seen;
        while (nullptr != p) {
#ifdef DEBUG
            std::cout << " p insert: " << p->val << "\t";
#endif
            seen.insert(p);
            p = p->parent;
        }
        while (nullptr != q) {
            if (seen.find(q) != seen.end()) {
                return q;
            }
            q = q->parent;
        }
        return nullptr;
    }
};

class SolutionDeg {
public:
    PTreeNode* lowestCommonAncestor(PTreeNode * p, PTreeNode * q) {
        int degP = 0, degQ = 0;
        while (nullptr != p) {
            degP++;
            p = p->parent;
        }
        while (nullptr != q) {
            degQ++;
            q = q->parent;
        }
        if (degP > degQ) {
            std::swap(p, q);
        }
        for (int upStep = 0; upStep < degQ - degP; upStep++) {
            q = q->parent;
        }
        while (p != q) {
            p = p->parent;
            q = q->parent;
        }
        return p;
    }
};

#define TEST_MAIN
#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    // Test Cases
    PTreeNode* p = nullptr;
    PTreeNode* q = nullptr;
    int const pVal = 5;
    int const qVal = 1;
    int const ancessor = 3;

    std::vector<int> nums{{3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4}};
    std::queue<PTreeNode*> que;
    PTreeNode* root = new PTreeNode(nums[0]);
    if (pVal == root->val) {
        p = root;
    } else if (qVal == root->val) {
        q = root;
    }
    que.emplace(root);
    int idx = 1;
    while (idx < nums.size()) {
        PTreeNode* cur = que.front(); que.pop();
        cur->left = new PTreeNode(nums[idx++]);
        cur->left->parent = cur;

        if (pVal == cur->left->val) {
            p = cur->left;
        } else if (qVal == cur->left->val) {
            q = cur->left;
        }

#ifdef DEBUG
        std::cout << cur->left->val << "\t" << cur->left->parent->val << " left\n";
#endif
        que.emplace(cur->left);
        cur->right = new PTreeNode(nums[idx++]);
        cur->right->parent = cur;
        if (pVal == cur->right->val) {
            p = cur->right;
        } else if (qVal == cur->right->val) {
            q = cur->right;
        }
#ifdef DEBUG
        std::cout << cur->right->val << "\t" << cur->right->parent->val << " right\n";
#endif
        que.emplace(cur->right);
    }



    Solution obj;
    PTreeNode* ans = obj.lowestCommonAncestor(p, q);
#ifdef PRINT_TO_SCREEN
    std::cout << p->val << ", " << q->val << " lca: " << (nullptr != ans ? ans->val : -1) << "\n";
#endif
    assert(ans->val == ancessor);

    SolutionDeg objDeg;
    ans = obj.lowestCommonAncestor(p, q);
#ifdef PRINT_TO_SCREEN
    std::cout << p->val << ", " << q->val << " lca: " << (nullptr != ans ? ans->val : -1) << "\n";
#endif
    assert(ans->val == ancessor);

    std::cout << "TEST SUCCESSFULY" << std::endl;
    return 0;
}
#endif
