#include "../../head.h"
#include "tree.h"
class Solution_with_flag {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        for (size_t index = 0; index < to_delete.size(); index++) {
            to_delete_nums.emplace(to_delete[index]);
        }
        dfs(root, true);
        return res;
    }
    TreeNode* dfs(TreeNode* root, bool is_root) {
        if (nullptr == root) {
            return nullptr;
        }
        bool deleted = (to_delete_nums.find(root->val) != to_delete_nums.end());
        if (is_root && !deleted) {
            res.emplace_back(root);
        }
        root->left = dfs(root->left, deleted);
        root->right = dfs(root->right, deleted);
        return deleted ? nullptr : root;
    }
private:
    std::set<int> to_delete_nums;
    std::vector<TreeNode*> res;
};

class Solution_without_flag {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        for (size_t index = 0; index < to_delete.size(); index++) {
            to_delete_nums.emplace(to_delete[index]);
        }
        dfs(root);
        return res;
    }
    TreeNode* dfs(root) {
        if (nullptr == root) {
            return nullptr;
        }
        root->left = dfs(root->left);
        root->right = dfs(root->right);
        if (to_delete_nums.end() != to_delete_nums.find(root->val)) {
            if (nullptr != root->left) {
                res.emplace_back(root->left);
            }
            if (nullptr != root->right) {
                res.emplace_back(root->right);
            }
            // need free the root's roomspace
            return nullptr;
        }
        return root;
    }

private:
    std::set<int> to_delete_nums;
    std::vector<TreeNode*> res;
};
