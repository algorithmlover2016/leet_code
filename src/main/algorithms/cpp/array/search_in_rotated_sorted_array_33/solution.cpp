#include "../../head.h"


class Solution {
public:
    int search(std::vector<int> const & nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        int const numsSize = nums.size();
        // return *std::min_element(nums.begin(), nums.end());
        int left = 0;
        int right = numsSize - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target == nums[mid]) {
                return mid;
            }
            if (target == nums[right]) {
                return right;
            }
            if (target == nums[left]) {
                return left;
            }
            if (nums[mid] > nums[right]) {
                // from left to mid is increasing
                if (target > nums[mid] || target < nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else {
                if (target > nums[mid] && target < nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};

class Solution {
public:
    int search(std::vector<int> const & nums, int target) {
        std::vector<int>::const_iterator it;
        std::vector<int>::const_iterator it2 = nums.cbegin();
        it = find(nums.cbegin(),nums.cend(),target);
        if(it!=nums.end()) {
            return it-it2;
        }
        else {
            return -1;
        }
    }
};
