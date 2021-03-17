#include "../../head.h"
#include "../tree.h"

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // plagiarizing from https://blog.csdn.net/zaker123/article/details/106644443
        // and https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/solution/er-cha-shu-de-jing-xiang-dui-er-cha-shu-ti-mu-de-l/
        // and https://blog.csdn.net/qq_32252957/article/details/102863036
        if (nullptr == root) {
            return nullptr;
        }
        std::swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // plagiarizing from https://blog.csdn.net/zaker123/article/details/106644443
        // and https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/solution/er-cha-shu-de-jing-xiang-dui-er-cha-shu-ti-mu-de-l/
        // and https://blog.csdn.net/qq_32252957/article/details/102863036
        if (nullptr == root) {
            return nullptr;
        }

        std::vector<TreeNode*> layerStack;
        layerStack.emplace_back(root);
        while (!layerStack.empty()) {
            TreeNode* cur = layerStack.back();
            layerStack.pop_back();
            if (nullptr != cur->left) {
                layerStack.emplace_back(cur->left);
            }
            if (nullptr != cur->right) {
                layerStack.emplace_back(cur->right);
            }
            std::swap(cur->left, cur->right);
        }
        return root;
    }
};
