#include "../../head.h"


class Solution {
public:
    std::vector<int> flipMatchVoyage(TreeNode* root, std::vector<int> const & voyage) {
        // plagiarizing from https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/discuss/214216/JavaC%2B%2BPython-DFS-Solution
        std::vector<int> ans;
        int idx = 0;
        if (dfsPreorder(root, voyage, idx, ans)) {
            return ans;
        }
        return {-1};
    }
    // set idx with reference
    bool dfsPreorder(TreeNode * root, std::vector<int> const & voyage, int & idx, std::vector<int> & ans) {
        if (nullptr == root) {
            return true;
        }

        if (root->val != voyage[idx++]) {
            return false;
        }

        if (nullptr != root->left && root->left->val != voyage[idx]) {
            ans.emplace_back(root->val);
            return dfsPreorder(root->right, voyage, idx, ans) && dfsPreorder(root->left, voyage, idx, ans);
        }
        return dfsPreorder(root->left, voyage, idx, ans) && dfsPreorder(root->right, voyage, idx, ans);
    }
};


class Solution {
public:
    std::vector<int> flipMatchVoyage(TreeNode* root, std::vector<int> const & voyage) {
        // plagiarizing from https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/discuss/214384/JavaC%2B%2BPython-Iterative-Solution-Using-Stack
        std::vector<int> ans;
        std::stack<TreeNode* > rootStack;
        rootStack.emplace(root);
        int idx = 0;
        while (!rootStack.empty()) {
            TreeNode * curRoot = rootStack.top();
            rootStack.pop();
            if (nullptr == curRoot) {
                continue;
            }
            if (voyage[idx++] != curRoot->val) {
                return std::vector<int>{-1};
            }
            if (nullptr != curRoot->right && curRoot->right->val == voyage[idx]) {
                if (nullptr != curRoot->left) {
                    ans.emplace_back(curRoot->val);
                }
                rootStack.emplace(curRoot->left);
                rootStack.emplace(curRoot->right);
            } else {
                rootStack.emplace(curRoot->right);
                rootStack.emplace(curRoot->left);
            }
        }
        return ans;
    }
};

class SolutionBetter {
public:
    std::vector<int> flipMatchVoyage(TreeNode* root, std::vector<int> const & voyage) {
        // plagiarizing from https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/discuss/214384/JavaC%2B%2BPython-Iterative-Solution-Using-Stack
        std::vector<int> ans;
        std::stack<TreeNode* > rootStack;
        rootStack.emplace(root);
        int idx = 0;
        while (!rootStack.empty()) {
            TreeNode * curRoot = rootStack.top();
            rootStack.pop();
            if (nullptr == curRoot) {
                continue;
            }
            if (voyage[idx++] != curRoot->val) {
                return std::vector<int>{-1};
            }
            if (nullptr != curRoot->left && curRoot->left->val != voyage[idx]) {
                ans.emplace_back(curRoot->val);
                rootStack.emplace(curRoot->left);
                rootStack.emplace(curRoot->right);
            } else {
                rootStack.emplace(curRoot->right);
                rootStack.emplace(curRoot->left);
            }
        }
        return ans;
    }
};
