#include "../../head.h"


class SolutionBFS {
public:
    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> res;
        if (nullptr == root) {
            return res;
        }
        std::queue<TreeNode*> todo;
        todo.emplace(root);
        int layerSize = 0;
        while (layerSize = todo.size()) {
            bool first = true;
            while (layerSize--) {
                TreeNode* cur = todo.front(); todo.pop();
                if (first) {
                    res.emplace_back(cur->val);
                    first = false;
                }
                if (nullptr != cur->right) {
                    todo.emplace(cur->right);
                }
                if (nullptr != cur->left) {
                    todo.emplace(cur->left);
                }
            }
        }
        return res;
    }
};

class Solution {
public:
    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> res;
        dfsHelper(root, 0, res);
        return res;
    }
    void dfsHelper(TreeNode* root, int height, std::vector<int> & res) {
        if (nullptr == root) {
            return;
        }
        if (height == res.size()) {
            res.emplace_back(root->val);
        } else {
            res[height] = root->val;
        }
        dfsHelper(root->left, height + 1, res);
        dfsHelper(root->right, height + 1, res);
    }
};
