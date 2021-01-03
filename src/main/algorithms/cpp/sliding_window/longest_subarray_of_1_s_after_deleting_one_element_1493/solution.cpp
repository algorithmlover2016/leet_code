#include "../../head.h"


class Solution {
public:
    int longestSubarray(std::vector<int> nums) {
        // nums.emplace_back(int(VALID_FLAG));
        // we can use stack to record all zero index,
        // and only the former and the former of the former will be used
        // so we can only use two val to record
        int prePreZeroIdx = -1;
        int preZeroIdx = -1;
        int ans = 0;
        for (int idx = 0; idx < nums.size(); idx++) {
            if (VALID_FLAG == nums[idx]) {
                ans = std::max(ans, idx - prePreZeroIdx - 1);
            } else {
                ans = std::max(ans, idx - preZeroIdx - 1);
                prePreZeroIdx = preZeroIdx;
                preZeroIdx = idx;
            }
        }
        return ans;

    }
    private:
    static int const VALID_FLAG = 1;
    static int const NOVALID_FLAG = 0;
};

class SolutionBetter {
public:
    int longestSubarray(std::vector<int> const & nums) {
        int i = 0, j = 0, K = 1, n = nums.size();
        for (j = 0; j < n; ++ j) {
            if (nums[j] == 0) {
                K--;
            }
            if (K < 0 && nums[i++] == 0) {
                ++K;
            }
        }
        return j - i - 1; // we need to remove a number
    }
};
