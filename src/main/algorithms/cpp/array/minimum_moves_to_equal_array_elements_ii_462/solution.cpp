#include "../../head.h"


class Solution {
public:
    int minMoves2(std::vector<int> nums) {
        // sum + p  - m = x * n;
        // min + a = x = max - b
        //     a + b = max - min
        // after a + b operation, we can get any number from min to max
        int const numsSize = nums.size();
        if (JUST_ONE >= numsSize) {
            return 0;
        }
        std::sort(nums.begin(), nums.end());
        int ans = 0;
        for (int left = 0, right = numsSize - 1; left < right; left++, right--) {
            ans += nums[right] - nums[left];
        }
        return ans;
    }
private:
    static int const JUST_ONE = 1;
};
