#include "../../head.h"


class Solution {
public:
    std::vector<TreeNode*> allPossibleFBT(int N) {
        // plagiarizing idea from https://youtu.be/F0dUVxzzg_M
        std::vector<TreeNode*> ans;
        if (EMPTY_FLAG == N) {
            ;
        } else if (JUST_ROOT_FLAG == N) {
            ans.emplace_back(new TreeNode(0));
        } else {
            for (int split = 1; split < N; split += 2) {
                std::vector<TreeNode*> leftTrees = allPossibleFBT(split);
                std::vector<TreeNode*> rightTrees = allPossibleFBT(N - 1 - split);
                for (auto const & left : leftTrees) {
                    for (auto const & right : rightTrees) {
                        TreeNode* root = new TreeNode(0);
                        root->left = left;
                        root->right = right;
                        ans.emplace_back(root);
                    }
                }

            }
        }
        return ans;
    }
private:
    static int const EMPTY_FLAG = 0;
    static int const JUST_ROOT_FLAG = 1;
};

class Solution {
private:
    std::unordered_map<int, std::vector<TreeNode*>> dpMemo;
    int const EMPTY_FLAG = 0;
    int const JUST_ROOT_FLAG = 1;
public:
    Solution() {
        dpMemo[EMPTY_FLAG] = {};
        dpMemo[JUST_ROOT_FLAG] = {new TreeNode(0)};
    }
    std::vector<TreeNode*> allPossibleFBT(int N) {
        // plagiarizing idea from https://youtu.be/F0dUVxzzg_M
        if (dpMemo.find(N) != dpMemo.end()) {
            return dpMemo[N];
        } else {
            std::vector<TreeNode*> ans;
            for (int split = 1; split < N; split += 2) {
                std::vector<TreeNode*> leftTrees = allPossibleFBT(split);
                std::vector<TreeNode*> rightTrees = allPossibleFBT(N - 1 - split);
                for (auto const & left : leftTrees) {
                    for (auto const & right : rightTrees) {
                        TreeNode* root = new TreeNode(0);
                        root->left = left;
                        root->right = right;
                        ans.emplace_back(root);
                    }
                }

            }
            return dpMemo[N] = ans;
        }
    }
};
