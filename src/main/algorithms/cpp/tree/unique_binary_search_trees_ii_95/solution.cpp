#include "../../head.h"


class SolutionWrongAns {
public:
    std::vector<TreeNode*> generateTrees(int n) {
        std::vector<TreeNode*> ans;
        std::vector<int> nums(n);
        std::iota(nums.begin(), nums.end(), 1);
        do {
            // [2, 1, 3] and [2, 3, 1] permutation with same Tree
            // can construct same tree
            TreeNode* root = constructBST(nums);
            if (nullptr != root) {
                ans.emplace_back(root);
            }
        } while (std::next_permutation(nums.begin(), nums.end()));
        return ans;

    }
private:
    TreeNode* constructBST(std::vector<int> const & nums) {
        if (nums.empty()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(nums[0]);
        TreeNode* cur = root;
        for (int idx = 1; idx < nums.size(); idx++) {
            while (true) {
                if (cur->val > nums[idx]) {
                    if (nullptr == cur->left) {
                        cur->left = new TreeNode(nums[idx]);
                        break;
                    } else {
                        cur = cur->left;
                    }
                } else {
                    if (nullptr == cur->right) {
                        cur->right = new TreeNode(nums[idx]);
                        break;
                    } else {
                        cur = cur->right;

                    }
                }
            }
        }
        return root;
    }
};

class Solution {
public:
    std::vector<TreeNode*> generateTrees(int n) {
        // plagiarizing from https://leetcode.com/problems/unique-binary-search-trees-ii/discuss/31494/A-simple-recursive-solution
        // plagiarizing from https://leetcode.com/problems/unique-binary-search-trees-ii/discuss/31508/Divide-and-conquer.-F(i)-G(i-1)-*-G(n-i)
        if (0 == n) {
            return {};
        }
        return generateTrees(1, n);
    }
    std::vector<TreeNode*> generateTrees(int start, int end) {
        std::vector<TreeNode*> ans;
        if (start > end) {
            ans.emplace_back(nullptr); // if we don't do this, the left and right will always empty
            return ans;
        }
        
        for (int root = start; root <= end; root++) {
            std::vector<TreeNode*> left = generateTrees(start, root - 1);
            std::vector<TreeNode*> right = generateTrees(root + 1, end);
            for (TreeNode* lNode : left) {
                for (TreeNode* rNode : right) {
                    TreeNode * rootPtr = new TreeNode(root, lNode, rNode);
                    ans.emplace_back(rootPtr);
                }
            }
        }
        return ans;
    }
};
