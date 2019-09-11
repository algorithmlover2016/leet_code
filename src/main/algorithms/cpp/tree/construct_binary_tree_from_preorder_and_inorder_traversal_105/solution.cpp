#include "../../head.h"
#include "../tree.h"


class Solution {
public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size()) {
            return nullptr;
        }
        int index = 0;
        return dfsHelper(preorder, inorder, index, 0, inorder.size());
    }
    TreeNode * dfsHelper(std::vector<int> & preorder, std::vector<int> & inorder, int & index, int start, int end) {
        if (index >= preorder.size() || (start >= end)) {
            return nullptr;
        }
        TreeNode * root = new TreeNode(preorder[index]);
        for (int subIndex = start; subIndex < end; subIndex++) {
            if (preorder[index] == inorder[subIndex]) {
                index++;
                root->left = dfsHelper(preorder, inorder, index, start, subIndex);
                root->right = dfsHelper(preorder, inorder, index, subIndex + 1, end);
                break;
            }
        }
        return root;
    }
};

class Solution {
public:

    TreeNode* recurs(const vector<int> & preorder, unordered_map<int, int> & indicesInOrder, int & rootIndex, int start, int end) {
        if (end < start) {
            return nullptr;
        }

        int rootVal = preorder[rootIndex];
        TreeNode* root = new TreeNode(rootVal);
        int rootInInorder = indicesInOrder[rootVal];

        ++rootIndex; // update ref
        root->left = recurs(preorder, indicesInOrder, rootIndex, start, rootInInorder - 1);
        root->right = recurs(preorder, indicesInOrder, rootIndex, rootInInorder + 1, end);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> indices;
        for (int j = 0; j < inorder.size(); ++j)
            indices[inorder[j]] = j;

        int rootIndex = 0;
        return recurs(preorder, indices, rootIndex, 0, inorder.size() - 1);
    }
};
