#include "../../head.h"


class Solution {
public:
    TreeNode* constructFromPrePost(std::vector<int> const & pre,
            std::vector<int> const & post) {
        // plagiarizing idea from https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/discuss/161268/C%2B%2BJavaPython-One-Pass-Real-O(N)
        int const preSize = pre.size();
        int const postSize = post.size();
        if (JUST_RETURN_NULL == preSize || preSize != postSize) {
            return nullptr;
        }
        int preIdx = 0;
        int postIdx = 0;
        return dfsHelper(pre, post, preIdx, postIdx);
    }
    TreeNode* dfsHelper(std::vector<int> const & pre,
            std::vector<int> const & post,
            int & preIdx, int & postIdx) {
        if (preIdx >= pre.size()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(pre[preIdx++]);
        if (root->val != post[postIdx]) {
            root->left = dfsHelper(pre, post, preIdx, postIdx);
        }
        if (root->val != post[postIdx]) {
            root->right = dfsHelper(pre, post, preIdx, postIdx);
        }
        postIdx++;
        return root;
    }

private:
    static int const JUST_RETURN_NULL = 0;

};
