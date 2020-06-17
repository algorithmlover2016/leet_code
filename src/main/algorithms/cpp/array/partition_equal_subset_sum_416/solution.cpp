#include "../../head.h"


class Solution {
public:
    bool canPartition(std::vector<int> const & nums) {
        int numsSize = nums.size();
        if (2 > numsSize) {
            return false;
        }
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        return sum & 0x01 ? false : dpFindSolution(nums, sum >> 1);
    }
    bool dpFindSolution(std::vector<int> const & nums, int target) {
        std::vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int ele : nums) {
            for (int index = target; index >= ele; index--) {
                // dp[index] += dp[index - ele]; std::vector<int> dp(target + 1, 0);
                dp[index] = dp[index] || dp[index - ele];
            }
        }
        return dp[target];
    }
};

class Solution {
public:
    bool canPartition(std::vector<int> & nums) {
        int s = 0;
        for (int i = 0; i < nums.size(); i ++) {
            s += nums[i];
        }
        if (s % 2 != 0) return false;
        int g = s / 2;
        std::sort(nums.rbegin(), nums.rend());

        return helper(nums, g, 0);

    }

    bool helper(std::vector<int> const & nums, int s, int i) {
        if (i == nums.size()) return false;
        // if(nums[i] == s) return true;
        if(s == nums[i]) return true;
        if(s < nums[i]) return false;
        return helper(nums, s - nums[i], i + 1) || helper(nums, s, i + 1);
    }

    bool helper2(std::vector<int>& nums, int sum, int index){
        if(index >= nums.size()) return false;
        if(sum == nums[index]) return true;
        if(sum < nums[index]) return false;
        return helper(nums,sum-nums[index],index+1) || helper(nums,sum,index+1);
    }
};
