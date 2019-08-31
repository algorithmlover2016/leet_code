#include "../../head.h"
#include "../tree.h"

class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        return helper(root).first;
    }
    std::pair<TreeNode*, size_t> helper(TreeNode* root) {
        if (nullptr == root) {
            // return std::make_pair(nullptr, 0);
            return {nullptr, 0};
        }
        auto left = helper(root->left);
        auto right = helper(root->right);
        if (left.second > right.second) {
            return {left.first, left.second + 1};
        } else if (left.second < right.second) {
            return {right.first, right.second + 1};
        } else {
            return {root, left.second};
        }
    }
};

class Solution2 {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
         helper(root, 0);
         return lca;
    }
    size_t helper(TreeNode* root, size_t depth) {
        if (depth > max_deepest) {
            max_deepest = depth;
        }
        if (nullptr == root) {
            // if return depth directly, then the judgement that depth and max_deepest should do first
            // if return depth -1 (the type of depth should be int, not size_t) the judgement can be do later
            return depth;
        }
        size_t left = helper(root->left, depth + 1);
        size_t right = helper(root->right, depth + 1);
        if (left == max_deepest && right == max_deepest) {
            lca = root;
        }
        return std::max(left, right);
    }
private:
    size_t max_deepest = 0;
    TreeNode* lca;
};
