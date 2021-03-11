#include "../../head.h"


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
            if (nums[left] == nums[right]) {
                left++;
                continue;
            }
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

class Solution {
public:
    int findMin(std::vector<int> const & nums) {
        int start = 0, end = nums.size() - 1;

        while(start < end) {
            int mid = start + (end - start) / 2;
            if(nums[mid] > nums[end]) {
                start = mid + 1;
            } else if(nums[mid] < nums[end]) {
                end = mid;
            } else {
                int idx = mid + 1;
                while (idx < end && nums[idx] == nums[idx-1]) {
                    ++idx;
                }
                if(idx == end) {
                    end = mid;
                } else {
                    return std::min(nums[idx], nums[mid]);
                }
            }
        }
        return nums[start];
    }
};
