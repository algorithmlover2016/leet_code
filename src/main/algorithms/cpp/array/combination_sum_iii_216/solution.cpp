#include "../../head.h"


class Solution {
public:
    std::vector<std::vector<int>> combinationSum3(int k, int target) {
        static bool initNumFlag = (initNums(), true);
        std::vector<std::vector<int>> ans;
        std::vector<int> curAns;
        dfs(nums, target, 0, k, curAns, ans);
        return ans;
    }
private:
    void dfs(std::vector<int> const & nums,
             int target, int idx, int leftNums,
             std::vector<int> & curAns, std::vector<std::vector<int>> & ans) {
        if (0 == target && 0 == leftNums) {
            ans.emplace_back(curAns);
            return;
        }
        if (0 == leftNums || NUMBER_SIZE < idx + leftNums  || nums[idx] > target) {
            return;
        }
        // skip the cur element
        dfs(nums, target, idx + 1, leftNums, curAns, ans);
        // still use the idx element
        curAns.emplace_back(nums[idx]);
        dfs(nums, target - nums[idx], idx + 1, leftNums - 1, curAns, ans);
        curAns.pop_back();
    }

    void initNums() {
        std::iota(nums.begin(), nums.end(), 1);
    }

    private:
    static int const NUMBER_SIZE = 9;
    static std::vector<int> nums;
};
std::vector<int> Solution::nums = std::vector<int>(Solution::NUMBER_SIZE, 0);

class Solution {
private:
    std::vector<std:::vector<int>> ret;
public:
    std::vector<std:::vector<int>> combinationSum3(int k, int n) {
        std::vector<int> v;
        work(k, n, v);
        return ret;
    }
    void work(int k, int n, std::vector<int> & v) {
        if (!k) {
            return;
        }
        if (k == 1) {
            if ((v.empty() || v.back() < n) && n < 10) {
                v.emplace_back(n);
                ret.emplace_back(v);
                v.pop_back();
            }
            return;
        }
        for (unsigned x = (v.empty() ? 0 : v.back()) + 1; x < 10 && x < n; ++x) {
            v.emplace_back(x);
            work(k - 1, n - x, v);
            v.pop_back();
        }
    }
};
