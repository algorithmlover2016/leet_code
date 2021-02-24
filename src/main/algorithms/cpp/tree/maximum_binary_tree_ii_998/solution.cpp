#include "../../head.h"
#include "../tree.h"


class Solution {
public:
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        // plagiarizing from https://leetcode.com/problems/maximum-binary-tree-ii/discuss/242936/JavaC%2B%2BPython-Recursion-and-Iteration
        if (root && root->val > val) {
            root->right = insertIntoMaxTree(root->right, val);
            return root;
        }
        TreeNode * newNode = new TreeNode(val);
        newNode->left = root;
        return newNode;
    }
};

class Solution {
public:
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        // plagiarizing from https://leetcode.com/problems/maximum-binary-tree-ii/discuss/242936/JavaC%2B%2BPython-Recursion-and-Iteration
        TreeNode * newNode = new TreeNode(val);

        // nullptr == root || root->val < val
        if (nullptr == root || root->val < val) {
            newNode->left = root;
            return newNode;
        }
        TreeNode *cur = root;
        while (cur->right && cur->right->val > val) {
            cur = cur->right;
        }

        newNode->left = cur->right;
        cur->right = newNode;

        return root;
    }
};
