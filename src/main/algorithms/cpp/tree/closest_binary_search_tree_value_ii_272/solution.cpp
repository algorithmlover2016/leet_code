#include "../../head.h"
#include "../tree.h"


class Solution {
public:
    std::vector<int> closestValues(TreeNode* root, float target, int k) {
        if (nullptr == root) {
            return {};
        }
        std::vector<int> ans;
        dfsInOrder(root, ans);
        int mid = 0;
        float diff = std::abs(ans[0] - target);
        for (int idx = 1; idx < ans.size(); idx++) {
            float curDiff = std::abs(ans[idx] - target);
            if (diff > curDiff) {
                diff = curDiff;
                mid = idx;
            }
        }
        std::vector<int> res;
        int left = mid, right = mid + 1;
        while (k-- > 0) {
            float leftDiff = left > -1 ? std::abs(ans[left] - target) : INT_MAX;
            float rightDiff = right < ans.size() ? std::abs(ans[right] - target) : INT_MAX;
            if (leftDiff < rightDiff) {
                res.emplace_back(ans[left]);
                left--;
            } else {
                res.emplace_back(ans[right]);
                right++;
            }
        }

        return res;

    }
    void dfsInOrder(TreeNode* root, std::vector<int> & ans) {
        if (nullptr == root) {
            return;
        }
        dfsInOrder(root->left, ans);
        ans.emplace_back(root->val);
        dfsInOrder(root->right, ans);
    }
};
#define TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    std::vector<int> nums{{4,2,5,1,3}};
    TreeNode * root = new TreeNode(nums[0]);
    std::queue<TreeNode*> que;
    que.emplace(root);

    for (int idx = 1; idx < nums.size();) {
        TreeNode * cur = que.front();
        cur->left = new TreeNode(nums[idx++]);
        que.emplace(cur->left);
        cur->right = new TreeNode(nums[idx++]);
        que.emplace(cur->right);
    }

    Solution obj;
    std::vector<int> ans = obj.closestValues(root, 3.714286, 2);
#ifdef PRINT_TO_SCREEN
    for (int const num : ans) {
        std::cout << num << "\t";
    }
    std::cout << "\n";
#endif
    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;

}
