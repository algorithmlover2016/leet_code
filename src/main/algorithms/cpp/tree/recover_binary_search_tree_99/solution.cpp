#include "../../head.h"


class Solution {
public:
    void recoverTree(TreeNode* root) {
        // plagiarizing from https://leetcode.com/problems/recover-binary-search-tree/discuss/32535/No-Fancy-Algorithm-just-Simple-and-Powerful-In-Order-Traversal
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        TreeNode* pre = nullptr;
        dfs(root, first, second, pre);
        if (nullptr != first && nullptr != second) {
            std::swap(first->val, second->val);
        }
    }
private:
    void dfs(TreeNode* root, TreeNode* & first, TreeNode* & second, TreeNode * & pre) {
        if (nullptr == root) {
            return ;
        }
        dfs(root->left, first, second, pre);
        // if there is a mistake swapping, there will be two reverse order when visiting in order
        if (nullptr == first && (nullptr != pre && pre->val > root->val)) {
            first = pre;
        }
        if (nullptr != first && (pre->val > root->val)) {
            second = root;
        }
        pre = root;
        dfs(root->right, first, second, pre);
    }
};


class SolutionMorrisTraversal {
public:
    void recoverTree(TreeNode* root) {
        // plagiarizing from https://leetcode.com/problems/recover-binary-search-tree/discuss/32559/Detail-Explain-about-How-Morris-Traversal-Finds-two-Incorrect-Pointer
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        TreeNode* pre = nullptr;
        while (nullptr != root) {
            if (nullptr != root->left) {
                TreeNode* moveP = root->left;
                while (nullptr != moveP->right && root != moveP->right) {
                    moveP = moveP->right;
                }
                if (nullptr == moveP->right) {
                    moveP->right = root;
                    root = root->left;
                } else {
                    moveP->right = nullptr;
                    if (nullptr != pre && pre->val > root->val) {
                        if (nullptr == first) {
                            // std::cout << "swap first: " << first->val << "\t";
                            first = pre;
                            second = root;
                        } else {
                            // std::cout << "swap second: " << second->val << "\t";
                            second = root;
                        }
                    }
                    // std::cout << "pre second: " << (nullptr == pre ? 0 : pre->val) << "\t";
                    pre = root;
                    // std::cout << "root second: " << pre->val << "\t";
                    root = root->right;
                }
            } else {
                if (nullptr != pre && pre->val > root->val) {
                    if (nullptr == first) {
                        first = pre;
                        // std::cout << "left swap first: " << first->val << "\t";
                        second = root;
                    } else {
                        second = root;
                        // std::cout << "left swap second: " << second->val << "\t";
                    }
                }
                // std::cout << "pre first: " << (nullptr == pre ? 0 : pre->val) << "\t";
                pre = root;
                // std::cout << "root first: " << pre->val << "\t";
                root = root->right;
            }
        }
        if (nullptr != first && nullptr != second) {
            std::swap(first->val, second->val);
        }
    }
};
