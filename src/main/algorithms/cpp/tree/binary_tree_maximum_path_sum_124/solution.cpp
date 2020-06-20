#include "../../head.h"


class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        dfs(root, res);
        return res;
    }
    int dfs(TreeNode * root, int & maxRes) {
        if (nullptr == root) {
            return INT_MIN;
        }
        int left = dfs(root->left, maxRes);
        int right = dfs(root->right, maxRes);
        int maxSubTree = std::max(left, right);
        if (0 > left) {
            left = 0;
        }
        if (0 > right) {
            right = 0;
        }
        maxRes = std::max(maxRes, std::max(maxSubTree, left + right + root->val));
        return std::max(left, right) + root->val;
    }
};

class SolutionBetterRuntime {
public:
    int ma = INT_MIN;
    int maxPathSum(TreeNode* root) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        if (root == NULL) {
            return 0;
        }
        func(root);
        return ma;
    }

    int func(TreeNode* tmp) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        if (tmp==NULL) {
            return 0;
        }
        int a1 = func(tmp->left), a2 = func(tmp->right);
        int x = std::max(a1, a2);
        int y = std::min(a1, a2);
        if (x < 0) {
            x = tmp->val;
            y = x;
        } else {
            x = tmp->val + x;
            if (y > 0) {
                y = x + y;
            } else {
                y = x;
            }
        }
        if (y > ma) {
            ma = y;
        }
        return x;
    }
};
