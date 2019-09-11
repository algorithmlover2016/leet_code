#include "../../head.h"
#include "../tree.h"

class Solution {
public:
    TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder) {
        if ((inorder.size() != postorder.size()) || inorder.empty()) {
            return nullptr;
        }
        std::unordered_map<int, int> inorderIndexMap;
        for (int index = 0; index < inorder.size(); index++) {
            inorderIndexMap[inorder[index]] = index;
        }

        int index = postorder.size() - 1;
        // return dfsHelper(inorder, postorder, index, 0, inorder.size());
        return dfsHelper(postorder, inorderIndexMap, index, 0, inorder.size());
    }

    // TreeNode * dfsHelper(std::vector<int> const & postorder, std::unordered_map<int, int> & inorderIndexMap, int & index, int start, int end) {
    //     if (index < 0 || start == end) {
    //         return nullptr;
    //     }
    //     TreeNode * root = new TreeNode(postorder[index]);
    //     index--;
    //     int partition = inorderIndexMap[root->val];
    //     root->right =  dfsHelper(postorder, inorderIndexMap, index, partition + 1, end);
    //     root->left =  dfsHelper(postorder, inorderIndexMap, index, start, partition);
    //     return root;
    //
    // }

    TreeNode * dfsHelper(std::vector<int> const & postorder, std::unordered_map<int, int> const & inorderIndexMap, int & index, int start, int end) {
        if (index < 0 || start == end) {
            return nullptr;
        }
        TreeNode * root = new TreeNode(postorder[index]);
        index--;
        //if you must use const  unordered_map, you must use at function (the upper function) not [] operator
        int partition = inorderIndexMap.at(root->val);
        root->right =  dfsHelper(postorder, inorderIndexMap, index, partition + 1, end);
        root->left =  dfsHelper(postorder, inorderIndexMap, index, start, partition);
        return root;

    }


    TreeNode * dfsHelper(std::vector<int> const & inorder,
            std::vector<int> const & postorder, int & index, int start, int end) {
        if (index < 0 || start == end) {
            return nullptr;
        }
        TreeNode * root = new TreeNode(postorder[index]);
        for (int subIndex = end - 1; subIndex >= start; subIndex--) {
            if (postorder[index] == inorder[subIndex]) {
                index--;
                root->right = dfsHelper(inorder, postorder, index, subIndex + 1, end);
                root->left = dfsHelper(inorder, postorder, index, start, subIndex);
                break;
            }
        }
        return root;
    }
};
