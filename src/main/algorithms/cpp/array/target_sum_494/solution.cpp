#include "../../head.h"


class SolutionTimeLimt {
public:
    int findTargetSumWays(std::vector<int> const & nums, int S) {
        int numsSize = nums.size();
        if (0 == numsSize) {
            return S == 0;
        }
        return static_cast<int>(binaryDfs(S, nums, 0));
    }
    long binaryDfs(long target,
            std::vector<int> const & nums,
            int start) {
        if (start >= nums.size()) {
            if (target == 0) {
                return 1;
            } else {
                return 0;
            }
        }
        return binaryDfs(target - nums[start], nums, start + 1) + binaryDfs(target + nums[start], nums, start + 1);
    }
};
/*
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        vector<unordered_map<int, int>> memo(nums.size());
        return helper(nums, S, 0, memo);
    }
    int helper(vector<int>& nums, long sum, int start, vector<unordered_map<int, int>>& memo) {
        if (start == nums.size()) return sum == 0;
        if (memo[start].count(sum)) return memo[start][sum];
        int cnt1 = helper(nums, sum - nums[start], start + 1, memo);
        int cnt2 = helper(nums, sum + nums[start], start + 1, memo);
        return memo[start][sum] = cnt1 + cnt2;
    }
};

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int n = nums.size();
        vector<unordered_map<int, int>> dp(n + 1);
        dp[0][0] = 1;
        for (int i = 0; i < n; ++i) {
            for (auto &a : dp[i]) {
                int sum = a.first, cnt = a.second;
                dp[i + 1][sum + nums[i]] += cnt;
                dp[i + 1][sum - nums[i]] += cnt;
            }
        }
        return dp[n][S];
    }
};
   */

class SolutionBetterRuntime {
public:
    int findTargetSumWays(std::vector<int> const & nums, int s) {
        // analysis https://blog.csdn.net/hit0803107/article/details/54894227
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        /*
           举例说明: nums = {1,2,3,4,5}, target=3, 一种可行的方案是+1-2+3-4+5 = 3
           该方案中数组元素可以分为两组，一组是数字符号为正(P={1,3,5})，另一组数字符号为负(N={2,4})
           因此: sum(1,3,5) - sum(2,4) = target
           sum(1,3,5) - sum(2,4) + sum(1,3,5) + sum(2,4) = target + sum(1,3,5) + sum(2,4)
           2sum(1,3,5) = target + sum(1,3,5) + sum(2,4)
           2sum(P) = target + sum(nums)
           sum(P) = (target + sum(nums)) / 2
           由于target和sum(nums)是固定值，因此原始问题转化为求解nums中子集的和等于sum(P)的方案个数问题
            ————————————————
            版权声明：本文为CSDN博主「TaoTao Yu」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
            原文链接：https://blog.csdn.net/hit0803107/java/article/details/54894227
           */
        return sum < s || (s + sum) & 1 ? 0 : subsetSum(nums, (s + sum) >> 1);
    }

    int subsetSum(std::vector<int> const & nums, int s) {
        std::vector<int> dp(s + 1, 0);
        dp[0] = 1;
        for (int n : nums)
            for (int i = s; i >= n; i--)
                // whether using n or not
                dp[i] += dp[i - n];
        return dp[s];
    }

};
