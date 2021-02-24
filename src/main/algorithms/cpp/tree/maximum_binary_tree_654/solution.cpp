#include "../../head.h"


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(std::vector<int> const & nums) {
        std::vector<TreeNode*> st;

        for (int i = 0; i < nums.size(); ++i) {
            TreeNode* new_node = new TreeNode(nums[i]);
            TreeNode* left_max = nullptr;

            while (!st.empty() && st.back()->val < nums[i]) {
                left_max = st.back();
                st.pop_back();
            }

            new_node->left = left_max;
            if (!st.empty()) {
                st.back()->right = new_node;
            }
            st.push_back(new_node);
        }
        return st.front();
    }   
};
