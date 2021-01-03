#include "../../head.h"


class Solution {
public:
    int constrainedSubsetSum(std::vector<int> const & nums, int k) {
        // plagaiarizing from https://leetcode.com/problems/constrained-subsequence-sum/discuss/597751/JavaC++Python-O(N)-Decreasing-Deque
        if (nums.empty()) {
            return 0;
        }

        int const numsSize = nums.size();

        int maxSum = INT_MIN;
        std::vector<int> preSum(numsSize, 0);
        std::deque<int> preMaxDec;

        for (int idx = 0; idx < numsSize; idx++) {
            preSum[idx] = (preMaxDec.empty() ? 0 : preSum[preMaxDec.front()]) + nums[idx];
            maxSum = std::max(maxSum, preSum[idx]);
            while (!preMaxDec.empty() && preSum[preMaxDec.back()] < preSum[idx]) {
                preMaxDec.pop_back();
            }
            if (preSum[idx] > 0) {
                preMaxDec.emplace_back(idx);
            }
            if (idx >= k && !preMaxDec.empty() &&
                    preSum[preMaxDec.front()] == preSum[idx - k]) {
                preMaxDec.pop_front();
            }
        }
        return maxSum;
    }
};
