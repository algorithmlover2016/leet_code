#include "../../head.h"


class SolutionWrongAns {
public:
    int combinationSum4(std::vector<int> const & nums, int target) {
        return dfs(nums, target, 0);

    }
private:
    // after traverse the idx, we will never back;
    int dfs(std::vector<int> const & nums, int target, int idx) {
        int const numsSize = nums.size();
        if (0 == target) {
            return 1;
        }
        if (idx == numsSize || target < 0) {
            return 0;
        }
        // still use the idx element
        int ans = dfs(nums, target - nums[idx], idx);

        // the last use of the idx
        ans += dfs(nums, target - nums[idx], idx + 1);
        return ans;
    }
};

class SolutionTLE {
public:
    int combinationSum4(std::vector<int> const & nums, int target) {
        return dfs(nums, target);
    }
private:
    int dfs(std::vector<int> const & nums, int target) {
        int const numsSize = nums.size();
        if (0 == target) {
            return 1;
        }
        if (target < 0) {
            return 0;
        }
        // still use the idx element

        int ans = 0;
        for (int idx = 0; idx < numsSize; idx++) {
            ans += dfs(nums, target - nums[idx]);
        }
        return ans;
    }
};

#ifdef OPTIMIZING_JUDGEMENT
class Solution {
public:
    int combinationSum4(std::vector<int> nums, int target) {
        // plagiarizing from https://leetcode.com/problems/combination-sum-iv/discuss/85079/My-3ms-Java-DP-solution
        if (0 > target) {
            return 0;
        }
        std::sort(nums.begin(), nums.end());
        std::vector<int> dpMemo(target + 1, 0);
#ifdef OPTIMIZING_JUDGEMENT
        dpMemo[0] = 1;
#endif
        for (int t = 1; t < dpMemo.size(); t++) {
            for (int const num : nums) {
#ifdef OPTIMIZING_JUDGEMENT
                if (t >= num) {
                    dpMemo[t] += dpMemo[t - num];
                } else {
                    break;
                }
#else
                if (num > t) {
                    break;
                } else if (num == t) {
                    dpMemo[t] += 1;
                } else {
                    dpMemo[t] += dpMemo[t - num];
                }
#endif
            }
            dpMemo[t] %= MOD;
        }
        return dpMemo[target];
    }
private:
    static int const MOD = INT_MAX;
};
