#include "../../head.h"


class Solution {
public:
    int distributeCoins(TreeNode* root) {
        // plagiarizing from https://www.youtube.com/watch?v=Dny7JhfvJ0o
        int res = 0;
        dfsHelper(root, res);
        return res;
    }
    int dfsHelper(TreeNode* root, int & res) {
        if (nullptr == root) {
            return 0;
        }
        int left = dfsHelper(root->left, res);
        int right = dfsHelper(root->right, res);
        res += std::abs(left) + std::abs(right);
        return root->val + left + right - 1;
    }
};
