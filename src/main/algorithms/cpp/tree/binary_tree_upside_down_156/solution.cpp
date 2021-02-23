#include "../../head.h"
#include "../tree.h"

#define TEST_MAIN

class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        return dfs(root);
    }

    TreeNode* dfs(TreeNode * root) {
        if (nullptr == root) {
            return nullptr;
        }
        if (nullptr == root->left) {
            return root;
        }
        TreeNode* newRoot = dfs(root->left);
        root->left->left = root->right;
        root->left->right = root;
        root->left = nullptr;
        root->right = nullptr;
        return newRoot;
    }
};

#ifdef TEST_MAIN

void preOrderTraversal(TreeNode* root) {
    if (nullptr == root) {
        return;
    }
    std::cout << root->val << ",\t";
    if (nullptr != root->left) {
        preOrderTraversal(root->left);
    }
    if (nullptr != root->right) {
        preOrderTraversal(root->right);
    }
}

int main() {
    Solution obj;

    TreeNode* root = nullptr;
    assert(nullptr == obj.upsideDownBinaryTree(root));
    std::cout << "nullptr return nullptr" << "\n";

    root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    TreeNode* cur = root->left;
    cur->left = new TreeNode(4);
    cur->right = new TreeNode(5);
    cur = root->right;
    cur->left = new TreeNode(6);
    cur->right = new TreeNode(7);
    preOrderTraversal(obj.upsideDownBinaryTree(root));
    std::cout << std::endl;
    return 0;
}

#endif
