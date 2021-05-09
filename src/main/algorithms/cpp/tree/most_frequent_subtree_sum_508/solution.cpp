#include "../../head.h"
#include "../tree.h"


class Solution {
public:
    std::vector<int> findFrequentTreeSum(TreeNode* root) {
        if (nullptr == root) {
            return {};
        }
        std::vector<int> ans;
        std::unordered_map<int, int> sumCnts;
        int maxCnt = 0;
        dfsPostOrder(root, ans, sumCnts, maxCnt);
        return ans;
    }
private:
    long dfsPostOrder(TreeNode* root, std::vector<int> & ans, std::unordered_map<int, int> & sumCnts, int & maxCnt) {
        if (nullptr == root) {
            return 0;
        }

        int leftSum = dfsPostOrder(root->left, ans, sumCnts, maxCnt);
        int rightSum = dfsPostOrder(root->right, ans, sumCnts, maxCnt);
        int curSum = leftSum + rightSum + root->val;
        int curSumCnt = ++sumCnts[curSum];
        if (curSumCnt > maxCnt) {
            std::vector<int>().swap(ans);
            ans.emplace_back(curSum);
            maxCnt = curSumCnt;
        } else if (curSumCnt == maxCnt) {
            ans.emplace_back(curSum);
        };
        return curSum;
    }
};

class Solution {
public:
    std::vector<int> findFrequentTreeSum(TreeNode* root) {

        if (nullptr == root) {
            return {};
        }
        std::vector<int> res;
        dfs(root);

        for (auto p : hash) {
            if (m == p.second) {
                res.push_back(p.first);
            }
        }
        return res;
    }

private:
    int dfs(TreeNode* root) {
        if(nullptr == root) {
            return 0;
        }

        int sum = root->val + dfs(root->right) + dfs(root->left);
        m = std::max(m, ++hash[sum]);
        return sum;
    }
private:
    std::unordered_map<int,int> hash;
    int m = INT_MIN;
};
