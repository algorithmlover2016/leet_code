#include "../../head.h"
#include "../tree.h"


class Solution {
public:
    int closestValues(TreeNode* root, float target) {
        if (nullptr == root) {
            return INT_MIN;
        }
        int ans = 0;
        float diff = INT_MAX;
        dfsPreOrder(root, target, diff, ans);
        return ans;

    }
    void dfsPreOrder(TreeNode* root, float target, float & diff, int & ans) {
        if (nullptr == root) {
            return;
        }
        float curDiff = std::abs(root->val - target);
        if (curDiff < diff) {
            diff = curDiff;
            ans = root->val;
        }
        dfsPreOrder(root->left, target, diff, ans);
        dfsPreOrder(root->right, target, diff, ans);
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
    int ans = obj.closestValues(root, 3.714286);
#ifdef PRINT_TO_SCREEN
    std::cout << "ans: " << ans << "\n";
#endif
    assert(ans == 4);
    std::cout << "TEST SUCCESSFULLY" << std::endl;
    return 0;

}
