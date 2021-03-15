#include "../../head.h"


class Solution {
public:
    int maximumScore(std::vector<int> const & nums, int k) {
        // plagiarizing from https://youtu.be/ONuuGA8U_iM
        int const numsSize = nums.size();
        if (k >= numsSize || k < 0) {
            return 0;
        }

        int left = k, right = k;
        int minNum = nums[k];
        int ans = nums[k];
        while (left > 0 || right < numsSize - 1) {
            if (left > 0 && right < numsSize - 1) {
                // we can choose num for either side, so we choose the bigger one
                if (nums[left - 1] > nums[right + 1]) {
                    minNum = std::min(minNum, nums[--left]);
                } else {
                    minNum = std::min(minNum, nums[++right]);
                }
            } else if (left > 0) {
                // the right is to border, we can only move to left
                minNum = std::min(minNum, nums[--left]);
            } else {
                // the left is to border, we can only move to right
                minNum = std::min(minNum, nums[++right]);
            }
            ans = std::max(ans, minNum * (right - left + 1));
        }
        return ans;

    }
};
