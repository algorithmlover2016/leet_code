#include "../../header.h"
#inlcude "../tree.h"

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        inorderTraversal(root, k);
        return target;
    }
    void  inorderTraversal(TreeNode* root, int k) {
        if (nullptr == root || INT_MAX != target) {
            return;
        }
        inorderTraversal(root->left, k);
        order++;
        if (order == k) {
            target = root->val;
        }
        inorderTraversal(root->right, k);
    }

    private:
    int target = INT_MAX;
    int order;
};

class Solution_smart {
public:
    void helper(TreeNode* root, int& k, int& res) {
        if (k < 0 || root == nullptr) return;
        helper(root->left, k, res);
        if (--k == 0) {
            res = root->val;
        }
        helper(root->right, k, res);
    }
    
    int kthSmallest(TreeNode* root, int k) {
        int res = 0;
        helper(root, k, res);
        return res;
    }
};

