#include "../../head.h"

class SolutionTLE {
public:
    int lengthOfLIS(std::vector<int> const & nums, int k) {
        // Time comlexsity O(n^2), space O(n)
        if (nums.empty()) {
            return 0;
        }
        assert(k >= 0);
        std::vector<int> dp(nums.size(), 1);
        int ans = 1;
        for (int idx = 1; idx < nums.size(); idx++) {
            for (int left = 0; left < idx; left++) {
                if (nums[left] + k >= nums[idx] && nums[idx] > nums[left]) {
                    dp[idx] = std::max(dp[left] + 1, dp[idx]);
                    ans = std::max(ans, dp[idx]);
                }
            }
        }
        return ans;
        
    }
};

class SolutionTLE {
public:
    int lengthOfLIS(std::vector<int> const & nums, int k) {
        // plagiarizing from https://leetcode.com/problems/longest-increasing-subsequence-ii/solutions/2560085/python-explanation-with-pictures-segment-tree/
        // and https://leetcode.com/problems/longest-increasing-subsequence-ii/solutions/2578352/segment-tree/
    }
};