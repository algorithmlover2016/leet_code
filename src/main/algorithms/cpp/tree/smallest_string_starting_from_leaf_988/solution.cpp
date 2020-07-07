#include "../../head.h"


class Solution {
public:
    std::string smallestFromLeaf(TreeNode* root) {
        std::string res;
        dfsHelper(root, "", res);
        return res;
    }
    void dfsHelper(TreeNode* root, std::string cur, std::string & res) {
        if (nullptr == root) {
            return;
        }
        // std::cout << "val: " << static_cast<char>(root->val + 'a') << "\t";
        cur += root->val + 'a';
        if (nullptr == root->left && nullptr == root->right) {
            std::reverse(cur.begin(), cur.end());
            // std::cout << "possibility: " << cur << "\n";
            if (res.empty() ||
                // cur.size() < res.size() ||
                // (cur.size() == res.size() && cur < res)) {
                (cur < res)) {
                res = cur;
                // std::cout << "res possibility: " << res << "\n";
            }
            return;
        }
        dfsHelper(root->left, cur, res);
        dfsHelper(root->right, cur, res);
    }
};
