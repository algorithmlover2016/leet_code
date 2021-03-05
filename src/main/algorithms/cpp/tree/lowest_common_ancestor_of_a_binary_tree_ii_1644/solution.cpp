#include "../../head.h"
#include "../tree.h"

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode * ans = nullptr;
        dfs(root, p, q, ans);
        return ans;
    }
    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode * & ans) {
        if (nullptr == root) {
            return false;
        }
        if (nullptr != ans) {
            return false;
        }
        bool lFind = dfs(root->left, p, q, ans);
        bool rFind = dfs(root->right, p, q, ans);
        bool curFind = (root->val == p->val || root->val == q->val);

        if ((lFind & rFind) || ((lFind | rFind) & curFind)) {
            ans = root;
        }
        return lFind | rFind | curFind;
    }
};

class SolutionCnt {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode * ans = nullptr;
        dfs(root, p, q, ans);
        return ans;
    }
    int dfs(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode * & ans) {
        if (nullptr == root) {
            return 0;
        }
        if (nullptr != ans) {
            return 2;
        }
        int cnt = 0;
        if (root->val == p->val || root->val == q->val) {
            cnt++;
        }
        cnt += dfs(root->left, p, q, ans);
        cnt += dfs(root->right, p, q, ans);
        if (2 == cnt && nullptr == ans) {
            ans = root;
        }
        return cnt; 
    }
};

class SolutionNode {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode * ans = nullptr;
        ans = dfs(root, p, q);
        return 2 == cnt ? ans : nullptr;
    }
    TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (nullptr == root) {
            return nullptr;
        }

        TreeNode * left = dfs(root->left, p, q);
        TreeNode * right = dfs(root->right, p, q);
        if (root->val == p->val || root->val == q->val) {
            cnt++;
            return root;
        }
        if (nullptr == left) {
            return right;
        } else if (nullptr == right) {
            return left;
        } else {
            return root;
        }
    }
private:
    int cnt = 0;
};

#define TEST_MAIN
#ifdef TEST_MAIN
#define PRINT_TO_SCREEN
int main() {
    std::vector<int> nums{{3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4}};
    std::queue<TreeNode*> que;
    TreeNode* root = new TreeNode(nums[0]);
    que.emplace(root);
    int idx = 1;
    while (idx < nums.size()) {
        TreeNode* cur = que.front(); que.pop();
        cur->left = new TreeNode(nums[idx++]);
        que.emplace(cur->left);
        cur->right = new TreeNode(nums[idx++]);
        que.emplace(cur->right);
    }
    Solution obj;
    TreeNode* p = new TreeNode(5);
    TreeNode* q = new TreeNode(1);
    TreeNode* ans = obj.lowestCommonAncestor(root, p, q);
#ifdef PRINT_TO_SCREEN
    std::cout << p->val << ", " << q->val << " lca: " << (nullptr != ans ? ans->val : -1) << "\n";
#endif
    assert(ans->val == 3);

    SolutionCnt objCnt;
    delete p; p = nullptr;
    delete q; q = nullptr;
    p = new TreeNode(5);
    q = new TreeNode(4);
    ans = objCnt.lowestCommonAncestor(root, p, q);
#ifdef PRINT_TO_SCREEN
    std::cout << p->val << ", " << q->val << " lca: " << (nullptr != ans ? ans->val : -1) << "\n";
#endif
    assert(ans->val == 5);

    SolutionNode objNode;
    delete p; p = nullptr;
    delete q; q = nullptr;
    p = new TreeNode(5);
    q = new TreeNode(10);
    ans = objNode.lowestCommonAncestor(root, p, q);
#ifdef PRINT_TO_SCREEN
    std::cout << p->val << ", " << q->val << " lca: " << (nullptr != ans ? ans->val : -1) << "\n";
#endif
    assert(ans == nullptr);
    std::cout << "TEST SUCCESSFULLY" << std::endl;
}
#endif
