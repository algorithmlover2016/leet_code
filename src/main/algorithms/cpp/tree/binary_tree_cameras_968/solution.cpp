#include "../../head.h"
#include "../tree.h"

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        if (nullptr == root) {
            return 0;
        }

        int res = 0;
        dfs(root, res);
        if (0 == root->val) {
            res++;
        }
        return res;
    }

    TreeNode* dfs(TreeNode* root, int & res) {
        if (nullptr == root) {
            return nullptr;
        }
        TreeNode* left = dfs(root->left, res);
        TreeNode* right = dfs(root->right, res);

        if (nullptr == left && nullptr == right) {
            return root;
        } else if (nullptr == left) {
            if (1 == right->val) {
                root->val = 2;
            } else if (0 == right->val) {
                root->val = 1;
                res++;
            }
        } else if (nullptr == right) {
            if (1 == left->val) {
                root->val = 2;
            } else if (0 == left->val) {
                root->val = 1;
                res++;
            }
        } else {
            if (0 == left->val || 0 == right->val) {
                root->val = 1;
                res++;
            } else if (1 == left->val || 1 == right->val) {
                root->val = 2;
            }
        }
        return root;

    }
};

class SolutionBetter {
private:
    int cams = 0;
    int solver(TreeNode* root) {
        if(!root) {
            return 0;
        }
        int l = solver(root->left), r = solver(root->right);
        if(l == 0 && r == 0) {
            return 1;
        } else if(l == 1 || r == 1) {
            cams++;
            return -1;
        }
        return 0;
    }
public:
    int minCameraCover(TreeNode* root) {
        int x = solver(root);
        return cams + (x == 1);
    }
};
