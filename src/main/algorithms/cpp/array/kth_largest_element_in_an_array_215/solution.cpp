#include "../../head.h"


class Solution {
public:
     int findKthLargest(std::vector<int> nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int p = partition(nums, left, right);
            if (p == k - 1) {
                return nums[p];
            }
            if (p > k - 1) {
                right = p - 1;
            } else {
                left = p + 1;
            }
        }
    }
private:
    int partition(std::vector<int> & nums, int left, int right) {
        int pivot = nums[left], l = left + 1, r = right;
        while (l <= r) {
            while (l <=r && nums[l] >= pivot) {
                l++;
            }
            while (l <=r && nums[r] <= pivot ) {
                r--;
            }
            if (l < r) {
                std::swap(nums[l++], nums[r--]);
            }
        }
        std::swap(nums[left], nums[r]);
        return r;
    }
};
