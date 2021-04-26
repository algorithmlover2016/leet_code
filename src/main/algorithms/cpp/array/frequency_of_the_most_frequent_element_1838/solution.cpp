#include "../../head.h"


#define DEBUG
class Solution {
public:
    int maxFrequency(std::vector<int> nums, int k) {
        int const numsSize = nums.size();
        if (0 == numsSize) {
            return 0;
        }
        std::sort(std::begin(nums), std::end(nums));

        // plagiarizing from https://youtu.be/e_oUSOkDahk
        // sliding window
        int left = 0;
        long slidingWindowSum = 0;
        int ans = 1;
        for (int right = 0; right < numsSize; right++) {
            // compute the times of add operation for the cur sliding window, if include the nums[right]
            while (nums[right] * (long)(right - left) - slidingWindowSum > k) {
                slidingWindowSum -= nums[left++];
            }
            ans = std::max(ans, right - left + 1);
            slidingWindowSum += nums[right];
        }
        return ans;
    }
};

class Solution {
public:
    int maxFrequency(std::vector<int> nums, int k) {
        std::sort(nums.begin(), nums.end());
        int res = 1;
        int left = 0;
        long slidingWindowSum = 0;
        for (int right = 1; right < (int) nums.size(); ++right) {
            slidingWindowSum += (long)(right - left) * (nums[right] - nums[right - 1]);
            // we only compute the delta
            while (slidingWindowSum > k) {
                slidingWindowSum -= nums[right] - nums[left];
                ++left;
            }
            res = std::max(res, right - left + 1);
        }
        return res;
    }
};
