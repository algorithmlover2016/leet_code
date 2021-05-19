#include "../../head.h"
#include "../tree.h"

#define COMPUTE_RESULT_IN_HELPER_RECURSIVE
class Solution {
public:

    // plagiarizing from https://github.com/grandyang/leetcode/issues/549
#ifdef COMPUTE_RESULT_IN_HELPER_RECURSIVE
    // compute in helper
    int longestConsecutive(TreeNode* root) {
        int ans = 0;
        helper(root, root, ans);
        return ans;
    }
private:
    std::pair<int, int> helper(TreeNode* cur, TreeNode* parent, int & ans) {
        if (nullptr == cur) {
            return std::make_pair(0, 0);
        }
        auto leftAns = helper(cur->left, cur, ans);
        auto rightAns = helper(cur->right, cur, ans);
        // first means the increasing order sequence, second means the decreasing order sequence
        ans = std::max(ans, leftAns.first + rightAns.second + 1);
        ans = std::max(ans, leftAns.second + rightAns.first + 1);
        int inc = 0, dec = 0;
        if (cur->val == parent->val + 1) {
            inc = std::max(leftAns.first, rightAns.first) + 1;
        } else if (cur->val + 1 == parent->val) {
            dec = std::max(leftAns.second, rightAns.second) + 1;
        }
        return std::make_pair(inc, dec); // {inc, dec};
    }
#else
    int longestConsecutive(TreeNode* root) {
        if (nullptr == root) {
            return 0;
        }
        int ans = helper(root, 1) + helper(root, -1) + 1;
        return std::max(ans, std::max(longestConsecutive(root->left), longestConsecutive(root->right)));
    }

private:
    int helper(TreeNode* root, int diff) {
        if (nullptr == root) {
            return 0;
        }
        int left = 0, right = 0;
        if (nullptr != root->left && root->val == root->left->val + diff) {
            left = 1 + helper(root->left, diff);
        }
        if (nullptr != root->right && root->val == root->right->val + diff) {
            right = 1 + helper(root->right, diff);
        }
        return std::max(left, right);

    }


#endif
};

#define TEST_MAIN

#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    Solution obj;
    TreeNode* cur = nullptr;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    cur = root->right;
    cur->left = new TreeNode(7); 
    cur = cur->left;
    cur->left = new TreeNode(6); 
    cur->right = new TreeNode(8); 

    int ans = obj.longestConsecutive(root);
#ifdef PRINT_TO_SCREEN
    std::cout << ans << "\n";
#endif
    assert(ans == 3);
    std::cout << "TEST_SUCCESSFULLY" << std::endl;
    return 0;
}
#endif
