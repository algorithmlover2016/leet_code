#include "../../head.h"


class Solution {
public:
    int findMin(std::vector<int>& nums) {
        return *std::min_element(nums.begin(), nums.end());
    }
};

class Solution {
public:
    int findMin(std::vector<int> const & nums) {
        if (nums.empty()) {
            return -1;
        }
        int const numsSize = nums.size();
        // return *std::min_element(nums.begin(), nums.end());
        int left = 0;
        int right = numsSize - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= nums[left]) {
                // from left to mid is increasing
                if (nums[mid] > nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else if (nums[mid] < nums[left]) {
                right = mid;
                left++;
            }
        }
        return nums[left];
    }
};
