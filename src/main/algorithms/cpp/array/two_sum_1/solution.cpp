#include "../../head.h"


class Solution {
public:
    std::vector<int> twoSum(std::vector<int> const & nums, int target) {
        int const numsSize = nums.size();
        std::unordered_map<int, int> num2Idx;
        for (int idx = 0; idx < numsSize; idx++) {
            int diff = target - nums[idx];
            if (num2Idx.find(diff) != num2Idx.end()) {
                return {num2Idx[diff], idx};
            }
            num2Idx[nums[idx]] = idx;
        }
        return {-1, -1};
    }
};
