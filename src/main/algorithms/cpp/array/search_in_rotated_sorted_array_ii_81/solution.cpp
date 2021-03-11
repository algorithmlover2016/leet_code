#include "../../head.h"


class Solution {
public:
    bool search(std::vector<int>& nums, int target) {
        if (nums.empty()) {
            return false;
        }
        int const numsSize = nums.size();
        // return *std::min_element(nums.begin(), nums.end());
        int left = 0;
        int right = numsSize - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target == nums[mid] || target == nums[right] || target == nums[left]) {
                return true;
            }
            if (nums[left] == nums[right]) {
                left++;
                continue;
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
        return false;
    }
};

class Solution {
public:
    bool search(std::vector<int> const & nums, int target) {
        return  searchHelper(0, nums.size()-1, nums, target);
    }
    bool searchHelper(int begin, int end, std::vector<int> const & nums, int target) {
        while (begin <= end) {
            int middle = (begin + end) / 2;
            if (nums[middle] == target) {
                return true;
            }

            if (nums[middle] == nums[begin] && nums[middle] == nums[end]) {
                bool answer1 = searchHelper(begin + 1, middle-1, nums, target);
                bool answer2 = searchHelper(middle + 1, end - 1, nums, target);
                return answer1 || answer2;
            }
            if (nums[middle] > nums[end]) {
                if (nums[middle] < target || target <= nums[end]) {
                    begin = middle+1;
                } else {
                    end = middle-1;
                }
            } else {
                if (target > nums[middle] && target <= nums[end]) {
                    begin = middle+1;
                } else {
                    end = middle-1;
                }
            }
        }
        return false;
    }
};

class Solution {
public:
    bool search(std::vector<int> const & nums, int target) {
        if (nums.empty()) return false;

        int l = 0, r = nums.size()-1;
        while (l < r) {
            int mid = l+(r-l)/2;
            if (nums[mid] == target) {
                return true;
            }
            if (nums[mid] > nums[r]) {
                if (nums[l] <= target and target < nums[mid]) {
                    r = mid;
                } else {
                    l = mid+1;
                }
            } else if (nums[mid] < nums[r]) {
                if (nums[mid] < target and target <= nums[r]) {
                    l = mid+1;
                } else {
                    r = mid;
                }
            } else {
                r--;
            }
        }
        return nums[l] == target;
    }
};

class Solution {
public:
    bool search(std::vector<int>& nums, int target) {
        if (nums.empty()) {
            return false;
        }
        int const numsSize = nums.size();
        // return *std::min_element(nums.begin(), nums.end());
        int left = 0;
        int right = numsSize - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (target == nums[mid] || target == nums[right] || target == nums[left]) {
                return true;
            }
            if (nums[left] == nums[right]) {
                left++;
                continue;
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
        // plagiarizing idea from the upper solution to make while loop condition exclude left == right
        return nums[left] == target;
    }
};
