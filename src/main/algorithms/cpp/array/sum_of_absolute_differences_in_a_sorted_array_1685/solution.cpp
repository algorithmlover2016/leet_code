#include "../../head.h"


class Solution {
public:
    std::vector<int> getSumAbsoluteDifferences(std::vector<int> const & nums) {
        // plagiarizing from https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/
        if (nums.empty()) {
            return {};
        }
        if (1 == nums.size()) {
            return nums;
        }
        int const numsSize = nums.size();
        std::vector<int> abDiff(numsSize, 0);
        std::vector<int> preSum(numsSize + 1, 0);
        for (int idx = 0; idx < numsSize; idx++) {
            preSum[idx + 1] = preSum[idx] + nums[idx];
        }
        for (int idx = 0; idx < numsSize; idx++) {
            /*
            abDiff[idx] = (idx + 1) * nums[idx] - preSum[idx + 1] + // the left abs diff
                            preSum[numsSize] - preSum[idx + 1] - (numsSize - 1 - idx) * nums[idx]; // the right abs diff
           */
            /*
            abDiff[idx] = (idx) * nums[idx] - preSum[idx] + // the left abs diff
                            preSum[numsSize] - preSum[idx] - (numsSize - idx) * nums[idx]; // the right abs diff
                            */
            abDiff[idx] = preSum[numsSize] - 2 * preSum[idx] + (idx * 2 - numsSize) * nums[idx];
        }
        return abDiff;
    }
};
